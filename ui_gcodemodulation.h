/********************************************************************************
** Form generated from reading UI file 'gcodemodulation.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GCODEMODULATION_H
#define UI_GCODEMODULATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gCodeModulation
{
public:
    QFrame *frame;
    QLabel *label;
    QSpinBox *sbPausLine;
    QPushButton *pbPaus;
    QLabel *label_2;
    QLabel *label_3;
    QPushButton *pbdeleteCodeLine;
    QPushButton *pbALLPaus;
    QPushButton *pbDeleteALLPaus;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_7;
    QLabel *label_9;
    QLabel *label_10;
    QScrollArea *rangeContainer;
    QWidget *scrollAreaWidgetContents;
    QPushButton *addRangeBtn;
    QPushButton *pbAganStart;
    QPushButton *saveVBtn;
    QLabel *label_6;
    QDoubleSpinBox *dsbLineV;
    QDoubleSpinBox *dsbAccV;
    QPlainTextEdit *pTEgcode;
    QPushButton *TransmissionBtn;

    void setupUi(QWidget *gCodeModulation)
    {
        if (gCodeModulation->objectName().isEmpty())
            gCodeModulation->setObjectName(QString::fromUtf8("gCodeModulation"));
        gCodeModulation->resize(1399, 936);
        gCodeModulation->setMaximumSize(QSize(1399, 936));
        frame = new QFrame(gCodeModulation);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 1401, 941));
        frame->setMaximumSize(QSize(1401, 944));
        frame->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(730, 100, 311, 51));
        sbPausLine = new QSpinBox(frame);
        sbPausLine->setObjectName(QString::fromUtf8("sbPausLine"));
        sbPausLine->setGeometry(QRect(860, 60, 81, 31));
        pbPaus = new QPushButton(frame);
        pbPaus->setObjectName(QString::fromUtf8("pbPaus"));
        pbPaus->setGeometry(QRect(860, 160, 80, 31));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(730, 60, 101, 31));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(730, 210, 211, 31));
        pbdeleteCodeLine = new QPushButton(frame);
        pbdeleteCodeLine->setObjectName(QString::fromUtf8("pbdeleteCodeLine"));
        pbdeleteCodeLine->setGeometry(QRect(860, 250, 80, 31));
        pbALLPaus = new QPushButton(frame);
        pbALLPaus->setObjectName(QString::fromUtf8("pbALLPaus"));
        pbALLPaus->setGeometry(QRect(740, 160, 91, 31));
        pbDeleteALLPaus = new QPushButton(frame);
        pbDeleteALLPaus->setObjectName(QString::fromUtf8("pbDeleteALLPaus"));
        pbDeleteALLPaus->setGeometry(QRect(740, 250, 91, 31));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(680, 20, 211, 31));
        label_5 = new QLabel(frame);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(670, 300, 561, 16));
        label_7 = new QLabel(frame);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(650, 790, 551, 16));
        label_9 = new QLabel(frame);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(690, 315, 101, 31));
        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(690, 390, 101, 31));
        rangeContainer = new QScrollArea(frame);
        rangeContainer->setObjectName(QString::fromUtf8("rangeContainer"));
        rangeContainer->setGeometry(QRect(670, 420, 731, 331));
        rangeContainer->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 729, 329));
        rangeContainer->setWidget(scrollAreaWidgetContents);
        addRangeBtn = new QPushButton(frame);
        addRangeBtn->setObjectName(QString::fromUtf8("addRangeBtn"));
        addRangeBtn->setGeometry(QRect(710, 759, 91, 31));
        pbAganStart = new QPushButton(frame);
        pbAganStart->setObjectName(QString::fromUtf8("pbAganStart"));
        pbAganStart->setGeometry(QRect(1060, 230, 91, 51));
        saveVBtn = new QPushButton(frame);
        saveVBtn->setObjectName(QString::fromUtf8("saveVBtn"));
        saveVBtn->setGeometry(QRect(990, 759, 91, 31));
        label_6 = new QLabel(frame);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(940, 320, 121, 21));
        dsbLineV = new QDoubleSpinBox(frame);
        dsbLineV->setObjectName(QString::fromUtf8("dsbLineV"));
        dsbLineV->setGeometry(QRect(760, 351, 111, 31));
        dsbLineV->setDecimals(1);
        dsbLineV->setMaximum(1000.000000000000000);
        dsbLineV->setValue(50.000000000000000);
        dsbAccV = new QDoubleSpinBox(frame);
        dsbAccV->setObjectName(QString::fromUtf8("dsbAccV"));
        dsbAccV->setGeometry(QRect(1000, 351, 111, 31));
        dsbAccV->setMaximum(1000.000000000000000);
        dsbAccV->setValue(100.000000000000000);
        pTEgcode = new QPlainTextEdit(frame);
        pTEgcode->setObjectName(QString::fromUtf8("pTEgcode"));
        pTEgcode->setGeometry(QRect(0, 0, 671, 851));
        pTEgcode->setStyleSheet(QString::fromUtf8("background-color:rgb(231, 231, 231)"));
        TransmissionBtn = new QPushButton(frame);
        TransmissionBtn->setObjectName(QString::fromUtf8("TransmissionBtn"));
        TransmissionBtn->setGeometry(QRect(1280, 760, 91, 31));

        retranslateUi(gCodeModulation);

        QMetaObject::connectSlotsByName(gCodeModulation);
    } // setupUi

    void retranslateUi(QWidget *gCodeModulation)
    {
        gCodeModulation->setWindowTitle(QApplication::translate("gCodeModulation", "Form", nullptr));
        label->setText(QApplication::translate("gCodeModulation", "<html><head/><body><p>\345\234\250\350\277\220\350\241\214\345\210\260N \350\241\214\345\217\267<br/>\346\227\266\346\232\202\345\201\234\357\274\232</p></body></html>", nullptr));
        pbPaus->setText(QApplication::translate("gCodeModulation", "\346\217\222\345\205\245", nullptr));
        label_2->setText(QApplication::translate("gCodeModulation", "\350\241\214\345\217\267\357\274\232", nullptr));
        label_3->setText(QApplication::translate("gCodeModulation", "\345\210\240\351\231\244N \350\241\214\345\217\267\357\274\232", nullptr));
        pbdeleteCodeLine->setText(QApplication::translate("gCodeModulation", "\345\210\240\351\231\244", nullptr));
        pbALLPaus->setText(QApplication::translate("gCodeModulation", "\345\205\250\351\203\250\346\217\222\345\205\245", nullptr));
        pbDeleteALLPaus->setText(QApplication::translate("gCodeModulation", "\345\205\250\351\203\250\345\210\240\351\231\244", nullptr));
        label_4->setText(QApplication::translate("gCodeModulation", "\345\215\225\346\255\245\346\232\202\345\201\234\350\260\203\350\257\225\357\274\232", nullptr));
        label_5->setText(QApplication::translate("gCodeModulation", "__________________________________________________________________________________", nullptr));
        label_7->setText(QApplication::translate("gCodeModulation", "______________________________________________________________________________________________", nullptr));
        label_9->setText(QApplication::translate("gCodeModulation", "\347\233\264\347\272\277\351\200\237\345\272\246\357\274\232", nullptr));
        label_10->setText(QApplication::translate("gCodeModulation", "\345\234\206\345\274\247\351\200\237\345\272\246\357\274\232", nullptr));
        addRangeBtn->setText(QApplication::translate("gCodeModulation", "\346\267\273\345\212\240\346\235\241\344\273\266", nullptr));
        pbAganStart->setText(QApplication::translate("gCodeModulation", "\345\206\215\345\220\257\345\212\250", nullptr));
        saveVBtn->setText(QApplication::translate("gCodeModulation", "\344\277\235\345\255\230\351\200\237\345\272\246", nullptr));
        label_6->setText(QApplication::translate("gCodeModulation", "\345\212\240\351\200\237\345\272\246\357\274\232", nullptr));
        TransmissionBtn->setText(QApplication::translate("gCodeModulation", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gCodeModulation: public Ui_gCodeModulation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GCODEMODULATION_H
