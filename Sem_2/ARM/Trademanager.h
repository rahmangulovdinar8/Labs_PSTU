#ifndef TRADEMANAGER_H
#define TRADEMANAGER_H

#include <QObject>
#include <QVector>
#include "item.h"
#include "Bartermodel.h"

// Управляет историей обменов
class TradeManager : public QObject
{
    Q_OBJECT

public:
    explicit TradeManager(BarterModel *model, QObject *parent = nullptr);

    // Зарегистрировать сделку обмена между двумя предметами
    bool makeTrade(int itemAId, int itemBId);

    // Загрузить историю из файла при старте
    void loadHistory(const QVector<TradeRecord> &history) {
        m_history = history;
        // Вычисляем следующий id
        m_nextTradeId = 1;
        for (const TradeRecord &r : m_history)
            if (r.id >= m_nextTradeId) m_nextTradeId = r.id + 1;
    }

    const QVector<TradeRecord>& history() const { return m_history; }

signals:
    void tradeCompleted(TradeRecord record);

private:
    BarterModel          *m_model;
    QVector<TradeRecord>  m_history;
    int                   m_nextTradeId;
};

#endif // TRADEMANAGER_H
