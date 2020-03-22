#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQuickItem>

#include "qsynth.h"

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QGuiApplication app(argc, argv);
    QQmlApplicationEngine engine;

    QSynth* const qsynth =
        engine.singletonInstance<QSynth *>(qmlRegisterSingletonType<QSynth>(
            "Synth", 1, 0, "Synth", [](QQmlEngine *, QJSEngine *) -> QObject * {
                return new QSynth(); }));

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
