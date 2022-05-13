#ifndef IMA_H
#define IMA_H
#include <QtCore>
#include <QtWidgets>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QStringList>
#include <QObject>

#define uint8 quint8
#define int8 qint8
#define uint16 quint16
#define int16 qint16
#define uint32 quint32
#define int32 qint32

class ima
{
public:
    ima();
    qint32 e_index,d_index;
    qint32 e_predsample,d_predsample;

public slots:
    qint16 decoder(quint8 b_code);
    quint8 encoder(qint16 sample);

};

#endif // IMA_H
