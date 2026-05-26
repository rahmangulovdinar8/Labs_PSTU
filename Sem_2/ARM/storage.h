#ifndef STORAGE_H
#define STORAGE_H

#include <QString>
#include <QVector>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include "item.h"

class Storage
{
public:
    static bool save(const QVector<Item> &items,
                     const QVector<TradeRecord> &history,
                     const QString &filePath = defaultPath());

    static bool load(QVector<Item> &items,
                     QVector<TradeRecord> &history,
                     const QString &filePath = defaultPath());

    static QString defaultPath();

private:
    static QJsonObject itemToJson(const Item &item);
    static Item        itemFromJson(const QJsonObject &obj);
    static QJsonObject tradeToJson(const TradeRecord &rec);
    static TradeRecord tradeFromJson(const QJsonObject &obj);
};

#endif // STORAGE_H
