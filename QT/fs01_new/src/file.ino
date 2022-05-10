#include "vimass.h"
// esptool.py --chip esp32 --port COM3 erase_flash
bool write_buf(String f_name,uint8* buf, int16 len){
	bool b=false;
	if(pwm_on)	return b;
	File f = SPIFFS.open(f_name, "w");
	while (f.available()){ 
		f.write(buf,len);
		b = true;
		f.close();
	}
	return b;
}

bool read_buf(String f_name){
	if(pwm_on)	return false;
 	File f = SPIFFS.open(f_name, "r");
	while (f.available()){ 
		voice_len=f.size();
		f.read(ima_buf,voice_len);
		f.close();
		return true;
	}
	return false;
}
bool rename(String s_src,String s_dst){
	return SPIFFS.rename(s_src,s_dst);
}
bool remove(String fname){
	return SPIFFS.remove(fname);
}
String list_file(){
String s="file list:\n",name;
File f;
	for(int i=0;i<16;i++){
		name="/a_"+String(i)+".wav";
		if(SPIFFS.exists(name)){
			s += name; 
			s += ":";
			f=SPIFFS.open(name, "r");
			s += String(f.size()*4)+"\n";
			f.close();
		}
	}	
	return s;
}
void read_ssid()
{ String s[16];
  int k;
  for (k=0;k<4;k++)
  { str_name[k]=str_pass[k]="";
  }
  k=0;
  File f = SPIFFS.open("/ssid.txt", "r");
  while ((f.available()) && (k < 8))
  { s[k] = f.readStringUntil(',');
    if(k) s[k].remove(0,1);
    if(s[k].startsWith(",")) s[k].remove(0,1);
    if(s[k].endsWith(",")) s[k].remove(s[k].length()-1,1);
    k++;
  }
  for (k=0;k<4;k++)
  { str_name[k]=s[k*2];
    str_pass[k]=s[k*2+1];
  }
  f.close();
}
void save_ssid(String s)
{ File f = SPIFFS.open("/ssid.txt", "w");
  if (f)  f.print(s);
  f.close();
  led_reset=15;
}

