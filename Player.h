#ifndef PLAYER_H
#define PLAYER_H

#include <QQuickItem>

class Player : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(int code READ code)
    Q_PROPERTY(QString name READ name)
public:
    Player();
    Player(int code, QString name);
    Player(Player* p);

    ~Player();


    int code() const;
    QString name() const;

private:
    int m_code;
    QString m_name;
    int m_iPrizeId;
};

#endif // PLAYER_H
