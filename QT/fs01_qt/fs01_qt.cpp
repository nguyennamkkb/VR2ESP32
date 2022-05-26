#include "fs01_qt.h"
#include "ui_fs01_qt.h"
QFont btn_font("Times", 12, QFont::Bold);
QFont btn2_font("Times", 16, QFont::Bold);

fs01_qt::fs01_qt(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::fs01_qt)
{
    ui->setupUi(this);
    n_ima=new ima();
    ser=new n_serial();
    u=new Udp_thread();
    thread = new QThread();
    u->moveToThread(thread);
    thread->start(QThread::HighestPriority);
    cfg_load();

#ifdef Q_OS_LINUX     // Q_OS_WIN
    ser->serial_port=serial1_port;
    ser->serial2_port=serial2_port;
    ser->use_pi=1;
#else
    ser->serial_port=serial_port;
    ser->serial2_port=serial3_port;
#endif
    fs01=new fs_01();
    size = qApp->screens()[0]->size();
    ui_init();
    get_ip();
    serial_scan();
    fp_btn_init();

    QTimer* timer1=new QTimer(this);
    connect(timer1, SIGNAL(timeout()), this, SLOT(Timer1()));
    timer1->start(1);
    connect(ser,SIGNAL(new_serial_msg(qint16,QString)),this,SLOT(new_string_msg(qint16,QString)));
    connect(ser,SIGNAL(new_serial_msg(qint16)),this,SLOT(new_serial_msg(qint16)));
    connect(u,SIGNAL(new_udp_signal(qint16,QString)),this,SLOT(new_string_msg(qint16,QString)));
    connect(u,SIGNAL(new_udp_signal(qint16)),this,SLOT(new_udp_msg(qint16)));
}
void fs01_qt::new_udp_str(qint16 response,QString s){
//    lb[1]->setText(s);
//    qDebug() << s;
}

void fs01_qt::new_udp_msg(qint16 response){
    ser->cmd_rx=u->udp_rx.cmd_rx;
    ser->data_rx=u->udp_rx.data_rx;
    new_serial_msg(response);
}
void fs01_qt::new_serial_msg(qint16 response){
QString s="";
QByteArray ba;
qint16 n,n1;
    if(response==FS01_BCAST){
        if(fs01_bcast_cnt++ & 1)        lb[1]->setStyleSheet("QLabel {color:red}");
        else                            lb[1]->setStyleSheet("QLabel {color:blue}");
        return;
    }
    if(response==cmd_response_prefix){
        if(ser->cmd_rx.rcm==voice_download){
            qDebug() << "cmd_response_prefix" << ser->cmd_rx.rcm;
        }else{
            qDebug() << "cmd_response_prefix" << ser->cmd_rx.rcm;
            ba.resize(sizeof(ser->cmd_rx));
            memcpy(ba.data(),ser->cmd_rx.prefix,ba.size());
            txt_append("FS01_cmd: "+fs01->ba_to_string(ba));
            s="fs01 cmd : "+fs01->enumToString(ser->cmd_rx.rcm)+" len="+n2s(ser->cmd_rx.len)+" ";
            if(ser->cmd_rx.data[0]==0){
                s += "Ok ";
                if(ser->cmd_rx.data[1] < 0){
                    s += fs01->return_string(ser->cmd_rx.data[1]);
                }else{
                    switch(ser->cmd_rx.rcm){
                        case fs01->Get_Empty_ID:
                        case fs01->Identify:
                            s += "Page id= "+n2s(ser->cmd_rx.data[1]);
                            break;
                        case fs01->Get_Enroll_Count:
                            s += "Fp_count= "+n2s(ser->cmd_rx.data[1]);
                            break;
                    }
                }
            }else{
                s += "ERR "+fs01->return_string(ser->cmd_rx.data[1]);
            }
            txt_append(s);
        }
    }else if(response==data_response_prefix){
        if(ser->data_rx.len < 8){
            ba.resize(ser->data_rx.len+8);
            memcpy(ba.data(),ser->data_rx.prefix,ba.size());
            txt_append("FS01_data: "+fs01->ba_to_string(ba));
            s="FS01_data: ";
        }
        memcpy(&n,ser->data_rx.data,2);
        memcpy(&n1,&ser->data_rx.data[2],2);
        if(n==0){
            switch(ser->data_rx.rcm){
                case fs01->Get_Enroll:
                    if(ser->data_rx.len==500){
                        memcpy(ser->fs01->char_buf,&ser->data_rx.data[1],498);
                        ba.resize(498);
                        memcpy(ba.data(),ser->fs01->char_buf,498);
                        k_input(QInputDialog::TextInput,"Nhập tên file để cất");
                        if (dlg_struct.ok){
                            txt_append("write file "+dlg_struct.sel_str);
                            write_page_file(dlg_struct.sel_str,ba);
                        }
//                        txt_append(fs01->ba_to_string(ba));
                    }
                    break;
                case fs01->Read_Page:
                    if(ser->data_rx.len==502){
                        memcpy(ser->fs01->char_buf,&ser->data_rx.data[2],498);
                        ba.resize(498);
                        memcpy(ba.data(),ser->fs01->char_buf,498);
                        k_input(QInputDialog::TextInput,"Nhập tên file để cất");
                        if (dlg_struct.ok){
                            write_page_file(dlg_struct.sel_str,ba);
                        }
                        txt_append(fs01->ba_to_string(ba.mid(0,16)));
                    }
                    break;
                case fs01->Verify_Feature:
                    s += fs01->enumToString(ser->data_rx.rcm);
                    if(n==0){
                        s += " Verify Ok ";
                    }else{
                        s += " Verify ERROR: "+fs01->return_string(n1);
                    }
                    lb[0]->setText(s);
                    txt_append(s);
                    break;
            }
        }
    }
}
void fs01_qt::new_serial_msg(QString s){
    lb[0]->setText(s);
}

