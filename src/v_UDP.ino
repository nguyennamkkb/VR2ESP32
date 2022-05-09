// void UDP_receive()
// { int16 n=myUDP.parsePacket();
//   String s="";
//   if (n >= 8)
//   { myUDP.read(udp_in_buf,sizeof(udp_in_buf));
//     for (int i=0;i<n;i++)
//     { s += (char)udp_in_buf[i];  
//     }
//     if(s.endsWith("#"))
//     { s = s.substring(0,s.length()-1);

//      UDP_msg(s);
      
//     }
    
//   }
// }


void yeu_cau_nhapmk(){

  biper1();
  
  udp_out_ip("105",hangdoi_Front());
}

void udp_out_ip(String sout,String ipout) 
{
  // add_to_serial(sout);
  // serial_out();
  sout = str_idtb(my_id)+"^"+sout+ "_" +bcc_check_step(sout,6);
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
    myUDP.beginPacket(ip,6000);   // 08/12/20
    myUDP.write(buf, sizeof(buf));
    myUDP.endPacket();
    sout = "";
  }
}