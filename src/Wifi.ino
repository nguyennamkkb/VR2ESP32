#include "vimass.h"

void wifi_setup()
{ WiFi.mode(WIFI_AP_STA);
  WiFi.softAPdisconnect (true);
  if (wifi_on) WiFi.disconnect(); wifi_on=0; 
  for (int i=0;i<4;i++)
  { if(str_pass[i].length() >= 8)
    { strcpy(ssid_name,str_name[i].c_str());
      strcpy(ssid_pass,str_pass[i].c_str());
      wifiMulti.addAP(ssid_name,ssid_pass);
    }
  }
// wifiMulti.addAP("The_Daudoc","hoianhnam");
// wifiMulti.addAP("VimassPhonghop","vimass8888");
wifiMulti.addAP("FPT_Telecom","bat4gdiban");
  WiFi.setAutoReconnect(true);
  uint8 sec_cnt=0;
  wifi_on=0;
  while(sec_cnt++ < 25)
  { if (wifiMulti.run() != WL_CONNECTED)
    { on_led1; delay(500); off_led1; delay(500);}
    else
    { sec_cnt=150;
      my_ip=bcast_ip=WiFi.localIP(); 
      bcast_ip[3]=255; wifi_on=300;
      pc_ip=bcast_ip;
    }
  }
  myUDP.begin(5000); 
}

void AP_setup()
{ WiFi.mode(WIFI_AP_STA);
  WiFi.softAPdisconnect (true);
  WiFi.softAPConfig(apIP, ap_gateway, IPAddress(255, 255, 255, 0)); 
  WiFi.softAP("vimass","12345678");
  pc_ip=bcast_ip;
  my_ip=apIP;
  myUDP.begin(5000); 
}

void UDP_receive()
{ 
  int16 n=myUDP.parsePacket();
  String s="";
  if (n){
    myUDP.read(udp_in_buf,sizeof(udp_in_buf));
    if(n != sizeof(udp_rx))               return;
    if(get_bcc(udp_in_buf,n) != 0x55)     return;
    memcpy(&udp_rx.bcc,udp_in_buf,sizeof(udp_rx));
    if(udp_rx.pkt_type==PC_BCAST){
      r_port=myUDP.remotePort();
      pc_ip=myUDP.remoteIP();
      pc_ip_cnt=500;
      return;
    }
    // uart1.println(udp_in_buf);
    // String aa=udp_in_buf;
    // uart0.println((uint8_t*)&&udp_in_buf);
    
   
    if(udp_rx.pkt_type==PC_01)  cmd_switch();//du lieu tach ntn để xử lí
  }
}

void string_send(String s){
  int len=s.length();
  uint8 buf[len];
  for(int i=0;i<len;i++){
    buf[i]=s.charAt(i);
  }
  memcpy(udp_tx.data_rx.data,buf,len);
  udp_tx.pkt_type=FS01_STRING;
  udp_tx.data_rx.len=len;
  uni_send(&udp_tx.bcc,sizeof(udp_tx));
}
uint8 get_bcc(uint8* buf,int len){
  uint8 bcc=0;
  for(int i=0;i<len;i++){
    bcc ^= *buf++;
  }
  return bcc;
}

void bcast_send(uint8 *buf,int len){
  buf[0]=0x55;
  buf[0]=get_bcc(buf,len);
  myUDP.beginPacket(bcast_ip,r_port);
  myUDP.write(buf, len);
  myUDP.endPacket();
}
void uni_send(uint8 *buf,int len){
  buf[0]=0x55;
  buf[0]=get_bcc(buf,len);
  myUDP.beginPacket(pc_ip,r_port);
  myUDP.write(buf, len);
  myUDP.endPacket();
}
