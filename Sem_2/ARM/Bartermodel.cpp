#include "Bartermodel.h"
#include <QMap>
#include <QColor>
#include <QBrush>

BarterModel::BarterModel(QObject *parent)
    : QAbstractTableModel(parent), m_nextId(1)
{

}

void BarterModel::loadItems(const QVector<Item> &items) {
    beginResetModel();
    m_items = items;
    m_nextId = 1;
    for (const Item &it : m_items)
        if (it.id >= m_nextId) m_nextId = it.id + 1;
    endResetModel();
    emit dataChanged2();
}

int BarterModel::rowCount(const QModelIndex &) const {
    return m_items.size();
}

int BarterModel::columnCount(const QModelIndex &) const {
    return 7; // id, название, владелец, комната, категория, статус, хочет взамен
}

QVariant BarterModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid() || index.row() >= m_items.size())
        return QVariant();

    const Item &item = m_items[index.row()];

    if (role == Qt::DisplayRole) {
        switch (index.column()) {
        case 0: return item.id;
        case 1: return item.name;
        case 2: return item.ownerName;
        case 3: return item.ownerRoom;
        case 4: return Item::categoryName(item.category);
        case 5: return Item::statusName(item.status);
        case 6: return item.wantInReturn;
        }
    }

    // Цветовая подсветка по статусу
    if (role == Qt::BackgroundRole) {
        switch (item.status) {
        case ItemStatus::Available: return QColor(220, 255, 220);
        case ItemStatus::InTrade:   return QColor(255, 255, 200);
        case ItemStatus::Traded:    return QColor(220, 220, 220);
        }
    }

    return QVariant();
}

QVariant BarterModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return QVariant();

    switch (section) {
    case 0: return "ID";
    case 1: return "Название";
    case 2: return "Владелец";
    case 3: return "Комната";
    case 4: return "Категория";
    case 5: return "Статус";
    case 6: return "Хочет взамен";
    }
    return QVariant();
}

void BarterModel::addItem(const Item &item) {
    beginInsertRows(QModelIndex(), m_items.size(), m_items.size());
    Item newItem = item;
    newItem.id = m_nextId++;
    m_items.append(newItem);
    endInsertRows();
    emit dataChanged2();
}

void BarterModel::removeItem(int row) {
    if (row < 0 || row >= m_items.size()) return;
    beginRemoveRows(QModelIndex(), row, row);
    m_items.removeAt(row);
    endRemoveRows();
    emit dataChanged2();
}

bool BarterModel::updateItemStatus(int id, ItemStatus status) {
    for (int i = 0; i < m_items.size(); ++i) {
        if (m_items[i].id == id) {
            m_items[i].status = status;
            emit dataChanged(index(i,0), index(i, columnCount()-1));
            emit dataChanged2();
            return true;
        }
    }
    return false;
}

Item* BarterModel::getItem(int row) {
    if (row < 0 || row >= m_items.size()) return nullptr;
    return &m_items[row];
}

QMap<ItemCategory, int> BarterModel::categoryCounts() const {
    QMap<ItemCategory, int> counts;
    for (const Item &it : m_items) {
        counts[it.category]++;
    }
    return counts;
}
