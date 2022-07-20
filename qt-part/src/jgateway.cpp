#include "jgateway.h"
#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif
#include "../lib/sailfishjava.h"

#include <cstring>
#include <string>



JGateway::JGateway(graal_isolatethread_t *threadPtr)
{
    thread = threadPtr;
}

void JGateway::postMessage(const QString &qMethodName, const QString &msg)
{
    qDebug() << "Called the C++ method with" << msg;
    QString result = QString(JGateway__invoke(thread, qMethodName.toUtf8().data(), msg.toUtf8().data()));
    qDebug() << "result" << result;
    emit invocationResult(result);
}
