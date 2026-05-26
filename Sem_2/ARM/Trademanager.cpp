#include "Trademanager.h"

TradeManager::TradeManager(BarterModel *model, QObject *parent)
    : QObject(parent), m_model(model), m_nextTradeId(1)
{}

bool TradeManager::makeTrade(int itemAId, int itemBId) {
    // Найдём оба предмета
    Item *a = nullptr, *b = nullptr;
    for (int i = 0; i < m_model->items().size(); ++i) {
        if (m_model->items()[i].id == itemAId) a = m_model->getItem(i);
        if (m_model->items()[i].id == itemBId) b = m_model->getItem(i);
    }

    if (!a || !b) return false;
    if (a->status != ItemStatus::Available || b->status != ItemStatus::Available)
        return false;

    // Обновляем статусы
    m_model->updateItemStatus(itemAId, ItemStatus::Traded);
    m_model->updateItemStatus(itemBId, ItemStatus::Traded);

    // Записываем сделку
    TradeRecord rec;
    rec.id      = m_nextTradeId++;
    rec.itemAId = itemAId;
    rec.itemBId = itemBId;
    rec.personA = a->ownerName;
    rec.personB = b->ownerName;
    rec.tradedAt = QDateTime::currentDateTime();
    m_history.append(rec);

    emit tradeCompleted(rec);
    return true;
}