QString fs01_qt::ba_str(QByteArray ba){
    QString s;
    for(int i=0;i<ba.size();i++){
        s += n2s(ba[i] & 0xff,16)+" ";
    }
    return s;
}

void fs01_qt::new_string_msg(qint16 n,QString s){
    if(n < 3){
        QStringList list={"Open","Close","Error",""};
        p_btn[Com_open]->setText(list[n & 3]);
        if(n==1)    p_btn[Com_open]->setStyleSheet("QPushButton {color:red}");
        else        p_btn[Com_open]->setStyleSheet("QPushButton {color:green}");
    }else if(n==lb_dst){
        lb[0]->setText(s);
    }else if(n==out_dst){
        txt_append(s);
    }
}
qint16 fs01_qt::str_to_int(QString s)
{QString s1="",sample="0123456789";
    for (int i=0;i<s.length();i++)
    {   if(sample.indexOf(s.mid(i,1)) >= 0) s1 += s.mid(i,1);
    }
    return s1.toInt();
}

void fs01_qt::cfg_load()
{   QFile mfile("cfg.ini");
    if (mfile.open( QIODevice::ReadOnly))
    {   QByteArray ba=mfile.readAll();
        mfile.close();
        QString s=ba;
        QStringList list=s.split("\n");
        for (int i=0;i<list.size();i++)
        {   s=list[i];
            s.remove("\r");
            s=s.mid(0,s.indexOf(";"));
            if (s.startsWith("FONT:")) k_btn=str_to_int(s);
            if (s.startsWith("SERIAL:"))
            {   s.remove("SERIAL:");
                s.remove("\r");
                serial_port=s;
            }
            if (s.startsWith("SERIAL1:"))
            {   s.remove("SERIAL1:");
                s.remove("\r");
                serial1_port=s;
            }
            if (s.startsWith("SERIAL2:"))
            {   s.remove("SERIAL2:");
                s.remove("\r");
                ser->serial2_port=s;
            }
            if (s.startsWith("SERIAL3:"))
            {   s.remove("SERIAL3:");
                s.remove("\r");
                serial3_port=s;
            }
            if (s.startsWith("IP:"))
            {   s.remove("IP:");
                s.remove("\r");
                ip_base=s;
            }
        }
    }
}

