// strcpy(ssid_name,str_name.c_str());
// String(int,HEX); dec to HEX
// n=strtol(s.c_str(),NULL,16); HEX to decimal	
#include "vimass.h"

#include <FS.h>
// #define use_little_fs
#ifdef use_little_fs
	#include "LITTLEFS.h"
	#define SPIFFS LITTLEFS
	#define CONFIG_LITTLEFS_SPIFFS_COMPAT 1
#else	
	#include "SPIFFS.h"// #include <dummy.h>
#endif	
#include <Math.h>
#include <dummy.h>
#include <WiFi.h>
#include "esp_attr.h"
#include "HardwareSerial.h"
#include <ArduinoOTA.h>
#include <WiFiMulti.h>
WiFiMulti wifiMulti;
hw_timer_t * timer = NULL;
portMUX_TYPE timerMux = portMUX_INITIALIZER_UNLOCKED;

IPAddress apIP(192,168,2,2),ap_gateway(192,168,2,1),bcast_ip(192,168,2,255),my_ip,pc_ip,esp2_ip;
WiFiUDP myUDP;

int16 led_cnt,led1_on,led2_on,led_reset=5,ms200=0,ms1000=0,pc_ip_cnt=0;
int16 ms10,pc_on,wifi_status,string_valid_cnt,ms2;
int16 timer_1ms;
int16 wifi_on,file_ok,udp_on=0,serial_on=0;
int16 new_millis,old_millis,rx2_time_out;

uint8 udp_in_buf[1400];
int16 my_id,hd_len;
int16 ms5,fp_off=0,fp_on=0,fp_detect_cnt=0,fp_off_delay=300,fp_mode_delay=0,fp_fail=0,fp_off_max=500;
int16 tx_pkt_len,hd_index,buf_id,match_delay=0,pulse_width=300,pulse_max=3;
uint8 char_buf[char_buf_len];
int16 data_pkt_cnt,door_open_delay=0;
int16 p_millis,n_millis,d_millis;
uint16 r_port=6000;
String s_log="";
uint8 rx_buf[rx_max];
String serial_in,params_str,serial2_out,serial2_in;
int16 page_id;
int16 hd_ok=0,rx_pkt_len,rx_cnt=0,pkt_type,check_sum,check_sum_ok;
uint8 ima_buf[ima_buf_max],file_buf[ima_buf_max];
int16 voice_len,pwm_val,pwm_on=0,ima_buf_cnt=0,sin_cnt=0,ima_haft=0,pwm_send=0,file_len=0,file_seg=0;
uint8 pwm_tmp;
int16 n_prefix,response,ret,ret_code;
int16 bip_on=0,fs01_on=0,fp_auto_off,fp_on_duration,fp_on_max;

char ssid_name[32],ssid_pass[32];
String str_name[4],str_pass[4];

int32 e_predsample,d_predsample;        
int16 e_index,d_index;                  

int16 encode_buf[2048];
cmd_tx_struct cmd_tx;
cmd_rx_struct cmd_rx;
data_tx_struct data_tx;
data_rx_struct data_rx;

udp_rx_header udp_rx;
udp_tx_header udp_tx;
file_tx_header file_tx;

