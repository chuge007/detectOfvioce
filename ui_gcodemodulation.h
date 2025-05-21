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
<<<<<<< HEAD
=======
#include <QtWidgets/QGridLayout>
>>>>>>> c82df02 (界面)
#include <QtWidgets/QLabel>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpinBox>
<<<<<<< HEAD
=======
#include <QtWidgets/QVBoxLayout>
>>>>>>> c82df02 (界面)
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_gCodeModulation
{
public:
<<<<<<< HEAD
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
=======
    QVBoxLayout *verticalLayout;
    QFrame *frame;
    QGridLayout *gridLayout_6;
    QFrame *frame_5;
    QGridLayout *gridLayout_3;
    QPlainTextEdit *pTEgcode;
    QLabel *label_4;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QPushButton *pbdeleteCodeLine;
    QLabel *label_3;
    QPushButton *pbDeleteALLPaus;
    QLabel *label;
    QPushButton *pbALLPaus;
    QPushButton *pbPaus;
    QPushButton *pbAganStart;
    QLabel *label_2;
    QSpinBox *sbPausLine;
    QLabel *label_10;
    QFrame *frame_4;
    QGridLayout *gridLayout_5;
    QScrollArea *rangeContainer;
    QWidget *scrollAreaWidgetContents;
    QPushButton *addRangeBtn;
    QPushButton *saveVBtn;
    QPushButton *TransmissionBtn;
    QFrame *frame_3;
    QGridLayout *gridLayout;
    QLabel *label_9;
    QLabel *label_6;
    QDoubleSpinBox *dsbLineV;
    QDoubleSpinBox *dsbAccV;
>>>>>>> c82df02 (界面)

    void setupUi(QWidget *gCodeModulation)
    {
        if (gCodeModulation->objectName().isEmpty())
            gCodeModulation->setObjectName(QString::fromUtf8("gCodeModulation"));
<<<<<<< HEAD
        gCodeModulation->resize(1399, 936);
        gCodeModulation->setMaximumSize(QSize(1399, 936));
        frame = new QFrame(gCodeModulation);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 1401, 941));
=======
        gCodeModulation->resize(1419, 614);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gCodeModulation->sizePolicy().hasHeightForWidth());
        gCodeModulation->setSizePolicy(sizePolicy);
        gCodeModulation->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout = new QVBoxLayout(gCodeModulation);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        frame = new QFrame(gCodeModulation);
        frame->setObjectName(QString::fromUtf8("frame"));
>>>>>>> c82df02 (界面)
        frame->setMaximumSize(QSize(1401, 944));
        frame->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
