//#include <termios.h>
//#include <stdio.h>
//#include <stdlib.h>
//#include <unistd.h>
//#include <fcntl.h>
//#include <signal.h>
//#include <sys/types.h>
//#include <sys/wait.h>
//#include <string.h>

#define DEFAULT_BAUDRATE   115200
#define DEFAULT_SERDEVICE  "/dev/ttyS0"
#define ENDMINITERM        0x1d

#ifndef DIALOG_H
#define DIALOG_H
#include <iostream>
#include <math.h>
#include <QDialog>
#include <QBluetoothSocket>
#include <QBluetoothServiceInfo>
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

private slots:
    void showRotation(float a);

    void on_pushButton_p_pressed();
    void on_pushButton_put_pressed();
    void on_pushButton_pressed();
    void on_pushButton_N_pressed();
    void on_pushButton_N_released();
    void on_pushButton_S_pressed();
    void on_pushButton_S_released();
    void on_pushButton_E_pressed();
    void on_pushButton_E_released();
    void on_pushButton_W_pressed();
    void on_pushButton_W_released();


private:
    Ui::Dialog *ui;
    qTh* myThread;

};

#endif // DIALOG_H
