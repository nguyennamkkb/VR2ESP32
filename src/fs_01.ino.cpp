# 1 "C:\\Users\\dungo\\AppData\\Local\\Temp\\tmp6hy1wpex"
#include <Arduino.h>
# 1 "D:/1.Work/ESP32/VR2ESP32/src/fs_01.ino"



#include "vimass.h"

#include "SPIFFS.h"
#include <Math.h>
#include <dummy.h>
#include <WiFi.h>
#include "esp_attr.h"
#include "HardwareSerial.h"
#include <ArduinoOTA.h>
#include <WiFiMulti.h>
#include <NTPClient.h>
#include <WiFiUdp.h>
#include <ESPmDNS.h>
#include <MD5.h>

WiFiMulti wifiMulti;
hw_timer_t *timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;



IPAddress apIP(192, 168, 2, 2), ap_gateway(192, 168, 2, 1), bcast_ip(192, 168, 2, 255), my_ip, pc_ip, esp2_ip;
WiFiUDP myUDP;
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);

int16 led_cnt, led1_on, led2_on, led_reset = 5, ms200 = 0, ms1000 = 0, pc_ip_cnt = 0;
int16 ms10, pc_on, wifi_status, string_valid_cnt, ms2;
int16 timer_1ms, udp_time = 0;
int16 wifi_on, file_ok, udp_on = 0, serial_on = 0;
int16 new_millis, old_millis, rx2_time_out;
int8 demghi = 0;
int64_t ms64_0, ms64, delta64;
int16 v_stat = 0, msg_type;
uint8 udp_in_buf[1400];
int16 my_id, hd_len;
int16 ms5, fp_off = 0, fp_on = 0, fp_detect_cnt = 0, fp_off_delay = 300, fp_mode_delay = 0, fp_fail = 0, fp_off_max = 500;
int16 tx_pkt_len, hd_index, buf_id, match_delay = 0, pulse_width = 300, pulse_max = 3;
uint8 char_buf[char_buf_len];
int16 data_pkt_cnt, door_open_delay = 0;
int16 p_millis, n_millis, d_millis;
uint16 r_port = 6000, solannhapmk = 0;
int16 rs485_tx_out = 0;

int16 vuaNhapPassConfirm = 0;
String s_log = "", magiaodich = "", str_door = "", str_lenhtbngoai = "", strdvtt = "", strdichvumaytram = "";
String idDelaySend[1];
String my_mac, serial_rs485, dulieughixacthuc = "", dau_dlxacthuc = "";
String iplocal[1];
String fp_save[5];
int trangthailenhtumaytinh = 0;
int ghivantay = 0;
int play_index = -1;

String uid_the = "", vid_the = "", ma_tbi = "", data_chamcong = "";

String tbttid[1];

String idDelayConfirm[1];

String dataServices[1];
uint8 datavantay[500];
uint8 rx_buf[rx_max];

String serial_in, params_str, serial2_out, serial2_in, vantay = "", khuonmat = "";
int16 page_id;
int16 hd_ok = 0, rx_pkt_len, rx_cnt = 0, pkt_type, check_sum, check_sum_ok;
uint8 ima_buf[ima_buf_max];
int16 voice_len, pwm_val, pwm_on = 0, ima_buf_cnt = 0, sin_cnt = 0, ima_haft = 0, pwm_send = 0;
uint8 pwm_tmp;
int16 n_prefix, response, ret, ret_code, door_cnt, fp_index = 0;
int16 bip_on = 0, fs01_on = 0, fp_auto_off, fp_on_duration, fp_on_max;
String data_khuonmat = "";

bool Validate = false;
bool TrangThaiThanhToan = false;
bool DichVuMayTram = false;
bool TrangThaiCacheCard = false;
bool xacthucvantay = 0, xacthuckhuonmat = 0, xacthutiengnoi = 0, ghi_ma_tbi = 1;
bool auto_docvt = 1;

char ssid_name[32], ssid_pass[32];
String ds_name[ds_max][sub_ds_max];
String str_name[4], str_pass[4];
String passDelaySend[1];
int soluongthietbi = 50000;
int32 e_predsample, d_predsample;
int16 e_index, d_index;
int duong_ra = 0, hang_doi_front = 0, hang_doi_rear = 0, hang_doi_sothietbidangdoi = 0, hang_doi_sothietbidangdoi2 = 0;
#define hang_doi_tong 3
String hang_doi[hang_doi_tong];
int16 encode_buf[2048];
cmd_tx_struct cmd_tx;
cmd_rx_struct cmd_rx;
data_tx_struct data_tx;
data_rx_struct data_rx;

udp_rx_header udp_rx;
udp_tx_header udp_tx;
int8 n_time[6];

int16 vtlen = 0, kmlen = 0;

struct struct_max
{
 int16 fx;
 int16 lcd_line;
 int16 dv_line0;
 int16 dv_index;
 int16 dv_index_max;
 int16 dv_td_index;
 int16 dv_td_index_max;
 int16 line_type[8];
 int16 ds_index;
 int16 ds_index_max;
 int16 sub_ds_index;
 int16 sub_ds_index_max[ds_max];
};
struct_max v_fx;

String dv_td[dv_max];

