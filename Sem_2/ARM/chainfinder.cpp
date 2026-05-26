#include "chainfinder.h"
#include <QStringList>

ChainFinder::ChainFinder(const QVector<Item> &items)
{
    // Берём только доступные предметы
    for (const Item &it : items) {
        if (it.status == ItemStatus::Available) {
            m_items.append(it);
            m_itemById[it.id] = it;
        }
    }
}


//  Проверяем, хочет ли владелец wanter то что предлагает offered
//  Три уровня совпадения:
//  1. Точное совпадение категории (если wantInReturn пустой)
//  2. Ключевые слова из wantInReturn встречаются в названии offered
//  3. Категории совпадают И wantInReturn не пустой

bool ChainFinder::wantsItem(const Item &wanter, const Item &offered) const
{
    // Нельзя обменять сам с собой
    if (wanter.ownerName == offered.ownerName) return false;

    QString want = wanter.wantInReturn.toLower().trimmed();

    // Если поле "хочу взамен" пустое — принимаем любую ту же категорию
    if (want.isEmpty()) {
        return wanter.category == offered.category;
    }

    // Ищем ключевые слова из wantInReturn в названии/описании offered
    QString offeredText = (offered.name + " " + offered.description +
                           " " + Item::categoryName(offered.category)).toLower();

    // Разбиваем want на слова и проверяем каждое
    QStringList keywords = want.split(QRegExp("\\s+|,|;"), QString::SkipEmptyParts);
    int matches = 0;
    for (const QString &kw : keywords) {
        if (kw.length() < 3) continue; // пропускаем короткие слова
        if (offeredText.contains(kw)) {
            matches++;
        }
    }

    // Достаточно одного совпадения ключевого слова
    if (matches > 0) return true;

    // Запасной вариант — совпадение категории
    QString catName = Item::categoryName(offered.category).toLower();
    if (want.contains(catName) || catName.contains(want.left(4)))
        return true;

    return false;
}


//  Строим граф: itemA → itemB если владелец A хочет B

void ChainFinder::buildGraph()
{
    m_graph.clear();
    for (const Item &a : m_items) {
        m_graph[a.id] = QVector<int>();
        for (const Item &b : m_items) {
            if (a.id == b.id) continue;
            if (wantsItem(a, b)) {
                m_graph[a.id].append(b.id);
            }
        }
    }
}


//  DFS: ищем путь от startItemId обратно к startItemId
//  path — текущий путь (список id предметов)

void ChainFinder::dfs(int startItemId,
                      int currentItemId,
                      QVector<int> &path,
                      QVector<bool> &visited,
                      int maxLen,
                      QVector<BarterChain> &result)
{
    // Смотрим соседей текущего узла
    for (int nextId : m_graph[currentItemId]) {

        // Нашли цикл! Вернулись к стартовому узлу
        if (nextId == startItemId && path.size() >= 2) {
            QVector<int> cyclePath = path;
            cyclePath.append(startItemId); // замыкаем цикл
            BarterChain chain = pathToChain(cyclePath);
            if (chain.length() > 0) {
                // Проверяем на дубли (одна и та же цепочка в другом порядке)
                bool duplicate = false;
                for (const BarterChain &existing : result) {
                    if (existing.length() == chain.length()) {
                        // Сравниваем наборы предметов
                        bool same = true;
                        for (int i = 0; i < chain.steps.size(); ++i) {
                            bool found = false;
                            for (const ChainStep &es : existing.steps) {
                                if (es.itemId == chain.steps[i].itemId) {
                                    found = true; break;
                                }
                            }
                            if (!found) { same = false; break; }
                        }
                        if (same) { duplicate = true; break; }
                    }
                }
                if (!duplicate) result.append(chain);
            }
            continue;
        }

        // Ограничение длины пути
        if ((int)path.size() >= maxLen) continue;

        // Не посещали этот узел в текущем пути?
        // Используем индекс в m_items для visited
        int idx = -1;
        for (int i = 0; i < m_items.size(); ++i) {
            if (m_items[i].id == nextId) { idx = i; break; }
        }
        if (idx == -1 || visited[idx]) continue;

        visited[idx] = true;
        path.append(nextId);

        dfs(startItemId, nextId, path, visited, maxLen, result);

        path.removeLast();
        visited[idx] = false;
    }
}


//  Конвертируем путь [id0, id1, id2, id0] в BarterChain
//  Каждый шаг: владелец items[i] отдаёт items[i], получает items[i+1]

BarterChain ChainFinder::pathToChain(const QVector<int> &itemIdPath) const
{
    BarterChain chain;
    for (int i = 0; i + 1 < itemIdPath.size(); ++i) {
        int givItemId = itemIdPath[i];
        int recItemId = itemIdPath[i + 1];

        if (!m_itemById.contains(givItemId) || !m_itemById.contains(recItemId))
            continue;

        const Item &givenItem    = m_itemById[givItemId];
        const Item &receivedItem = m_itemById[recItemId];

        ChainStep step;
        step.giverId   = givenItem.id;
        step.takerId   = receivedItem.id;
        step.itemId    = givenItem.id;
        step.giverName = givenItem.ownerName;
        step.takerName = receivedItem.ownerName;
        step.itemName  = givenItem.name;
        chain.steps.append(step);
    }
    return chain;
}


//  Главная функция: строим граф и запускаем DFS от каждого узла

QVector<BarterChain> ChainFinder::findChains(int maxLen)
{
    buildGraph();

    QVector<BarterChain> result;
    int n = m_items.size();

    for (int i = 0; i < n; ++i) {
        int startId = m_items[i].id;

        QVector<int>  path;
        QVector<bool> visited(n, false);

        path.append(startId);
        visited[i] = true;

        dfs(startId, startId, path, visited, maxLen, result);
    }

    // Сортируем: сначала короткие цепочки
    std::sort(result.begin(), result.end(),
              [](const BarterChain &a, const BarterChain &b){
                  return a.length() < b.length();
              });

    return result;
}
