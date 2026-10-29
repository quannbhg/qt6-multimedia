#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include "viewmodels/appinfoviewmodel.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    AppInfoViewModel appInfo;

    QQmlApplicationEngine engine;
    engine.rootContext()->setContextProperty("appInfo", &appInfo);

    engine.loadFromModule("MultimediaApp", "Main");

    if (engine.rootObjects().isEmpty()) {
        return -1;
    }
    return app.exec();
}