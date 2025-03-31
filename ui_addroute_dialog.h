/********************************************************************************
** Form generated from reading UI file 'addroute_dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDROUTE_DIALOG_H
#define UI_ADDROUTE_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_addRoute_dialog
{
public:
    QLabel *yCurPos_lab;
    QPushButton *RxSub_btn;
    QLabel *label_9;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *RyAdd_btn;
    QLabel *label_8;
    QLabel *xCurPos_lab;
    QPushButton *RxAdd_btn;
    QPushButton *RySub_btn;
    QPushButton *RrAdd_btn;
    QPushButton *RrSub_btn;
    QLabel *rCurPos_lab;
    QLabel *label_10;
    QLabel *label_11;
    QFrame *frame_trans;
    QLabel *label_3;
    QLineEdit *yTrans_lin;
    QLineEdit *xTrans_lin;
    QLineEdit *rTrans_lin;
    QLineEdit *zTrans_lin;
    QFrame *frame_star;
    QLabel *label_14;
    QLabel *label_2;
    QLineEdit *rEnd_lin;
    QLineEdit *xEnd_lin;
    QLabel *label_12;
    QLineEdit *yEnd_lin;
    QLabel *label_13;
    QLineEdit *zEnd_lin;
    QLabel *label_17;
    QPushButton *setCurposToEnd_but;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *setCursPosToTrans_but;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *zCurPos_lab;
    QPushButton *RzSub_Btn;
    QPushButton *RzAdd_btn;

    void setupUi(QDialog *addRoute_dialog)
    {
        if (addRoute_dialog->objectName().isEmpty())
            addRoute_dialog->setObjectName(QString::fromUtf8("addRoute_dialog"));
        addRoute_dialog->resize(816, 499);
        yCurPos_lab = new QLabel(addRoute_dialog);
        yCurPos_lab->setObjectName(QString::fromUtf8("yCurPos_lab"));
        yCurPos_lab->setGeometry(QRect(610, 80, 151, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("3ds"));
        font.setPointSize(11);
        yCurPos_lab->setFont(font);
        RxSub_btn = new QPushButton(addRoute_dialog);
        RxSub_btn->setObjectName(QString::fromUtf8("RxSub_btn"));
        RxSub_btn->setGeometry(QRect(700, 220, 91, 41));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(RxSub_btn->sizePolicy().hasHeightForWidth());
        RxSub_btn->setSizePolicy(sizePolicy);
        RxSub_btn->setAutoRepeat(false);
        RxSub_btn->setAutoExclusive(false);
        label_9 = new QLabel(addRoute_dialog);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(770, 80, 41, 31));
        QFont font1;
        font1.setFamily(QString::fromUtf8("SansSerif"));
        font1.setPointSize(11);
        label_9->setFont(font1);
        label_6 = new QLabel(addRoute_dialog);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(570, 30, 41, 31));
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_7 = new QLabel(addRoute_dialog);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(570, 80, 41, 31));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        RyAdd_btn = new QPushButton(addRoute_dialog);
        RyAdd_btn->setObjectName(QString::fromUtf8("RyAdd_btn"));
        RyAdd_btn->setGeometry(QRect(560, 270, 91, 41));
        sizePolicy.setHeightForWidth(RyAdd_btn->sizePolicy().hasHeightForWidth());
        RyAdd_btn->setSizePolicy(sizePolicy);
        RyAdd_btn->setAutoRepeat(false);
        RyAdd_btn->setAutoExclusive(false);
        label_8 = new QLabel(addRoute_dialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(770, 30, 41, 31));
        label_8->setFont(font1);
        xCurPos_lab = new QLabel(addRoute_dialog);
        xCurPos_lab->setObjectName(QString::fromUtf8("xCurPos_lab"));
        xCurPos_lab->setGeometry(QRect(610, 30, 151, 31));
        xCurPos_lab->setFont(font);
        RxAdd_btn = new QPushButton(addRoute_dialog);
        RxAdd_btn->setObjectName(QString::fromUtf8("RxAdd_btn"));
        RxAdd_btn->setGeometry(QRect(560, 220, 91, 41));
        sizePolicy.setHeightForWidth(RxAdd_btn->sizePolicy().hasHeightForWidth());
        RxAdd_btn->setSizePolicy(sizePolicy);
        RxAdd_btn->setAutoRepeat(false);
        RxAdd_btn->setAutoExclusive(false);
        RySub_btn = new QPushButton(addRoute_dialog);
        RySub_btn->setObjectName(QString::fromUtf8("RySub_btn"));
        RySub_btn->setGeometry(QRect(700, 270, 91, 41));
        sizePolicy.setHeightForWidth(RySub_btn->sizePolicy().hasHeightForWidth());
        RySub_btn->setSizePolicy(sizePolicy);
        RySub_btn->setAutoRepeat(false);
        RySub_btn->setAutoExclusive(false);
        RrAdd_btn = new QPushButton(addRoute_dialog);
        RrAdd_btn->setObjectName(QString::fromUtf8("RrAdd_btn"));
        RrAdd_btn->setGeometry(QRect(700, 370, 91, 41));
        sizePolicy.setHeightForWidth(RrAdd_btn->sizePolicy().hasHeightForWidth());
        RrAdd_btn->setSizePolicy(sizePolicy);
        RrAdd_btn->setAutoRepeat(false);
        RrAdd_btn->setAutoExclusive(false);
        RrSub_btn = new QPushButton(addRoute_dialog);
        RrSub_btn->setObjectName(QString::fromUtf8("RrSub_btn"));
        RrSub_btn->setGeometry(QRect(560, 370, 91, 41));
        sizePolicy.setHeightForWidth(RrSub_btn->sizePolicy().hasHeightForWidth());
        RrSub_btn->setSizePolicy(sizePolicy);
        RrSub_btn->setAutoRepeat(false);
        RrSub_btn->setAutoExclusive(false);
        rCurPos_lab = new QLabel(addRoute_dialog);
        rCurPos_lab->setObjectName(QString::fromUtf8("rCurPos_lab"));
        rCurPos_lab->setGeometry(QRect(610, 160, 151, 31));
        rCurPos_lab->setFont(font);
        label_10 = new QLabel(addRoute_dialog);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(570, 160, 41, 31));
        label_10->setFont(font);
        label_10->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_11 = new QLabel(addRoute_dialog);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(770, 160, 41, 31));
        label_11->setFont(font1);
        frame_trans = new QFrame(addRoute_dialog);
        frame_trans->setObjectName(QString::fromUtf8("frame_trans"));
        frame_trans->setGeometry(QRect(20, 170, 541, 81));
        frame_trans->setFrameShape(QFrame::StyledPanel);
        frame_trans->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame_trans);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 16, 91, 41));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        label_3->setFont(font2);
        yTrans_lin = new QLineEdit(frame_trans);
        yTrans_lin->setObjectName(QString::fromUtf8("yTrans_lin"));
        yTrans_lin->setGeometry(QRect(190, 20, 101, 31));
        xTrans_lin = new QLineEdit(frame_trans);
        xTrans_lin->setObjectName(QString::fromUtf8("xTrans_lin"));
        xTrans_lin->setGeometry(QRect(80, 20, 101, 31));
        rTrans_lin = new QLineEdit(frame_trans);
        rTrans_lin->setObjectName(QString::fromUtf8("rTrans_lin"));
        rTrans_lin->setGeometry(QRect(420, 20, 101, 31));
        zTrans_lin = new QLineEdit(frame_trans);
        zTrans_lin->setObjectName(QString::fromUtf8("zTrans_lin"));
        zTrans_lin->setGeometry(QRect(300, 20, 101, 31));
        frame_star = new QFrame(addRoute_dialog);
        frame_star->setObjectName(QString::fromUtf8("frame_star"));
        frame_star->setGeometry(QRect(20, 80, 541, 80));
        frame_star->setFrameShape(QFrame::StyledPanel);
        frame_star->setFrameShadow(QFrame::Raised);
        label_14 = new QLabel(frame_star);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(110, 0, 21, 31));
        label_14->setFont(font);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(frame_star);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 36, 91, 31));
        label_2->setFont(font2);
        rEnd_lin = new QLineEdit(frame_star);
        rEnd_lin->setObjectName(QString::fromUtf8("rEnd_lin"));
        rEnd_lin->setGeometry(QRect(420, 40, 101, 31));
        xEnd_lin = new QLineEdit(frame_star);
        xEnd_lin->setObjectName(QString::fromUtf8("xEnd_lin"));
        xEnd_lin->setGeometry(QRect(80, 40, 101, 31));
        label_12 = new QLabel(frame_star);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(450, 0, 21, 31));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        yEnd_lin = new QLineEdit(frame_star);
        yEnd_lin->setObjectName(QString::fromUtf8("yEnd_lin"));
        yEnd_lin->setGeometry(QRect(190, 40, 101, 31));
        label_13 = new QLabel(frame_star);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(220, 0, 21, 31));
        label_13->setFont(font);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        zEnd_lin = new QLineEdit(frame_star);
        zEnd_lin->setObjectName(QString::fromUtf8("zEnd_lin"));
        zEnd_lin->setGeometry(QRect(300, 40, 101, 31));
        label_17 = new QLabel(frame_star);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(330, 0, 21, 31));
        label_17->setFont(font);
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        setCurposToEnd_but = new QPushButton(addRoute_dialog);
        setCurposToEnd_but->setObjectName(QString::fromUtf8("setCurposToEnd_but"));
        setCurposToEnd_but->setGeometry(QRect(120, 280, 161, 41));
        sizePolicy.setHeightForWidth(setCurposToEnd_but->sizePolicy().hasHeightForWidth());
        setCurposToEnd_but->setSizePolicy(sizePolicy);
        setCurposToEnd_but->setAutoRepeat(false);
        setCurposToEnd_but->setAutoExclusive(false);
        layoutWidget = new QWidget(addRoute_dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(560, 440, 240, 30));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        setCursPosToTrans_but = new QPushButton(addRoute_dialog);
        setCursPosToTrans_but->setObjectName(QString::fromUtf8("setCursPosToTrans_but"));
        setCursPosToTrans_but->setGeometry(QRect(350, 280, 151, 41));
        sizePolicy.setHeightForWidth(setCursPosToTrans_but->sizePolicy().hasHeightForWidth());
        setCursPosToTrans_but->setSizePolicy(sizePolicy);
        setCursPosToTrans_but->setAutoRepeat(false);
        setCursPosToTrans_but->setAutoExclusive(false);
        label_15 = new QLabel(addRoute_dialog);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(570, 120, 41, 31));
        label_15->setFont(font);
        label_15->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_16 = new QLabel(addRoute_dialog);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(770, 120, 41, 31));
        label_16->setFont(font1);
        zCurPos_lab = new QLabel(addRoute_dialog);
        zCurPos_lab->setObjectName(QString::fromUtf8("zCurPos_lab"));
        zCurPos_lab->setGeometry(QRect(610, 120, 151, 31));
        zCurPos_lab->setFont(font);
        RzSub_Btn = new QPushButton(addRoute_dialog);
        RzSub_Btn->setObjectName(QString::fromUtf8("RzSub_Btn"));
        RzSub_Btn->setGeometry(QRect(560, 320, 91, 41));
        sizePolicy.setHeightForWidth(RzSub_Btn->sizePolicy().hasHeightForWidth());
        RzSub_Btn->setSizePolicy(sizePolicy);
        RzSub_Btn->setAutoRepeat(false);
        RzSub_Btn->setAutoExclusive(false);
        RzAdd_btn = new QPushButton(addRoute_dialog);
        RzAdd_btn->setObjectName(QString::fromUtf8("RzAdd_btn"));
        RzAdd_btn->setGeometry(QRect(700, 320, 91, 41));
        sizePolicy.setHeightForWidth(RzAdd_btn->sizePolicy().hasHeightForWidth());
        RzAdd_btn->setSizePolicy(sizePolicy);
        RzAdd_btn->setAutoRepeat(false);
        RzAdd_btn->setAutoExclusive(false);

        retranslateUi(addRoute_dialog);

        QMetaObject::connectSlotsByName(addRoute_dialog);
    } // setupUi

    void retranslateUi(QDialog *addRoute_dialog)
    {
        addRoute_dialog->setWindowTitle(QApplication::translate("addRoute_dialog", "Create Route", nullptr));
        yCurPos_lab->setText(QString());
        RxSub_btn->setText(QApplication::translate("addRoute_dialog", "X-", nullptr));
        label_9->setText(QApplication::translate("addRoute_dialog", "mm", nullptr));
        label_6->setText(QApplication::translate("addRoute_dialog", "x\357\274\232", nullptr));
        label_7->setText(QApplication::translate("addRoute_dialog", "y\357\274\232", nullptr));
        RyAdd_btn->setText(QApplication::translate("addRoute_dialog", "Y+", nullptr));
        label_8->setText(QApplication::translate("addRoute_dialog", "mm", nullptr));
        xCurPos_lab->setText(QString());
        RxAdd_btn->setText(QApplication::translate("addRoute_dialog", "X+", nullptr));
        RySub_btn->setText(QApplication::translate("addRoute_dialog", "Y-", nullptr));
        RrAdd_btn->setText(QApplication::translate("addRoute_dialog", "R+", nullptr));
        RrSub_btn->setText(QApplication::translate("addRoute_dialog", "R-", nullptr));
        rCurPos_lab->setText(QString());
        label_10->setText(QApplication::translate("addRoute_dialog", "R\357\274\232", nullptr));
        label_11->setText(QApplication::translate("addRoute_dialog", "mm", nullptr));
        label_3->setText(QApplication::translate("addRoute_dialog", "\350\277\207\346\270\241\347\202\271\357\274\232", nullptr));
        yTrans_lin->setText(QString());
        xTrans_lin->setText(QString());
        rTrans_lin->setText(QString());
        zTrans_lin->setText(QString());
        label_14->setText(QApplication::translate("addRoute_dialog", "X", nullptr));
        label_2->setText(QApplication::translate("addRoute_dialog", "\347\273\210\347\202\271\357\274\232", nullptr));
        rEnd_lin->setText(QString());
        xEnd_lin->setText(QString());
        label_12->setText(QApplication::translate("addRoute_dialog", "R", nullptr));
        yEnd_lin->setText(QString());
        label_13->setText(QApplication::translate("addRoute_dialog", "Y", nullptr));
        zEnd_lin->setText(QString());
        label_17->setText(QApplication::translate("addRoute_dialog", "Z", nullptr));
        setCurposToEnd_but->setText(QApplication::translate("addRoute_dialog", "\350\256\276\345\256\232\344\270\272\347\273\210\347\202\271", nullptr));
        pushButton->setText(QApplication::translate("addRoute_dialog", "OK", nullptr));
        pushButton_2->setText(QApplication::translate("addRoute_dialog", "Cancel", nullptr));
        setCursPosToTrans_but->setText(QApplication::translate("addRoute_dialog", "\350\256\276\345\256\232\344\270\272\350\277\207\345\272\246\347\202\271", nullptr));
        label_15->setText(QApplication::translate("addRoute_dialog", "Z\357\274\232", nullptr));
        label_16->setText(QApplication::translate("addRoute_dialog", "mm", nullptr));
        zCurPos_lab->setText(QString());
        RzSub_Btn->setText(QApplication::translate("addRoute_dialog", "Z-", nullptr));
        RzAdd_btn->setText(QApplication::translate("addRoute_dialog", "Z+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addRoute_dialog: public Ui_addRoute_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDROUTE_DIALOG_H
