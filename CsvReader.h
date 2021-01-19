#ifndef CSVREADER_H
#define CSVREADER_H

#include <QFile>
#include "Player.h"

class CsvReader
{
public:
    CsvReader();
    static QList<Player*> LoadPlayerList(QString filePath);
};

#endif // CSVREADER_H
