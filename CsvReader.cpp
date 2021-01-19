#include "CsvReader.h"

CsvReader::CsvReader()
{

}

QList<Player *> CsvReader::LoadPlayerList(QString filePath)
{
    QList<Player*> ret;
    QFile file(filePath);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    in.setCodec("UTF-8");
    while(!in.atEnd()) {

        QString line = in.readLine();
        QStringList  fields = line.split(",");

        Player* p = new Player(fields.first().toInt(), fields[1].trimmed());
        ret.append(p);
    }
    file.close();
    return ret;
}
