#include "fpm.h"

fpm::fpm(QObject *parent) : QObject(parent)
{   QTimer* timer1=new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(f_timer()));
    timer1->start(1);

}
void fpm::f_timer(){

}

qint16 fpm::serial_msg(QByteArray ba){
    pkt_id=ba[6] & 0xff;
    switch(last_cmd){
        case FPM_IMGUPLOAD:
            if((pkt_id==FPM_DATAPACKET) || (pkt_id==FPM_ENDDATAPACKET) ){
                fp_ba += ba.mid(sizeof(fpm_rx),128);
                pkt_cnt++;
            }
            if(pkt_id==FPM_ENDDATAPACKET){
                emit new_img(fp_ba,last_cmd);
            }
            break;
        case FPM_UPCHAR:
            last_upload=0;
            if((pkt_id==FPM_ENDDATAPACKET) || (pkt_id==FPM_DATAPACKET)){
                fp_ba += ba.mid(sizeof(fpm_rx),128);
            }
            if(pkt_id==FPM_ENDDATAPACKET){
                last_upload=1;
                emit new_img(fp_ba.mid(0,256),last_cmd);
            }
            break;
        case GR_IDENTIFY:
        case FPM_SEARCH:
        case FPM_LOAD:
        case FPM_GETIMAGE:
        case FPM_IMAGE2TZ:
        case FPM_STORE:
        case FPM_REGMODEL:
        case FPM_PAIRMATCH:
        case FPM_READSYSPARAM:
        case FPM_TEMPLATECOUNT:
            emit new_ser_msg(ba,last_cmd);
            break;
        default:
            break;
    }
    return last_cmd;
}

qint16 fpm::get_int(QByteArray ba,qint16 index){
   qint16 n=ba[index++] & 0xff;
   n <<= 8;
   n |= ba[index] & 0xff;
   return n;
}

QByteArray fpm::get_checksum(QByteArray ba){
    quint16 sum=0,len=ba.size();
    for(int i=6;i<len-2;i++){
        sum += (quint8)(ba[i] & 0xff);
    }
    ba[len-2] = (sum >> 8) & 0xff;
    ba[len-1] = sum & 0xff;
    return ba;
}
QByteArray fpm::get_cmd_array(quint8 *buf,int len){
    QByteArray ba;
    last_cmd=buf[0];
    if((last_cmd == FPM_UPCHAR) || (last_cmd == FPM_IMGUPLOAD)) fp_ba.clear();
    qint16 len1=sizeof(fpm_tx)+len;
    ba.resize(len1);
    memcpy(fpm_tx.hd,fpm_hd.data(),6);
    fpm_tx.pkt_id=FPM_COMMANDPACKET;
    fpm_tx.pkt_len[0]=(len >> 8) & 0xff;
    fpm_tx.pkt_len[1]=(len) & 0xff;
    memcpy(ba.data(),fpm_tx.hd,sizeof(fpm_tx));
    memcpy(ba.data()+sizeof(fpm_tx),buf,len);
    return get_checksum(ba);
}
QByteArray fpm::cmd_1(quint8 cmd){
    return get_cmd_array(&cmd,3);
}
QByteArray fpm::cmd_2(quint8 cmd,quint8 buf_id){
    quint8 buf[2];
    buf[0]=cmd;
    buf[1]=buf_id;
    return get_cmd_array(buf,4);
}
QByteArray fpm::cmd_3(quint8 cmd,quint8 b1,quint8 b2){
    quint8 buf[3];
    buf[0]=cmd;
    buf[1]=b1;
    buf[2]=b2;
    return get_cmd_array(buf,5);
}
QByteArray fpm::cmd_4(quint8 cmd,quint8 buf_id,qint16 page_id){
    quint8 buf[4];
    buf[0]=cmd;
    buf[1]=buf_id;
    buf[2]=(page_id >> 8) & 0xff;
    buf[3]=page_id & 0xff;
    return get_cmd_array(buf,6);
}
QByteArray fpm::cmd_5(quint8 cmd,qint16 n1,qint16 n2){
    quint8 buf[5];
    buf[0]=cmd;
    buf[1]=(n1 >> 8) & 0xff;
    buf[2]=n1 & 0xff;
    buf[3]=(n2 >> 8) & 0xff;
    buf[4]=n2 & 0xff;
    return get_cmd_array(buf,7);
}
QByteArray fpm::cmd_6(quint8 cmd,quint8 buf_id,qint16 n1,qint16 n2){
    quint8 buf[6];
    buf[0]=cmd;
    buf[1]=buf_id;
    buf[2]=(n1 >> 8) & 0xff;
    buf[3]=n1 & 0xff;
    buf[4]=(n2 >> 8) & 0xff;
    buf[5]=n2 & 0xff;
    return get_cmd_array(buf,8);
}

QByteArray fpm::buf_out(){
    int len=130;
    QByteArray ba = get_out_array(FPM_DATAPACKET,char_buf,len);
    ba += get_out_array(FPM_ENDDATAPACKET,&char_buf[128],len);
    return ba;
}
QByteArray fpm::get_out_array(quint8 pkt_type,quint8 *buf,int len){
    QByteArray ba;
    qint16 len1=sizeof(fpm_tx)+len;
    ba.resize(len1);
    memcpy(fpm_tx.hd,fpm_hd.data(),6);
    fpm_tx.pkt_id=pkt_type;
    fpm_tx.pkt_len[0]=(len >> 8) & 0xff;
    fpm_tx.pkt_len[1]=(len) & 0xff;
    memcpy(ba.data(),fpm_tx.hd,sizeof(fpm_tx));
    memcpy(ba.data()+sizeof(fpm_tx),buf,len);
    return get_checksum(ba);
}

