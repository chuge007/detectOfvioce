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
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ascan
{
public:
    QPushButton *saveScanStan_but;
    QPushButton *autoCorrection_but;
    QGraphicsView *graphicsView;
    QLabel *label;
    QLabel *disPlayIformationLb;

    void setupUi(QWidget *ascan)
    {
        if (ascan->objectName().isEmpty())
            ascan->setObjectName(QString::fromUtf8("ascan"));
        ascan->resize(1344, 1067);
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

        retranslateUi(ascan);

        QMetaObject::connectSlotsByName(ascan);
    } // setupUi

    void retranslateUi(QWidget *ascan)
    {
        ascan->setWindowTitle(QApplication::translate("ascan", "Form", nullptr));
        saveScanStan_but->setText(QApplication::translate("ascan", "\344\277\235\345\255\230\346\240\207\345\207\206\347\202\271", nullptr));
        autoCorrection_but->setText(QApplication::translate("ascan", "\350\207\252\345\212\250\347\272\240\345\201\217", nullptr));
        label->setText(QApplication::translate("ascan", "\344\277\241\346\201\257\357\274\232", nullptr));
        disPlayIformationLb->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class ascan: public Ui_ascan {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ASCAN_H
