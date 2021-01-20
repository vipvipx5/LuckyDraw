#ifndef LASTPRIZEITEMMODEL_H
#define LASTPRIZEITEMMODEL_H

#include <QAbstractListModel>
#include "PlayerManager.h"

class LastPrizeItemModel  : public QAbstractListModel
{
    Q_OBJECT
public:
    enum PrizeRoles {
        CodeRole = Qt::UserRole + 1,
        NameRole
    };

    explicit LastPrizeItemModel(QObject *parent = nullptr);

    Q_INVOKABLE void addPrize(Player* player);
    Q_INVOKABLE void resetPrize();
    Q_INVOKABLE void removeLastPrize();
    Q_INVOKABLE void removePrize(QString code);

    // QAbstractItemModel interface
public:
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;

protected:
    QHash<int, QByteArray> roleNames() const;

signals:
private:
    QList<Player*> m_displayList;

};

#endif // LASTPRIZEITEMMODEL_H
