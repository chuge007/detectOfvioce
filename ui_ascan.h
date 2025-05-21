/********************************************************************************
** Form generated from reading UI file 'ascan.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASCAN_H
#define UI_ASCAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
<<<<<<< HEAD
#include <QtWidgets/QGraphicsView>
=======
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
>>>>>>> c82df02 (界面)
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ascan
{
public:
<<<<<<< HEAD
    QPushButton *saveScanStan_but;
    QPushButton *autoCorrection_but;
    QGraphicsView *graphicsView;
    QLabel *label;
    QLabel *disPlayIformationLb;
=======
    QGridLayout *gridLayout_3;
    QGraphicsView *graphicsView;
    QLabel *label;
    QFrame *frame_3;
    QGridLayout *gridLayout_2;
    QLabel *disPlayIformationLb;
    QFrame *frame;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QDoubleSpinBox *searchRange_dSb;
    QLabel *label_3;
    QDoubleSpinBox *searchStep_dsb;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QPushButton *saveScanStan_but;
    QPushButton *autoCorrection_but;
>>>>>>> c82df02 (界面)

    void setupUi(QWidget *ascan)
    {
        if (ascan->objectName().isEmpty())
            ascan->setObjectName(QString::fromUtf8("ascan"));
        ascan->resize(1344, 1067);
<<<<<<< HEAD
        ascan->setMaximumSize(QSize(1344, 1067));
        saveScanStan_but = new QPushButton(ascan);
        saveScanStan_but->setObjectName(QString::fromUtf8("saveScanStan_but"));
        saveScanStan_but->setGeometry(QRect(910, 990, 150, 46));
        autoCorrection_but = new QPushButton(ascan);
        autoCorrection_but->setObjectName(QString::fromUtf8("autoCorrection_but"));
        autoCorrection_but->setGeometry(QRect(1170, 990, 150, 46));
        graphicsView = new QGraphicsView(ascan);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(-20, 0, 911, 1081));
        label = new QLabel(ascan);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(910, 110, 108, 51));
        disPlayIformationLb = new QLabel(ascan);
        disPlayIformationLb->setObjectName(QString::fromUtf8("disPlayIformationLb"));
        disPlayIformationLb->setGeometry(QRect(970, 160, 341, 201));
=======
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(ascan->sizePolicy().hasHeightForWidth());
        ascan->setSizePolicy(sizePolicy);
        ascan->setMaximumSize(QSize(16777215, 16777215));
        gridLayout_3 = new QGridLayout(ascan);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        graphicsView = new QGraphicsView(ascan);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));

        gridLayout_3->addWidget(graphicsView, 0, 0, 4, 1);

        label = new QLabel(ascan);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);

        gridLayout_3->addWidget(label, 0, 1, 1, 1);

        frame_3 = new QFrame(ascan);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame_3);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        disPlayIformationLb = new QLabel(frame_3);
        disPlayIformationLb->setObjectName(QString::fromUtf8("disPlayIformationLb"));

        gridLayout_2->addWidget(disPlayIformationLb, 0, 0, 1, 1);


        gridLayout_3->addWidget(frame_3, 1, 1, 1, 1);

        frame = new QFrame(ascan);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        horizontalLayout = new QHBoxLayout(frame);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout->addWidget(label_2);

        searchRange_dSb = new QDoubleSpinBox(frame);
        searchRange_dSb->setObjectName(QString::fromUtf8("searchRange_dSb"));

        horizontalLayout->addWidget(searchRange_dSb);

        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        searchStep_dsb = new QDoubleSpinBox(frame);
        searchStep_dsb->setObjectName(QString::fromUtf8("searchStep_dsb"));

        horizontalLayout->addWidget(searchStep_dsb);


        gridLayout_3->addWidget(frame, 2, 1, 1, 1);

        frame_2 = new QFrame(ascan);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        saveScanStan_but = new QPushButton(frame_2);
        saveScanStan_but->setObjectName(QString::fromUtf8("saveScanStan_but"));

        gridLayout->addWidget(saveScanStan_but, 0, 0, 1, 1);

        autoCorrection_but = new QPushButton(frame_2);
        autoCorrection_but->setObjectName(QString::fromUtf8("autoCorrection_but"));

        gridLayout->addWidget(autoCorrection_but, 0, 1, 1, 1);


        gridLayout_3->addWidget(frame_2, 3, 1, 1, 1);

>>>>>>> c82df02 (界面)

        retranslateUi(ascan);

        QMetaObject::connectSlotsByName(ascan);
    } // setupUi

    void retranslateUi(QWidget *ascan)
    {
        ascan->setWindowTitle(QApplication::translate("ascan", "Form", nullptr));
<<<<<<< HEAD
        saveScanStan_but->setText(QApplication::translate("ascan", "\344\277\235\345\255\230\346\240\207\345\207\206\347\202\271", nullptr));
        autoCorrection_but->setText(QApplication::translate("ascan", "\350\207\252\345\212\250\347\272\240\345\201\217", nullptr));
        label->setText(QApplication::translate("ascan", "\344\277\241\346\201\257\357\274\232", nullptr));
        disPlayIformationLb->setText(QString());
=======
        label->setText(QApplication::translate("ascan", "\344\277\241\346\201\257\357\274\232", nullptr));
        disPlayIformationLb->setText(QString());
        label_2->setText(QApplication::translate("ascan", "\346\220\234\347\264\242\350\214\203\345\233\264\357\274\232", nullptr));
        label_3->setText(QApplication::translate("ascan", "\346\220\234\347\264\242\346\255\245\351\225\277\357\274\232", nullptr));
        saveScanStan_but->setText(QApplication::translate("ascan", "\344\277\235\345\255\230\346\240\207\345\207\206\347\202\271", nullptr));
        autoCorrection_but->setText(QApplication::translate("ascan", "\350\207\252\345\212\250\347\272\240\345\201\217", nullptr));
>>>>>>> c82df02 (界面)
    } // retranslateUi

};

namespace Ui {
    class ascan: public Ui_ascan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASCAN_H
