#include "storage.h"
#include <QFile>
#include <QCoreApplication>

QString Storage::defaultPath() {
    return QCoreApplication::applicationDirPath() + "/barterdata.json";
}

// ── Item → JSON ──────────────────────────────────────────────
QJsonObject Storage::itemToJson(const Item &item) {
    QJsonObject obj;
    obj["id"]           = item.id;
    obj["name"]         = item.name;
    obj["description"]  = item.description;
    obj["ownerName"]    = item.ownerName;
    obj["ownerRoom"]    = item.ownerRoom;
    obj["wantInReturn"] = item.wantInReturn;
    obj["category"]     = static_cast<int>(item.category);
    obj["status"]       = static_cast<int>(item.status);
    obj["addedAt"]      = item.addedAt.toString(Qt::ISODate);
    return obj;
}

Item Storage::itemFromJson(const QJsonObject &obj) {
    Item item;
    item.id           = obj["id"].toInt();
    item.name         = obj["name"].toString();
    item.description  = obj["description"].toString();
    item.ownerName    = obj["ownerName"].toString();
    item.ownerRoom    = obj["ownerRoom"].toString();
    item.wantInReturn = obj["wantInReturn"].toString();
    item.category     = static_cast<ItemCategory>(obj["category"].toInt());
    item.status       = static_cast<ItemStatus>(obj["status"].toInt());
    item.addedAt      = QDateTime::fromString(obj["addedAt"].toString(),
                                              Qt::ISODate);
    return item;
}

// ── TradeRecord → JSON ───────────────────────────────────────
QJsonObject Storage::tradeToJson(const TradeRecord &rec) {
    QJsonObject obj;
    obj["id"]       = rec.id;
    obj["itemAId"]  = rec.itemAId;
    obj["itemBId"]  = rec.itemBId;
    obj["personA"]  = rec.personA;
    obj["personB"]  = rec.personB;
    obj["tradedAt"] = rec.tradedAt.toString(Qt::ISODate);
    return obj;
}

TradeRecord Storage::tradeFromJson(const QJsonObject &obj) {
    TradeRecord rec;
    rec.id       = obj["id"].toInt();
    rec.itemAId  = obj["itemAId"].toInt();
    rec.itemBId  = obj["itemBId"].toInt();
    rec.personA  = obj["personA"].toString();
    rec.personB  = obj["personB"].toString();
    rec.tradedAt = QDateTime::fromString(obj["tradedAt"].toString(),
                                         Qt::ISODate);
    return rec;
}

// ── Сохранение ───────────────────────────────────────────────
bool Storage::save(const QVector<Item> &items,
                   const QVector<TradeRecord> &history,
                   const QString &filePath)
{
    QJsonArray itemsArr;
    for (const Item &it : items)
        itemsArr.append(itemToJson(it));

    QJsonArray histArr;
    for (const TradeRecord &rec : history)
        histArr.append(tradeToJson(rec));

    QJsonObject root;
    root["version"] = 1;
    root["items"]   = itemsArr;
    root["history"] = histArr;

    QJsonDocument doc(root);

    QFile file(filePath);
    if (!file.open(QIODevice::WriteOnly)) return false;
    file.write(doc.toJson(QJsonDocument::Indented));
    file.close();
    return true;
}

// ── Загрузка ─────────────────────────────────────────────────
bool Storage::load(QVector<Item> &items,
                   QVector<TradeRecord> &history,
                   const QString &filePath)
{
    QFile file(filePath);
    if (!file.exists() || !file.open(QIODevice::ReadOnly))
        return false;   // файла нет — первый запуск, это нормально

    QJsonParseError err;
    QJsonDocument doc = QJsonDocument::fromJson(file.readAll(), &err);
    file.close();

    if (err.error != QJsonParseError::NoError || !doc.isObject())
        return false;

    QJsonObject root = doc.object();

    items.clear();
    for (const QJsonValue &v : root["items"].toArray())
        items.append(itemFromJson(v.toObject()));

    history.clear();
    for (const QJsonValue &v : root["history"].toArray())
        history.append(tradeFromJson(v.toObject()));

    return true;
}