struct cfg_struct
{
 int16 media;
 int16 key_bounce;
 int16 key_inhibit;
 int16 brate0;
 int16 https_timeout;
 int16 page_delay[4];
};
cfg_struct v_cfg;
void setup();
void IRAM_ATTR fp_isr();
void fp_test();
void loop();
void millis_1();
void bcast_out();
void led_test();
void reset_7462(String a);
void bipok1();
void bipok2();
void biper1();
void biper2();
void Play_voice(int code);
void dongcua();
void mocua();
void bip4_no_internet();
void readFile(const char *path);
String dec_to_string(int a);
void wifi_setup();
void AP_setup();
void UDP_receive();
void string_send(String s);
uint8 get_bcc(uint8 *buf, int len);
void bcast_send(uint8 *buf, int len);
void uni_send(uint8 *buf, int len);
void setbip(int n);
void bip(int len, int type);
bool write_buf(String f_name, uint8 *buf, int16 len);
bool read_buf(String f_name);
bool rename(String s_src, String s_dst);
bool remove(String fname);
String list_file();
void read_ssid();
void save_ssid(String s);
void read_TBTTId();
void read_iplocal();
void save_TBTTId(String s);
void ghimatbi(String s);
void docmatbi();
void ghivantay2(String s);
void save_iplocal(String s);
void save_cfg(String s);
void save_id();
void checkCardOffline(String cardInput);
void save_cardOpenDoorOffline(String s);
void get_tx_cks(int16 len);
int16 get_rx_cks(int16 len);
int16 get_cmd_len(int16 cmd);
void cmd_send(int16 cmd, int16 len, int16 page_id);
bool cmd_found(int16 cmd);
void cmd_switch();
void voice_init();
void send_https(String s);
String https_decode(String s);
String https_encode(String s);
void confirm_service(String s);
void xuLyGuiThongTinLienQuanDenDoor(String s);
void confirmSaveCardOffline(String s);
void door_service(String s);
void xuLyYeuCauDichVuSauKetNoiLan1(String payload);
void payment_confirmation(String s);
void get_vantay(String data);
void getms(String data);
int16 IRAM_ATTR decoder(uint8 code);
void ota_init();
void set_pwm_val(int16 n16);
void pwm_init();
void timer_init(bool on_timer);
void IRAM_ATTR onTimer();
void yeu_cau_nhapmk();
void udp_out_ip(String sout,String ipout);
void new_cmd(String s0,uint8 src);
void resetServicesStatus();
void ram_rd(String s);
void new_time(String s);
String n_fix_len(int16 n,int16 len);
String fix_len(String s,int16 len);
void ram_wr(String s);
String bcc_check_len(String s,int a);
String bcc_check_step(String s, int step);
void add_to_serial(String s);
void serial_out();
void khoitao_ghixacthuc(String s);
void showOpenDoor(String s);
void showCloseDoor(String s);
void resetDoorStatus();
void xuLyDanhSachThe(String s);
void checkOfflineCardOpenDoor(String s);
String hangdoi_Front();
int16 fs_01_cks(uint8 *buf, int16 len, int16 k);
void fp_lock();
void serial_test();
void serial2_test();
void serial2_out_test();
void char_buf_to_ev2();
uint8 hex_to_byte(String s);
String tinhCKS_Du(String s, int n);
void XTvanTay(String strvt);
String hextostr(String s1);
void ghivantayvaothe(String vantay);
void ghivantayvaoESP32(String vantay);
void FS01_RES(String s1);
void caidatthietbi(String s);
String str_idtb(int a);
String tinhCKS(String s);
#line 136 "D:/1.Work/ESP32/VR2ESP32/src/fs_01.ino"
void setup()
{
 pinMode(LED1, OUTPUT);
 pinMode(LED2, OUTPUT);
 pinMode(COI, OUTPUT);
 pinMode(rs485_ctrl, OUTPUT);
 pinMode(door_gate, OUTPUT);
 pinMode(fp_detect_pin, INPUT_PULLDOWN);
 coi_off;
 off_led2;

 Serial.begin(115200, SERIAL_8N1);
 Serial2.begin(115200, SERIAL_8N1);
 Serial1.begin(115200, SERIAL_8N1, pin_rx1, pin_tx1);
 file_ok = (SPIFFS.begin(true)) ? 1 : 0;
 my_mac = WiFi.macAddress();
 ms64 = millis();
 memset(n_time, 0, sizeof(n_time));
 delay(1000);
 digitalWrite(12, 0);
 delay(1000);
 rs485_out;
 wifi_setup();
 ota_init();
 s_log = SPIFFS.begin(true) ? "FS Ok" : "FS fail";
 s_log += " size= " + String(SPIFFS.totalBytes() >> 10);
 s_log += " used= " + String(SPIFFS.usedBytes() >> 10);
 pwm_init();
 cmd_send(Set_Security, 2, 0);
 uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
 send_https("56_" + tbttid[0]);
 read_iplocal();
 timeClient.begin();
 timeClient.setTimeOffset(+7 * 60 * 60);
 bipok1();


 readFile("/hello.txt");
}
void IRAM_ATTR fp_isr()
{
}
void fp_test()
{
 if (auto_docvt)
 {
  if (fp_detect_cnt < 200)
   fp_detect_cnt++;
  fp_on_duration++;
 }
 else
 {
  if (fp_detect_cnt)
  {
   fp_detect_cnt--;
  }
  else
  {
   if (fp_on_duration)
   {
    fp_on_max = fp_on_duration;
    fp_on_duration = 0;
   }
  }
 }
 if (fp_detect_cnt >= 200)
 {
  fp_detect_cnt = 0;
  if (fp_auto_off == 0)
  {
   cmd_send(Identify, 0, 0);
   uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
  }
 }
}
void loop()
{
 if (pwm_on == 0)
  ArduinoOTA.handle();
 millis_1();
}
void millis_1()
{
 new_millis = millis() & 0x3fff;
 if (old_millis == new_millis)
  return;
 old_millis = new_millis;
 String s;
 serial_test();
 serial2_test();
 serial2_out_test();
 digitalWrite(door_gate, 1);
 UDP_receive();
 ms10 &= 0xf;
 if (++ms10 > 9)
 {
  ms10 = 0;
  fp_test();
  int wifi_status = WiFi.status();
  if (wifi_status == WL_CONNECTED)
   wifi_on = 300;
  if (wifi_on)
   wifi_on--;
  else
   ESP.restart();

  if (pc_ip_cnt)
  {
   pc_ip_cnt--;
  }
  else
  {
   pc_ip = bcast_ip;
   r_port = 6000;
  }
  if (fp_auto_off)
   fp_auto_off--;


 }
 ms200 &= 0x1ff;
 if (++ms200 > 200)
 {
  ms200 = 0;
  led_test();
 }
 ms1000 &= 0xfff;
 if (++ms1000 > 1000)
 {
  ms1000 = 0;
  bcast_out();
 }
}
void bcast_out()
{
 String s = s_log + " " + String(fp_on_max) + " " + String(fp_detect_cnt) + " " + String(fp_auto_off);
 uint8 buf[s.length()];
 udp_tx.pkt_type = FS01_BCAST;
 udp_tx.data_rx.rcm = WiFi.RSSI();
 udp_tx.data_rx.len = s.length();
 udp_tx.cmd_rx.data[0] = my_ip[3];
 udp_tx.cmd_rx.data[0] <<= 8;
 udp_tx.cmd_rx.data[0] |= my_ip[3];
 udp_tx.cmd_rx.data[1] = digitalRead(master_in);
 for (int i = 0; i < udp_tx.data_rx.len; i++)
 {
  buf[i] = s.charAt(i);
 }
 memcpy(udp_tx.data_rx.data, buf, sizeof(buf));
 bcast_send(&udp_tx.bcc, sizeof(udp_tx));
}
void led_test()
{
 led_cnt &= 0x1f;
 if (led_cnt <= 0)
 {
  led1_on = 0;
  if (wifi_on)
   led1_on++;
  if (pc_ip_cnt)
   led1_on = 2;
  if (fs01_on)
   led1_on += 2;
  led_cnt = led1_on * 2 + 2;
 }
 else if ((--led_cnt & 1) && led1_on)
 {
  led1_on--;
  on_led1;
 }
 else
 {
  off_led1;
 }
 if (led_reset)
 {
  led_reset--;
  on_led1;
 }
}

void reset_7462(String a)
{
 uart0.println("reset_7462:" + a);






 String s = "", serialto7462 = "!^" + a + "#";



 while (serialto7462.length())
 {

  if (serialto7462.length() > 123)
  {
   s = serial2_out.substring(0, 124);
   serial2_out.remove(0, 124);
  }
  else if (serialto7462.length())
  {
   s = serialto7462;
   serialto7462 = "";
   ms5 = (s.length() & 0x7c) + 4;
   while (s.length() < ms5)
   {
    s += "0";
   }
   ms5 = 0;
  }
  if (s.length())
  {
   Serial2.print(s);
   ms5 = 4;
  }
  delay(5);
 }
}

void bipok1()
{
 coi_on;
 delay(150);
 coi_off;
 delay(150);
}
void bipok2()
{
 bipok1();
 bipok1();
}
void biper1()
{
 coi_on;
 delay(500);
 coi_off;
 delay(500);
}
void biper2()
{
 biper1();
 biper1();
}

void Play_voice(int code)
{

 if (play_index != code)
 {
  read_buf("/a_" + String(code) + ".wav");
 }
 play_index = code;
 voice_init();
}

void dongcua()
{
 bipok2();
 digitalWrite(door_gate, 1);
 Serial.println("cua dong\n");
 delay(1000);
}
void mocua()
{
 bipok1();
 digitalWrite(door_gate, 0);
 Serial.println("cua mo\n");
 delay(1000);
}

void bip4_no_internet()
{
 coi_on;
 delay(300);
 coi_off;
 delay(300);
 coi_on;
 delay(300);
 coi_off;
 delay(300);
}

void readFile(const char *path)
{


 File file = SPIFFS.open(path);
 if (!file || file.isDirectory())
 {

  return;
 }
 ma_tbi = "";
 int n = 0;

 while (file.available())
 {
  n = file.read();
  ma_tbi += dec_to_string(n - 48);

 }
 add_to_serial(ma_tbi);
 serial_out();

}

String dec_to_string(int a)
{
 String str = "01234567890000000ABCDEF", s = "";
 s = str.substring(a, a + 1);
 return s;
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/Wifi.ino"
#include "vimass.h"

void wifi_setup()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPdisconnect(true);
  if (wifi_on)
    WiFi.disconnect();
  wifi_on = 0;
  for (int i = 0; i < 4; i++)
  {
    if (str_pass[i].length() >= 8)
    {
      strcpy(ssid_name, str_name[i].c_str());
      strcpy(ssid_pass, str_pass[i].c_str());
      wifiMulti.addAP(ssid_name, ssid_pass);
    }
  }

  wifiMulti.addAP("ViMASS_PC", "VMPC6996");






  WiFi.setAutoReconnect(true);
  uint8 sec_cnt = 0;
  wifi_on = 0;
  while (sec_cnt++ < 25)
  {
    if (wifiMulti.run() != WL_CONNECTED)
    {
      on_led1;
      delay(500);
      off_led1;
      delay(500);
    }
    else
    {
      sec_cnt = 150;
      my_ip = bcast_ip = WiFi.localIP();
      bcast_ip[3] = 255;
      wifi_on = 300;
      pc_ip = bcast_ip;
      uart0.println(WiFi.localIP());
    }
  }
  myUDP.begin(5000);
}

