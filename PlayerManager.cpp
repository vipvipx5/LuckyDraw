#include "PlayerManager.h"
#include <QRandomGenerator>

PlayerManager::PlayerManager()
{

}

PlayerManager::PlayerManager(QList<Player *> playerList) :
    m_playerList(playerList)
{

}

QList<Player *> PlayerManager::getPlayerList()
{
    return m_playerList;
}

QList<Player *> PlayerManager::getLastPrizeList()
{
    if(m_prizeList.isEmpty()){
        return QList<Player*>();
    }
    return m_prizeList.last();
}

int PlayerManager::getLastPrizeListCount()
{
    return getLastPrizeList().count();
}

Player *PlayerManager::getLastPrizeListItem(int iIndex)
{
    QList<Player*> prized = getLastPrizeList();
    if(iIndex < 0 || iIndex>= prized.count()) {
        return NULL;
    }
    return prized[iIndex];
}

Player *PlayerManager::randomPrize(int iPrizeId)
{
    if(m_playerList.count() == 0){
        return NULL;
    }
    int index = QRandomGenerator::global()->bounded(m_playerList.count());
    Player* p = m_playerList.takeAt(index);
    return p;
}
