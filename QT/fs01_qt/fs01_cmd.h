#ifndef FS01_CMD_H
#define FS01_CMD_H

#include <QObject>
#include <QtCore>
#include <QWidget>

class fs01_cmd
{    Q_OBJECT

public:
    fs01_cmd();
    QString enumToString(qint16 cmd);
    enum fs01_code{
        Verify=0x101,
        Identify, Enroll, Enroll_1, delete_Page,
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
};

#endif // FS01_CMD_H