void AP_setup()
{
  WiFi.mode(WIFI_AP_STA);
  WiFi.softAPdisconnect(true);
  WiFi.softAPConfig(apIP, ap_gateway, IPAddress(255, 255, 255, 0));
  WiFi.softAP("vimass", "12345678");
  pc_ip = bcast_ip;
  my_ip = apIP;
  myUDP.begin(5000);
}

void UDP_receive()
{
  int16 n = myUDP.parsePacket();
  String s = "";
  if (n)
  {
    myUDP.read(udp_in_buf, sizeof(udp_in_buf));
    if (n != sizeof(udp_rx))
      return;
    if (get_bcc(udp_in_buf, n) != 0x55)
      return;
    memcpy(&udp_rx.bcc, udp_in_buf, sizeof(udp_rx));
    if (udp_rx.pkt_type == PC_BCAST)
    {
      r_port = myUDP.remotePort();
      pc_ip = myUDP.remoteIP();
      pc_ip_cnt = 500;
      return;
    }
    String sss = "";
    uint8 n8, n;
    for (int i = 0; i < sizeof(udp_in_buf); i++)
    {

      n8 = udp_in_buf[i];
      n = (n8 >> 4) & 0xf;
      sss += s_hex.substring(n, n + 1);
      n = n8 & 0xf;
      sss += s_hex.substring(n, n + 1);
    }
# 105 "D:/1.Work/ESP32/VR2ESP32/src/Wifi.ino"
    if (udp_rx.pkt_type == PC_01)
      cmd_switch();
  }
}

void string_send(String s)
{
  int len = s.length();
  uint8 buf[len];
  for (int i = 0; i < len; i++)
  {
    buf[i] = s.charAt(i);
  }
  memcpy(udp_tx.data_rx.data, buf, len);
  udp_tx.pkt_type = FS01_STRING;
  udp_tx.data_rx.len = len;
  uni_send(&udp_tx.bcc, sizeof(udp_tx));
}
uint8 get_bcc(uint8 *buf, int len)
{
  uint8 bcc = 0;
  for (int i = 0; i < len; i++)
  {
    bcc ^= *buf++;
  }
  return bcc;
}

