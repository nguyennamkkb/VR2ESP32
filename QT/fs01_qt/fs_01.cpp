#include "fs_01.h"

fs_01::fs_01(QObject *parent) : QObject(parent)
{
    fp_btn_check();

}
void fs_01::fp_btn_check(){
    qint16 k=0;
    QString s;
    for(int i=0;i<128;i++){
        s = enumToString(i+0x101);
        if(s.length() > 2){
            fs01_index[k++]=i+0x101;
        }
    }
}
QString fs_01::enumToString(qint16 cmd)
{   int index = metaObject()->indexOfEnumerator("fs01_code");
    QMetaEnum metaEnum = metaObject()->enumerator(index);
    return metaEnum.valueToKey(cmd);
}
QString fs_01::return_string(qint16 ret_code){
QString s;
    for(int i=0;i<error_code.size()/2;i++){
        s=error_code[2*i];
        if((qint16)(s.toInt(nullptr,16))==ret_code)    return error_code[2*i+1];
    }
    return "";
}

QString fs_01::ba_to_string(QByteArray ba){
QString s="";
    for(int i=0;i<ba.size();i++){
        s += fix_len(ba[i] & 0xff,2)+" ";
    }
    return s;
}
QString fs_01::fix_len(qint16 n,qint16 k){
    QString s=n2s(n,16);
    while(s.length() < k){
        s = "0"+s;
    }
    if(s.length() > k)  s=s.mid(0,k);
    return s;
}

QByteArray fs_01::ba_to_send(qint16 cmd,qint16 len,qint16 page_id){
QByteArray ba;
qint16 n;
    switch(len){
        case 0:
        case 2:
            cmd_tx.prefix[0]=cmd_prefix & 0xff;
            cmd_tx.prefix[1]=(cmd_prefix >> 8) & 0xff;
            cmd_tx.cmd=cmd;
            cmd_tx.len=len;
            memset(cmd_tx.data,0,sizeof(cmd_tx.data));
            if(cmd==Verify_Feature){
                cmd_tx.data[0]=498;
            }else if(len){
                cmd_tx.data[0]=page_id;
            }
            ba=get_tx_cks(len);
        case 14:
            cmd_tx.prefix[0]=cmd_prefix & 0xff;
            cmd_tx.prefix[1]=(cmd_prefix >> 8) & 0xff;
            cmd_tx.cmd=cmd;
            cmd_tx.len=len;
            memset(cmd_tx.data,0,sizeof(cmd_tx.data));
            ba=get_tx_cks(len);
            qDebug() << n2s(cmd,16) << ba.size();
            break;
        case 498:
            data_tx.prefix[0]=data_prefix & 0xff;
            data_tx.prefix[1]=(data_prefix >> 8) & 0xff;
            data_tx.cmd=cmd;
            data_tx.len=len;
//            memset(char_buf,0,64);
            memcpy(data_tx.data,char_buf,char_buf_len);
            ba=get_tx_cks(len);
            break;
    }
    return ba;
}
QByteArray fs_01::get_tx_cks(int16 len){
QByteArray ba;
quint8 *ptr;
quint16 cks=0;
    if(len <= 2){
        ptr=cmd_tx.prefix;
        for(int i=0;i<(int)(sizeof(cmd_tx))-2;i++){
            cks += *ptr++;
        }
        cmd_tx.cks=cks;
        ba.resize(sizeof(cmd_tx));
        memcpy(ba.data(),cmd_tx.prefix,ba.size());
    }else if (len==14){
        ptr=cmd_tx.prefix;
        for(int i=0;i<(int)(sizeof(cmd_tx))-2;i++){
            cks += *ptr++;
        }
        cmd_tx.cks=cks;
        ba.resize(sizeof(cmd_tx));
        memcpy(ba.data(),cmd_tx.prefix,ba.size());
    }else if (len==498){
        ptr=data_tx.prefix;
        for(int i=0;i<6+len;i++){
            cks += *ptr++;
        }
        data_tx.data[len >> 1]=cks;
        ba.resize(6+len+2);
        memcpy(ba.data(),data_tx.prefix,ba.size());
    }
//    qDebug() << ba.size();
    return ba;
}

bool fs_01::get_rx_cks(int16 len){
int16 cks=0,cks1;
quint8 *ptr;
    if(len <= 2){
        ptr=cmd_rx.prefix;
        for(int i=0;i<(int)(sizeof(cmd_rx))-2;i++){
            cks += *ptr++;
        }
        return (cmd_rx.cks==cks);
    }else{
        ptr=data_rx.prefix;
        for(int i=0;i<6+len;i++){
            cks += *ptr++;
        }
        return (cks==data_tx.data[len >> 1]);
    }
}
