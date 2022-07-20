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
    Shared__invoke__0efe8de76652db7fd14620b97b81808050326907(thread, qMethodName.toUtf8().data(), msg.toUtf8().data());
}
