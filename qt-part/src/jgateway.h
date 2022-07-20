#ifndef JGATEWAY_H
#define JGATEWAY_H


#include <QObject>
#include "lib/graal_isolate.h"

class JGateway: public QObject
{
    graal_isolatethread_t *thread;
    Q_OBJECT
public:
    JGateway(graal_isolatethread_t *thread);
    Q_INVOKABLE void postMessage(const QString &qMethodName, const QString &msg);


signals:

public slots:

};

#endif // JGATEWAY_H
