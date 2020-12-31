/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.11.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QLabel *label;
    QPushButton *pushButton_E;
    QPushButton *pushButton_N;
    QPushButton *pushButton_W;
    QPushButton *pushButton_S;
    QPushButton *pushButton;
    QLabel *label_2;
    QPushButton *pushButton_put;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(400, 300);
        label = new QLabel(Dialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(310, 260, 68, 22));
        pushButton_E = new QPushButton(Dialog);
        pushButton_E->setObjectName(QStringLiteral("pushButton_E"));
        pushButton_E->setGeometry(QRect(280, 130, 40, 40));
        pushButton_N = new QPushButton(Dialog);
        pushButton_N->setObjectName(QStringLiteral("pushButton_N"));
        pushButton_N->setGeometry(QRect(180, 30, 40, 40));
        pushButton_W = new QPushButton(Dialog);
        pushButton_W->setObjectName(QStringLiteral("pushButton_W"));
        pushButton_W->setGeometry(QRect(80, 130, 40, 40));
        pushButton_S = new QPushButton(Dialog);
        pushButton_S->setObjectName(QStringLiteral("pushButton_S"));
        pushButton_S->setGeometry(QRect(180, 230, 40, 40));
        pushButton = new QPushButton(Dialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(160, 110, 80, 80));
        label_2 = new QLabel(Dialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(190, 0, 20, 22));
        pushButton_put = new QPushButton(Dialog);
        pushButton_put->setObjectName(QStringLiteral("pushButton_put"));
        pushButton_put->setGeometry(QRect(260, 230, 50, 50));
        pushButton_2 = new QPushButton(Dialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 30, 99, 30));

        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Dialog", nullptr));
        label->setText(QString());
        pushButton_E->setText(QString());
        pushButton_N->setText(QString());
        pushButton_W->setText(QString());
        pushButton_S->setText(QString());
        pushButton->setText(QApplication::translate("Dialog", "balancing", nullptr));
        label_2->setText(QApplication::translate("Dialog", "N", nullptr));
        pushButton_put->setText(QApplication::translate("Dialog", "Put", nullptr));
        pushButton_2->setText(QApplication::translate("Dialog", "p", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
