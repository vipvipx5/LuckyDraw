#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include "LastPrizeItemModel.h"
#include <qqmlcontext.h>
#include "Player.h"
#include "CsvReader.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    qmlRegisterType<PlayerManager>("PlayerManager", 1, 0, "PlayerManager");
    qmlRegisterType<Player>("Player", 1, 0, "Player");


    LastPrizeItemModel lastPrizeItemModel;
    QList<Player*> listPlayer = CsvReader::LoadPlayerList("list.csv");
    PlayerManager playerManager(listPlayer);

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);

    QQmlContext *ctxt = engine.rootContext();
    ctxt->setContextProperty("lastPrizeItemModel", &lastPrizeItemModel);
    ctxt->setContextProperty("playerManager", &playerManager);

    engine.load(url);

    return app.exec();
}
