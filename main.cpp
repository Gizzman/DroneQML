#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include "planecontroller.h"
#include "wayinfo.h"
int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);
    WayInfo way;
    PlaneController myplane;
    QQmlApplicationEngine engine;

    engine.rootContext()->setContextProperty("way", &way);
    engine.rootContext()->setContextProperty("myPlaneControl",&myplane);
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
