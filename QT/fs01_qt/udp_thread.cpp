#include "udp_thread.h"

Udp_thread::Udp_thread(QObject *parent) :
    QObject(parent)
{   wifi_socket = new QUdpSocket(this);
    wifi_socket->bind(QHostAddress::AnyIPv4,6000, QUdpSocket::ShareAddress);
    connect(wifi_socket,SIGNAL(readyRead()),this,SLOT(wifi_read()));

    QTimer* timer_1=new QTimer(this);
    timer_1->setTimerType(Qt::PreciseTimer);
    connect(timer_1, SIGNAL(timeout()), this, SLOT(Timer()));
    timer_1->start(1);
    for(int i=0;i<32;i++){
        if(i<16)    hex16[i]=1 << i;
        hex32[i]=1 << i;
    }
    fs01=new fs_01();
    ip_scan();
}
QByteArray Udp_thread::get_bcc(QByteArray ba,uint8 k){
quint8 bcc=0;
    if(k)   ba[0]=k;
    for(int i=0;i<ba.size();i++){
        bcc ^= ba[i] & 0xff;
    }
    if(k==0){
        ba.resize(1);
    }
    ba[0]=bcc;
    return ba;
}

void Udp_thread::Timer()
{   if (++ms10 > 9)
    {   ms10=0;
        if(++ms1000 > 99)
        {   ms1000=0;
            bcast_out();
//            big_out();
        }
    }
}
void Udp_thread::ip_scan(){
    ip_list_max=0;
    memset(ip_list,0,sizeof(ip_list));
}
void Udp_thread::big_out(){
    QByteArray ba;
    ba.resize(8192);
    memset(ba.data(),0x55,ba.size());
    wifi_socket->writeDatagram(ba,QHostAddress(bcast_ip),5000);
}
void Udp_thread::bcast_out(){
    QByteArray ba;
    memset(&bcast_tx.bcc,0,sizeof(bcast_tx));
    bcast_tx.pkt_type=PC_BCAST;
    ba.resize(sizeof(bcast_tx));
    memcpy(ba.data(),&bcast_tx.bcc,ba.size());
    if(udp_on){
            ba=get_bcc(ba,0x55);
            wifi_socket->writeDatagram(ba,QHostAddress(bcast_ip),5000);
//            qDebug() << "udp out" << fs01->ba_to_string(ba);
    }
}

void Udp_thread::socket_send(QByteArray ba)
{   if(udp_on){
        ba=get_bcc(ba,0x55);
        if(!esp_ip.endsWith("255")){
            wifi_socket->writeDatagram(ba,QHostAddress(esp_ip),5000);
//            qDebug() << "udp out" << fs01->ba_to_string(ba);
        }
    }
}
void Udp_thread::udp_send(int16 cmd, int16 len, int16 page_id){
    udp_tx.pkt_type=PC_01;
    udp_tx.cmd=cmd;
    udp_tx.len=len;
    udp_tx.page_id=page_id;
    QByteArray ba;
    ba.resize(sizeof(udp_tx));
    memcpy(ba.data(),&udp_tx.bcc,ba.size());
    socket_send(ba);
}
void Udp_thread::ip_test(){
    qint16 ip=bcast_rx.cmd_rx.data[0];
    if(ip){
        for(int i=0;i<32;i++){
            if(ip == ip_list[i]) return;
        }
        ip_list[ip_list_max++]=ip;
        qDebug() << esp_ip << n2s(ip,16) << bcast_rx.data_rx.rcm;
    }
}

void Udp_thread::wifi_read()
{   QByteArray ba;
    QHostAddress sender;
    quint16 senderPort;
    qint16 len;
    QString s_ip,s;
    while (wifi_socket->hasPendingDatagrams())
    {   len=wifi_socket->pendingDatagramSize();
        if (len > 0)
        {   ba.resize(len);
            wifi_socket->readDatagram(ba.data(),ba.size(),&sender,&senderPort);
            s_ip=sender.toString();
            if(sender.toString() == pc_ip){
                qDebug() << "my bcast";
                return;
            }
            pkt_type=ba[1] & 0xff;
            if(pkt_type == FILE_DATA){

            }else{
                memcpy(&udp_rx.bcc,ba.data(),sizeof(udp_rx));
                switch (pkt_type) {
                    case FS01_STRING:
                        len=udp_rx.data_rx.len;
                        ba.resize(len);
                        memcpy(ba.data(),udp_rx.data_rx.data,ba.size());
                        s=ba;
                        emit new_udp_signal(out_dst,s);
                        break;
                    case FS01_BCAST:
                        bcast_rx=udp_rx;
                        len=udp_rx.data_rx.len;
                        ba.resize(len);
                        memcpy(ba.data(),udp_rx.data_rx.data,ba.size());
                        bcast_msg=ba;
    //                    if(ip_fix==0)
                            esp_ip=sender.toString();
                        udp_on=1;
                        ip_test();
    //                    qDebug()  << s;
                        emit new_udp_signal(FS01_BCAST);
                        break;
                    case FS02_BCAST:

                        break;
                    case FS01_CMD:
                        emit new_udp_signal(cmd_response_prefix);
                        break;
                    case FS01_DATA:
                        emit new_udp_signal(data_response_prefix);
                        break;
                    default:
                        break;
                }
            }
        }
    }
}
QString Udp_thread::fix_len(int n,int len){
    QString s="0000"+n2s(n);
    return s.right(len);
}
