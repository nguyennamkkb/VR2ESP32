#ifndef FS_01_H
#define FS_01_H

#include <QObject>
#include <QWidget>
#include <QtCore>

#include <QTimer>
#include <QTime>
#include <QDebug>
#include <QString>
#include <QByteArray>

#define cmd_prefix	0xaa55
#define cmd_response_prefix	0x55aa
#define data_prefix	0xa55a
#define data_response_prefix	0x5aa5
#define cmd_response	1
#define data_response	2

#define uint8 quint8
#define int8 qint8
#define uint16 quint16
#define int16 qint16
#define uint32 quint32
#define int32 qint32
#define n2s QString::number
#define char_buf_len 498

#define btn_dst 0
#define lb_dst 4
#define out_dst 5

#define FS01_STRING                  0x0
#define FS01_BCAST                   0x1
#define FS01_CMD                     0x2
#define FS01_DATA                    0x3

#define PC_BCAST                     0x10
#define PC_01                        0x11
#define PC_02                        0x12

#define FS02_STRING                  0x20
#define FS02_BCAST                   0x21
#define FS02_CMD                     0x22
#define FS02_DATA                    0x23

#define FILE_DATA                    0x30

const QString s_num="0123456789";
const QString shex="0123456789ABCDEF";
struct cmd_tx_struct{
    uint8 prefix[2];
    int16 cmd;
    int16 len;
    int16 data[8];
    int16 cks;
};
struct data_tx_struct{
    uint8 prefix[2];
    int16 cmd;
    int16 len;
    int16 data[252];
};
struct cmd_rx_struct{
    uint8 prefix[2];
    int16 rcm;          // last cmd
    int16 len;
    int16 data[8];
    int16 cks;
};
struct data_rx_struct{
    uint8 prefix[2];
    int16 rcm;          // last cmd
    int16 len;
    int16 data[252];
};
struct udp_tx_header{
    uint8 bcc;
    uint8 pkt_type;
    int16 cmd;
    int16 len;
    int16 page_id;
    int16 app_id;
    int16 seg_type;
    int16 seg_len;
    int16 data[512];
};
struct udp_rx_header{
    uint8 bcc;
    uint8 pkt_type;
    int16 app_id;
    cmd_rx_struct cmd_rx;
    data_rx_struct data_rx;
};

const int16 rcm_len[38]={
    4, 4, 6, 6, 4,
    4, 4, 4, 6, 502,    // Read_Page
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,
    4, 4, 4, 4, 500,    // Get_Enroll
    500, 4, 4, 16, 4,   // Get_Feature
    4, 4, 4, 4, 4,
    2, 2, 2
};

class fs_01 : public QObject
{
    Q_OBJECT
public:
    explicit fs_01(QObject *parent = 0);

    quint8 char_buf[char_buf_len];