void setup() 
{ pinMode(LED1,OUTPUT);
	// pinMode(door_gate,OUTPUT);
	// door_close;
	pinMode(buzz_in,INPUT);
	pinMode(led_in,INPUT);
	pinMode(fp_detect_pin,INPUT_PULLDOWN);
	// attachInterrupt(fp_detect,fp_isr,FALLING);
	// digitalWrite(fp_power, 1);
	Serial.begin(115200,SERIAL_8N1);
	Serial2.begin(115200,SERIAL_8N1);
	Serial1.begin(115200,SERIAL_8N1,pin_rx1,pin_tx1);
	wifi_setup();
  ota_init();
  s_log=SPIFFS.begin(true)? "FS Ok":"FS fail";
  s_log += " size= "+String(SPIFFS.totalBytes() >> 10);
  s_log += " used= "+String(SPIFFS.usedBytes() >> 10);
  pwm_init();
	cmd_send(Test_Connection,0,0);
  uart1.write(cmd_tx.prefix,sizeof(cmd_tx));
}
void IRAM_ATTR fp_isr(){
}
void fp_test(){
	if(digitalRead(fp_detect_pin)){
		if(fp_detect_cnt < 100)	fp_detect_cnt++;
		fp_on_duration++;	
	}else{ 
		if(fp_detect_cnt){
			fp_detect_cnt--;
		}else{
			if(fp_on_duration){
				fp_on_max=fp_on_duration;
				fp_on_duration=0;
			}
		} 
	}
	if(fp_detect_cnt > 50){
		// fp_detect_cnt=0;
		if(fp_auto_off==0){
			cmd_send(Identify,0,0);
		  uart1.write(cmd_tx.prefix,sizeof(cmd_tx));
		}
	}
}
void loop() 
{ if(pwm_on==0)	ArduinoOTA.handle();
	millis_1();
}
void millis_1(){
  new_millis=millis() & 0x3fff;
  if(old_millis == new_millis) return;
  old_millis = new_millis;
	String s;
	serial_test();
	serial2_test();
	serial2_out_test();
	UDP_receive();
		// portENTER_CRITICAL(&timerMux);
		// portEXIT_CRITICAL(&timerMux);
	ms10 &= 0xf;
	if (++ms10 > 9) // vong lap 10ms
	{	ms10=0;
		fp_test();
    int wifi_status=WiFi.status();
    if (wifi_status==WL_CONNECTED) wifi_on=300;
		if(wifi_on)	wifi_on--;		
		// else ESP.restart();
		if(pc_ip_cnt){
			pc_ip_cnt--;
		}else{
			pc_ip=bcast_ip;
			r_port=6000;
		}	
		if(fp_auto_off)	fp_auto_off--;
		int16 len=file_len-file_seg;
		if(file_len && (len > 0)){
			if(len > 1024){
				
			}
		}
		// if(door_open_delay)	door_open_delay--;
		// else 				door_close;
	}
	ms200 &= 0x1ff;
	if (++ms200 > 200)  // vong 200ms kiem tra led
	{	ms200=0;
		led_test();
	}
	ms1000 &= 0xfff;
	if (++ms1000 > 1000) 
	{	ms1000=0;
		bcast_out();
	}
}
void bcast_out(){
		String s=s_log; //+" "+String(fp_on_max)+" "+String(fp_detect_cnt)+" "+String(fp_auto_off);
		uint8 buf[s.length()];
		udp_tx.pkt_type=FS01_BCAST;
		udp_tx.data_rx.rcm=WiFi.RSSI();
		udp_tx.data_rx.len=s.length();
		udp_tx.cmd_rx.data[0]=my_ip[3];
		udp_tx.cmd_rx.data[0] <<= 8;
		udp_tx.cmd_rx.data[0] |= my_ip[3];
		udp_tx.cmd_rx.data[1]=digitalRead(master_in);
		for(int i=0;i<udp_tx.data_rx.len;i++){
			buf[i]=s.charAt(i);
		}
		memcpy(udp_tx.data_rx.data,buf,sizeof(buf));
		bcast_send(&udp_tx.bcc,sizeof(udp_tx));
}
void led_test()
{ led_cnt &= 0x1f;
	if (led_cnt <= 0)			
	{	led1_on = 0;
		if(wifi_on)	led1_on++;
		if(pc_ip_cnt)	led1_on = 2;
		if(fs01_on)	led1_on += 2;	
		led_cnt=led1_on * 2 + 2;
	}
	else if ((--led_cnt & 1) && led1_on)
	{	led1_on--; on_led1;
	}else 	{ off_led1;}      
	if (led_reset)      { led_reset--; on_led1;}
}

