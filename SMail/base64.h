#ifndef BASE64
#define BASE64

#include <QtCore>


QString base64_encode(QString some)
{
    QByteArray ba;
    ba.append(some);
    return ba.toBase64();
}

QString base64_decode(QString some)
{
    QByteArray ba;
    ba.append(some);
    return QByteArray::fromBase64(ba);
}

#endif
