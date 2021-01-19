#ifndef PLAYERMANAGER_H
#define PLAYERMANAGER_H

#include <QQuickItem>
#include "Player.h"

class PlayerManager : public QQuickItem
{
    Q_OBJECT
public:
    PlayerManager();
    PlayerManager(QList<Player*> playerList);

    QList<Player*> getPlayerList();

    QList<Player *> getLastPrizeList();
    int getLastPrizeListCount();
    Player* getLastPrizeListItem(int iIndex);

    Q_INVOKABLE Player* randomPrize(int iPrizeId);

signals:

private:
    QList<Player*> m_playerList;
    QList<QList<Player*>> m_prizeList;
};

#endif // PLAYERMANAGER_H
