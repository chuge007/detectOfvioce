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
    QLabel *yCurPos;
    QPushButton *xSubBtn_2;
    QLabel *label_9;
    QLabel *label_6;
    QLabel *label_7;
    QPushButton *yAddBtn_2;
    QLabel *label_8;
    QLabel *xCurPos;
    QPushButton *xAddBtn_2;
    QPushButton *ySubBtn_2;
    QPushButton *rAddBtn_2;
    QPushButton *rSubBtn_2;
    QLabel *rCurPos;
    QLabel *label_10;
    QLabel *label_11;
    QFrame *frame_trans;
    QLabel *label_3;
    QLineEdit *yTrans;
    QLineEdit *xTrans;
    QLineEdit *rTrans;
    QLineEdit *zTrans;
    QFrame *frame_star;
    QLabel *label_14;
    QLabel *label_2;
    QLineEdit *rEnd;
    QLineEdit *xEnd;
    QLabel *label_12;
    QLineEdit *yEnd;
    QLabel *label_13;
    QLineEdit *zEnd;
    QLabel *label_17;
    QPushButton *setCurposToEnd_but;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *setCursPosToTrans_but;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *zCurPos;
    QPushButton *zSubBtn_2;
    QPushButton *zAddBtn_2;

    void setupUi(QDialog *addRoute_dialog)
    {
        if (addRoute_dialog->objectName().isEmpty())
            addRoute_dialog->setObjectName(QString::fromUtf8("addRoute_dialog"));
        addRoute_dialog->resize(841, 499);
        yCurPos = new QLabel(addRoute_dialog);
        yCurPos->setObjectName(QString::fromUtf8("yCurPos"));
        yCurPos->setGeometry(QRect(610, 80, 151, 31));
        QFont font;
        font.setFamily(QString::fromUtf8("3ds"));
        font.setPointSize(11);
        yCurPos->setFont(font);
        xSubBtn_2 = new QPushButton(addRoute_dialog);
        xSubBtn_2->setObjectName(QString::fromUtf8("xSubBtn_2"));
        xSubBtn_2->setGeometry(QRect(700, 220, 91, 41));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(xSubBtn_2->sizePolicy().hasHeightForWidth());
        xSubBtn_2->setSizePolicy(sizePolicy);
        xSubBtn_2->setAutoRepeat(false);
        xSubBtn_2->setAutoExclusive(false);
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
        yAddBtn_2 = new QPushButton(addRoute_dialog);
        yAddBtn_2->setObjectName(QString::fromUtf8("yAddBtn_2"));
        yAddBtn_2->setGeometry(QRect(560, 270, 91, 41));
        sizePolicy.setHeightForWidth(yAddBtn_2->sizePolicy().hasHeightForWidth());
        yAddBtn_2->setSizePolicy(sizePolicy);
        yAddBtn_2->setAutoRepeat(false);
        yAddBtn_2->setAutoExclusive(false);
        label_8 = new QLabel(addRoute_dialog);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(770, 30, 41, 31));
        label_8->setFont(font1);
        xCurPos = new QLabel(addRoute_dialog);
        xCurPos->setObjectName(QString::fromUtf8("xCurPos"));
        xCurPos->setGeometry(QRect(610, 30, 151, 31));
        xCurPos->setFont(font);
        xAddBtn_2 = new QPushButton(addRoute_dialog);
        xAddBtn_2->setObjectName(QString::fromUtf8("xAddBtn_2"));
        xAddBtn_2->setGeometry(QRect(560, 220, 91, 41));
        sizePolicy.setHeightForWidth(xAddBtn_2->sizePolicy().hasHeightForWidth());
        xAddBtn_2->setSizePolicy(sizePolicy);
        xAddBtn_2->setAutoRepeat(false);
        xAddBtn_2->setAutoExclusive(false);
        ySubBtn_2 = new QPushButton(addRoute_dialog);
        ySubBtn_2->setObjectName(QString::fromUtf8("ySubBtn_2"));
        ySubBtn_2->setGeometry(QRect(700, 270, 91, 41));
        sizePolicy.setHeightForWidth(ySubBtn_2->sizePolicy().hasHeightForWidth());
        ySubBtn_2->setSizePolicy(sizePolicy);
        ySubBtn_2->setAutoRepeat(false);
        ySubBtn_2->setAutoExclusive(false);
        rAddBtn_2 = new QPushButton(addRoute_dialog);
        rAddBtn_2->setObjectName(QString::fromUtf8("rAddBtn_2"));
        rAddBtn_2->setGeometry(QRect(700, 370, 91, 41));
        sizePolicy.setHeightForWidth(rAddBtn_2->sizePolicy().hasHeightForWidth());
        rAddBtn_2->setSizePolicy(sizePolicy);
        rAddBtn_2->setAutoRepeat(false);
        rAddBtn_2->setAutoExclusive(false);
        rSubBtn_2 = new QPushButton(addRoute_dialog);
        rSubBtn_2->setObjectName(QString::fromUtf8("rSubBtn_2"));
        rSubBtn_2->setGeometry(QRect(560, 370, 91, 41));
        sizePolicy.setHeightForWidth(rSubBtn_2->sizePolicy().hasHeightForWidth());
        rSubBtn_2->setSizePolicy(sizePolicy);
        rSubBtn_2->setAutoRepeat(false);
        rSubBtn_2->setAutoExclusive(false);
        rCurPos = new QLabel(addRoute_dialog);
        rCurPos->setObjectName(QString::fromUtf8("rCurPos"));
        rCurPos->setGeometry(QRect(610, 160, 151, 31));
        rCurPos->setFont(font);
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
        frame_trans->setGeometry(QRect(20, 170, 481, 81));
        frame_trans->setFrameShape(QFrame::StyledPanel);
        frame_trans->setFrameShadow(QFrame::Raised);
        label_3 = new QLabel(frame_trans);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 16, 61, 31));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        label_3->setFont(font2);
        yTrans = new QLineEdit(frame_trans);
        yTrans->setObjectName(QString::fromUtf8("yTrans"));
        yTrans->setGeometry(QRect(150, 20, 91, 31));
        xTrans = new QLineEdit(frame_trans);
        xTrans->setObjectName(QString::fromUtf8("xTrans"));
        xTrans->setGeometry(QRect(60, 20, 81, 31));
        rTrans = new QLineEdit(frame_trans);
        rTrans->setObjectName(QString::fromUtf8("rTrans"));
        rTrans->setGeometry(QRect(370, 20, 91, 31));
        zTrans = new QLineEdit(frame_trans);
        zTrans->setObjectName(QString::fromUtf8("zTrans"));
        zTrans->setGeometry(QRect(250, 20, 91, 31));
        frame_star = new QFrame(addRoute_dialog);
        frame_star->setObjectName(QString::fromUtf8("frame_star"));
        frame_star->setGeometry(QRect(20, 80, 481, 80));
        frame_star->setFrameShape(QFrame::StyledPanel);
        frame_star->setFrameShadow(QFrame::Raised);
        label_14 = new QLabel(frame_star);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(80, 0, 21, 31));
        label_14->setFont(font);
        label_14->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        label_2 = new QLabel(frame_star);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 36, 51, 31));
        label_2->setFont(font2);
        rEnd = new QLineEdit(frame_star);
        rEnd->setObjectName(QString::fromUtf8("rEnd"));
        rEnd->setGeometry(QRect(370, 40, 91, 31));
        xEnd = new QLineEdit(frame_star);
        xEnd->setObjectName(QString::fromUtf8("xEnd"));
        xEnd->setGeometry(QRect(60, 40, 81, 31));
        label_12 = new QLabel(frame_star);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(390, 0, 21, 31));
        label_12->setFont(font);
        label_12->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        yEnd = new QLineEdit(frame_star);
        yEnd->setObjectName(QString::fromUtf8("yEnd"));
        yEnd->setGeometry(QRect(150, 40, 91, 31));
        label_13 = new QLabel(frame_star);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(180, 0, 21, 31));
        label_13->setFont(font);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        zEnd = new QLineEdit(frame_star);
        zEnd->setObjectName(QString::fromUtf8("zEnd"));
        zEnd->setGeometry(QRect(250, 40, 91, 31));
        label_17 = new QLabel(frame_star);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(280, 0, 21, 31));
        label_17->setFont(font);
        label_17->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        setCurposToEnd_but = new QPushButton(addRoute_dialog);
        setCurposToEnd_but->setObjectName(QString::fromUtf8("setCurposToEnd_but"));
        setCurposToEnd_but->setGeometry(QRect(20, 280, 161, 41));
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
        setCursPosToTrans_but->setGeometry(QRect(220, 280, 151, 41));
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
        zCurPos = new QLabel(addRoute_dialog);
        zCurPos->setObjectName(QString::fromUtf8("zCurPos"));
        zCurPos->setGeometry(QRect(610, 120, 151, 31));
        zCurPos->setFont(font);
        zSubBtn_2 = new QPushButton(addRoute_dialog);
        zSubBtn_2->setObjectName(QString::fromUtf8("zSubBtn_2"));
        zSubBtn_2->setGeometry(QRect(560, 320, 91, 41));
        sizePolicy.setHeightForWidth(zSubBtn_2->sizePolicy().hasHeightForWidth());
        zSubBtn_2->setSizePolicy(sizePolicy);
        zSubBtn_2->setAutoRepeat(false);
        zSubBtn_2->setAutoExclusive(false);
        zAddBtn_2 = new QPushButton(addRoute_dialog);
        zAddBtn_2->setObjectName(QString::fromUtf8("zAddBtn_2"));
        zAddBtn_2->setGeometry(QRect(700, 320, 91, 41));
        sizePolicy.setHeightForWidth(zAddBtn_2->sizePolicy().hasHeightForWidth());
        zAddBtn_2->setSizePolicy(sizePolicy);
        zAddBtn_2->setAutoRepeat(false);
        zAddBtn_2->setAutoExclusive(false);

        retranslateUi(addRoute_dialog);

        QMetaObject::connectSlotsByName(addRoute_dialog);
    } // setupUi

    void retranslateUi(QDialog *addRoute_dialog)
    {
        addRoute_dialog->setWindowTitle(QApplication::translate("addRoute_dialog", "Create Route", nullptr));
        yCurPos->setText(QString());
        xSubBtn_2->setText(QApplication::translate("addRoute_dialog", "X-", nullptr));
        label_9->setText(QApplication::translate("addRoute_dialog", "mm", nullptr));
        label_6->setText(QApplication::translate("addRoute_dialog", "x\357\274\232", nullptr));
        label_7->setText(QApplication::translate("addRoute_dialog", "y\357\274\232", nullptr));
        yAddBtn_2->setText(QApplication::translate("addRoute_dialog", "Y+", nullptr));
        label_8->setText(QApplication::translate("addRoute_dialog", "mm", nullptr));
        xCurPos->setText(QString());
        xAddBtn_2->setText(QApplication::translate("addRoute_dialog", "X+", nullptr));
        ySubBtn_2->setText(QApplication::translate("addRoute_dialog", "Y-", nullptr));
        rAddBtn_2->setText(QApplication::translate("addRoute_dialog", "R+", nullptr));
        rSubBtn_2->setText(QApplication::translate("addRoute_dialog", "R-", nullptr));
        rCurPos->setText(QString());
        label_10->setText(QApplication::translate("addRoute_dialog", "R\357\274\232", nullptr));
        label_11->setText(QApplication::translate("addRoute_dialog", "mm", nullptr));
        label_3->setText(QApplication::translate("addRoute_dialog", "\350\277\207\346\270\241\347\202\271\357\274\232", nullptr));
        yTrans->setText(QString());
        xTrans->setText(QString());
        rTrans->setText(QString());
        zTrans->setText(QString());
        label_14->setText(QApplication::translate("addRoute_dialog", "X", nullptr));
        label_2->setText(QApplication::translate("addRoute_dialog", "\347\273\210\347\202\271\357\274\232", nullptr));
        rEnd->setText(QString());
        xEnd->setText(QString());
        label_12->setText(QApplication::translate("addRoute_dialog", "R", nullptr));
        yEnd->setText(QString());
        label_13->setText(QApplication::translate("addRoute_dialog", "Y", nullptr));
        zEnd->setText(QString());
        label_17->setText(QApplication::translate("addRoute_dialog", "Z", nullptr));
        setCurposToEnd_but->setText(QApplication::translate("addRoute_dialog", "\350\256\276\345\256\232\344\270\272\347\273\210\347\202\271", nullptr));
        pushButton->setText(QApplication::translate("addRoute_dialog", "OK", nullptr));
        pushButton_2->setText(QApplication::translate("addRoute_dialog", "Cancel", nullptr));
        setCursPosToTrans_but->setText(QApplication::translate("addRoute_dialog", "\350\256\276\345\256\232\344\270\272\350\277\207\345\272\246\347\202\271", nullptr));
        label_15->setText(QApplication::translate("addRoute_dialog", "Z\357\274\232", nullptr));
        label_16->setText(QApplication::translate("addRoute_dialog", "mm", nullptr));
        zCurPos->setText(QString());
        zSubBtn_2->setText(QApplication::translate("addRoute_dialog", "Z-", nullptr));
        zAddBtn_2->setText(QApplication::translate("addRoute_dialog", "Z+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class addRoute_dialog: public Ui_addRoute_dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDROUTE_DIALOG_H
