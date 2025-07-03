/********************************************************************************
** Form generated from reading UI file 'gcodemodulation.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GCODEMODULATION_H
#define UI_GCODEMODULATION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
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
    QGridLayout *gridLayout_6;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QLabel *label_4;
    QFrame *frame_5;
    QFormLayout *formLayout;
    QPlainTextEdit *pTEgcode;
    QLabel *label_10;
    QFrame *frame_4;
    QGridLayout *gridLayout_5;
    QPushButton *addRangeBtn;
    QPushButton *saveVBtn;
    QPushButton *TransmissionBtn;
    QScrollArea *rangeContainer;
    QWidget *scrollAreaWidgetContents;
    QFrame *frame_3;
    QGridLayout *gridLayout;
    QDoubleSpinBox *dsbAccV;
    QLabel *label_9;
    QLabel *label_6;
    QDoubleSpinBox *dsbLineV;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QPushButton *pbDeleteALLPaus;
    QSpinBox *sbPausLine;
    QLabel *label_2;
    QPushButton *pbdeleteCodeLine;
    QPushButton *pbALLPaus;
    QLabel *label_3;
    QPushButton *pbAganStart;
    QLabel *label;
    QPushButton *pbPaus;
    QFrame *frame_6;
    QGridLayout *gridLayout_4;
    QPushButton *trajectory_smooth_but;
    QDoubleSpinBox *trajectory_smooth_dsb;

    void setupUi(QWidget *gCodeModulation)
    {
        if (gCodeModulation->objectName().isEmpty())
            gCodeModulation->setObjectName(QString::fromUtf8("gCodeModulation"));
        gCodeModulation->resize(995, 571);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(gCodeModulation->sizePolicy().hasHeightForWidth());
        gCodeModulation->setSizePolicy(sizePolicy);
        gCodeModulation->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_6 = new QGridLayout(gCodeModulation);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        frame = new QFrame(gCodeModulation);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMaximumSize(QSize(1401, 944));
        frame->setStyleSheet(QString::fromUtf8("background-color:rgb(255, 255, 255)"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_4, 0, 1, 1, 1);

        frame_5 = new QFrame(frame);
        frame_5->setObjectName(QString::fromUtf8("frame_5"));
        sizePolicy.setHeightForWidth(frame_5->sizePolicy().hasHeightForWidth());
        frame_5->setSizePolicy(sizePolicy);
        frame_5->setMinimumSize(QSize(0, 0));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        formLayout = new QFormLayout(frame_5);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        pTEgcode = new QPlainTextEdit(frame_5);
        pTEgcode->setObjectName(QString::fromUtf8("pTEgcode"));
        sizePolicy.setHeightForWidth(pTEgcode->sizePolicy().hasHeightForWidth());
        pTEgcode->setSizePolicy(sizePolicy);
        pTEgcode->setMinimumSize(QSize(0, 0));
        pTEgcode->setStyleSheet(QString::fromUtf8("background-color:rgb(231, 231, 231)"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, pTEgcode);


        gridLayout_3->addWidget(frame_5, 0, 0, 6, 1);

        label_10 = new QLabel(frame);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);

        gridLayout_3->addWidget(label_10, 4, 1, 1, 1);

        frame_4 = new QFrame(frame);
        frame_4->setObjectName(QString::fromUtf8("frame_4"));
        sizePolicy.setHeightForWidth(frame_4->sizePolicy().hasHeightForWidth());
        frame_4->setSizePolicy(sizePolicy);
        frame_4->setMinimumSize(QSize(0, 0));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        gridLayout_5 = new QGridLayout(frame_4);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        addRangeBtn = new QPushButton(frame_4);
        addRangeBtn->setObjectName(QString::fromUtf8("addRangeBtn"));
        sizePolicy.setHeightForWidth(addRangeBtn->sizePolicy().hasHeightForWidth());
        addRangeBtn->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(addRangeBtn, 1, 0, 1, 1);

        saveVBtn = new QPushButton(frame_4);
        saveVBtn->setObjectName(QString::fromUtf8("saveVBtn"));
        sizePolicy.setHeightForWidth(saveVBtn->sizePolicy().hasHeightForWidth());
        saveVBtn->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(saveVBtn, 1, 1, 1, 1);

        TransmissionBtn = new QPushButton(frame_4);
        TransmissionBtn->setObjectName(QString::fromUtf8("TransmissionBtn"));
        sizePolicy.setHeightForWidth(TransmissionBtn->sizePolicy().hasHeightForWidth());
        TransmissionBtn->setSizePolicy(sizePolicy);

        gridLayout_5->addWidget(TransmissionBtn, 1, 2, 1, 1);

        rangeContainer = new QScrollArea(frame_4);
        rangeContainer->setObjectName(QString::fromUtf8("rangeContainer"));
        sizePolicy.setHeightForWidth(rangeContainer->sizePolicy().hasHeightForWidth());
        rangeContainer->setSizePolicy(sizePolicy);
        rangeContainer->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 451, 183));
        rangeContainer->setWidget(scrollAreaWidgetContents);

        gridLayout_5->addWidget(rangeContainer, 0, 0, 1, 3);

        gridLayout_5->setRowStretch(0, 10);

        gridLayout_3->addWidget(frame_4, 5, 1, 1, 2);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        dsbAccV = new QDoubleSpinBox(frame_3);
        dsbAccV->setObjectName(QString::fromUtf8("dsbAccV"));
        sizePolicy.setHeightForWidth(dsbAccV->sizePolicy().hasHeightForWidth());
        dsbAccV->setSizePolicy(sizePolicy);
        dsbAccV->setMaximum(1000.000000000000000);
        dsbAccV->setValue(100.000000000000000);

        gridLayout->addWidget(dsbAccV, 1, 1, 1, 1);

        label_9 = new QLabel(frame_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_9, 0, 0, 1, 1);

        label_6 = new QLabel(frame_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);

        gridLayout->addWidget(label_6, 0, 1, 1, 1);

        dsbLineV = new QDoubleSpinBox(frame_3);
        dsbLineV->setObjectName(QString::fromUtf8("dsbLineV"));
        sizePolicy.setHeightForWidth(dsbLineV->sizePolicy().hasHeightForWidth());
        dsbLineV->setSizePolicy(sizePolicy);
        dsbLineV->setDecimals(1);
        dsbLineV->setMaximum(1000.000000000000000);
        dsbLineV->setValue(50.000000000000000);

        gridLayout->addWidget(dsbLineV, 1, 0, 1, 1);


        gridLayout_3->addWidget(frame_3, 3, 1, 1, 2);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pbDeleteALLPaus = new QPushButton(frame_2);
        pbDeleteALLPaus->setObjectName(QString::fromUtf8("pbDeleteALLPaus"));
        sizePolicy.setHeightForWidth(pbDeleteALLPaus->sizePolicy().hasHeightForWidth());
        pbDeleteALLPaus->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pbDeleteALLPaus, 4, 0, 1, 1);

        sbPausLine = new QSpinBox(frame_2);
        sbPausLine->setObjectName(QString::fromUtf8("sbPausLine"));
        sizePolicy.setHeightForWidth(sbPausLine->sizePolicy().hasHeightForWidth());
        sbPausLine->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(sbPausLine, 0, 1, 1, 1);

        label_2 = new QLabel(frame_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_2, 0, 0, 1, 1);

        pbdeleteCodeLine = new QPushButton(frame_2);
        pbdeleteCodeLine->setObjectName(QString::fromUtf8("pbdeleteCodeLine"));
        sizePolicy.setHeightForWidth(pbdeleteCodeLine->sizePolicy().hasHeightForWidth());
        pbdeleteCodeLine->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pbdeleteCodeLine, 4, 1, 1, 1);

        pbALLPaus = new QPushButton(frame_2);
        pbALLPaus->setObjectName(QString::fromUtf8("pbALLPaus"));
        sizePolicy.setHeightForWidth(pbALLPaus->sizePolicy().hasHeightForWidth());
        pbALLPaus->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pbALLPaus, 2, 0, 1, 1);

        label_3 = new QLabel(frame_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label_3, 3, 0, 1, 2);

        pbAganStart = new QPushButton(frame_2);
        pbAganStart->setObjectName(QString::fromUtf8("pbAganStart"));
        sizePolicy.setHeightForWidth(pbAganStart->sizePolicy().hasHeightForWidth());
        pbAganStart->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pbAganStart, 3, 2, 2, 1);

        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(label, 1, 0, 1, 2);

        pbPaus = new QPushButton(frame_2);
        pbPaus->setObjectName(QString::fromUtf8("pbPaus"));
        sizePolicy.setHeightForWidth(pbPaus->sizePolicy().hasHeightForWidth());
        pbPaus->setSizePolicy(sizePolicy);

        gridLayout_2->addWidget(pbPaus, 2, 1, 1, 1);


        gridLayout_3->addWidget(frame_2, 1, 1, 1, 2);

        frame_6 = new QFrame(frame);
        frame_6->setObjectName(QString::fromUtf8("frame_6"));
        sizePolicy.setHeightForWidth(frame_6->sizePolicy().hasHeightForWidth());
        frame_6->setSizePolicy(sizePolicy);
        frame_6->setFrameShape(QFrame::StyledPanel);
        frame_6->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_6);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        trajectory_smooth_but = new QPushButton(frame_6);
        trajectory_smooth_but->setObjectName(QString::fromUtf8("trajectory_smooth_but"));
        sizePolicy.setHeightForWidth(trajectory_smooth_but->sizePolicy().hasHeightForWidth());
        trajectory_smooth_but->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(trajectory_smooth_but, 0, 0, 1, 1);

        trajectory_smooth_dsb = new QDoubleSpinBox(frame_6);
        trajectory_smooth_dsb->setObjectName(QString::fromUtf8("trajectory_smooth_dsb"));
        sizePolicy.setHeightForWidth(trajectory_smooth_dsb->sizePolicy().hasHeightForWidth());
        trajectory_smooth_dsb->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(trajectory_smooth_dsb, 0, 1, 1, 1);


        gridLayout_3->addWidget(frame_6, 2, 1, 1, 2);

        gridLayout_3->setRowStretch(5, 10);
        gridLayout_3->setColumnStretch(0, 5);
        gridLayout_3->setColumnStretch(2, 4);

        gridLayout_6->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(gCodeModulation);

        QMetaObject::connectSlotsByName(gCodeModulation);
    } // setupUi

    void retranslateUi(QWidget *gCodeModulation)
    {
        gCodeModulation->setWindowTitle(QCoreApplication::translate("gCodeModulation", "Form", nullptr));
        label_4->setText(QCoreApplication::translate("gCodeModulation", "\345\215\225\346\255\245\346\232\202\345\201\234\350\260\203\350\257\225\357\274\232", nullptr));
        label_10->setText(QCoreApplication::translate("gCodeModulation", "\345\234\206\345\274\247\351\200\237\345\272\246\357\274\232", nullptr));
        addRangeBtn->setText(QCoreApplication::translate("gCodeModulation", "\346\267\273\345\212\240\346\235\241\344\273\266", nullptr));
        saveVBtn->setText(QCoreApplication::translate("gCodeModulation", "\344\277\235\345\255\230\351\200\237\345\272\246", nullptr));
        TransmissionBtn->setText(QCoreApplication::translate("gCodeModulation", "\345\217\221\351\200\201\346\226\207\344\273\266", nullptr));
        label_9->setText(QCoreApplication::translate("gCodeModulation", "\347\233\264\347\272\277\351\200\237\345\272\246\357\274\232", nullptr));
        label_6->setText(QCoreApplication::translate("gCodeModulation", "\345\212\240\351\200\237\345\272\246\357\274\232", nullptr));
        pbDeleteALLPaus->setText(QCoreApplication::translate("gCodeModulation", "\345\205\250\351\203\250\345\210\240\351\231\244", nullptr));
        label_2->setText(QCoreApplication::translate("gCodeModulation", "\350\241\214\345\217\267\357\274\232", nullptr));
        pbdeleteCodeLine->setText(QCoreApplication::translate("gCodeModulation", "\345\210\240\351\231\244", nullptr));
        pbALLPaus->setText(QCoreApplication::translate("gCodeModulation", "\345\205\250\351\203\250\346\217\222\345\205\245", nullptr));
        label_3->setText(QCoreApplication::translate("gCodeModulation", "\345\210\240\351\231\244N \350\241\214\345\217\267\357\274\232", nullptr));
        pbAganStart->setText(QCoreApplication::translate("gCodeModulation", "\345\206\215\345\220\257\345\212\250", nullptr));
        label->setText(QCoreApplication::translate("gCodeModulation", "<html><head/><body><p>\345\234\250\350\277\220\350\241\214\345\210\260N \350\241\214\345\217\267<br/>\346\227\266\346\232\202\345\201\234\357\274\232</p></body></html>", nullptr));
        pbPaus->setText(QCoreApplication::translate("gCodeModulation", "\346\217\222\345\205\245", nullptr));
        trajectory_smooth_but->setText(QCoreApplication::translate("gCodeModulation", "\350\275\250\350\277\271\351\241\272\346\273\221", nullptr));
    } // retranslateUi

};

namespace Ui {
    class gCodeModulation: public Ui_gCodeModulation {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GCODEMODULATION_H
