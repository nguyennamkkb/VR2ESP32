#ifndef V_H_
#define V_H_
// #include <Enum.h>
#include "fs_01.h"

#define rx_max 1024

#define FS01_APP_ID                  0x400

#define FS01_STRING                  0x0
#define FS01_BCAST                   0x1
#define FS01_CMD                     0x2
#define FS01_DATA                    0x3
#define FS01_02                      0x4

#define PC_BCAST                     0x10
#define PC_01                        0x11
#define PC_02                        0x12

#define FS02_STRING                  0x20
#define FS02_BCAST                   0x21
#define FS02_CMD                     0x22
#define FS02_DATA                    0x23
#define FS02_01                      0x24

//Out1 14, Out2 12 In1 18 In2 19
//Buzz 23 led 26 Door 33 RS485 32

#define pwm_ch 0
#define freq  78125
#define pwm_bit  9
#define zero_level 256
#define ima_seg_max 32
#define ima_seg_len 1024        
#define ima_buf_max 32768        

#define pkt_cmd 1
#define pkt_data 0

#define cmd_buf_max 16
#define total_page_len 200
const int16 sin8[]={0, 180, 255, 180, 0, -180, -255, -180};
const String s_hex="0123456789ABCDEF";

#define uart0  Serial
#define uart1 Serial1
#define uart2   Serial2

#define pin_tx1   27
#define pin_rx1   14

#define buzze_ctrl 23
#define rs485_ctrl 32
#define door_gate 33

#define fp_detect_pin 4 //36
#define master_in 36

// #define PCBA2
#ifdef PCBA2
        #define out0 12      // 34
        #define out1 13
        #define buzz_in 34
        #define led_in 35
        #define LED1 26
#else
        #define pwm_pin 12      // 34
        #define LED1 15// vr1 la 25 va 26
        #define LED2 2
        #define COI 33//vr1 la 23
        #define out0 36      // 34
        #define out1 39
        #define buzz_in 34
        #define led_in 35
#endif
#define door_open digitalWrite(door_gate,1)
#define door_close digitalWrite(door_gate,0)
#define off_led1 digitalWrite(LED1, 1)
#define on_led1 digitalWrite(LED1, 0)
#define rs485_out digitalWrite(rs485_ctrl,1)
#define rs485_in digitalWrite(rs485_ctrl,0)
#define buzze_on digitalWrite(buzze_ctrl,1)
#define buzze_off digitalWrite(buzze_ctrl,0)
#define out0_hi digitalWrite(out0,0)
#define out0_low digitalWrite(out0,1)
#define out1_hi digitalWrite(out1,0)
#define out1_low digitalWrite(out1,1)

#endif
// iiik^.....ssss#
// iii id : 0-999
// k : key_code (1-20) = ascii(k) - 0x40
// ssss check sum

// ^6ramwr_dv00_CHUYEN DEN DT_SO TIEN=_SO DIEN THOAI=_ _MK THE=_*dv01_  	*
// ^6ramwr_nt00_Ngan hang A Chau_Ngan hang Phuong Nam_ ...*nt01_ 			*
// ^3cl*li0_This line 1*li1_This line 2*csccr*
// ^3pa0_line 1_line 2_line 3_line 4*pa1_line 1_line 2_line 3_line 4*pa2_line 1_line 2_line 3_line 4_*