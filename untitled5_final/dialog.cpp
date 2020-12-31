#include "dialog.h"
#include "ui_dialog.h"
#include "qTh.h"
#include <iostream>
#include <math.h>

#define pi 3.141592
#define hlen 20.0
#define len 40.0
#define rad 100.0


using namespace std;
QBluetoothSocket *socket;
char c;
QByteArray msg;

//using namespace QBluetooth;
Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)

{
    ui->setupUi(this);
    myThread = new qTh(this);
    connect(myThread,SIGNAL(setAngle(float)),this,SLOT(showRotation(float)));
    myThread->start();
    socket=new QBluetoothSocket(QBluetoothServiceInfo::RfcommProtocol);
    socket->connectToService(QBluetoothAddress("98:D3:71:FD:6F:62"),1);
    socket->open(QIODevice::WriteOnly);
    QDataStream out(&msg,QIODevice::WriteOnly);
    //ui->label->setText(socket->peerAddress().toString());
}

Dialog::~Dialog()
{
    delete ui;
}




void Dialog::on_pushButton_put_pressed(){
    c='R';
    msg=QByteArray::fromRawData(&c,1);
    socket->write(msg.data(),msg.size());

}
void Dialog::on_pushButton_p_pressed(){
    c='P';
    msg=QByteArray::fromRawData(&c,1);
    socket->write(msg.data(),msg.size());


}
void Dialog::on_pushButton_S_pressed()
{
        c='S';
        msg=QByteArray::fromRawData(&c,1);
        socket->write(msg.data(),msg.size());


}

void Dialog::on_pushButton_N_pressed()
{

        c='N';
        msg=QByteArray::fromRawData(&c,1);
        socket->write(msg.data(),msg.size());

}

void Dialog::on_pushButton_W_pressed()
{

        c='W';
        msg=QByteArray::fromRawData(&c,1);
        socket->write(msg.data(),msg.size());

}

void Dialog::on_pushButton_E_pressed()
{

        c='E';
        msg=QByteArray::fromRawData(&c,1);
        socket->write(msg.data(),msg.size());

}
void Dialog::on_pushButton_pressed(){
    c='X';
    msg=QByteArray::fromRawData(&c,1);
    socket->write(msg.data(),msg.size());
}
void Dialog::on_pushButton_E_released(){
    c='Q';
    msg=QByteArray::fromRawData(&c,1);
    socket->write(msg.data(),msg.size());
}
void Dialog::on_pushButton_N_released(){
    c='Q';
    msg=QByteArray::fromRawData(&c,1);
    socket->write(msg.data(),msg.size());
}
void Dialog::on_pushButton_W_released(){
    c='Q';
    msg=QByteArray::fromRawData(&c,1);
    socket->write(msg.data(),msg.size());

}
void Dialog::on_pushButton_S_released(){
    c='Q';
    msg=QByteArray::fromRawData(&c,1);
    socket->write(msg.data(),msg.size());

}

void Dialog::showRotation(float a){
    float cosN=cos(a);
    float sinN=sin(a);
  //  ui->label->setText(QString::number(a));
    ui->pushButton_E->setGeometry(200.0+rad*cosN-hlen,150.0-rad*sinN-hlen,len,len);//qt angle direction diff w yaw
    ui->pushButton_N->setGeometry(200.0-rad*sinN-hlen,150.0-rad*cosN-hlen,len,len);
    ui->pushButton_W->setGeometry(200.0-rad*cosN-hlen,150.0+rad*sinN-hlen,len,len);
    ui->pushButton_S->setGeometry(200.0+rad*sinN-hlen,150.0+rad*cosN-hlen,len,len);
}
