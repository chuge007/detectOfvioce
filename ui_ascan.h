/********************************************************************************
** Form generated from reading UI file 'ascan.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ASCAN_H
#define UI_ASCAN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ascan
{
public:
    QGridLayout *gridLayout_3;
    QGraphicsView *graphicsView;
    QLabel *label;
    QFrame *frame_3;
    QGridLayout *gridLayout_2;
    QLabel *disPlayIformationLb;
    QFrame *frame;
    QGridLayout *gridLayout_4;
    QLabel *label_3;
    QLabel *label_2;
    QDoubleSpinBox *searchRange_dSb;
    QDoubleSpinBox *searchStep_dsb;
    QLabel *label_4;
    QSpinBox *stepCorretionNumRow_sB;
    QSpinBox *stepCorretionNumCol_sB;
    QFrame *frame_2;
    QGridLayout *gridLayout;
    QPushButton *pbstepCorrect;
    QPushButton *autoCorrection_but;
    QPushButton *saveScanStan_but;
    QPushButton *pbstopCorrcet;

    void setupUi(QWidget *ascan)
    {
        if (ascan->objectName().isEmpty())
            ascan->setObjectName(QString::fromUtf8("ascan"));
        ascan->resize(800, 498);
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
        gridLayout_4 = new QGridLayout(frame);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_3 = new QLabel(frame);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_4->addWidget(label_3, 0, 3, 1, 1);

        label_2 = new QLabel(frame);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_4->addWidget(label_2, 0, 0, 1, 1);

        searchRange_dSb = new QDoubleSpinBox(frame);
        searchRange_dSb->setObjectName(QString::fromUtf8("searchRange_dSb"));
        searchRange_dSb->setMinimum(1.000000000000000);
        searchRange_dSb->setValue(1.000000000000000);

        gridLayout_4->addWidget(searchRange_dSb, 0, 1, 1, 1);

        searchStep_dsb = new QDoubleSpinBox(frame);
        searchStep_dsb->setObjectName(QString::fromUtf8("searchStep_dsb"));
        searchStep_dsb->setValue(1.000000000000000);

        gridLayout_4->addWidget(searchStep_dsb, 0, 4, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout_4->addWidget(label_4, 1, 0, 1, 1);

        stepCorretionNumRow_sB = new QSpinBox(frame);
        stepCorretionNumRow_sB->setObjectName(QString::fromUtf8("stepCorretionNumRow_sB"));
        stepCorretionNumRow_sB->setMaximum(999999999);

        gridLayout_4->addWidget(stepCorretionNumRow_sB, 1, 1, 1, 1);

        stepCorretionNumCol_sB = new QSpinBox(frame);
        stepCorretionNumCol_sB->setObjectName(QString::fromUtf8("stepCorretionNumCol_sB"));
        stepCorretionNumCol_sB->setMinimum(1);
        stepCorretionNumCol_sB->setMaximum(3);

        gridLayout_4->addWidget(stepCorretionNumCol_sB, 1, 3, 1, 1);


        gridLayout_3->addWidget(frame, 2, 1, 1, 1);

        frame_2 = new QFrame(ascan);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout = new QGridLayout(frame_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        pbstepCorrect = new QPushButton(frame_2);
        pbstepCorrect->setObjectName(QString::fromUtf8("pbstepCorrect"));

        gridLayout->addWidget(pbstepCorrect, 0, 0, 1, 1);

        autoCorrection_but = new QPushButton(frame_2);
        autoCorrection_but->setObjectName(QString::fromUtf8("autoCorrection_but"));

        gridLayout->addWidget(autoCorrection_but, 0, 3, 1, 1);

        saveScanStan_but = new QPushButton(frame_2);
        saveScanStan_but->setObjectName(QString::fromUtf8("saveScanStan_but"));

        gridLayout->addWidget(saveScanStan_but, 1, 0, 1, 1);

        pbstopCorrcet = new QPushButton(frame_2);
        pbstopCorrcet->setObjectName(QString::fromUtf8("pbstopCorrcet"));

        gridLayout->addWidget(pbstopCorrcet, 1, 3, 1, 1);


        gridLayout_3->addWidget(frame_2, 3, 1, 1, 1);


        retranslateUi(ascan);

        QMetaObject::connectSlotsByName(ascan);
    } // setupUi

    void retranslateUi(QWidget *ascan)
    {
        ascan->setWindowTitle(QCoreApplication::translate("ascan", "Form", nullptr));
        label->setText(QCoreApplication::translate("ascan", "\344\277\241\346\201\257\357\274\232", nullptr));
        disPlayIformationLb->setText(QString());
        label_3->setText(QCoreApplication::translate("ascan", "\346\220\234\347\264\242\346\255\245\351\225\277\357\274\232", nullptr));
        label_2->setText(QCoreApplication::translate("ascan", "\346\220\234\347\264\242\350\214\203\345\233\264\357\274\232", nullptr));
        label_4->setText(QCoreApplication::translate("ascan", "\345\215\225\346\255\245\347\272\240\345\201\217\347\202\271\350\241\214\345\222\214\345\210\227\357\274\232", nullptr));
        pbstepCorrect->setText(QCoreApplication::translate("ascan", "\345\215\225\346\255\245\347\272\240\345\201\217", nullptr));
        autoCorrection_but->setText(QCoreApplication::translate("ascan", "\350\207\252\345\212\250\347\272\240\345\201\217", nullptr));
        saveScanStan_but->setText(QCoreApplication::translate("ascan", "\344\277\235\345\255\230\346\240\207\345\207\206\347\202\271", nullptr));
        pbstopCorrcet->setText(QCoreApplication::translate("ascan", "\345\201\234\346\255\242\347\272\240\345\201\217", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ascan: public Ui_ascan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASCAN_H
