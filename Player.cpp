#include "Player.h"

Player::Player() :
    m_code(-1),
    m_name(""),
    m_iPrizeId(-1)
{

}

Player::Player(int code, QString name):
    m_code(code),
    m_name(name),
    m_iPrizeId(-1)
{

}

Player::Player(Player *p):
    m_code(p->m_code),
    m_name(p->m_name),
    m_iPrizeId(p->m_iPrizeId)
{

}

Player::~Player()
{
    m_code = -1;
}

int Player::code() const
{
    return m_code;
}

QString Player::name() const
{
    return m_name;
}
