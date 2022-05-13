#ifndef N_SERIAL_H
#define N_SERIAL_H

#include <QObject>
#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include "fs_01.h"

class n_serial : public QObject
{
    Q_OBJECT
public:
    explicit n_serial(QObject *parent = 0);

    QSerialPort *serial;
    QSerialPort *serial2;

    qint16 serial_on=0,rx_time_out=0,ms10,ms20=0;
    QByteArray rxbuf,rxtmp,rxbuf_2,rx_ok;
    QString serial_in="",serial_port="ttyUSB0",serial2_port="ttyS0",serial2_out;
    qint16 serial_open=0,pkt_len,hd_ok=0,use_pi=0;
    qint16 response_code=0,data_len=0,page_id,rx_show=0;
    cmd_tx_struct cmd_tx;
    cmd_rx_struct cmd_rx,cmd_tmp;
    data_tx_struct data_tx;
    data_rx_struct data_rx,data_tmp;
    fs_01 *fs01;

signals:
    void new_serial_msg(qint16,QString);
    void new_serial_msg(qint16);
public slots:
    void serial_create(QString comport);
    void serial_out(QByteArray ba);
    quint8 get_bcc(quint8 *buf,int len);
    void send_ev2();
    QString str_fix_len(QString s, int len);
    void serial2_out_test();
    qint16 get_len(qint16 k);

private slots:
    void Timer_2();
    void serial_test();
    void serial2_test();
private:
};

#endif // N_SERIAL_H
