#ifndef FS01_QT_H
#define FS01_QT_H

#include "n_serial.h"
#include "fs_01.h"
#include "wav.h"
#include "ima.h"
#include "udp_thread.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QtSerialPort/QSerialPort>
#include <QCoreApplication>

#include <QMainWindow>
#include <QDebug>
#include <QTimer>
#include <QTime>
#include <QFile>
#include <QStringList>
#include <QObject>
#include <QNetworkInterface>
#include <QHostAddress>
#include <QUdpSocket>
#include <QtNetwork>
#include <QElapsedTimer>
#include <QCloseEvent>
#include <QtCore>
#include <QtWidgets>

#include <QGroupBox>
#include <QGridLayout>
#include <QLabel>
#include <QPixmap>
#include <QPainter>
#include <QVBoxLayout>
#include <QtWidgets>
#include <QSlider>
#include <QFormLayout>
#include <QTextEdit>
#include <QFileDialog>
#include <QImage>
#include <QRgba64>
#include <QMouseEvent>
#include <QInputDialog>
#include <QSlider>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidgetItem>
#include <QTableWidget>
#include <QPalette>
#include <QToolTip>
#include <QDebug>
#include <QStatusBar>
#include <QMenuBar>
#include <QScrollBar>
#include <QMessageBox>
#include <QColor>
#include <QComboBox>
#include <QMessageBox>
#include <QMetaEnum>

#define cmd_buf_max 16

namespace Ui {
class fs01_qt;
}

class fs01_qt : public QMainWindow
{
    Q_OBJECT

public:
    explicit fs01_qt(QWidget *parent = 0);
    ~fs01_qt();
    QSize size;
    QByteArray voice_ba;
    qint16 x_max,y_max,k_btn=40,fs01_bcast_cnt;
    qint16 ms10,ms1000,udp_cnt=0;
    QString  serial1_port="ttyUSB",serial2_port="ttyS0",serial_port="COM3",serial3_port="COM5";
    QString ip_base="192.168.",bcast_ip="192.168.1.255",my_ip;
    QString char_file_name="",EV2_string="",w_file_name;
    qint16 page_id,seg_state;
    const qint16 hbox_index[24]={0,0,0, 1,1,1,1, 2,2,2,2, 3,3,3,3, 4,4,4,4, 5,5,5,5, 5};
    enum {  seg_begin,seg_append,seg_save};

    enum btn_list{
        Com_open, Scan, Clear,
        Identify, Count, Delete, Empty,
        Detect, Enroll_1, Enroll, Read_fp,
        Verify, Cancel, First_ID, Get_Enroll,
        Download, Play, Ev2, Ssid,
        Bip_on, Ip_Show, List,
        Set_pass,Veri_pass
    };
    Q_ENUM(btn_list)

    struct dialog_struct{
        qint16 ok;
        qint16 sel_int;
        QString sel_str;
    };
    dialog_struct dlg_struct;
    enum {  voice_download, voice_play, file_rename, file_list, set_bip_on, send_ev2, add_ssid};
    wav_header wav_hd;

private slots:
    void closeEvent(QCloseEvent *event);
    void cfg_load();
    void get_ip();
    void Timer1();
    void ui_init();
    void new_udp_msg(qint16 response);
    void new_serial_msg(qint16 response);
    void new_serial_msg(QString s);
    void serial_scan();
    void new_string_msg(qint16 n,QString s);
    QString ba_str(QByteArray ba);
    void btn_click(int k);

    void fp_click(int i);
    qint16 str_to_int(QString s);
    void k_input(QInputDialog::InputMode input_mode,QString prompt_txt);
    QByteArray read_page_file();
    void write_page_file(QString fname,QByteArray ba);
    qint16 msg_box(QString s);
    void fp_btn_init();
    QString btn_name(qint16 i);
    void cmd_send(qint16 cmd);
    void txt_append(QString s);
    qint16 string_to_int(QString s);
    QByteArray read_wave_file();
    void encode_ba(QByteArray ba,int seg);
    void new_udp_str(qint16 response,QString s);
    void voice_send();

private:
    Ui::fs01_qt *ui;
    n_serial *ser;
    fs_01 *fs01;
    ima *n_ima;
    Udp_thread *u;
    QThread *thread;

    QGridLayout *grid;
    QGroupBox *gr1;
    QVBoxLayout *vbox;
    QHBoxLayout *hbox[8];
    QLineEdit *in_txt[8];
    QTextEdit *out_txt[8];
    QPushButton *p_btn[24];
    QCheckBox *chk[8];
    QComboBox *combo[8];
    QLabel *lb[8];

    QGridLayout *fp_grid;
    QGroupBox *fp_group;
    QPushButton *fp_btn[40]; // v1, v2, Save, Cancel
    QHBoxLayout *fp_hbox[8];

};

/*

*/ 
#endif // FS01_QT_H
