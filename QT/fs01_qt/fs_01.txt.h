#ifndef FS01_
#define FS01_

#define cmd_prefix	0xaa55
#define cmd_response_prefix	0x55aa
#define data_prefix	0xa55a
#define data_response_prefix	0x5aa5

#define uint8 quint8
#define int8 qint8
#define uint16 quint16
#define int16 qint16
#define uint32 quint32
#define int32 qint32

struct cmd_tx_struct{
	uint8 prefix[2];
	int16 cmd;
	int16 len;
	uint8 data[16];
	uint8 cks[2];
};
struct data_tx_struct{
	uint8 prefix[2];
	int16 cmd;
	int16 len;
    uint8 data[504];
};
struct cmd_rx_struct{
	uint8 prefix[2];
    int16 rcm;          // last cmd
	int16 len;
    int16 ret;          // 0:success, 1: fail
	uint8 data[16];
	uint8 cks[2];
};
struct data_rx_struct{
	uint8 prefix[2];
    int16 rcm;          // last cmd
	int16 len;
    int16 ret;          // 0:success, 1: fail
    uint8 data[504];
};
const int16 cmd_on[]={
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 1, 1, 1, 1,
    1, 0, 0
};
const int16 rcm_len[]={
	4, 4, 6, 6, 4, 
	4, 4, 4, 6, 502, 
	4, 4, 4, 4, 4, 
	4, 4, 4, 4, 4, 
	4, 4, 4, 4, 500, 
	500, 4, 4, 16, 4, 
	4, 4, 4, 4, 4, 
	2, 2, 2
};

#endif
