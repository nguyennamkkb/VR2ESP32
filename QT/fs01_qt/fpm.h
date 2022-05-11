#ifndef FPM_H
#define FPM_H

#include <QObject>
#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QString>
#include <QByteArray>
#include "r307.h"
#include "fs_01.h"

#define n2s QString::number
#define cmd_buf_max 16
class fpm : public QObject
{
    Q_OBJECT
public:
    explicit fpm(QObject *parent = 0);

    struct fpm_out_header{
      quint8 hd[2];
      quint8 fpm_addr[4];
      quint8 pkt_id;
      quint8 pkt_len[2];
    };
    struct fpm_in_header{
      quint8 hd[2];
      quint8 fpm_addr[4];
      quint8 pkt_id;
      quint8 pkt_len[2];
    };

    fpm_out_header fpm_tx;
    fpm_in_header fpm_rx;
    qint16 fpm_len,pkt_id,confirm_code,last_cmd,page_id,location_id,pkt_cnt;
    QByteArray fp_ba;
    quint8 char_buf[496];
signals:
    void new_img(QByteArray,qint16);
    void new_ser_msg(QByteArray,qint16);
    void new_str_msg(QString);

public slots:
    QByteArray get_checksum(QByteArray ba);
    QByteArray get_cmd_array(quint8 *buf,int len);
    QByteArray get_out_array(quint8 pkt_type,quint8 *buf,int len);
    QByteArray buf_out();
    qint16 serial_msg(QByteArray ba);
    void f_timer();
    qint16 get_int(QByteArray ba,qint16 index);
};

#endif // FPM_H
