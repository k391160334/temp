
#define DEFAULT_BAUDRATE   115200
#define DEFAULT_SERDEVICE  "/dev/ttyS0"
#define ENDMINITERM        0x1d

#ifndef DIALOG_H
#define DIALOG_H
#include <iostream>
#include <math.h>
#include <QDialog>
#include<QMainWindow>
#include<QTcpSocket>
#include "qTh.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
public slots:
    void onReadyRead();

private :
    QTcpSocket _socket;


    void on_id_combo_activated(int index);

    void on_kick_combo_currentIndexChanged(int index);

    void on_id_combo_currentIndexChanged(int index);

    void on_submit_btn_clicked();

private:
    Ui::Dialog *ui;
    qTh* myThread;

};

#endif // DIALOG_H
