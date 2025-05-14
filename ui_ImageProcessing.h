/********************************************************************************
** Form generated from reading UI file 'ImageProcessing.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMAGEPROCESSING_H
#define UI_IMAGEPROCESSING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imageprocessing
{
public:
    QFrame *frame;
    QGraphicsView *gVimageprocess;
    QPushButton *pBimagesProcess;
    QPushButton *pBtestReport;
    QPushButton *pBsetImagePath;
    QLabel *label;
    QLabel *lbprocessImage;
    QFrame *frame_2;
    QFrame *frame_3;
    QPushButton *pbSetRoi;
    QPushButton *pbCleanRoi;

    void setupUi(QWidget *imageprocessing)
    {
        if (imageprocessing->objectName().isEmpty())
            imageprocessing->setObjectName(QString::fromUtf8("imageprocessing"));
        imageprocessing->resize(1463, 1149);
        frame = new QFrame(imageprocessing);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(-110, 0, 1611, 1151));
        frame->setStyleSheet(QString::fromUtf8("background-color:rgb(254, 254, 254)"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gVimageprocess = new QGraphicsView(frame);
        gVimageprocess->setObjectName(QString::fromUtf8("gVimageprocess"));
        gVimageprocess->setGeometry(QRect(120, 0, 1131, 1221));
        gVimageprocess->setStyleSheet(QString::fromUtf8("background-color:rgb(234, 234, 234)"));
        pBimagesProcess = new QPushButton(frame);
        pBimagesProcess->setObjectName(QString::fromUtf8("pBimagesProcess"));
        pBimagesProcess->setGeometry(QRect(1260, 1060, 151, 51));
        pBtestReport = new QPushButton(frame);
        pBtestReport->setObjectName(QString::fromUtf8("pBtestReport"));
        pBtestReport->setGeometry(QRect(1420, 1060, 151, 51));
        pBsetImagePath = new QPushButton(frame);
        pBsetImagePath->setObjectName(QString::fromUtf8("pBsetImagePath"));
        pBsetImagePath->setGeometry(QRect(1380, 200, 191, 41));
        label = new QLabel(frame);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(1270, 40, 151, 21));
        lbprocessImage = new QLabel(frame);
        lbprocessImage->setObjectName(QString::fromUtf8("lbprocessImage"));
        lbprocessImage->setGeometry(QRect(1290, 70, 271, 101));
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(1250, 20, 331, 291));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0)"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setGeometry(QRect(1250, 330, 331, 681));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0)"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        pbSetRoi = new QPushButton(frame_3);
        pbSetRoi->setObjectName(QString::fromUtf8("pbSetRoi"));
        pbSetRoi->setGeometry(QRect(200, 50, 111, 51));
        pbSetRoi->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100)"));
        pbCleanRoi = new QPushButton(frame_3);
        pbCleanRoi->setObjectName(QString::fromUtf8("pbCleanRoi"));
        pbCleanRoi->setGeometry(QRect(40, 50, 111, 51));
        pbCleanRoi->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100)"));
        frame_2->raise();
        gVimageprocess->raise();
        pBimagesProcess->raise();
        pBtestReport->raise();
        pBsetImagePath->raise();
        label->raise();
        lbprocessImage->raise();
        frame_3->raise();

        retranslateUi(imageprocessing);

        QMetaObject::connectSlotsByName(imageprocessing);
    } // setupUi

    void retranslateUi(QWidget *imageprocessing)
    {
        imageprocessing->setWindowTitle(QApplication::translate("imageprocessing", "Form", nullptr));
        pBimagesProcess->setText(QApplication::translate("imageprocessing", "\350\266\205\345\243\260\345\233\276\345\203\217\345\210\206\346\236\220", nullptr));
        pBtestReport->setText(QApplication::translate("imageprocessing", "\347\224\237\346\210\220\346\243\200\346\265\213\346\212\245\345\221\212", nullptr));
        pBsetImagePath->setText(QApplication::translate("imageprocessing", "\350\256\276\345\256\232\345\244\204\347\220\206\345\233\276\345\203\217\350\267\257\345\276\204", nullptr));
        label->setText(QApplication::translate("imageprocessing", "\345\244\204\347\220\206\347\232\204\345\233\276\345\203\217\357\274\232", nullptr));
        lbprocessImage->setText(QString());
        pbSetRoi->setText(QApplication::translate("imageprocessing", "\351\200\211\346\213\251\345\214\272\345\237\237", nullptr));
        pbCleanRoi->setText(QApplication::translate("imageprocessing", "\346\270\205\347\220\206\345\214\272\345\237\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class imageprocessing: public Ui_imageprocessing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESSING_H
