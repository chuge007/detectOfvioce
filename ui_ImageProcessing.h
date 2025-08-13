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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imageprocessing
{
public:
    QGridLayout *gridLayout_4;
    QFrame *frame;
    QGridLayout *gridLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pBtestReport;
    QPushButton *pBimagesProcess;
    QFrame *frame_2;
    QGridLayout *gridLayout_2;
    QPushButton *pBsetImagePath;
    QVBoxLayout *verticalLayout_5;
    QLabel *label;
    QLabel *lbprocessImage;
    QFrame *frame_3;
    QGridLayout *gridLayout;
    QPushButton *pbSetRoi;
    QPushButton *pbCleanRoi;
    QPushButton *pbSetRegion;
    QGraphicsView *gVimageprocess;

    void setupUi(QWidget *imageprocessing)
    {
        if (imageprocessing->objectName().isEmpty())
            imageprocessing->setObjectName(QString::fromUtf8("imageprocessing"));
        imageprocessing->resize(709, 514);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(imageprocessing->sizePolicy().hasHeightForWidth());
        imageprocessing->setSizePolicy(sizePolicy);
        gridLayout_4 = new QGridLayout(imageprocessing);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        frame = new QFrame(imageprocessing);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setStyleSheet(QString::fromUtf8("background-color:rgb(254, 254, 254)"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pBtestReport = new QPushButton(frame);
        pBtestReport->setObjectName(QString::fromUtf8("pBtestReport"));

        horizontalLayout_2->addWidget(pBtestReport);

        pBimagesProcess = new QPushButton(frame);
        pBimagesProcess->setObjectName(QString::fromUtf8("pBimagesProcess"));

        horizontalLayout_2->addWidget(pBimagesProcess);


        gridLayout_3->addLayout(horizontalLayout_2, 4, 4, 1, 1);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0)"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pBsetImagePath = new QPushButton(frame_2);
        pBsetImagePath->setObjectName(QString::fromUtf8("pBsetImagePath"));

        gridLayout_2->addWidget(pBsetImagePath, 3, 1, 1, 1);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(5, 0, -1, 95);
        label = new QLabel(frame_2);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_5->addWidget(label);


        gridLayout_2->addLayout(verticalLayout_5, 0, 0, 1, 1);

        lbprocessImage = new QLabel(frame_2);
        lbprocessImage->setObjectName(QString::fromUtf8("lbprocessImage"));

        gridLayout_2->addWidget(lbprocessImage, 1, 0, 2, 2);


        gridLayout_3->addWidget(frame_2, 0, 4, 2, 1);

        frame_3 = new QFrame(frame);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 0)"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_3);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pbSetRoi = new QPushButton(frame_3);
        pbSetRoi->setObjectName(QString::fromUtf8("pbSetRoi"));
        pbSetRoi->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100)"));

        gridLayout->addWidget(pbSetRoi, 1, 3, 1, 1);

        pbCleanRoi = new QPushButton(frame_3);
        pbCleanRoi->setObjectName(QString::fromUtf8("pbCleanRoi"));
        pbCleanRoi->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100)"));

        gridLayout->addWidget(pbCleanRoi, 1, 1, 1, 1);

        pbSetRegion = new QPushButton(frame_3);
        pbSetRegion->setObjectName(QString::fromUtf8("pbSetRegion"));
        pbSetRegion->setStyleSheet(QString::fromUtf8("background-color: rgba(255, 255, 255, 100)"));

        gridLayout->addWidget(pbSetRegion, 0, 1, 1, 1);


        gridLayout_3->addWidget(frame_3, 3, 4, 1, 1);

        gVimageprocess = new QGraphicsView(frame);
        gVimageprocess->setObjectName(QString::fromUtf8("gVimageprocess"));
        gVimageprocess->setStyleSheet(QString::fromUtf8("background-color:rgb(234, 234, 234)"));

        gridLayout_3->addWidget(gVimageprocess, 0, 0, 5, 4);

        gVimageprocess->raise();
        frame_3->raise();
        frame_2->raise();

        gridLayout_4->addWidget(frame, 0, 0, 1, 1);


        retranslateUi(imageprocessing);

        QMetaObject::connectSlotsByName(imageprocessing);
    } // setupUi

    void retranslateUi(QWidget *imageprocessing)
    {
        imageprocessing->setWindowTitle(QApplication::translate("imageprocessing", "Form", nullptr));
        pBtestReport->setText(QApplication::translate("imageprocessing", "\347\224\237\346\210\220\346\243\200\346\265\213\346\212\245\345\221\212", nullptr));
        pBimagesProcess->setText(QApplication::translate("imageprocessing", "\350\266\205\345\243\260\345\233\276\345\203\217\345\210\206\346\236\220", nullptr));
        pBsetImagePath->setText(QApplication::translate("imageprocessing", "\350\256\276\345\256\232\345\244\204\347\220\206\345\233\276\345\203\217\350\267\257\345\276\204", nullptr));
        label->setText(QApplication::translate("imageprocessing", "\345\244\204\347\220\206\347\232\204\345\233\276\345\203\217\357\274\232", nullptr));
        lbprocessImage->setText(QString());
        pbSetRoi->setText(QApplication::translate("imageprocessing", "\351\200\211\346\213\251\345\214\272\345\237\237", nullptr));
        pbCleanRoi->setText(QApplication::translate("imageprocessing", "\346\270\205\347\220\206\345\214\272\345\237\237", nullptr));
        pbSetRegion->setText(QApplication::translate("imageprocessing", "\351\205\215\347\275\256\345\214\272\345\237\237", nullptr));
    } // retranslateUi

};

namespace Ui {
    class imageprocessing: public Ui_imageprocessing {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMAGEPROCESSING_H
