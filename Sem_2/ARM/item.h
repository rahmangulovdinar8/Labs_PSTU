#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QDateTime>

enum class ItemCategory {
    Electronics,  // Электроника
    Books,        // Книги
    Clothing,     // Одежда
    Food,         // Еда
    Hygiene,      // Гигиена и уход
    SportGame,    // Спорт и игры
    Stationery,   // Канцелярия
    Furniture,    // Мебель / быт
    Other         // Прочее
};

enum class ItemStatus {
    Available,  // Доступен
    InTrade,    // В процессе обмена
    Traded      // Обменян
};

struct Item {
    int          id;
    QString      name;
    QString      description;
    QString      ownerName;
    QString      ownerRoom;
    ItemCategory category;
    ItemStatus   status;
    QString      wantInReturn;
    QDateTime    addedAt;

    static void categoryColor(ItemCategory cat, float &r, float &g, float &b) {
        switch (cat) {
        case ItemCategory::Electronics: r=0.2f; g=0.6f; b=1.0f; break;
        case ItemCategory::Books:       r=0.4f; g=0.8f; b=0.3f; break;
        case ItemCategory::Clothing:    r=1.0f; g=0.5f; b=0.2f; break;
        case ItemCategory::Food:        r=1.0f; g=0.8f; b=0.1f; break;
        case ItemCategory::Hygiene:     r=0.2f; g=0.9f; b=0.8f; break;
        case ItemCategory::SportGame:   r=0.9f; g=0.3f; b=0.5f; break;
        case ItemCategory::Stationery:  r=0.8f; g=0.7f; b=0.1f; break;
        case ItemCategory::Furniture:   r=0.6f; g=0.4f; b=0.2f; break;
        default:                        r=0.7f; g=0.7f; b=0.7f; break;
        }
    }

    static QString categoryName(ItemCategory cat) {
        switch (cat) {
        case ItemCategory::Electronics: return "Электроника";
        case ItemCategory::Books:       return "Книги";
        case ItemCategory::Clothing:    return "Одежда";
        case ItemCategory::Food:        return "Еда";
        case ItemCategory::Hygiene:     return "Гигиена";
        case ItemCategory::SportGame:   return "Спорт/Игры";
        case ItemCategory::Stationery:  return "Канцелярия";
        case ItemCategory::Furniture:   return "Быт/Мебель";
        default:                        return "Прочее";
        }
    }

    static QString statusName(ItemStatus s) {
        switch (s) {
        case ItemStatus::Available: return "Доступен";
        case ItemStatus::InTrade:   return "В обмене";
        case ItemStatus::Traded:    return "Обменян";
        }
        return "";
    }
};

struct TradeRecord {
    int       id;
    int       itemAId;
    int       itemBId;
    QString   personA;
    QString   personB;
    QDateTime tradedAt;
};

#endif // ITEM_H