    enum fs01_code{
        Verify=0x101,
        Identify, Enroll_3, Enroll_1, Delete_Page,
        Empty, Get_Empty_ID, Get_Page_Sta, Get_Broken_Page, Read_Page,
        Write_Page, Set_Security, Get_Security, Set_Time_Out, Get_Time_Out,
        Set_Device_ID, Get_Device_ID, Get_FW_Version, Finger_Detect, Set_BaudRate,
        Set_Dup_Check, Get_Dup_Check, Stadby_Mode, Enroll_RAM, Get_Enroll,
        Get_Feature, Verify_Feature, Identify_Feature, Get_Device_Name,
        LED_Control=0x124,
        Identify_Free, Set_Psw, Verify_Psw, Get_Enroll_Count, Change_Page,
        FP_Cancel=0x130,
        Test_Connection=0x150,
        Incorrect_Command
    };
    Q_ENUM(fs01_code)
    qint16 cmd_len[80]={
        Verify,2, Identify,0, Enroll_3,2, Enroll_1,2, Delete_Page,2,
        Empty,0, Get_Empty_ID,0, Get_Page_Sta,2, Get_Broken_Page,0, Read_Page,2,
        Write_Page,2, Set_Security,2, Get_Security,0, Set_Time_Out,2, Get_Time_Out,0,
        Set_Device_ID,2, Get_Device_ID,0, Get_FW_Version,0, Finger_Detect,0, Set_BaudRate,2,
        Set_Dup_Check,2, Get_Dup_Check,0, Stadby_Mode,0, Enroll_RAM,0, Get_Enroll,0,
        Get_Feature,0, Verify_Feature,2, Identify_Feature,2, Get_Device_Name,0, LED_Control,2,
        Identify_Free,0, Set_Psw,14, Verify_Psw,14, Get_Enroll_Count,0, Change_Page,2,
        FP_Cancel,0, Test_Connection,0, Incorrect_Command,0
    };
    QStringList error_code={
        "0x00" ,"GD_NO_DETECT_FINGER",
        "0x01" ,"GD_DETECT_FINGER",
        "0x11" ,"ERR_VERIFY",
        "0x12" ,"ERR_IDENTIFY",
        "0x13" ,"ERR_TMPL_EMPTY",
        "0x14" ,"ERR_TMPL_NOT_EMPTY",
        "0x15" ,"ERR_ALL_TMPL_EMPTY",
        "0x16" ,"ERR_EMPTY_ID_NOEXIST",
        "0x17" ,"ERR_BROKEN_ID_NOEXIST",
        "0x18" ,"ERR_INVALID_TMPL_DATA",
        "0x19" ,"ERR_DUPLICATION_ID",
        "0x21" ,"ERR_BAD_QUALITY",
        "0x23" ,"ERR_TIME_OUT",
        "0x24" ,"ERR_NOT_AUTHORIZED",
        "0x30" ,"ERR_GENERALIZE",
        "0x41" ,"ERR_FP_CANCEL",
        "0x50" ,"ERR_INTERNAL",
        "0x51" ,"ERR_EXCEPTION",
        "0x60" ,"ERR_INVALID_TMPL_NO",
        "0x61" ,"ERR_INVALID_SEC_VAL",
        "0x62" ,"ERR_INVALID_TIME_OUT",
        "0x63" ,"ERR_INVALID_BAUDRATE",
        "0x65" ,"ERR_INVALID_ DUP_VAL",
        "0x70" ,"ERR_INVALID_PARAM",
        "0x71" ,"ERR_NO_RELEASE",
        "0xA1" ,"GD_DOWNLOAD_SUCCESS",
        "0xFFF1" ,"GD_NEED_FIRST_SWEEP",
        "0xFFF2" ,"GD_NEED_SECOND_SWEEP",
        "0xFFF3" ,"GD_NEED_THIRD_SWEEP",
        "0xFFF4" ,"GD_NEED_RELEASE_FINGER",
        "0x01" ,"GD_TEMPLATE_NOT_EMPTY",
        "0x00" ,"GD_TEMPLATE_EMPTY"
    };

    qint16 w_data_len[6]={
        Write_Page,500,Verify_Feature,498, Identify_Feature,500
    };
    qint16 fs01_index[128];
    qint16 page_id;

    cmd_tx_struct cmd_tx;
    cmd_rx_struct cmd_rx;
    data_tx_struct data_tx;
    data_rx_struct data_rx;

public slots:
    QString enumToString(qint16 cmd);
    void fp_btn_check();
    QByteArray ba_to_send(qint16 cmd,qint16 len,qint16 page_id);
    QByteArray get_tx_cks(int16 len);
    bool get_rx_cks(int16 len);
    QString fix_len(qint16 n,qint16 k);
    QString ba_to_string(QByteArray ba);
    QString return_string(qint16 ret_code);

};
#endif // FS_01_H
/*
Get_Enroll_Count	ret + err_code or count
Identify		ret + err_code or page_id
Delete_Page		ret + err_code or page_id
Empty			ret + err_code or cleared_count
Enroll			ret + err_code or page_id
Finger_Detect		ret + err_code or page_id
Write_Page		ret + err_code or page_id

 */
