uint8 uid[8];
void wiegand_init()
{ pinMode(out0, OUTPUT);
  pinMode(out1, OUTPUT);
  out0_hi;
  out1_hi;
}

void pulse_out(bool k)
{	if(k){
		out1_low;
		delayMicroseconds(50);
		out1_hi;
		delay(2);
	}else{
		out0_low;
		delayMicroseconds(50);
		out0_hi;
		delay(2);
	}
}

String wiegand26(uint8 *buf)
{uint32 k;
	memcpy(&k,buf,3);
	k &= 0xffffff;
	String s=String(k,2);
	s = fix_len(s,24);	
	return s;
}

String wiegand34(uint8 *buf)
{uint32 k;
	memcpy(&k,buf,4);
	String s=String(k,2);
	s = fix_len(s,32);	
	return s;
}
String wiegand58(uint8 *buf)
{uint32 k[2];
	memcpy(k,buf,8);
	String s0=String(k[0],2),s1=String(k[1],2);;
	s0 = fix_len(s0,32);	
	s1 = fix_len(s1,24);	
	return s1+s0;
}

void wiegand_out(int8 wiegand_type)
{String s;
	switch(wiegand_type)
	{	case 26:	s=wiegand26(uid);
			break;
		case 34:	s=wiegand34(uid);
			break;
		case 58:	s=wiegand58(uid);
			break;
	}
	if (s.length())	string_out(s,2);
}
void string_out(String s,int8 m)
{	int8 k=0,n=s.length() >> 1; 
	for (int i=0;i<n;i++)
	{	if (s.charAt(i)=='1')	k ^= 1;
		if (s.charAt(i+n)=='1')	k ^= 2;
		k ^= m;
	}
	if (k & 1)	{	s = "1"+s;}	else {	s = "0"+s;}
	if (k & 2)	{	s += "1";}	else {	s += "0";}
	for (int i=0;i<s.length();i++)
	{	pulse_out((s.charAt(i)=='1'));
	}
}

String fix_len(String s,int len)
{ if (s.length() > len) s.remove(0,s.length()-len);
  while (s.length() < len)  { s = "0"+s;}
  return s;
}
