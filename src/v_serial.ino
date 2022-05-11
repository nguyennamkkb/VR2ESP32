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
								case Identify:
									// fp_auto_off=500;
									break;
								case Verify_Feature:
									// fp_auto_off=500;
									cmd_send(Verify_Feature, 498, 0);
									uart1.write(data_tx.prefix, 498 + 8);
									break;
								case Read_Page:
									break;
								case Enroll_RAM:
									if (ret_code == 0)
									{
										// fp_auto_off=500;
										cmd_send(Get_Enroll, 0, 0);
										uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
									}
									break;
								}
							}
							else
							{
								if (ret == 0)
								{
									switch (cmd_rx.rcm)
									{
									case Identify:
										fp_auto_off = 0;
										break;
									case Verify_Feature:
										// fp_auto_off=500;
										break;
									}
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
							ret = data_rx.data[0];
							ret_code = data_rx.data[1];
							memcpy(udp_tx.data_rx.prefix, data_rx.prefix, sizeof(data_rx));
							// switch(){
							// 	case Read_Page:
							// 		break;

							// }

							if (ret == 0)
							{
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

/// sdjfrywsfsdfs
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
				// bd1
				if (serial2_in.endsWith("!"))
				{
					serial2_in = "";
				}
				else if (serial2_in.endsWith("***"))

				{
					serial2_in.remove(serial2_in.length() - 3, 3); // remove #
					if (serial2_in.startsWith("^7") && xacthucvantay == 1)
					{
						serial2_in.remove(0, 2);
						vtlen += serial2_in.length();
						vantay += serial2_in;
						// if(vantay.length()> 400){
						// 	uart0.println(serial2_in);
						// }
						
						if (vtlen == 500)
						{
							
							vantay.remove(vantay.length() - 2, 4);
							// uart0.println(vantay.length());
							XTvanTay(vantay);
							vantay = "";
							xacthucvantay = vtlen = 0;
						}
					}
				}

				else if (serial2_in.endsWith("#") && xacthucvantay == 0)
				// else if (serial2_in.endsWith("#"))
				{

					serial2_in.remove(serial2_in.length() - 1, 1); // remove #
					// add_to_serial("7462 out:"+serial2_in);
					// serial_out();


					// if (serial2_in.startsWith("^0"))
					// { // receive ev2_char_buf
					// 	s = serial2_in.substring(2);
					// 	uart0.println(s);
					// 	if (s.length() == char_buf_len * 2)
					// 	{
					// 		for (int i = 0; i < char_buf_len; i++)
					// 		{
					// 			char_buf[i] = hex_to_byte(s.substring(0, 2));
					// 			s = s.substring(2);
					// 		}
					// 		cmd_send(Verify_Feature, 2, 0);
					// 		uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
					// 		led_reset = 5;
					// 	}
					// }

					if (serial2_in.startsWith("^1"))
					{
						if (serial2_in.startsWith("^135"))
						{
							uid_the = serial2_in.substring(5, 19);
							add_to_serial("uid =:" + uid_the);
							serial_out();
						}
						TrangThaiThanhToan = false;
						magiaodich = "";
						String s = serial2_in;
						s.remove(0, 2);

						// add_to_serial(s);  //chuyen ^1 tu 7462 ra cong com

						if (s.startsWith("cfs"))
						{
							s.remove(0, 3);
							if (wifi_on)
								confirm_service(s);
						}
						else
						{
							// reset_7462("2xx3"); // du dang lam
							// xacthucvantay = 1;
							// reset_7462("2x7");//lenh ghi vào7
							// gốc
							// reset_7462("2x3");
							// delay(1000);
							// 	if (wifi_on) send_https(s);
						}
					}
					else if (serial2_in.startsWith("^6"))
					{
						String s;
						demghi++;
						serial2_out = "!^2" + uid_the + "$114000" + fp_save[demghi] + "$" + tinhCKS_Du("2" + uid_the + "$114000" + fp_save[demghi], 5) + "#";
						// serial2_out="!^2040D52F2CD7080$114000"+fp_save[demghi]+"$"+ tinhCKS_Du("2040D52F2CD7080$114000"+fp_save[demghi],5)+"#";
						uart0.println("ghi lan tiep theo" + serial2_out);
						if (demghi == 4)
							demghi = 1;
					}

					else if (serial2_in.startsWith("^8"))
					{
					}
					else if (serial2_in.startsWith("^4"))
					{
						String sout = "";
						bipok1();
						serial2_in.remove(0, 3);

						if (duong_ra == ra_udp && hangdoi_Front() != "")
						{

							udp_out_ip("100" + serial2_in + "#", hangdoi_Front());
						}
					}
					serial2_in = "";
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
// ghi van tay vao file7

// void char_buf_to_ev2()
// {

// 	// reset_7462("2x7");
// 	delay(1000);
// 	String s = "", snew, snew1 = "2" + uid_the + "$114000";
// 	uint8 n8, n;
// 	for (int i = 0; i < char_buf_len; i++)
// 	{
// 		n8 = char_buf[i];
// 		n = (n8 >> 4) & 0xf;
// 		s += s_hex.substring(n, n + 1);
// 		n = n8 & 0xf;
// 		s += s_hex.substring(n, n + 1);
// 	}
// 	s += "0000";
// 	uart0.println(s);
// 	for (int i = 1; i < 5; i++)
// 	{
// 		fp_save[i] = s.substring(0, 250);
// 		s.remove(0, 250);
// 	}

// 	serial2_out = "!^" + snew1 + fp_save[1] + "$" + tinhCKS_Du(snew1 + fp_save[1], 5) + "#";
// 	uart0.println(serial2_out);
// }

void char_buf_to_ev2()
{
	String s = "!^0";
	uint8 n8, n;
	for (int i = 0; i < char_buf_len; i++)
	{
		n8 = char_buf[i];
		n = (n8 >> 4) & 0xf;
		s += s_hex.substring(n, n + 1);
		n = n8 & 0xf;
		s += s_hex.substring(n, n + 1);
	}
	s += "#";
	// uart2.print(s);
	serial2_out = s;
	// uart0.println(s);
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
// String fix_len(String s,int16 len)
// {	if (s.length() > len)	s=s.substring(s.length()-len,s.length());
// 	while (s.length() < len)	{	s = "0"+s;}
// 	return s;
// }

// void XTvanTay(String strvt)
// {
// 	if (strvt.length() == char_buf_len * 2)
// 	{
// 		bipok1();
// 		for (int i = 0; i < char_buf_len; i++)
// 		{
// 			char_buf[i] = hex_to_byte(strvt.substring(0, 2));
// 			strvt = strvt.substring(2);
// 		}
// 		cmd_send(Verify_Feature, 2, 0);
// 		uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
// 		led_reset = 5;
// 	}
// }
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
		delay(100);
		cmd_send(Verify_Feature, 2, 0);
		delay(100);
		uart1.write(cmd_tx.prefix, sizeof(cmd_tx));
		led_reset = 5;
	}
}