void fs01_qt::get_ip()
{QList<QNetworkInterface> allInterfaces = QNetworkInterface::allInterfaces();
QNetworkInterface eth;
QString new_ip;
QHostAddress addr;
    foreach(eth, allInterfaces) {
        QList<QNetworkAddressEntry> allEntries = eth.addressEntries();
        QNetworkAddressEntry entry;
        foreach (entry, allEntries)
        {   addr=entry.ip();
            if (addr.protocol() == QAbstractSocket::IPv4Protocol && addr != QHostAddress(QHostAddress::LocalHost))
            {   if (eth.flags()==0x27){
                    if ((eth.name().startsWith("wire",Qt::CaseSensitive)) || (eth.name().startsWith("wlan",Qt::CaseSensitive))){
                        new_ip=addr.toString();
                        if(new_ip.startsWith(ip_base)){
                            u->pc_ip=new_ip;
                            u->ip_base=new_ip.mid(0,new_ip.lastIndexOf(".",-1, Qt::CaseSensitive))+".";
                            u->bcast_ip=u->ip_base+"255";
                            out_txt[0]->append(u->pc_ip+" "+u->ip_base);
                        }
                    }
                }

            }
        }
    }
}
void fs01_qt::Timer1(){
    ms1000 &= 0xfff;
    u->ip_fix=chk[0]->isChecked()? 1:0;
    if(++ms1000 > 99){
        ms1000=0;
    }
    ms10 &= 0xf;
    if(++ms10 > 9){
        ms10=0;
        voice_send();
    }
}
void fs01_qt::voice_send(){
    if((seg_state < seg_save) && voice_ba.size()){
        if(voice_ba.size() >= 4096){
            encode_ba(voice_ba.mid(0,4096),seg_append);
            voice_ba.remove(0,4096);
        }else{
            encode_ba(voice_ba,seg_save);
            voice_ba.clear();
        }
    }
}

qint16 fs01_qt::msg_box(QString s){
    QMessageBox msgBox;
    msgBox.setText(s);
//    msgBox.setInformativeText("Do you want to save your changes?");
    msgBox.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
    msgBox.setDefaultButton(QMessageBox::Ok);
    msgBox.setStyleSheet("* { font-size: 18pt; }");
    return msgBox.exec();
}
void fs01_qt::fp_click(int i){
    cmd_send(fs01->fs01_index[i]);
}
void fs01_qt::txt_append(QString s){
    out_txt[0]->append(s);
    out_txt[0]->verticalScrollBar()->setValue(out_txt[0]->verticalScrollBar()->maximum());
}

void fs01_qt::fp_btn_init(){
    fp_group=new QGroupBox();
    fp_grid= new QGridLayout(fp_group);
    fp_group->setFixedSize(x_max,y_max);
    for(int i=0;i<40;i++){
        if(i < 8){
            fp_hbox[i]=new QHBoxLayout();
            fp_grid->addLayout(fp_hbox[i],i,0,1,1);
        }
        fp_btn[i]=new QPushButton(fs01->enumToString(fs01->fs01_index[i]));
        fp_btn[i]->setFont(btn_font);
        fp_btn[i]->setStyleSheet("QPushButton {color:blue}");
        fp_hbox[i/5]->addWidget(fp_btn[i]);
        connect(fp_btn[i],&QPushButton::clicked,this,[i,this](bool){this->fp_click(i);});
    }
}
void fs01_qt::cmd_send(qint16 cmd){
QByteArray ba;
int16 len=0;
QString s;
    for(int j=0;j<40;j++){
        if(cmd==fs01->cmd_len[2*j]){
            len=fs01->cmd_len[2*j+1];
            j=40;
        }
    }
    switch(cmd){
        case fs01->Enroll_1:
        case fs01->Enroll_3:
        case fs01->Delete_Page:
        case fs01->Read_Page:
            k_input(QInputDialog::IntInput,"Nhập Page Id");
            if (dlg_struct.ok){
                ser->page_id=page_id=dlg_struct.sel_int;
            }
        break;
    }
    ba=fs01->ba_to_send(cmd,len,page_id);
    if(ser->serial->isOpen()){
        ser->serial_out(ba);
    }else{
//        memset(&u->udp_tx.bcc,0,sizeof(u->udp_tx));
        u->udp_send(cmd,len,page_id);
    }
    txt_append("PC: "+fs01->ba_to_string(ba));
}

