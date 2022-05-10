int16 fs_01_cks(uint8* buf,int16 len,int16 k){
int16 cks=0;
	for(int i=0;i<len-2;i++){
		cks += buf[i];
	}
	if(k){
		memcpy(&buf[len-2],&cks,2);
	}
	return cks;
}


void fp_lock(){
	if(++fp_fail > 5){
	fp_off=fp_off_max;
	fp_fail=0;
	}		 
}
void serial_test(){ 
	while (uart1.available()){ 
  		int16 n;
	  	while (uart1.available()){ 
	  		n = uart1.read();
	  		if (n != -1){
	  			rx_buf[rx_cnt++]=n & 0xff;
	  			rx_cnt &= rx_max-1;
		  		if(!hd_ok && (rx_cnt >= 2)){
		  			memcpy(&n_prefix,rx_buf,2);
		  			if((n_prefix==cmd_response_prefix) || (n_prefix==data_response_prefix)){
		  				hd_ok=1;
		  				rx_pkt_len = -1;
		  			}else{
		  				rx_cnt=0;
		  			}
		  		}
		  		if(hd_ok){
		  			if(rx_cnt >= 6){
		  				if(rx_pkt_len == -1){
		  					memcpy(&rx_pkt_len,&rx_buf[4],2);
		  				}
		  			}
		  			if(n_prefix==cmd_response_prefix){
	                    if(rx_cnt == 24){
	                        memcpy(cmd_rx.prefix,rx_buf,sizeof(cmd_rx));
	                        ret=cmd_rx.data[0];
	                        ret_code=cmd_rx.data[1];
	                        memcpy(udp_tx.cmd_rx.prefix,cmd_rx.prefix,sizeof(cmd_rx));
	                        if(ret==0){
	                        	switch(cmd_rx.rcm){
	                        		case Test_Connection:
	                        			fs01_on=1;
	                        			break;
	                        		case Identify:
	                        			// fp_auto_off=500;
	                        			break;
	                        		case Verify_Feature:
	                        			// fp_auto_off=500;
										cmd_send(Verify_Feature,498,0);
										uart1.write(data_tx.prefix,498+8);
	                        			break;
	                        		case Read_Page:
	                        			break;
	                        		case Enroll_RAM:
		                        		if(ret_code==0){
		                        			// fp_auto_off=500;
											cmd_send(Get_Enroll,0,0);
											uart1.write(cmd_tx.prefix,sizeof(cmd_tx));
		                        		}
	                        			break;
	                        	}
                        	}else{
	                        	switch(cmd_rx.rcm){
	                        		case Identify:
	                        			fp_auto_off=0;
	                        			break;
	                        		case Verify_Feature:
	                        			// fp_auto_off=500;
	                        			break;
	                        	}
                        	}
                        	hd_ok=rx_cnt=0;
	                    	udp_tx.pkt_type=FS01_CMD;
	                    	uni_send(&udp_tx.bcc,sizeof(udp_tx));
	                    }
	  				}else if(n_prefix==data_response_prefix){
	                    if(rx_cnt == (6+rx_pkt_len+2)){
	                        memcpy(data_rx.prefix,rx_buf,sizeof(data_rx));
	                        ret=data_rx.data[0];
	                        ret_code=data_rx.data[1];
	                        memcpy(udp_tx.data_rx.prefix,data_rx.prefix,sizeof(data_rx));
	                        if(ret==0){
		                        switch(data_rx.rcm){
	                        		case Verify_Feature:
	                        			led_reset=10;
		                       			break;
		                        }

                        	}else{

                        	}
                        	hd_ok=rx_cnt=0;
	                    	udp_tx.pkt_type=FS01_DATA;
	                    	uni_send(&udp_tx.bcc,sizeof(udp_tx));
	                    }
	  				}
		  		}
	  		}
	  	}
	}
}
void serial2_test() 
{String s;	
int n;
  	while (uart2.available()) 
  	{ n = uart2.read();
  		if (n != -1)
  		{	serial2_in += (char)(n & 0xff);
  			if (serial2_in.endsWith("!"))	
			{	serial2_in = "";
			}	
	 		if (serial2_in.endsWith("#"))	
	 		{	serial2_in.remove(serial2_in.length()-1,1);		// remove #
	 			if (serial2_in.startsWith("^0")){		// receive ev2_char_buf
	 			 	s=serial2_in.substring(2);
	 				if(s.length()==char_buf_len*2){
	 					for(int i=0;i<char_buf_len;i++){
	 						char_buf[i]=hex_to_byte(s.substring(0,2));
	 						s=s.substring(2);
	 					}
						cmd_send(Verify_Feature,2,0);
						uart1.write(cmd_tx.prefix,sizeof(cmd_tx));// sao uart1.write có 2 tham số, md_tx.prefix có 2 byte sao cần thêm sizeof(cmd_tx). sizeof(cmd_tx) được hiểu như thế nào?
						led_reset=5;
	 				}
	 			}
 			 	serial2_in="";
	 		}
			if (serial2_in.length() > rx_max)	serial2_in.clear();
  		}
	}
}
void serial2_out_test()
{int len;
	if (uart2.availableForWrite() >= 127)
	{	ms5 &= 7;
		if (ms5)
		{	if(--ms5==0)
			{	String s="";
				if (serial2_out.length() > 123)
				{	s=serial2_out.substring(0,124);
					serial2_out.remove(0,124);
				}
				else if (serial2_out.length())
				{	s=serial2_out;
					serial2_out="";	
					len=(s.length() & 0x7c) + 4;
					if (len > 124)	len=124;
					while(s.length() < len)	{	s += "0";}
				}
				if (s.length())	
				{	uart2.print(s);
					ms5=4;
				}
			}
		}
		else if (serial2_out.length())
		{	ms5=4;
		}	
	}
}

void char_buf_to_ev2(){
String s="!^0";
uint8 n8,n;
	for(int i=0;i<char_buf_len;i++){
		n8=char_buf[i];
		n=(n8 >> 4) & 0xf;
		s += s_hex.substring(n,n+1);
		n=n8 & 0xf;
		s += s_hex.substring(n,n+1);
	}
	s += "#";
	// uart2.print(s);
	serial2_out=s;
}
uint8 hex_to_byte(String s){
	s.toUpperCase();
	uint8 n8; int n;
	n = s_hex.indexOf(s.substring(0,1));
	n8 = (n != -1)? n:0;
	n8 <<= 4;
	n = s_hex.indexOf(s.substring(1,2));
	n8 |= (n != -1)? n:0;
	return n8;
}