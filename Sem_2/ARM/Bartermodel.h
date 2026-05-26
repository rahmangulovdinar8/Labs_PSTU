#ifndef BARTERMODEL_H
#define BARTERMODEL_H

#include <QAbstractTableModel>
#include <QVector>
#include "item.h"

class BarterModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    explicit BarterModel(QObject *parent = nullptr);

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void addItem(const Item &item);
    void removeItem(int row);
    bool updateItemStatus(int id, ItemStatus status);
    Item* getItem(int row);
    const QVector<Item>& items() const { return m_items; }

    QMap<ItemCategory, int> categoryCounts() const;

    int nextId() const { return m_nextId; }

    // Загрузить данные напрямую (используется при старте из файла)
    void loadItems(const QVector<Item> &items);

signals:
    void dataChanged2();

private:
    QVector<Item> m_items;
    int           m_nextId;
};

#endif // BARTERMODEL_H
