#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "infrastructure/qtplaybackengine.h"
#include "services/playbackservice.h"
#include "viewmodels/appinfoviewmodel.h"
#include "viewmodels/playerviewmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    /* Create objects from inside to outside. */
    QtPlaybackEngine playbackEngine;
    PlaybackService playbackService(&playbackEngine);
    PlayerViewModel playerVM(&playbackService);
    AppInfoViewModel appInfo;

    /* The QML engine is declared last, so it is destroyed first. */
    QQmlApplicationEngine qmlEngine;
    qmlEngine.rootContext()->setContextProperty("appInfo", &appInfo);
    qmlEngine.rootContext()->setContextProperty("playerVM", &playerVM);

    qmlEngine.loadFromModule("MultimediaApp", "Main");

    if (qmlEngine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec();
}