<<<<<<< HEAD
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
=======
        gridLayout_6 = new QGridLayout(frame);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        frame_5 = new QFrame(frame);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        frame_5->setMinimumSize(QSize(700, 0));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_5);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pTEgcode = new QPlainTextEdit(frame_5);
        pTEgcode->setObjectName(QString::fromUtf8("pTEgcode"));
        pTEgcode->setMinimumSize(QSize(800, 0));
        pTEgcode->setStyleSheet(QString::fromUtf8("background-color:rgb(231, 231, 231)"));

        gridLayout_3->addWidget(pTEgcode, 0, 0, 1, 1);


        gridLayout_6->addWidget(frame_5, 0, 0, 5, 2);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_6->addWidget(label_4, 0, 2, 1, 1);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pbdeleteCodeLine = new QPushButton(frame_2);
        pbdeleteCodeLine->setObjectName(QString::fromUtf8("pbdeleteCodeLine"));

        gridLayout_2->addWidget(pbdeleteCodeLine, 4, 1, 1, 1);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_2->addWidget(label_3, 3, 0, 1, 2);

        pbDeleteALLPaus = new QPushButton(frame_2);
        pbDeleteALLPaus->setObjectName(QString::fromUtf8("pbDeleteALLPaus"));

        gridLayout_2->addWidget(pbDeleteALLPaus, 4, 0, 1, 1);

        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_2->addWidget(label, 1, 0, 1, 2);

        pbALLPaus = new QPushButton(frame_2);
        pbALLPaus->setObjectName(QString::fromUtf8("pbALLPaus"));

        gridLayout_2->addWidget(pbALLPaus, 2, 0, 1, 1);

        pbPaus = new QPushButton(frame_2);
        pbPaus->setObjectName(QString::fromUtf8("pbPaus"));

        gridLayout_2->addWidget(pbPaus, 2, 1, 1, 1);

        pbAganStart = new QPushButton(frame_2);
        pbAganStart->setObjectName(QString::fromUtf8("pbAganStart"));

        gridLayout_2->addWidget(pbAganStart, 3, 2, 2, 1);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        sbPausLine = new QSpinBox(frame_2);
        sbPausLine->setObjectName(QString::fromUtf8("sbPausLine"));

        gridLayout_2->addWidget(sbPausLine, 0, 1, 1, 1);


        gridLayout_6->addWidget(frame_2, 1, 2, 1, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        gridLayout_6->addWidget(label_10, 3, 2, 1, 1);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        frame_4->setMinimumSize(QSize(700, 0));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        rangeContainer = new QScrollArea(frame_4);
        rangeContainer->setObjectName(QString::fromUtf8("rangeContainer"));
        rangeContainer->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 678, 274));
        rangeContainer->setWidget(scrollAreaWidgetContents);

        gridLayout_5->addWidget(rangeContainer, 0, 0, 1, 3);

        addRangeBtn = new QPushButton(frame_4);
        addRangeBtn->setObjectName(QString::fromUtf8("addRangeBtn"));

        gridLayout_5->addWidget(addRangeBtn, 1, 0, 1, 1);

        saveVBtn = new QPushButton(frame_4);
        saveVBtn->setObjectName(QString::fromUtf8("saveVBtn"));

        gridLayout_5->addWidget(saveVBtn, 1, 1, 1, 1);

        TransmissionBtn = new QPushButton(frame_4);
        TransmissionBtn->setObjectName(QString::fromUtf8("TransmissionBtn"));

        gridLayout_5->addWidget(TransmissionBtn, 1, 2, 1, 1);


        gridLayout_6->addWidget(frame_4, 4, 2, 1, 1);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_9 = new QLabel(frame_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout->addWidget(label_9, 0, 0, 1, 1);

        label_6 = new QLabel(frame_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 0, 1, 1, 1);

        dsbLineV = new QDoubleSpinBox(frame_3);
        dsbLineV->setObjectName(QString::fromUtf8("dsbLineV"));
        dsbLineV->setDecimals(1);
        dsbLineV->setMaximum(1000.000000000000000);
        dsbLineV->setValue(50.000000000000000);

        gridLayout->addWidget(dsbLineV, 1, 0, 1, 1);

        dsbAccV = new QDoubleSpinBox(frame_3);
        dsbAccV->setObjectName(QString::fromUtf8("dsbAccV"));
        dsbAccV->setMaximum(1000.000000000000000);
        dsbAccV->setValue(100.000000000000000);

        gridLayout->addWidget(dsbAccV, 1, 1, 1, 1);


        gridLayout_6->addWidget(frame_3, 2, 2, 1, 1);


        verticalLayout->addWidget(frame);

>>>>>>> c82df02 (界面)

        retranslateUi(gCodeModulation);

        QMetaObject::connectSlotsByName(gCodeModulation);
    } // setupUi

    void retranslateUi(QWidget *gCodeModulation)
    {
        gCodeModulation->setWindowTitle(QApplication::translate("gCodeModulation", "Form", nullptr));
<<<<<<< HEAD
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
=======
        label_4->setText(QApplication::translate("gCodeModulation", "\345\215\225\346\255\245\346\232\202\345\201\234\350\260\203\350\257\225\357\274\232", nullptr));
        pbdeleteCodeLine->setText(QApplication::translate("gCodeModulation", "\345\210\240\351\231\244", nullptr));
        label_3->setText(QApplication::translate("gCodeModulation", "\345\210\240\351\231\244N \350\241\214\345\217\267\357\274\232", nullptr));
        pbDeleteALLPaus->setText(QApplication::translate("gCodeModulation", "\345\205\250\351\203\250\345\210\240\351\231\244", nullptr));
        label->setText(QApplication::translate("gCodeModulation", "<html><head/><body><p>\345\234\250\350\277\220\350\241\214\345\210\260N \350\241\214\345\217\267<br/>\346\227\266\346\232\202\345\201\234\357\274\232</p></body></html>", nullptr));
        pbALLPaus->setText(QApplication::translate("gCodeModulation", "\345\205\250\351\203\250\346\217\222\345\205\245", nullptr));
        pbPaus->setText(QApplication::translate("gCodeModulation", "\346\217\222\345\205\245", nullptr));
        pbAganStart->setText(QApplication::translate("gCodeModulation", "\345\206\215\345\220\257\345\212\250", nullptr));
        label_2->setText(QApplication::translate("gCodeModulation", "\350\241\214\345\217\267\357\274\232", nullptr));
        label_10->setText(QApplication::translate("gCodeModulation", "\345\234\206\345\274\247\351\200\237\345\272\246\357\274\232", nullptr));
        addRangeBtn->setText(QApplication::translate("gCodeModulation", "\346\267\273\345\212\240\346\235\241\344\273\266", nullptr));
        saveVBtn->setText(QApplication::translate("gCodeModulation", "\344\277\235\345\255\230\351\200\237\345\272\246", nullptr));
        TransmissionBtn->setText(QApplication::translate("gCodeModulation", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        label_9->setText(QApplication::translate("gCodeModulation", "\347\233\264\347\272\277\351\200\237\345\272\246\357\274\232", nullptr));
        label_6->setText(QApplication::translate("gCodeModulation", "\345\212\240\351\200\237\345\272\246\357\274\232", nullptr));
>>>>>>> c82df02 (界面)
    } // retranslateUi

};

namespace Ui {
    class gCodeModulation: public Ui_gCodeModulation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GCODEMODULATION_H
