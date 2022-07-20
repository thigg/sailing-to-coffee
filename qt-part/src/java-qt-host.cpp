#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include <cstdio>
#include "../lib/graal_isolate.h"
#include "../lib/sailfishjava.h"
#include "src/jgateway.h"

int main(int argc, char *argv[])
{
    graal_isolatethread_t *thread = nullptr;
    if (graal_create_isolate(nullptr, nullptr, &thread) != 0) {
        fprintf(stderr, "error on isolate creation or attach\n");
        return 1;
    }
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    QQmlContext *context = view.data()->rootContext();

    qDebug() << " thread " << thread;
    JGateway javaGateway(thread);

    //Init JGateway
    Shared__init__32d66b024a8aca0e01c06f37c82e74a1ffa4df4b(thread);

    context->setContextProperty("JGateway", &javaGateway);

    view->setSource(SailfishApp::pathTo("qml/java-qt-host.qml"));
    view->show();

    return app->exec();
}