void fs01_qt::btn_click(int k){
QByteArray ba;
QString s1,s,s2;
QStringList list;
qint16 n=0;
    page_id=0;
    s=out_txt[0]->toPlainText();
//    if(!s.startsWith("android:"))
        out_txt[0]->clear();
    switch(k){
        case Com_open:
            ser->serial_create(combo[0]->currentText());
            break;
        case Scan:
            serial_scan();
            break;
        case Detect:
            cmd_send(fs01->Finger_Detect);
            break;
        case Clear:
            s.remove("\n");
            if(s.startsWith("android:")){
                s2=s=s.mid(8);
                list=s.split(",");
                s="";
                for(int i=0;i<list.size();i++){
                    s1=list[i];
                    if(s1.contains("=")){
                        n=string_to_int(s1);
                        s1=s1.mid(0,s1.indexOf("="));
                    }
                    if(s2.contains("0x"))   s += "public static final int "+s1+" = 0x"+n2s(n,16)+";\n";
                    else                    s += "public static final int "+s1+" = "+n2s(n)+";\n";
                    n++;
                }
                out_txt[0]->setText(s);
            }else{
                out_txt[0]->clear();
                out_txt[0]->setText(fs01->ba_to_string(ser->rxtmp));
            }
            break;
        case Delete:
            k_input(QInputDialog::IntInput,"Nhập Page Id cần xóa 0-999");
            if (dlg_struct.ok){
                page_id=dlg_struct.sel_int;
                cmd_send(fs01->Delete_Page);
            }
            break;
        case Count:
            cmd_send(fs01->Get_Enroll_Count);
            break;
        case Identify:
            cmd_send(fs01->Identify);
            break;
        case Empty:
            if(msg_box("Xóa toàn bộ thư viện")){
                cmd_send(fs01->Empty);
            }
            break;
        case Enroll_1:
            cmd_send(fs01->Enroll_1);
            break;
        case Enroll:
            out_txt[0]->clear();
            cmd_send(fs01->Enroll_3);
            break;
        case Verify:
            ba=read_page_file();
            if(ba.size() == char_buf_len){
                memcpy(ser->fs01->char_buf,ba.data(),char_buf_len);
                memcpy(u->udp_tx.data,ba.data(),char_buf_len);
                cmd_send(fs01->Verify_Feature);
            }
            break;
        case Get_Enroll:
            out_txt[0]->clear();
            cmd_send(fs01->Enroll_RAM);
            break;
        case First_ID:
            cmd_send(fs01->Get_Empty_ID);
            break;
        case Set_pass:
            cmd_send(fs01->Set_Psw);
            break;
        case Veri_pass:
            cmd_send(fs01->Verify_Psw);
            break;
        case Read_fp:
            if(combo[1]->currentText().startsWith(u->ip_base)){
                cmd_send(fs01->Read_Page);
            }
            break;
        case Ip_Show:
            combo[1]->clear();
            for(int i=0;i<u->ip_list_max;i++){
                s=u->ip_base+n2s((u->ip_list[i] >> 8) & 0xff)+" "+u->ip_base+n2s(u->ip_list[i] & 0xff);
                combo[1]->addItem(s,u->ip_list[i]);
            }
//            lb[0]->setText(u->bcast_msg);
            break;
        case Bip_on:
            memset(&u->udp_tx.bcc,0,sizeof(u->udp_tx));
            u->udp_send(set_bip_on,0,0);
            lb[0]->setText(u->bcast_msg);
            break;
        case Cancel:
            cmd_send(fs01->FP_Cancel);
            break;
        case Ev2:
            ba=read_page_file();
            if(ba.size()==char_buf_len){
                memcpy(u->udp_tx.data,ba.data(),char_buf_len);
                u->udp_send(send_ev2,0,0);
            }
            break;
        case Ssid:
            ba=out_txt[0]->toPlainText().toUtf8();
            memcpy(u->udp_tx.data,ba.data(),ba.size());
            u->udp_send(add_ssid,ba.size(),0);
            break;
        case List:
            u->udp_send(file_list,ba.size(),0);
            break;
        case Play:
            k_input(QInputDialog::IntInput,"Nhập số thứ tự");
            if (dlg_struct.ok){
                page_id=dlg_struct.sel_int;
                u->udp_send(voice_play,ba.size(),page_id);
            }
            break;
        case Download:
            ba=read_wave_file();
            if(ba.size() < 44)  return;
            memcpy(&wav_hd.Riff.ChunkID,ba.data(),sizeof(wav_hd));
            int16 w_pcm,w_mono,w_rate,w_format;
            w_pcm=wav_hd.Fmt.Subchunk1Size; // 16
            w_mono=wav_hd.Fmt.NumChannels;  // 1
            w_rate=wav_hd.Fmt.SampleRate;   // 8000
            w_format=wav_hd.Fmt.AudioFormat;    // 1 : PCM
            s=w_file_name;
            s=s.mid(s.lastIndexOf("/")+1);
            s=s.mid(0,s.indexOf("_"));
            u->udp_tx.page_id=s.toInt();
            lb[0]->setText(n2s(u->udp_tx.page_id)+" "+n2s(w_pcm)+" "+n2s(w_format)+((w_mono == 1)? " Mono":" Stereo")+" "+n2s(w_rate));
            if((w_pcm != 16) || (w_format != 1) || (w_mono != 1) || (w_rate != 8000)){
                return;
            }
            ba=ba.mid(44);
            n_ima->e_predsample=0;
            n_ima->e_index=0;
            if(ba.size() > 4096*31)  ba.resize(4096*31);
            encode_ba(ba.mid(0,4096),seg_begin);
            voice_ba=ba.mid(4096);
            memset(voice_ba.data()+voice_ba.size()-1024,0,1024);
            ba.resize(8192);
            memset(ba.data(),0,ba.size());
            voice_ba += ba;
            break;
    }
}
void fs01_qt::encode_ba(QByteArray ba,int seg){
quint8 b8,b;
qint16 n16,len=ba.size()/4;
quint8 buf8[1024];
    for(int i=0;i<1024;i++){
        if(ba.size() >= 4){
            memcpy(&n16,ba.data(),2);
            b8 = n_ima->encoder(n16);
            b8 <<= 4;
            ba.remove(0,2);
            memcpy(&n16,ba.data(),2);
            b = n_ima->encoder(n16);
            b8 |= b;
            ba.remove(0,2);
            buf8[i]=b8;
        }else{
            b8 = n_ima->encoder(0);
            b8 <<= 4;
            b = n_ima->encoder(0);
            b8 |= b;
            buf8[i]=b8;
        }
    }
    memcpy(u->udp_tx.data,buf8,len);
    seg_state=u->udp_tx.seg_type=seg;
    u->udp_tx.pkt_type=PC_01;
    u->udp_tx.cmd=voice_download;
    u->udp_tx.seg_len=1024;
    ba.resize(sizeof(u->udp_tx));
    memcpy(ba.data(),&u->udp_tx.bcc,ba.size());
    u->socket_send(ba);
    txt_append(ba.data());
    qDebug() << "wav sending " << len << seg << voice_ba.size();

}

