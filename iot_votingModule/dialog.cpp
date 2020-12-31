#include "dialog.h"
#include "ui_dialog.h"
#include "qTh.h"
#include <QApplication>
#include <iostream>
#include<QDebug>
#include<QHostAddress>

#define MEM_NUM 4

using namespace std;
QByteArray msg;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    _socket(this)
{
    ui->setupUi(this);
    _socket.connectToHost(QHostAddress("127.0.0.1"),4242);
    connect(&_socket,SIGNAL(readyRead(),this,SLOT(onReadyRead())));
}



Dialog::~Dialog()
{
    delete ui;
}
int vote_rslt[MEM_NUM+1]={0};
int temp_id=0;
int temp_kick=0;
void Dialog::onReadyRead()
{
    QByteArray datas=_socket.readAll();
    qDebug() << datas;
    _socket.write(QByteArray("ok !\n"));

}
void Dialog::on_kick_combo_currentIndexChanged(int index)
{
    temp_kick=index;
}

void Dialog::on_id_combo_currentIndexChanged(int index)
{
    temp_id=index;
}

void Dialog::on_submit_btn_clicked()
{
    if(temp_id!=0&&temp_kick!=0){
        vote_rslt[temp_id]=temp_kick;
        temp_id=0;
        temp_kick=0;
    }
    if (vote_rslt[MEMNUM]!=0){

    }
}
