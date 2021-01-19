#include "LastPrizeItemModel.h"

#define MAX_COLUMN 1

LastPrizeItemModel::LastPrizeItemModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void LastPrizeItemModel::addPrize(Player *player)
{
    beginResetModel();
    m_displayList.append(new Player(player));
    endResetModel();
    delete player;
}

void LastPrizeItemModel::resetPrize()
{
    beginResetModel();
    m_displayList.clear();
    endResetModel();
}

void LastPrizeItemModel::removeLastPrize()
{
    if(m_displayList.count() ==0){
        return;
    }
    beginResetModel();
    m_displayList.removeLast();
    endResetModel();
}

int LastPrizeItemModel::rowCount(const QModelIndex &parent) const
{
    int count = m_displayList.count();
    int row = count%MAX_COLUMN == 0 ? count/MAX_COLUMN : count/MAX_COLUMN + 1;
    return row;
}

int LastPrizeItemModel::columnCount(const QModelIndex &parent) const
{
    int count = m_displayList.count();
    int column = count>MAX_COLUMN ? MAX_COLUMN : count;
    return column;
}

QVariant LastPrizeItemModel::data(const QModelIndex &index, int role) const
{
    int iIndex = index.row() * MAX_COLUMN + index.column();
    if (index.row() < 0 || index.row() >= rowCount() || index.column() < 0 || index.column() >= columnCount() || iIndex >= m_displayList.count())
        return QVariant();

    const Player* player = m_displayList.at(iIndex);
    if (role == CodeRole)
        return QString("%1").arg(player->code(), 3, 10, QChar('0'));
    else if (role == NameRole)
        return player->name();
    return QVariant();
}

QHash<int, QByteArray> LastPrizeItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CodeRole] = "code";
    roles[NameRole] = "name";
    return roles;
}
