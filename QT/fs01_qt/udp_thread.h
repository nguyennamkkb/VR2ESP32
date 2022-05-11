#ifndef UDP_THREAD_H
#define UDP_THREAD_H

#include <QObject>
#include <QtCore>
#include <QThread>
#include <QTimer>
#include <QDebug>

#include <QNetworkInterface>
#include <QHostAddress>
#include <QUdpSocket>
#include <QtNetwork>

#include <QFont>

#include <QString>
#include <QFile>
#include <QTextStream>
#include <QColor>
#include <QPalette>
#include <QTextStream>

#include <QDateTime>
#include <QTimer>
#include <QDate>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QCoreApplication>

#include <QMutex>
#include <QEventLoop>
#include <QElapsedTimer>

#define uint8 quint8
#define int8 qint8
#define uint16 quint16
#define int16 qint16
#define uint32 quint32
#define int32 qint32

#include "fs_01.h"

#define read_param 0
#define read_count 1
#define delete_fid 2
#define delet_all 3
#define add_template 4

#define n2s QString::number

class Udp_thread : public QObject
{
      Q_OBJECT
public:
    explicit Udp_thread(QObject *parent = 0);

    QString bcast_ip="192.168.1.255",esp_ip="192.168.1.255",dst_ip="192.168.1.255",pc_ip="",ip_base="192.168.";
    QString bcast_msg;
    qint16 udp_on=0,ip_fix=0;
    qint16 ms10=0,ms256,ms1000=0,lan_on=0,ms64,wifi=0,wifi_on=0,bcast_cnt=0;
    qint16 hex16[16];
    quint8 pkt_type;
    qint16 hex_val,hex_on,min_cnt;
    quint32 hex32[32];
    quint16 ip_list[32];
    qint16 ip_scan_cnt=0,ip_list_max=0;

    udp_tx_header udp_tx,bcast_tx;
    udp_rx_header udp_rx,bcast_rx;

signals:
    void new_udp_signal(qint16,QString);
    void new_udp_signal(qint16);

public slots:
    void socket_send(QByteArray ba);
    QString fix_len(int n,int len);
    void bcast_out();
    void big_out();
    void udp_send(int16 cmd, int16 len, int16 page_id);
    QByteArray get_bcc(QByteArray ba,uint8 k);
    void ip_scan();
    void ip_test();

private slots:
    void wifi_read();
    void Timer();

private:
    QUdpSocket *wifi_socket;
    fs_01 *fs01;
public:

};

#endif // UDP_THREAD_H
