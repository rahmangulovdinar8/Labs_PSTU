#ifndef CHAINFINDER_H
#define CHAINFINDER_H

#include <QVector>
#include <QMap>
#include <QString>
#include "item.h"

// Один шаг в цепочке обмена
struct ChainStep {
    int     giverId;    // кто отдаёт
    int     takerId;    // кто получает
    int     itemId;     // какой предмет переходит
    QString giverName;
    QString takerName;
    QString itemName;
};

// Полная цепочка обмена
struct BarterChain {
    QVector<ChainStep> steps;

    QString description() const {
        if (steps.isEmpty()) return "";
        QString s;
        for (int i = 0; i < steps.size(); ++i) {
            s += QString("%1 отдаёт «%2» → %3")
                 .arg(steps[i].giverName)
                 .arg(steps[i].itemName)
                 .arg(steps[i].takerName);
            if (i < steps.size() - 1) s += "\n";
        }
        return s;
    }

    int length() const { return steps.size(); }
};

// ─────────────────────────────────────────────
//  Алгоритм поиска бартерных цепочек
//  Строим ориентированный граф:
//    узел  = предмет (доступный)
//    ребро = "владелец предмета A хочет предмет B"
//  Ищем все циклы длиной 2..maxLen через DFS
// ─────────────────────────────────────────────
class ChainFinder
{
public:
    explicit ChainFinder(const QVector<Item> &items);

    // Найти все цепочки длиной от 2 до maxLen
    QVector<BarterChain> findChains(int maxLen = 5);

private:
    // Построить граф смежности:
    // edge[itemA] = список itemB, которые нужны владельцу itemA
    void buildGraph();

    // DFS поиск циклов начиная с startId
    void dfs(int startItemId,
             int currentItemId,
             QVector<int> &path,
             QVector<bool> &visited,
             int maxLen,
             QVector<BarterChain> &result);

    // Проверяет совместимость: хочет ли владелец item1 то, что предлагает item2?
    // Простая эвристика — сравниваем ключевые слова из wantInReturn
    bool wantsItem(const Item &wanter, const Item &offered) const;

    // Конвертация пути узлов в BarterChain
    BarterChain pathToChain(const QVector<int> &itemIdPath) const;

    QVector<Item>               m_items;
    QMap<int, Item>             m_itemById;
    QMap<int, QVector<int>>     m_graph;
};

#endif // CHAINFINDER_H
