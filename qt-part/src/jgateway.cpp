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
    std::string methodName = qMethodName.toStdString();
    std::string methodParam = msg.toStdString();
    char * p1 = new char [methodName.length()+1];
    std::strcpy (p1, methodName.data());
    char * p2 =  new char [methodParam.length()+1];
    std::strcpy (p2, methodParam.data());
    Shared__invoke__0efe8de76652db7fd14620b97b81808050326907(thread, p1, p2);
}
