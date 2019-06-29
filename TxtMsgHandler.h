#ifndef TXTMSGHANDLER_H
#define TXTMSGHANDLER_H

#include <QTcpSocket>
#include "TextMessage.h"

class TxtMsgHandler
{
public:
    virtual void handle(QTcpSocket& obj, TextMessage&message) = 0;
};

#endif // TXTMSGHANDLER_H