qint16 fs01_qt::string_to_int(QString s){
    QString s1="";
    for(int i=0;i<s.length();i++){
        if(s_num.contains(s.mid(i,1))) s1 += s.mid(i,1);
    }
    if(s.contains("0x"))    return s1.toInt(nullptr,16);
    else                    return s1.toInt();
}

void fs01_qt::k_input(QInputDialog::InputMode input_mode,QString prompt_txt){
    QInputDialog dlg_input;
    dlg_input.setLabelText(prompt_txt);
    dlg_input.setInputMode(input_mode);
    dlg_input.setOkButtonText("OK");
    dlg_input.setCancelButtonText("Cancel");
    dlg_input.setStyleSheet("* { font-size: 18pt; }");
    dlg_struct.ok=dlg_input.exec();
    dlg_struct.sel_int=dlg_input.intValue();
    dlg_struct.sel_str=dlg_input.textValue();
}
QByteArray fs01_qt::read_page_file()
{QByteArray ba;
    QFileDialog dialog_(this);
    QString filename=dialog_.getOpenFileName(this,"Open file","fp_save/",tr("Text (*.fpt)"));
    QFile mfile(filename);
    if (mfile.open( QIODevice::ReadOnly))
    {   ba=mfile.readAll();
        mfile.close();
    }
    return ba;
}
QByteArray fs01_qt::read_wave_file()
{QByteArray ba;
//    QFileDialog my_dialog(this);
    w_file_name=QFileDialog::getOpenFileName(this,"Open wave file","wav/",tr("Text (*.wav)"));
    QFile mfile(w_file_name);
    if (mfile.open( QIODevice::ReadOnly))
    {   ba=mfile.readAll();
        mfile.close();
    }
    qDebug() << w_file_name << mfile.size();
    return ba;
}

