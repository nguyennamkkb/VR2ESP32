#include "n_serial.h"
n_serial::n_serial(QObject *parent) : QObject(parent)
{   serial = new QSerialPort(this);
    serial->setBaudRate(115200);
    serial->setReadBufferSize(20000);
    serial->setDataBits(QSerialPort::Data8);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setParity(QSerialPort::NoParity);

    serial2 = new QSerialPort(this);
    serial2->setBaudRate(115200);
    serial2->setReadBufferSize(20000);
    serial2->setDataBits(QSerialPort::Data8);
    serial2->setStopBits(QSerialPort::OneStop);
    serial2->setParity(QSerialPort::NoParity);
    QTimer* timer_1=new QTimer(this);
    timer_1->setTimerType(Qt::PreciseTimer);
    connect(timer_1, SIGNAL(timeout()), this, SLOT(Timer_2()));
    timer_1->start(1);
    fs01=new fs_01();
}
void n_serial::Timer_2()
{   serial_test();
    serial2_test();
    serial2_out_test();
    QByteArray b;
    if(++rx_time_out > 100){
        rx_time_out=0;
        if(rxtmp.size()){
            QString s="COM timeout: ";
            s += fs01->ba_to_string(rxtmp);
            emit new_serial_msg(out_dst,s);
        }
        rxtmp.clear();
        rxbuf.clear();
    }
    ms10 &= 0x1f;
    if(++ms10 > 9){
        ms10=0;
    }
    if(ms20)    ms20--;
}
void n_serial::serial2_out_test()
{qint16 len;
    if (ms20)   ms20--;
    if(ms20==0)
    {	QString s="";
        if (serial2_out.length() > 123)
        {	s=serial2_out.mid(0,124);
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
        {	serial2->write(s.toUtf8());
            ms20=20;
        }
    }
}
void n_serial::send_ev2(){
QString s="!^0";
quint8 n8=0;
    if (serial2->isOpen()){
        for(int i=0;i<498;i++){
            s += n2s((n8 >> 4) & 0xf,16);
            s += n2s(n8 & 0xf,16);
        }
        s += "#";
        serial2_out=s;
        qDebug() << s.length();
//        serial2->write(s.toUtf8());
    }
}
QString n_serial::str_fix_len(QString s, int len){
    while(s.length() < len){
        s = "0"+s;
    }
    s=s.right(len);
    return s;
}
void n_serial::serial2_test()
{QByteArray ba;
QString s;
    if (serial2->isOpen())
    {   if (serial2->bytesAvailable())
        {   ba = serial2->readAll();
            if(ba.size()){
                for(int i=0;i<ba.size();i++){
                    s=ba.mid(i,1);
                    if(s=="!"){
                       serial_in="";
                    }else if(s=="#"){
                        if(serial_in.startsWith("^0")){
                            serial_in.remove(0,2);
//                            qDebug() << "serial 2" << serial_in.length();
                            ba.clear();
                            if(serial_in.length()==498*2){
                                while (serial_in.length()){
                                    ba += (quint8)(serial_in.mid(0,2).toInt(nullptr,16));
                                    serial_in.remove(0,2);
                                }
                                memcpy(fs01->char_buf,ba.data(),498);
                                serial_out(fs01->ba_to_send(fs01->Verify_Feature,2,0));
                            }
                        }
                    }else{
                        serial_in += s;
                    }
                }
                if(serial_in.length() > 32000)  serial_in="";
            }
        }
    }
}
qint16 n_serial::get_len(qint16 k){
    qint16 len=rxbuf[k+1] & 0xff;
    len <<= 8;
    return len | (rxbuf[k] & 0xff);
}

void n_serial::serial_test()
{QByteArray ba;
qint16 n,ret;
QString s,s1;
    if (serial->isOpen())
    {   if (serial->bytesAvailable())
        {   ba = serial->readAll();
            if(ba.size()){
                rxbuf += ba;
                rxtmp += ba;
                rx_time_out=0;
                if(rx_show) qDebug() << fs01->ba_to_string(ba);
            }
            if(!hd_ok){
                if(rxbuf.size() >= 2){
                    memcpy(&n,rxbuf.data(),2);
                    if((n == cmd_response_prefix) || (n == data_response_prefix)){
                        hd_ok=1;
                        data_len=-1;
                        response_code=n;
                        qDebug() << "HD OK" << n2s(n,16);
                    }else{
                        rxbuf.clear();
                        hd_ok=0;
                    }
                }
            }
            if(hd_ok){
                if(rxbuf.size() >= 6){
                    if(data_len==-1){
                        data_len=get_len(4);
                    }
                }
                if(response_code==cmd_response_prefix){
                    if(rxbuf.size() >= 24){
                        memcpy(cmd_rx.prefix,rxbuf.data(),sizeof(cmd_rx));
                        ret=cmd_rx.data[1];
                        s="fs01 cmd : "+fs01->enumToString(cmd_rx.rcm)+" len="+n2s(cmd_rx.len/2)+" ";
                        s += (cmd_rx.data[0])? "Err ":"Ok ";
                        if(cmd_rx.data[0]==0){
                            switch (cmd_rx.rcm) {
                                case fs01->Enroll_RAM:
                                    if(ret){
                                        s += fs01->return_string(ret);
                                    }else{
                                        serial_out(fs01->ba_to_send(fs01->Get_Enroll,0,0));
                                    }
                                    break;
                                case fs01->Verify_Feature:
                                    ba=fs01->ba_to_send(fs01->Verify_Feature,498,0);
                                    serial_out(ba);
                                    s1="PC: "+fs01->ba_to_string(ba);
                                    emit new_serial_msg(out_dst,s1);
                                    if((ret < 0) || (ret > 1))  s += fs01->return_string(ret);
                                    rx_show=1;
                                    break;
                                case fs01->Get_Enroll_Count:
                                    s += "Count= "+n2s(ret);
                                    break;
                                case fs01->Identify:
                                    if((ret < 0) || (ret > 999))  s += fs01->return_string(ret);
                                    else                        s += "Id= "+n2s(ret);
                                    break;
                                default:
                                    if((ret < 0) || (ret > 1)){
                                        s += fs01->return_string(ret);
                                    }else if(cmd_rx.len > 2){
                                        s += n2s(ret);
                                    }
                                    break;
                                }
                        }
                        hd_ok=0;
                        rx_ok=rxbuf;
                        rxbuf.remove(0,24);
                        rxtmp.clear();
                        emit new_serial_msg(cmd_response_prefix);
//                        emit new_serial_msg(out_dst,s);
                    }
                }else{
                    if(rxbuf.size() >= (6+data_len+2)){
                        memcpy(data_rx.prefix,rxbuf.data(),6+data_len+2);
                        qDebug() << data_rx.rcm << data_rx.len;
                        hd_ok=0;
                        rx_ok=rxbuf;
                        rxbuf.clear();
                        rxtmp.clear();
                        emit new_serial_msg(data_response_prefix);
                    }
                }
            }
        }
    }
}

quint8 n_serial::get_bcc(quint8 *buf,int len){
    quint8 bcc=0;
    for(int i=0;i<len;i++){
        bcc ^= *buf++;
    }
    return bcc;
}

void n_serial::serial_out(QByteArray ba){
    if (serial->isOpen())
    {   if(ba.size() >= 24){
            serial->write(ba);
            rxbuf.clear();
            hd_ok=0;
            rx_show=0;
        }
    }
}
void n_serial::serial_create(QString comport)
{qint16 n=0;
    QString s;
    serial->setPortName(comport);
    if (!serial->isOpen())
    {   if(serial->open(QIODevice::ReadWrite))
        {   n=1;
            s=serial_port+" Opened";
        }else{
            s=serial_port+" Error";
            n=2;
        }
    }else{
        s=serial_port+" Closed";
        serial->close();
        n=0;
    }
    if(use_pi){
        s +=" ";
        serial2->setPortName(serial2_port);
        if (!serial2->isOpen())
        {   if(serial2->open(QIODevice::ReadWrite)){
                s+=serial2_port+" Opened";
            }else{
                s+=serial2_port+" Error";
            }
        }else{
            s+=serial2_port+" Closed";
            serial2->close();
        }
    }
    emit new_serial_msg(n,s);
}
