#include "LastPrizeItemModel.h"

#define MAX_COLUMN 3
#define MAX_ROW 4

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

void LastPrizeItemModel::removePrize(QString code)
{
    int icode = code.toInt();
     beginResetModel();
     for(int i= 0; i<m_displayList.count(); i++)
     {
         Player* player = m_displayList[i];
         if(player != NULL && player->code() == icode){
             m_displayList.removeAt(i);
             break;
         }
     }
     endResetModel();
}


int LastPrizeItemModel::rowCount(const QModelIndex &parent) const
{
    int count = m_displayList.count();
    int column_count = columnCount();
    if(column_count == 0){
        return 0;
    }
    int row = (count%column_count == 0) ? count/column_count : count/column_count + 1;
    return row;
}

int LastPrizeItemModel::columnCount(const QModelIndex &parent) const
{
    int count = m_displayList.count();
    int iMaxRow = MAX_ROW;
    if(count/MAX_ROW > 2){
        iMaxRow += 2;
    } else {
        iMaxRow += count/MAX_ROW;
    }
    int column = count/iMaxRow;
    if(count % iMaxRow > 0){
        column += 1;
    }
    column = column > MAX_COLUMN ? MAX_COLUMN : column;
    return column;
}

QVariant LastPrizeItemModel::data(const QModelIndex &index, int role) const
{
    int iIndex = index.row() * columnCount() + index.column();
    if (index.row() < 0 || index.row() >= rowCount() || index.column() < 0 || index.column() >= columnCount() || iIndex >= m_displayList.count())
        return QVariant();

    const Player* player = m_displayList.at(iIndex);
    if (role == CodeRole)
        return QString("%1").arg(player->code(), 3, 10, QChar('0'));
    else if (role == NameRole)
        return player->name();
    else if(role == Qt::TextAlignmentRole) {
        return Qt::AlignCenter;
    }
    return QVariant();
}

Qt::ItemFlags LastPrizeItemModel::flags(const QModelIndex &index) const
{
    int iIndex = index.row() * columnCount() + index.column();
    if (index.row() < 0 || index.row() >= rowCount() || index.column() < 0 || index.column() >= columnCount() || iIndex >= m_displayList.count()) {
        return Qt::NoItemFlags;
    } else {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
}

QHash<int, QByteArray> LastPrizeItemModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CodeRole] = "code";
    roles[NameRole] = "name";
    return roles;
}