QString fs01_qt::btn_name(qint16 i){
    int index = metaObject()->indexOfEnumerator("btn_list");
    QMetaEnum metaEnum = metaObject()->enumerator(index);
    return metaEnum.valueToKey(i);
}
void fs01_qt::serial_scan(){
    p_btn[Com_open]->setEnabled(false);
    combo[0]->clear();
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {   combo[0]->addItem(info.portName());
        if(info.portName().length() > 2)
            p_btn[Com_open]->setEnabled(true);
    }
}

void fs01_qt::ui_init()
{   x_max = size.width()*75/100;
    y_max=size.height()*75/100;
    btn_font.setPixelSize(y_max*k_btn/1000);
    btn2_font.setPixelSize(y_max*k_btn/600);
    this->setFixedSize(x_max,y_max);

    QMetaEnum   btn_num = QMetaEnum::fromType<btn_list>();
//    qDebug() << "Btn count" << btn_num.keyCount();
    gr1=new QGroupBox(this);
    grid= new QGridLayout(gr1);
    gr1->setFixedSize(x_max-10,y_max-10);
    vbox=new QVBoxLayout();
    grid->addLayout(vbox,0,0,1,1);
    for(int i=0;i<btn_num.keyCount();i++){
        p_btn[i]=new QPushButton(btn_name(i));
        p_btn[i]->setFont(btn_font);
        p_btn[i]->setStyleSheet("QPushButton {color:green}");
        p_btn[i]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
        connect(p_btn[i],&QPushButton::clicked,this,[i,this](bool){this->btn_click(i);});
        if(i < 8){
            hbox[i]=new QHBoxLayout();
            in_txt[i]=new QLineEdit();
            in_txt[i]->setFont(btn_font);
            in_txt[i]->setStyleSheet("QLineEdit {color:red}");
            in_txt[i]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
            out_txt[i]=new QTextEdit();
            out_txt[i]->setStyleSheet("QTextEdit {color:blue}");
            out_txt[i]->setFont(btn_font);
            out_txt[i]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
            combo[i]=new QComboBox();
            combo[i]->setFont(btn_font);
            combo[i]->setStyleSheet("QComboBox {color:red}");
            chk[i]=new QCheckBox();
            chk[i]->setFont(btn_font);
            chk[i]->setStyleSheet("QCheckBox {color:red}");
            lb[i]=new QLabel("");
            lb[i]->setFrameStyle(1);
            lb[i]->setFont(btn2_font);
            lb[i]->setAlignment(Qt::AlignHCenter);
            lb[i]->setStyleSheet("QLabel {color:red}");
        }
        if(i<8){
            vbox->addLayout(hbox[i]);
        }
    }
    combo[1]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    hbox[0]->addWidget(combo[0]);

    lb[0]->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    lb[1]->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Preferred);
    lb[1]->setText("FS_ON");
    hbox[6]->addWidget(lb[0]);
    hbox[6]->addWidget(lb[1]);

    hbox[7]->addWidget(chk[0]);
    chk[0]->setText("IP");
    hbox[7]->addWidget(combo[1]);
    for(int i=0;i<btn_num.keyCount();i++){
        hbox[hbox_index[i]]->addWidget(p_btn[i]);
    }
    vbox->addWidget(out_txt[0]);
}

void fs01_qt::write_page_file(QString fname,QByteArray ba){
QFile mfile("fp_save/"+fname+".fpt");
    if (mfile.open( QIODevice::WriteOnly))
    {   mfile.write(ba);
        mfile.close();
    }

}

void fs01_qt::closeEvent(QCloseEvent *event)
{   fp_group->close();
    event->accept();
}

fs01_qt::~fs01_qt()
{
    delete ui;
}