void bcast_send(uint8 *buf, int len)
{
  buf[0] = 0x55;
  buf[0] = get_bcc(buf, len);
  myUDP.beginPacket(bcast_ip, r_port);
  myUDP.write(buf, len);
  myUDP.endPacket();
}
void uni_send(uint8 *buf, int len)
{
  buf[0] = 0x55;
  buf[0] = get_bcc(buf, len);
  myUDP.beginPacket(pc_ip, r_port);
  myUDP.write(buf, len);
  myUDP.endPacket();
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/bip.ino"
# 16 "D:/1.Work/ESP32/VR2ESP32/src/bip.ino"
void setbip(int n)
{
    switch (n)
    {
    case Cham_the:
        bip(1, 2);
        break;
    case Nhac_the:
        bip(2, 1);
        break;
    case Cham_van_tay:
        bip(1, 3);
        break;
    case Thanh_Cong:
        bip(2, 1);
        break;
    case Loi:
        bip(3, 1);
        break;
    }
}

void bip(int len, int type)
{

    for (int i = 0; i < len; i++)
    {
        coi_on;
        delay(75 * type);
        coi_off;
        delay(75 * type);
    }
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/file.ino"
#include "vimass.h"

bool write_buf(String f_name, uint8 *buf, int16 len)
{

  File f = SPIFFS.open(f_name, "w");
  while (f.available())
  {
    f.write(buf, len);
    f.close();
    return true;
  }
  return false;
}

bool read_buf(String f_name)
{


  File f = SPIFFS.open(f_name, "r");
  while (f.available())
  {
    voice_len = f.size();
    f.read(ima_buf, voice_len);
    f.close();
    return true;
  }
  return false;
}
bool rename(String s_src, String s_dst)
{
  return SPIFFS.rename(s_src, s_dst);
}
bool remove(String fname)
{
  return SPIFFS.remove(fname);
}
String list_file()
{
  String s = "file list:\n", name;
  File f;
  for (int i = 0; i < 16; i++)
  {
    name = "/a_" + String(i) + ".wav";
    if (SPIFFS.exists(name))
    {
      s += name;
      s += ":";
      f = SPIFFS.open(name, "r");
      s += String(f.size() * 4) + "\n";
      f.close();
    }
  }
  return s;
}
void read_ssid()
{
  String s[16];
  int k;
  for (k = 0; k < 4; k++)
  {
    str_name[k] = str_pass[k] = "";
  }
  k = 0;
  File f = SPIFFS.open("/ssid.txt", "r");
  while ((f.available()) && (k < 8))
  {
    s[k] = f.readStringUntil(',');
    if (k)
      s[k].remove(0, 1);
    if (s[k].startsWith(","))
      s[k].remove(0, 1);
    if (s[k].endsWith(","))
      s[k].remove(s[k].length() - 1, 1);
    k++;
  }
  for (k = 0; k < 4; k++)
  {
    str_name[k] = s[k * 2];
    str_pass[k] = s[k * 2 + 1];
  }
  f.close();
}
void save_ssid(String s)
{
  File f = SPIFFS.open("/ssid.txt", "w");
  if (f)
    f.print(s);
  f.close();
  led_reset = 15;
}

void read_TBTTId()
{
  String s[16];
  int k = 0;
  tbttid[0] = "262626";
  File f = SPIFFS.open("/tbttid.txt", "r");
  while ((f.available()) && (k < 8))
  {
    s[k] = f.readStringUntil('_');

    tbttid[0] = s[k];
    k++;
  }


  f.close();
}

void read_iplocal()
{
  String s[16];
  int k = 0;
  iplocal[0] = "";
  File f = SPIFFS.open("/iplocal.txt", "r");

  while ((f.available()) && (k < 8))
  {
    s[k] = f.readStringUntil('_');


    iplocal[0] = s[k];
    k++;
  }


  f.close();
}

void save_TBTTId(String s)
{
  File f = SPIFFS.open("/tbttid.txt", "w");
  if (f)
    f.print(s);
  f.close();
  led_reset = 15;
}

void ghimatbi(String s)
{
  File f = SPIFFS.open("/hello.txt", "w");
  if (f)
    f.print(s);
  f.close();
}

void docmatbi()
{
  File f = SPIFFS.open("/hello.txt", FILE_READ);
  while (f.available())
  {
    ma_tbi = f.read();
    f.close();
    uart0.println("..." + f.read());
    return;
  }
}
void ghivantay2(String s)
{
  File f = SPIFFS.open("/vantay.txt", "a");
  if (f)
    f.print(s);
  f.close();
}
void save_iplocal(String s)
{
  File f = SPIFFS.open("/iplocal.txt", "w");
  if (f)
    f.print(s);
  f.close();
  led_reset = 15;
}

void save_cfg(String s)
{
  File f = SPIFFS.open("/cfg.txt", "w");
  if (f)
    f.print(s);
  f.close();
  led_reset = 15;
}

void save_id()
{

  File f = SPIFFS.open("/id.txt", "w");
  if (f)
  {
    f.print(String(my_id));
  }
  f.close();
  led_reset = 15;
}

void checkCardOffline(String cardInput)
{
  TrangThaiCacheCard = false;
  File f = SPIFFS.open("/cardOpenDoorOffline.txt", "r");
  String card = "";




  while ((f.available()))
  {
    card = f.readStringUntil('_');



    if (card.equals(cardInput))
    {
      TrangThaiCacheCard = true;
      break;
    }
  }
  f.close();
}

void save_cardOpenDoorOffline(String s)
{
  File f = SPIFFS.open("/cardOpenDoorOffline.txt", "w");
  if (f)
    f.print(s);
  f.close();
  led_reset = 15;
}

void writeFile(fs::FS &fs, const char *path, const char *message)
{


  File file = fs.open(path, FILE_WRITE);
  if (!file)
  {
    Serial.println("− failed to open file for writing");
    return;
  }
  if (file.print(message))
  {
    Serial.println("− file written");
  }
  else
  {
    Serial.println("− frite failed");
  }
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/fs01_cmd.ino"
#include "vimass.h"
void get_tx_cks(int16 len)
{
    uint8 *ptr;
    uint16 cks = 0;
    if (len <= 2)
    {
        ptr = cmd_tx.prefix;
        for (int i = 0; i < (int)(sizeof(cmd_tx)) - 2; i++)
        {
            cks += *ptr++;
        }
        cmd_tx.cks = cks;
    }
    else if (len == 498)
    {
        ptr = data_tx.prefix;
        for (int i = 0; i < 6 + len; i++)
        {
            cks += *ptr++;
        }
        data_tx.data[len >> 1] = cks;
    }
}

int16 get_rx_cks(int16 len)
{
    int16 cks = 0;
    uint8 *ptr;
    if (len <= 2)
    {
        ptr = cmd_rx.prefix;
        for (int i = 0; i < (int)(sizeof(cmd_rx)) - 2; i++)
        {
            cks += *ptr++;
        }
        return (cmd_rx.cks == cks);
    }
    else
    {
        ptr = data_rx.prefix;
        for (int i = 0; i < 6 + len; i++)
        {
            cks += *ptr++;
        }
        return (cks == data_tx.data[len >> 1]);
    }
}

int16 get_cmd_len(int16 cmd)
{
    for (int i = 0; i < 38; i++)
    {
        if (cmd_len[i * 2] == cmd)
        {
            return cmd_len[i * 2 + 1];
        }
    }
    return 0;
}
void cmd_send(int16 cmd, int16 len, int16 page_id)
{
    switch (cmd)
    {
    case Verify:
    case Identify:
    case Enroll_3:
    case Enroll_1:
    case Get_Feature:
    case Verify_Feature:
    case Enroll_RAM:


    case Identify_Feature:
        fp_auto_off = 250;
        break;
    default:
        break;
    }
    switch (len)
    {
    case 0:
    case 2:
        cmd_tx.prefix[0] = cmd_prefix & 0xff;
        cmd_tx.prefix[1] = (cmd_prefix >> 8) & 0xff;
        cmd_tx.cmd = cmd;
        cmd_tx.len = len;
        memset(cmd_tx.data, 0, sizeof(cmd_tx.data));
        if (cmd == Verify_Feature)
        {
            cmd_tx.data[0] = 498;
            memcpy(char_buf, udp_rx.data, char_buf_len);
        }
        else if (cmd == Set_Security)
        {
            cmd_tx.data[0] = 2;
            cmd_tx.data[1] = 0;

        }
        else if (cmd == Get_Security)
        {
            cmd_tx.data[0] = 0;
            cmd_tx.data[1] = 0;

        }
        else if (len)
        {
            cmd_tx.data[0] = page_id;
        }
        get_tx_cks(len);
    case 14:
        break;
    case 498:
        data_tx.prefix[0] = data_prefix & 0xff;
        data_tx.prefix[1] = (data_prefix >> 8) & 0xff;
        data_tx.cmd = cmd;
        data_tx.len = len;
        memcpy(data_tx.data, char_buf, char_buf_len);
        get_tx_cks(len);
        break;
    }
      if (cmd == Enroll_1 || cmd == Enroll_3)
      {
        delay(1000);
        Play_voice(Moi_dat_van_tay);
        delay(1000);
      }
}
bool cmd_found(int16 cmd)
{
    bool b = false;
    for (int i = 0; i < sizeof(cmd_len) / 4; i++)
    {
        if (cmd == cmd_len[i * 2])
        {
            b = true;
            i = sizeof(cmd_len);
        }
    }
    return b;
}
void cmd_switch()
{
    rx_cnt = 0;







    String s = "";
    int16 len = 0;


    if ((udp_rx.cmd > 0x100) && (udp_rx.cmd < 0x151))
    {
        cmd_send(udp_rx.cmd, udp_rx.len, udp_rx.page_id);
        uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
        led_reset = 5;
        return;
    }
    switch (udp_rx.cmd)
    {
    case voice_download:

        if (udp_rx.seg_type == seg_save)
        {
            len = udp_rx.seg_len;
            if (len > ima_seg_len)
                len = ima_seg_len;
            memcpy(&ima_buf[voice_len], udp_rx.data, len);
            voice_len += len;

            remove("/a_" + String(udp_rx.page_id & 0xf) + ".wav");

            if (write_buf("/a_" + String(udp_rx.page_id & 0xf) + ".wav", ima_buf, voice_len))
                led_reset = 10;
        }
        else if (voice_len < (ima_seg_max - 1) * ima_seg_len)
        {
            if (udp_rx.seg_type == seg_begin)
            {
                voice_len = 0;
            }
            len = udp_rx.seg_len;
            if (len > ima_seg_len)
                len = ima_seg_len;
            memcpy(&ima_buf[voice_len], udp_rx.data, len);
            voice_len += len;
        }
        memcpy(udp_tx.cmd_rx.prefix, cmd_rx.prefix, sizeof(cmd_rx));
        udp_tx.pkt_type = FS01_CMD;
        udp_tx.cmd_rx.rcm = udp_rx.cmd;
        udp_tx.cmd_rx.len = voice_len;
        uni_send(&udp_tx.bcc, sizeof(udp_tx));
        break;
    case voice_play:
        if (read_buf("/a_" + String(udp_rx.page_id & 0xf) + ".wav"))
        {
            voice_init();
        }



        break;
    case file_rename:
        break;
    case file_list:
        string_send(list_file());
        break;
    case set_bip_on:
        xacthucvantay = 1;
        reset_7462("2xx3");

        break;
    case send_ev2:


        memcpy(char_buf, udp_rx.data, char_buf_len);
        char_buf_to_ev2();

        break;
    case add_ssid:
        String fl ;

        for (int i = 0; i < 10; i++)
        {
            fl = "/a_"+String(i)+".wav";
            if (remove(fl))
            {
                uart0.println("Xoa"+fl+" thanh cong");
            }else{
                uart0.println("Xoa "+fl+"  khong thanh cong");
            }
        }

        break;
    }
}
void voice_init()
{
    d_predsample = 0;
    d_index = 0;
    ima_buf_cnt = 0;
    ima_haft = 0;
    timer_init(true);
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/https.ino"
# 16 "D:/1.Work/ESP32/VR2ESP32/src/https.ino"
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

WiFiClientSecure client;
HTTPClient httpMC;
const char *server = "www.vimass.vn";
const char *status_open_door = "^6*door_open";

void send_https(String s)
{
 s = https_encode(s);
 if (str_door.startsWith("12_") || str_door.startsWith("13"))
 {
  xuLyGuiThongTinLienQuanDenDoor(s);
 }
 else
 {

  String param = "";
  if (str_lenhtbngoai.indexOf("PASS") != -1)
  {
   str_lenhtbngoai.remove(0, 5);
   str_lenhtbngoai = https_encode(str_lenhtbngoai);
   param = "51_" + idDelaySend[0] + str_lenhtbngoai;
   resetServicesStatus();
  }
  else if (str_lenhtbngoai.indexOf("YEU CAU THANH TOAN") != -1)
  {
   param = "2244_";
  }
  else if (str_lenhtbngoai != "")
  {
   str_lenhtbngoai = https_encode(str_lenhtbngoai);
   param = "50_99_dv_" + str_lenhtbngoai;
  }
  else if (idDelaySend[0] != "" && str_lenhtbngoai.indexOf("PASS") == -1 && solannhapmk < 3)
  {
   solannhapmk++;
   if (solannhapmk < 3)
   {
    udp_out_ip("105", hangdoi_Front());
   }
   else
   {
    resetServicesStatus();
   }
   return;
  }
  solannhapmk = 0;
  str_lenhtbngoai = "";

  httpMC.setReuse(true);
  httpMC.begin("http://124.158.4.173:8080/vmbank/services/TBTTService/requestComand?param=" + param + s);

  int httpCode = httpMC.GET();
  httpMC.setConnectTimeout(5000);

  if (httpCode > 0)
  {
   String sout = httpMC.getString();
   add_to_serial("server ve:" + sout + "---");
   serial_out();
   if (sout.indexOf("2x1") != -1)
   {
    udp_out_ip("106TBC010", hangdoi_Front());
   }




   if (v_stat == dv_F1)
   {
    xuLyYeuCauDichVuSauKetNoiLan1(sout);
   }
   else if (sout.startsWith("^2x1") && vuaNhapPassConfirm == 1)
   {
    vuaNhapPassConfirm = 0;
   }
   else
   {

    sout = https_decode(sout);


    add_to_serial("dang tim:" + sout);
    serial_out();
    if (sout.indexOf("$112") > 0 || sout.indexOf("$113") > 0)
    {
     khoitao_ghixacthuc(sout);
    }
    else
    {
     new_cmd(sout, https_src);
    }
   }

  }
  else
  {
   resetServicesStatus();





   new_cmd("^2x1^", https_src);
  }
  httpMC.end();
 }
}
String https_decode(String s)
{
 String s0 = "";
 int16 n;
 while (s.length())
 {
  if (s.substring(0, 1) != "%")
  {
   s0 += s.substring(0, 1);
   s.remove(0, 1);
  }
  else
  {
   n = strtol(s.substring(1, 3).c_str(), NULL, 16);
   s0 += char(n & 0x7f);
   s.remove(0, 3);
  }
 }
 return s0;
}

String ctrl_char = " !#$%&()+,/:;<=>?[]^{}|~";
String https_encode(String s)
{
 String s1, s0 = "";
 while (s.length())
 {
  s1 = s.substring(0, 1);
  s.remove(0, 1);
  if (ctrl_char.indexOf(s1) >= 0)
  {
   s0 += "%" + fix_len(String(s1.charAt(0), HEX), 2);
  }
  else
  {
   s0 += s1;
  }
 }
 return s0;
}
void confirm_service(String s)
{

 if (s.startsWith("000"))
 {
  if (idDelayConfirm[0].length() > 0)
  {
   delay(100);
   httpMC.setReuse(true);
   s = https_encode(s);
   httpMC.begin("http://124.158.4.173:8080/vmbank/services/TBTTService/requestComand?param=" + idDelayConfirm[0]);
   httpMC.setConnectTimeout(5000);
   int httpCode = httpMC.GET();

   idDelayConfirm[0] = "";
   if (httpCode <= 0)
   {
    wifi_setup();
   }
   else
   {
    String sout = httpMC.getString();
    sout = https_decode(sout);


    new_cmd(sout, https_src);
   }
  }
 }
 else
 {
  s = https_encode(s);
  idDelayConfirm[0] = idDelayConfirm[0] + "_" + s;
 }

 httpMC.end();
}

void xuLyGuiThongTinLienQuanDenDoor(String s)
{
 String param = "";
 boolean openThuong = false;
 if (str_door.startsWith("13"))
 {
  String temp = tinhCKS(passDelaySend[0]);
  param = "51_" + idDelaySend[0] + "_" + temp;
 }
 else
 {
  openThuong = true;
 }
 resetDoorStatus();
 httpMC.setReuse(true);
 httpMC.begin("http://" + iplocal[0] + ":8080/ApiPkiWeb/services/DichVuMayTram/openGate?input=" + param + s);
 httpMC.setConnectTimeout(1000);
 int httpCode = httpMC.GET();

 if (httpCode > 0)
 {
  String payload = httpMC.getString();


  if (payload.startsWith(status_open_door))
  {
   showOpenDoor(payload);
  }
  else if (payload.startsWith("^6*showPass_openDoor_"))
  {

   v_stat = dv_PASS;
   str_door = "13";
   payload.remove(0, 21);
   idDelaySend[0] = payload;

   yeu_cau_nhapmk();
  }
  else
  {
   if (openThuong)
   {
    checkOfflineCardOpenDoor(s);
   }
   else
   {
    showCloseDoor(payload);
   }
  }
 }
 else
 {



  if (openThuong)
  {
   checkOfflineCardOpenDoor(s);
  }
 }
 httpMC.end();
}

void confirmSaveCardOffline(String s)
{
 httpMC.setReuse(true);
 httpMC.begin("http://" + iplocal[0] + ":8080/ApiPkiWeb/services/DichVuMayTram/confirmListCardDoor?input=" + s);
 httpMC.setConnectTimeout(5000);
 int httpCode = httpMC.GET();
 if (httpCode > 0)
 {
 }




 httpMC.end();
}

void door_service(String s)
{
}

void xuLyYeuCauDichVuSauKetNoiLan1(String payload)
{
 if (payload.startsWith("^2x1"))
 {

 }
 else if (payload.startsWith("^6*showPass_"))
 {
  v_stat = dv_PASS;
  str_door = "15";
  payload.remove(0, 12);
  idDelaySend[0] = payload;
  yeu_cau_nhapmk();
 }
 else
 {
  resetServicesStatus();
  new_cmd(payload, https_src);
 }
}

void payment_confirmation(String s)
{
 magiaodich = "";
 httpMC.setReuse(true);
 s = https_encode(s);
 httpMC.begin("http://124.158.4.173:8080/vmbank/services/TBTTService/requestComand?param=" + s);
 httpMC.setConnectTimeout(5000);
 int httpCode = httpMC.GET();
 idDelayConfirm[0] = "";
 httpMC.end();
}

void get_vantay(String data)
{
 String uid1 = "1";
 if (WiFi.status() == WL_CONNECTED)
 {
  httpMC.setReuse(true);
  httpMC.begin("http://210.245.8.7:12317/api/"+ data);

  int httpCode = httpMC.GET();
  httpMC.setConnectTimeout(5000);
  if (httpCode > 0)
  {
   String sout = httpMC.getString();
   Serial.println("http out:" + sout);
   if (sout.equals(uid1) == 1)
   {


   }
   else
   {
    bipok2();
   }
  }
  httpMC.end();
 }
 else
 {
  bip4_no_internet();

  wifi_setup();
 }
}
void getms(String data)
{
 String uid1 = "1";
 if (WiFi.status() == WL_CONNECTED)
 {
  httpMC.setReuse(true);

  httpMC.begin("http://210.245.8.7:12317/api/"+ data);

  int httpCode = httpMC.GET();
  httpMC.setConnectTimeout(5000);
  uart0.println(httpCode);
  if (httpCode > 0)
  {
   String sout = httpMC.getString();
   Serial.println("http out:" + sout);
   if (sout.equals(uid1) == 1)
   {
    Play_voice(Xin_cam_on);
    mocua();
   }
   else
   {
    if (sout.equals("err4"))
    {
     mocua();
    }
    else
    {
     dongcua();
    }
   }
  }
  else
  {
   mocua();
  }
  httpMC.end();
 }
 else
 {
  bip4_no_internet();
  mocua();
  wifi_setup();
 }
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/ima16.ino"
#include "vimass.h"


const int16 Index_Table[16] = {
    -1, -1, -1, -1, 2, 4, 6, 8,
    -1, -1, -1, -1, 2, 4, 6, 8
};

const int16 Step_Table[89] = {
    7, 8, 9, 10, 11, 12, 13, 14, 16, 17,
    19, 21, 23, 25, 28, 31, 34, 37, 41, 45,
    50, 55, 60, 66, 73, 80, 88, 97, 107, 118,
    130, 143, 157, 173, 190, 209, 230, 253, 279, 307,
    337, 371, 408, 449, 494, 544, 598, 658, 724, 796,
    876, 963, 1060, 1166, 1282, 1411, 1552, 1707, 1878, 2066,
    2272, 2499, 2749, 3024, 3327, 3660, 4026, 4428, 4871, 5358,
    5894, 6484, 7132, 7845, 8630, 9493, 10442, 11487, 12635, 13899,
    15289, 16818, 18500, 20350, 22385, 24623, 27086, 29794, 32767
};
#define ima_max 32767
#define index_max 88


int16 IRAM_ATTR decoder(uint8 code)
{int16 step,diffq;
    code &= 0xf;
    step = Step_Table[d_index];
    diffq = step >> 3;
    if(code & 4) diffq += step;
    if(code & 2) diffq += (step >> 1);
    if(code & 1) diffq += (step >> 2);
    if(code & 8) d_predsample -= diffq;
    else d_predsample += diffq;
    if(d_predsample > ima_max) d_predsample = ima_max;
    else if(d_predsample < -ima_max) d_predsample = -ima_max;
    d_index += Index_Table[code];
    if(d_index < 0) d_index = 0;
    if(d_index > index_max) d_index = index_max;
    return((int16)d_predsample);
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/ota_init.ino"
void ota_init(){






  ArduinoOTA.setPassword("12345678");

  ArduinoOTA.onStart([]() {
    String type;
    if (ArduinoOTA.getCommand() == U_FLASH) {
      type = "sketch";
    } else {
      type = "filesystem";
    }



  });
  ArduinoOTA.onEnd([]() {

  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {

  });
  ArduinoOTA.onError([](ota_error_t error) {
# 41 "D:/1.Work/ESP32/VR2ESP32/src/ota_init.ino"
  });
  ArduinoOTA.begin();




}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/timer.ino"
void set_pwm_val(int16 n16)
{
 if (n16 < 0)
  n16 = 0;
 if (n16 > 511)
  n16 = 511;
 ledcWrite(pwm_ch, n16);
}

void pwm_init()
{
 ledcSetup(pwm_ch, freq, pwm_bit);
 ledcAttachPin(pwm_pin, pwm_ch);
 ledcWrite(pwm_ch, zero_level);
}
void timer_init(bool on_timer)
{
 if (on_timer)
 {
  timer = timerBegin(3, 1, true);
  timerAttachInterrupt(timer, &onTimer, true);
  timerAlarmWrite(timer, 40 * 125, true);
  timerAlarmEnable(timer);
  pwm_on = 1;
 }
 else
 {
  ledcWrite(pwm_ch, zero_level);
  timerDetachInterrupt(timer);
  timerEnd(timer);
  pwm_on = 0;
  timer = NULL;
 }
}
void IRAM_ATTR onTimer()
{



 if (bip_on)
 {
  set_pwm_val(sin8[--bip_on & 7] + zero_level);
  if (bip_on == 0)
   timer_init(false);
 }
 else
 {
  if (ima_buf_cnt < voice_len)
  {
   if (ima_haft == 0)
   {
    pwm_tmp = ima_buf[ima_buf_cnt];
    pwm_val = decoder(pwm_tmp >> 4);
    ima_haft = 1;
   }
   else
   {
    pwm_val = decoder(pwm_tmp);
    ima_haft = 0;
    ima_buf_cnt++;
   }
   pwm_val >>= 7;
   set_pwm_val(pwm_val + zero_level);
  }
  else
  {
   timer_init(false);
  }
 }
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/v_UDP.ino"
# 20 "D:/1.Work/ESP32/VR2ESP32/src/v_UDP.ino"
void yeu_cau_nhapmk(){

  bipok1();

  udp_out_ip("105",hangdoi_Front());
}

void udp_out_ip(String sout,String ipout)
{


  sout = str_idtb(my_id)+"^"+sout+ "_" +bcc_check_step(sout+ "_" ,6);
  udp_time = 0;
  int t[4],i=0;
  for(i = 0; i < 4;i++)
  {
    t[i] = ipout.substring(0,3).toInt();
    ipout.remove(0,3);
  }
  IPAddress ip(t[0], t[1], t[2], t[3]);
  if (sout.length())
  {
    uint8 buf[sout.length()], *ptr;
    ptr=buf;
    for (int i=0;i<(int)sizeof(buf);i++)
    { *ptr++=sout.charAt(i);
    }
    myUDP.beginPacket(ip,6000);
    myUDP.write(buf, sizeof(buf));
    myUDP.endPacket();
    sout = "";
  }
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/v_cmd.ino"
void new_cmd(String s0,uint8 src)
{

 int k;
 String s,s1;
 while(s0.startsWith("^"))
 { s0.remove(0,1);
  k=s0.indexOf("^");
  if (k >= 0)
  { s1=s0.substring(0,k);
   s0.remove(0,k);
   k=s1.charAt(0);
   s1.remove(0,1);
   switch(k)
   {
    case pc_to_lcd:
     if (s1.length())
          {
          }
    case nfc_to_lcd:
        if (s1.length())
          {
          }
     break;
    case wifi_reset:
       WiFi.disconnect(true);
        delay(2000);
       ESP.restart();
     break;
    case rs485_query:


     break;
    case pc_to_nfc:
     resetServicesStatus();

     serial2_out += "!^2" + s1 + "#";


     uart0.println("du_1:"+serial2_out);
     break;
    case pc_to_https:

       send_https(s1);
     break;
    case ram_write:
     ram_wr(s1);
     break;
    case wifi_write:
     save_ssid(s1);
     break;
    case pc_to_esp:

     while(s1.startsWith("*"))
     {
      s1.remove(0,1);
      k=s1.indexOf("*");
      if (k >= 0)
      {
       s=s1.substring(0,k);
       s1.remove(0,k);


       caidatthietbi(s);
      }
      else
      { s1="";
      }
     }
     break;
   }
  }
  else
  { s0="";
  }
 }

}

void resetServicesStatus()
{

 Validate = false;



 str_door = "";
 v_stat=fx_waiting;
 dataServices[0] = "";
 strdvtt="";
 str_lenhtbngoai="";
 idDelaySend[0]="";
 solannhapmk=0;
}

void ram_rd(String s)
{ for(int i=0;i<v_fx.dv_index_max;i++)
 { if (s.length() < 3500) s += "dv"+n_fix_len(i,2)+dv_td[i]+"_";
 }

 for(int i=0;i<v_fx.ds_index_max;i++)
 { s += "ds"+n_fix_len(i,2)+"_";
  for (int j=0;j<v_fx.sub_ds_index_max[i];j++)
  { if (s.length() < 3500) s += ds_name[i][j]+"_";
  }
 }

}

void new_time(String s)
{ s.remove(0,5);
 if (s.length() > 5)
 { ms64=millis();
  n_time[0]=n_time[3]=s.substring(0,2).toInt();
  s.remove(0,2);
  n_time[1]=n_time[4]=s.substring(0,2).toInt();
  s.remove(0,2);
  n_time[2]=n_time[5]=s.substring(0,2).toInt();
 }
}
String n_fix_len(int16 n,int16 len)
{ return fix_len(String(n),len);
}

String fix_len(String s,int16 len)
{ if (s.length() > len) s=s.substring(s.length()-len,s.length());
 while (s.length() < len) { s = "0"+s;}
 return s;
}

void ram_wr(String s)
{
 String s0;
 int k;
 while(s.startsWith("*"))
 { s.remove(0,1);
  k=s.indexOf("*");
  if (k >= 0)
  { s0=s.substring(0,k);
   s.remove(0,k);
     }
     else
     { s="";
     }
 }
 v_stat=dv_selecting;


}
String bcc_check_len(String s,int a)
{ int32 bcc=0;
 for (int i=0;i<s.length();i++) { bcc += (uint8)s.charAt(i);}
 return fix_len(String(bcc),a);
}
String bcc_check_step(String s, int step){
 int32 bcc=0;
 int32 tong = 0;
 int i = 0;
 for (i=0;i<s.length();i++){
  bcc = (uint8)s.charAt(i);
  if(i % step == 0) bcc = bcc + ( i / step) + 3;
  tong += bcc;
 }
 return fix_len(String(tong),4);
}

void add_to_serial(String s)
{
  serial_rs485 = s;
}
void serial_out()
{
  if (serial_rs485.length())
  {
    rs485_tx_out=127;
    rs485_out;
    Serial.print(serial_rs485);
    serial_rs485="";
  }
}

void khoitao_ghixacthuc(String s){

 dau_dlxacthuc = s.substring(1,20);
 s.remove(0,20);
 dulieughixacthuc = s;
 s="";
 trangthailenhtumaytinh = 1;

}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/v_door.ino"
void showOpenDoor(String s)
{
 door_open;
 door_cnt = 1;
 bipok1();


 xuLyDanhSachThe(s);
}


void showCloseDoor(String s)
{
 door_close;
 door_cnt = 0;
 biper1();




}

void resetDoorStatus()
{
   str_door = "";
   v_stat = fx_waiting;
}

void xuLyDanhSachThe(String s)
{
 if(s.length() > 12)
 {
  s.remove(0, 12);
 }
 if(s.length() > 10)
 {
  String deviceId = "";
  if(s.startsWith("_"))
  {
   s.remove(0,1);
  }
  int n=s.indexOf("_");
  deviceId=s.substring(0,n);
  s.remove(0,n);

  save_cardOpenDoorOffline(s);

  confirmSaveCardOffline(deviceId);
 }
}

void checkOfflineCardOpenDoor(String s)
{
 if(s.startsWith("35_"))
 {
  s= https_decode(s);
  int n=s.indexOf("_");
  String funcId=s.substring(0,n);
  s.remove(0,n);
  if(s.startsWith("_"))
  {
   s.remove(0,1);
  }




  n=s.indexOf("_");
  String uid=s.substring(0,n);
  s.remove(0,n);
  if(s.startsWith("_"))
  {
   s.remove(0,1);
  }
  n=s.indexOf("_");
  String tbttId=s.substring(0,n);
  s.remove(0,n);
  if(s.startsWith("_"))
  {
   s.remove(0,1);
  }

  n=s.indexOf("_");
  String cks1=s.substring(0,n);
  s.remove(0,n);
  if(s.startsWith("_"))
  {
   s.remove(0,1);
  }

  n=s.indexOf("_");
  String cks2=s.substring(0,n);
  s.remove(0,n);
  if(s.startsWith("_"))
  {
   s.remove(0,1);
  }

  n=s.indexOf("_");
  String cks3=s.substring(0,n);
  s.remove(0,n);
  if(s.startsWith("_"))
  {
   s.remove(0,1);
  }

  n=s.indexOf("_");
  String vidInput=s.substring(0,n);
  s.remove(0,n);
  if(s.startsWith("_"))
  {
   s.remove(0,1);
  }

  vidInput.replace(" ", "");
  vidInput.replace("%20", "");

  TrangThaiCacheCard = false;
  checkCardOffline(vidInput);

  if(TrangThaiCacheCard)
  {
   showOpenDoor("");
  }
  else
  {
   showCloseDoor("");
  }
 }
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/v_queue.ino"
String hangdoi_Front(){

 int len=0;
 while(hang_doi[hang_doi_front] == "" && len <= hang_doi_tong){
     hang_doi_front = (hang_doi_front + 1) % hang_doi_tong;
  hang_doi_sothietbidangdoi = hang_doi_sothietbidangdoi - 1;
  len++;
 }
 return hang_doi[hang_doi_front];
}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/v_serial.ino"
int16 fs_01_cks(uint8 *buf, int16 len, int16 k)
{
 int16 cks = 0;
 for (int i = 0; i < len - 2; i++)
 {
  cks += buf[i];
 }
 if (k)
 {
  memcpy(&buf[len - 2], &cks, 2);
 }
 return cks;
}

void fp_lock()
{
 if (++fp_fail > 5)
 {
  fp_off = fp_off_max;
  fp_fail = 0;
 }
}
void serial_test()
{
 while (uart1.available())
 {
  int16 n;
  while (uart1.available())
  {
   n = uart1.read();
   if (n != -1)
   {
    rx_buf[rx_cnt++] = n & 0xff;

    rx_cnt &= rx_max - 1;
    if (!hd_ok && (rx_cnt >= 2))
    {
     memcpy(&n_prefix, rx_buf, 2);
     if ((n_prefix == cmd_response_prefix) || (n_prefix == data_response_prefix))
     {
      hd_ok = 1;
      rx_pkt_len = -1;
     }
     else
     {
      rx_cnt = 0;
     }
    }
    if (hd_ok)
    {

     if (rx_cnt >= 6)
     {
      if (rx_pkt_len == -1)
      {
       memcpy(&rx_pkt_len, &rx_buf[4], 2);
      }
     }
     if (n_prefix == cmd_response_prefix)
     {

      if (rx_cnt == 24)
      {

       memcpy(cmd_rx.prefix, rx_buf, sizeof(cmd_rx));

       ret = cmd_rx.data[0];
       ret_code = cmd_rx.data[1];



       memcpy(udp_tx.cmd_rx.prefix, cmd_rx.prefix, sizeof(cmd_rx));
       if (ret == 0)
       {
        switch (cmd_rx.rcm)
        {
        case Test_Connection:
         fs01_on = 1;
         break;
        case Verify_Feature:

         cmd_send(Verify_Feature, 498, 0);
         uart1.write(data_tx.prefix, 498 + 8);
         break;
        case Read_Page:
         break;

        case Identify:

         if (ret_code == -12)
          break;
         if (ret_code > 0)
         {
          Play_voice(Xin_cam_on);
          mocua();

          String page = String(ret_code);
          uart0.println("ma_vt" + page);
          data_chamcong = "getAccessDoor?fpIndex=" + page + "&&readercode=" + ma_tbi;

          get_vantay(data_chamcong);
         }
         break;
        case Enroll_RAM:






         if (ret_code == -15 || ret_code == -13)
         {
          delay(1000);
          Play_voice(Moi_dat_van_tay);
         }
         if (ret_code == 0)
         {

          reset_7462("2x7");
          cmd_send(Get_Enroll, 0, 0);
          uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
         }
         break;
        case Enroll_1:






         break;


        case Enroll_3:
         if (ret_code == -13)
         {
          delay(1000);
          Play_voice(Moi_dat_van_tay);
         }
         if (ret_code > 0)
         {
          delay(1000);
          Play_voice(Thanh_cong);
         }

         break;
        }
       }
       else
       {


        switch (cmd_rx.rcm)
        {
        case Test_Connection:
         fs01_on = 1;
         break;
        case Verify_Feature:

         break;
        case Read_Page:
         break;

        case Identify:

         break;
        case Enroll_RAM:

         break;

        case Enroll_1:
         if (cmd_rx.data[1] > 1)
          break;
         Play_voice(Khong_thanh_cong);
         break;
        }
       }
       hd_ok = rx_cnt = 0;
       udp_tx.pkt_type = FS01_CMD;
       uni_send(&udp_tx.bcc, sizeof(udp_tx));
      }
     }
     else if (n_prefix == data_response_prefix)
     {

      if (rx_cnt == (6 + rx_pkt_len + 2))
      {

       memcpy(data_rx.prefix, rx_buf, sizeof(data_rx));
       ret = rx_buf[9];
       ret_code = data_rx.data[1];
       memcpy(udp_tx.data_rx.prefix, data_rx.prefix, sizeof(data_rx));

       if (ret > 0)
       {

        String sss = "";
        uint8 n8, n;
        for (int i = 0; i < 498; i++)
        {

         n8 = rx_buf[i + 8];
         n = (n8 >> 4) & 0xf;
         sss += s_hex.substring(n, n + 1);
         n = n8 & 0xf;
         sss += s_hex.substring(n, n + 1);
        }
        ghivantay = 1;


        ghivantayvaoESP32(sss);
       }
       else
       {

       }
       hd_ok = rx_cnt = 0;
       udp_tx.pkt_type = FS01_DATA;
       uni_send(&udp_tx.bcc, sizeof(udp_tx));
      }
     }
    }
   }
  }
 }
}

void serial2_test()
{
 if (Serial2.available())
 {
  String s;
  int n;
  while (Serial2.available())
  {
   n = Serial2.read();

   if (n != -1)
   {
    serial2_in += (char)(n & 0xff);

    if (xacthucvantay == 1 || xacthuckhuonmat == 1 || xacthutiengnoi == 1)
    {
     if (serial2_in.endsWith("!"))
     {
      if (serial2_in.startsWith("^5") || serial2_in.startsWith("^6") || serial2_in.startsWith("^7"))
      {
       serial2_in = serial2_in;
      }
      else
      {
       serial2_in = "";
      }
     }
     else if (serial2_in.endsWith("***"))
     {

      serial2_in.remove(serial2_in.length() - 3, 3);
      if (serial2_in.substring(0, 1) == "!")
       serial2_in.remove(0, 1);

      add_to_serial("7462 nhan1" + hextostr(serial2_in));
      serial_out();
      serial2_in = "";
      if (serial2_in.startsWith("^5"))
      {
       uart0.println("thanh cong");
       setbip(Thanh_Cong);
       uart0.println("data tieng noi" + hextostr(data_khuonmat));
      }
      if (serial2_in.startsWith("^7") && xacthucvantay == 1)
      {
# 287 "D:/1.Work/ESP32/VR2ESP32/src/v_serial.ino"
      }
      else if (serial2_in.startsWith("^5") && xacthuckhuonmat == 1)
      {
      }
      else if (serial2_in.startsWith("^6") && xacthutiengnoi == 1)
      {


      }
     }
    }
    else
    {
     if (serial2_in.endsWith("!"))
     {
      serial2_in = "";
     }

     else if (serial2_in.endsWith("#"))
     {

      serial2_in.remove(serial2_in.length() - 1, 1);




      if (serial2_in.startsWith("^1"))
      {
       if (ghivantay == 1)
       {
        reset_7462("2x7");
       }
       if (serial2_in.startsWith("^135"))
       {
        uid_the = serial2_in.substring(5, 19);
        vid_the = serial2_in.substring(76, 83);
        vid_the.replace(" ", "");

        if (ghi_ma_tbi == 1)
        {
         ma_tbi = serial2_in.substring(20, 53);
         add_to_serial("ma_tbi:" + ma_tbi);
         serial_out();
         ghimatbi(ma_tbi);
         ghi_ma_tbi = 0;
        }
        data_chamcong = "getAccessDoorByCard?vid=" + vid_the + "&readercode=" + ma_tbi;

       }
       TrangThaiThanhToan = false;
       magiaodich = "";
       String s = serial2_in;
       s.remove(0, 2);



       if (s.startsWith("cfs"))
       {
        s.remove(0, 3);
        if (wifi_on)
         confirm_service(s);
       }
       else
       {
        reset_7462("2xx2");


        xacthutiengnoi = 1;





       }
      }
      else if (serial2_in.startsWith("^5"))
      {


      }
      else if (serial2_in.startsWith("^6"))
      {
       String s;
       if (demghi == 0)
        break;
       serial2_out = "!^2" + uid_the + "$114000" + fp_save[demghi] + "$" + tinhCKS_Du("2" + uid_the + "$114000" + fp_save[demghi], 5) + "#";
       uart0.println("ghi lan tiep theo," + String(demghi) + "," + serial2_out);
       demghi++;
       if (demghi > 4)
       {
        demghi = 0;
        ghivantay = 0;

       }
      }
      else if (serial2_in.startsWith("^8"))
      {
      }
      else if (serial2_in.startsWith("^4"))
      {
       String sout = "";

       setbip(Thanh_Cong);


       serial2_in.remove(0, 3);
       if (duong_ra == ra_udp && hangdoi_Front() != "")
       {
        udp_out_ip("100" + serial2_in + "#", hangdoi_Front());
       }
      }
      serial2_in = "";
     }
    }
    if (serial2_in.length() > rx_max)
     serial2_in.clear();
   }
  }
 }
}

void serial2_out_test()
{
 int len;
 if (uart2.availableForWrite() >= 127)
 {
  ms5 &= 7;
  if (ms5)
  {
   if (--ms5 == 0)
   {
    String s = "";
    if (serial2_out.length() > 123)
    {
     s = serial2_out.substring(0, 124);

     serial2_out.remove(0, 124);
    }
    else if (serial2_out.length())
    {
     s = serial2_out;
     serial2_out = "";
     len = (s.length() & 0x7c) + 4;
     if (len > 124)
      len = 124;
     while (s.length() < len)
     {
      s += "0";
     }
    }
    if (s.length())
    {
     uart2.print(s);
     ms5 = 4;
    }
   }
  }
  else if (serial2_out.length())
  {
   ms5 = 4;
  }
 }
}


void char_buf_to_ev2()
{
 String s = "", snew, snew1 = "2" + uid_the + "$114000";
 uint8 n8, n;
 for (int i = 0; i < char_buf_len; i++)
 {
  n8 = char_buf[i];
  n = (n8 >> 4) & 0xf;
  s += s_hex.substring(n, n + 1);
  n = n8 & 0xf;
  s += s_hex.substring(n, n + 1);
 }
 s += "0000";

 for (int i = 1; i < 5; i++)
 {
  fp_save[i] = s.substring(0, 250);
  s.remove(0, 250);
 }

 serial2_out = "!^" + snew1 + fp_save[1] + "$" + tinhCKS_Du(snew1 + fp_save[1], 5) + "#";

}

uint8 hex_to_byte(String s)
{
 s.toUpperCase();
 uint8 n8;
 int n;
 n = s_hex.indexOf(s.substring(0, 1));
 n8 = (n != -1) ? n : 0;
 n8 <<= 4;
 n = s_hex.indexOf(s.substring(1, 2));
 n8 |= (n != -1) ? n : 0;
 return n8;
}

String tinhCKS_Du(String s, int n)
{
 int32 bcc = 0;
 for (int i = 0; i < s.length(); i++)
 {
  bcc += (uint8)s.charAt(i);
 }
 return fix_len(String(bcc), n);
}

void XTvanTay(String strvt)
{
 if (strvt.length() == char_buf_len)
 {
  bipok1();
  for (int i = 0; i < char_buf_len; i++)
  {
   char_buf[i] = (int)strvt.charAt(i);
  }
  uart0.println("Vao xt vantay:");
  cmd_send(Verify_Feature, 498, 0);
  uart1.write(data_tx.prefix, 498 + 8);
  Play_voice(Moi_dat_van_tay);
  led_reset = 5;
 }
}

String hextostr(String s1)
{
 String s = "";
 uint8 n8, n;
 for (int i = 0; i < s1.length(); i++)
 {
  n8 = s1.charAt(i);
  n = (n8 >> 4) & 0xf;
  s += s_hex.substring(n, n + 1);
  n = n8 & 0xf;
  s += s_hex.substring(n, n + 1);
 }
 return s;
}

void ghivantayvaothe(String vantay)
{

 setbip(Cham_the);



 String s = "", snew1 = "2" + uid_the + "$114000";
 vantay += "0000";
 uart0.println(vantay);
 for (int i = 1; i < 5; i++)
 {
  fp_save[i] = vantay.substring(0, 250);
  vantay.remove(0, 250);
 }
 demghi = 1;
}
void ghivantayvaoESP32(String vantay)
{
 String s = "*" + vid_the + vantay;
 ghivantay2(s);
}
void FS01_RES(String s1)
{
 String sss = "";
 uint8 n8, n;
 for (int i = 0; i < rx_cnt; i++)
 {

  n8 = cmd_rx.prefix[i];
  n = (n8 >> 4) & 0xf;
  sss += s_hex.substring(n, n + 1);
  n = n8 & 0xf;
  sss += s_hex.substring(n, n + 1);
 }

}
# 1 "D:/1.Work/ESP32/VR2ESP32/src/v_untils.ino"
void caidatthietbi(String s){


 if (s.startsWith("id_"))
 {
  s.remove(0,3);
  my_id=s.substring(0,5).toInt();
  if (my_id < soluongthietbi && my_id > 0){
   save_id();
      bipok1();
      udp_out_ip("106TBC011", hangdoi_Front());
  }else{
   my_id=0;
   save_id();
   biper1();
  }
 }
 else if (s.startsWith("cfg_"))
 { s.remove(0,4);
  save_cfg(s);
  bipok1();
  udp_out_ip("106TBC011", hangdoi_Front());

 }

 else if(s.startsWith("dsChoThanhToan_"))
 {
  TrangThaiThanhToan = true;
  s.remove(0,14);
 }
 else if(s.startsWith("thongbaotrangthai_"))
 {
  s.remove(0,17);
  udp_out_ip("106TBCSV_"+s, hangdoi_Front());
 }

  else if(s.startsWith("showPass_"))
 {
  s.remove(0,9);
  idDelaySend[0] = s;
  yeu_cau_nhapmk();
 }
 else if(s.startsWith("iplocalw_"))
 {
  s.remove(0,9);
  save_iplocal(s);
  bipok1();
  udp_out_ip("106TBC011", hangdoi_Front());
 }
 else if(s.startsWith("serialId_"))
 {
  s.remove(0,9);
  save_TBTTId(s);
  bipok1();
  udp_out_ip("106TBC011", hangdoi_Front());
 }
 else if (s.startsWith("wifiw_"))
 {
  s.remove(0,6);
  if(s.length() > 10)
  {
   save_ssid(s);
   bipok1();
   udp_out_ip("106TBC011", hangdoi_Front());
  }
 }

 else if (s.startsWith("wifir"))
 { s="wifir";
  for (int i=0;i<8;i++)
  { s += str_name[i]+"_"+str_pass[i]+"_";
  }
  if(v_cfg.media==https_media) {}
  else if(v_cfg.media==rs485_media){}
 }
 else if (s.startsWith("gett_"))
 {
 }
 else if (s.startsWith("sett_"))
 { new_time(s);
 }
 else if (s.startsWith("ramcl_"))
 {
 }
 else if (s.startsWith("ramrd_"))
 { s.remove(0,6);
  ram_rd(s);
 }
 else if(s.startsWith("dichvumaytram_"))
 {
  s.remove(0,14);
  DichVuMayTram = true;
  strdichvumaytram = s;
 }
 else if (s.startsWith("door_open")){
  mocua();
 }
 else if (s.startsWith("door_close")){

  door_close;
  biper1();
 }
}

String str_idtb(int a){
 String b;
 b = fix_len(String(a),5);
 return b;
}

String tinhCKS(String s)
{
 int32 bcc=0;
 for (int i=0;i<s.length();i++)
 {
  bcc += (uint8)s.charAt(i);
 }
 return fix_len(String(bcc),3);
}