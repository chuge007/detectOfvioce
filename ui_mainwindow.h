/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <tgraphicsviewrefactor.h>
#include "reason_tbview.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QFrame *line;
    QFrame *line_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *ipLineEdit;
    QLabel *label_2;
    QLineEdit *portLineEdit;
    QPushButton *connectButton;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLabel *xCurPos;
    QLabel *label_8;
    QLabel *label_13;
    QLabel *zCurPos;
    QLabel *label_12;
    QLabel *label_7;
    QLabel *yCurPos;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *rCurPos;
    QLabel *label_10;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_2;
    QPushButton *xAddBtn_2;
    QPushButton *yAddBtn_2;
    QPushButton *zAddBtn_2;
    QPushButton *rAddBtn_2;
    QPushButton *xSubBtn_2;
    QPushButton *ySubBtn_2;
    QPushButton *zSubBtn_2;
    QPushButton *rSubBtn_2;
    QWidget *widget;
    QLabel *V_label_2;
    QLabel *label_16;
    QLineEdit *dec_vel;
    QLabel *label_18;
    QLabel *label_15;
    QLineEdit *scan_velocity;
    QLabel *V_label_6;
    QLineEdit *acc_vel;
    QLabel *V_label_5;
    QLabel *V_label_7;
    QLabel *label_14;
    QLabel *label_17;
    QLineEdit *scan_velocity_3;
    QLabel *V_label_8;
    QLineEdit *scan_velocity_2;
    QFrame *frame;
    QPushButton *pushButton;
    QPushButton *startScanBtn;
    QPushButton *alarmResetBtn;
    QPushButton *setOriginBtn;
    QPushButton *stopScanBtn;
    QPushButton *endScanBtn;
    QPushButton *more_Button;
    QFrame *line_3;
    QPushButton *DXF_importBut;
    QLineEdit *traject_y0;
    QPushButton *setTrajec_start;
    QLineEdit *traject_x0;
    QLabel *V_label_3;
    QLabel *V_label_4;
    QPushButton *ascan_but;
    TGraphicsViewRefactor *graphicsView;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QPushButton *add_but;
    QPushButton *insertArcPos_but;
    QPushButton *delete_but;
    QPushButton *writePLC_but;
    QPushButton *cleanTable_but;
    QPushButton *insertLinePos_but;
    QPushButton *editPos_but;
    QPushButton *creatG_but;
    reason_tbview *tableView;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1926, 1332);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(11, 51, 519, 41));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(540, 10, 16, 81));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        line_2 = new QFrame(centralwidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setGeometry(QRect(10, 90, 1241, 20));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        layoutWidget = new QWidget(centralwidget);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 10, 521, 37));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(layoutWidget);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        ipLineEdit = new QLineEdit(layoutWidget);
        ipLineEdit->setObjectName(QString::fromUtf8("ipLineEdit"));
        ipLineEdit->setMinimumSize(QSize(0, 32));

        horizontalLayout_2->addWidget(ipLineEdit);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        portLineEdit = new QLineEdit(layoutWidget);
        portLineEdit->setObjectName(QString::fromUtf8("portLineEdit"));
        portLineEdit->setMinimumSize(QSize(0, 32));
        portLineEdit->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(portLineEdit);

        connectButton = new QPushButton(layoutWidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setMinimumSize(QSize(0, 35));

        horizontalLayout_2->addWidget(connectButton);

        layoutWidget1 = new QWidget(centralwidget);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(560, 10, 621, 81));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        label_6 = new QLabel(layoutWidget1);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        QFont font;
        font.setFamily(QString::fromUtf8("3ds"));
        font.setPointSize(11);
        label_6->setFont(font);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_6, 0, 0, 1, 1);

        xCurPos = new QLabel(layoutWidget1);
        xCurPos->setObjectName(QString::fromUtf8("xCurPos"));
        xCurPos->setFont(font);

        gridLayout->addWidget(xCurPos, 0, 1, 1, 1);

        label_8 = new QLabel(layoutWidget1);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("SansSerif"));
        font1.setPointSize(11);
        label_8->setFont(font1);

        gridLayout->addWidget(label_8, 0, 2, 1, 1);

        label_13 = new QLabel(layoutWidget1);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setFont(font);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_13, 0, 3, 1, 1);

        zCurPos = new QLabel(layoutWidget1);
        zCurPos->setObjectName(QString::fromUtf8("zCurPos"));
        zCurPos->setFont(font);

        gridLayout->addWidget(zCurPos, 0, 4, 1, 1);

        label_12 = new QLabel(layoutWidget1);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font1);

        gridLayout->addWidget(label_12, 0, 5, 1, 1);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        yCurPos = new QLabel(layoutWidget1);
        yCurPos->setObjectName(QString::fromUtf8("yCurPos"));
        yCurPos->setFont(font);

        gridLayout->addWidget(yCurPos, 1, 1, 1, 1);

        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font1);

        gridLayout->addWidget(label_9, 1, 2, 1, 1);

        label_11 = new QLabel(layoutWidget1);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 1, 3, 1, 1);

        rCurPos = new QLabel(layoutWidget1);
        rCurPos->setObjectName(QString::fromUtf8("rCurPos"));
        rCurPos->setFont(font);

        gridLayout->addWidget(rCurPos, 1, 4, 1, 1);

        label_10 = new QLabel(layoutWidget1);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setFont(font1);

        gridLayout->addWidget(label_10, 1, 5, 1, 1);

        layoutWidget2 = new QWidget(centralwidget);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(1220, 10, 481, 81));
        gridLayout_2 = new QGridLayout(layoutWidget2);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        xAddBtn_2 = new QPushButton(layoutWidget2);
        xAddBtn_2->setObjectName(QString::fromUtf8("xAddBtn_2"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(xAddBtn_2->sizePolicy().hasHeightForWidth());
        xAddBtn_2->setSizePolicy(sizePolicy);
        xAddBtn_2->setAutoRepeat(false);
        xAddBtn_2->setAutoExclusive(false);

        gridLayout_2->addWidget(xAddBtn_2, 0, 0, 1, 1);

        yAddBtn_2 = new QPushButton(layoutWidget2);
        yAddBtn_2->setObjectName(QString::fromUtf8("yAddBtn_2"));
        sizePolicy.setHeightForWidth(yAddBtn_2->sizePolicy().hasHeightForWidth());
        yAddBtn_2->setSizePolicy(sizePolicy);
        yAddBtn_2->setAutoRepeat(false);
        yAddBtn_2->setAutoExclusive(false);

        gridLayout_2->addWidget(yAddBtn_2, 0, 1, 1, 1);

        zAddBtn_2 = new QPushButton(layoutWidget2);
        zAddBtn_2->setObjectName(QString::fromUtf8("zAddBtn_2"));
        sizePolicy.setHeightForWidth(zAddBtn_2->sizePolicy().hasHeightForWidth());
        zAddBtn_2->setSizePolicy(sizePolicy);
        zAddBtn_2->setAutoRepeat(false);
        zAddBtn_2->setAutoExclusive(false);

        gridLayout_2->addWidget(zAddBtn_2, 0, 2, 1, 1);

        rAddBtn_2 = new QPushButton(layoutWidget2);
        rAddBtn_2->setObjectName(QString::fromUtf8("rAddBtn_2"));
        sizePolicy.setHeightForWidth(rAddBtn_2->sizePolicy().hasHeightForWidth());
        rAddBtn_2->setSizePolicy(sizePolicy);
        rAddBtn_2->setAutoRepeat(false);
        rAddBtn_2->setAutoExclusive(false);

        gridLayout_2->addWidget(rAddBtn_2, 0, 3, 1, 1);

        xSubBtn_2 = new QPushButton(layoutWidget2);
        xSubBtn_2->setObjectName(QString::fromUtf8("xSubBtn_2"));
        sizePolicy.setHeightForWidth(xSubBtn_2->sizePolicy().hasHeightForWidth());
        xSubBtn_2->setSizePolicy(sizePolicy);
        xSubBtn_2->setAutoRepeat(false);
        xSubBtn_2->setAutoExclusive(false);

        gridLayout_2->addWidget(xSubBtn_2, 1, 0, 1, 1);

        ySubBtn_2 = new QPushButton(layoutWidget2);
        ySubBtn_2->setObjectName(QString::fromUtf8("ySubBtn_2"));
        sizePolicy.setHeightForWidth(ySubBtn_2->sizePolicy().hasHeightForWidth());
        ySubBtn_2->setSizePolicy(sizePolicy);
        ySubBtn_2->setAutoRepeat(false);
        ySubBtn_2->setAutoExclusive(false);

        gridLayout_2->addWidget(ySubBtn_2, 1, 1, 1, 1);

        zSubBtn_2 = new QPushButton(layoutWidget2);
        zSubBtn_2->setObjectName(QString::fromUtf8("zSubBtn_2"));
        sizePolicy.setHeightForWidth(zSubBtn_2->sizePolicy().hasHeightForWidth());
        zSubBtn_2->setSizePolicy(sizePolicy);
        zSubBtn_2->setAutoRepeat(false);
        zSubBtn_2->setAutoExclusive(false);

        gridLayout_2->addWidget(zSubBtn_2, 1, 2, 1, 1);

        rSubBtn_2 = new QPushButton(layoutWidget2);
        rSubBtn_2->setObjectName(QString::fromUtf8("rSubBtn_2"));
        sizePolicy.setHeightForWidth(rSubBtn_2->sizePolicy().hasHeightForWidth());
        rSubBtn_2->setSizePolicy(sizePolicy);
        rSubBtn_2->setAutoRepeat(false);
        rSubBtn_2->setAutoExclusive(false);

        gridLayout_2->addWidget(rSubBtn_2, 1, 3, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 1220, 1591, 51));
        V_label_2 = new QLabel(widget);
        V_label_2->setObjectName(QString::fromUtf8("V_label_2"));
        V_label_2->setGeometry(QRect(10, 10, 61, 26));
        V_label_2->setFont(font1);
        V_label_2->setStyleSheet(QString::fromUtf8(""));
        label_16 = new QLabel(widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(1520, 10, 61, 31));
        label_16->setFont(font1);
        dec_vel = new QLineEdit(widget);
        dec_vel->setObjectName(QString::fromUtf8("dec_vel"));
        dec_vel->setGeometry(QRect(1420, 10, 81, 31));
        label_18 = new QLabel(widget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(870, 10, 61, 31));
        label_18->setFont(font1);
        label_15 = new QLabel(widget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(1180, 10, 81, 31));
        label_15->setFont(font1);
        scan_velocity = new QLineEdit(widget);
        scan_velocity->setObjectName(QString::fromUtf8("scan_velocity"));
        scan_velocity->setGeometry(QRect(70, 10, 91, 31));
        V_label_6 = new QLabel(widget);
        V_label_6->setObjectName(QString::fromUtf8("V_label_6"));
        V_label_6->setGeometry(QRect(1360, 10, 61, 26));
        V_label_6->setFont(font1);
        V_label_6->setStyleSheet(QString::fromUtf8(""));
        acc_vel = new QLineEdit(widget);
        acc_vel->setObjectName(QString::fromUtf8("acc_vel"));
        acc_vel->setGeometry(QRect(1080, 10, 81, 31));
        V_label_5 = new QLabel(widget);
        V_label_5->setObjectName(QString::fromUtf8("V_label_5"));
        V_label_5->setGeometry(QRect(990, 10, 81, 26));
        V_label_5->setFont(font1);
        V_label_5->setStyleSheet(QString::fromUtf8(""));
        V_label_7 = new QLabel(widget);
        V_label_7->setObjectName(QString::fromUtf8("V_label_7"));
        V_label_7->setGeometry(QRect(270, 10, 151, 26));
        V_label_7->setFont(font1);
        V_label_7->setStyleSheet(QString::fromUtf8(""));
        label_14 = new QLabel(widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(170, 10, 91, 31));
        label_14->setFont(font1);
        label_17 = new QLabel(widget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(520, 10, 71, 31));
        label_17->setFont(font1);
        scan_velocity_3 = new QLineEdit(widget);
        scan_velocity_3->setObjectName(QString::fromUtf8("scan_velocity_3"));
        scan_velocity_3->setGeometry(QRect(780, 10, 81, 31));
        V_label_8 = new QLabel(widget);
        V_label_8->setObjectName(QString::fromUtf8("V_label_8"));
        V_label_8->setGeometry(QRect(620, 10, 151, 26));
        V_label_8->setFont(font1);
        V_label_8->setStyleSheet(QString::fromUtf8(""));
        scan_velocity_2 = new QLineEdit(widget);
        scan_velocity_2->setObjectName(QString::fromUtf8("scan_velocity_2"));
        scan_velocity_2->setGeometry(QRect(400, 10, 111, 31));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(20, 1120, 1701, 81));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(610, 20, 121, 41));
        startScanBtn = new QPushButton(frame);
        startScanBtn->setObjectName(QString::fromUtf8("startScanBtn"));
        startScanBtn->setGeometry(QRect(930, 20, 101, 41));
        sizePolicy.setHeightForWidth(startScanBtn->sizePolicy().hasHeightForWidth());
        startScanBtn->setSizePolicy(sizePolicy);
        alarmResetBtn = new QPushButton(frame);
        alarmResetBtn->setObjectName(QString::fromUtf8("alarmResetBtn"));
        alarmResetBtn->setGeometry(QRect(1520, 20, 111, 41));
        sizePolicy.setHeightForWidth(alarmResetBtn->sizePolicy().hasHeightForWidth());
        alarmResetBtn->setSizePolicy(sizePolicy);
        setOriginBtn = new QPushButton(frame);
        setOriginBtn->setObjectName(QString::fromUtf8("setOriginBtn"));
        setOriginBtn->setGeometry(QRect(760, 20, 121, 41));
        sizePolicy.setHeightForWidth(setOriginBtn->sizePolicy().hasHeightForWidth());
        setOriginBtn->setSizePolicy(sizePolicy);
        stopScanBtn = new QPushButton(frame);
        stopScanBtn->setObjectName(QString::fromUtf8("stopScanBtn"));
        stopScanBtn->setGeometry(QRect(1150, 20, 101, 41));
        sizePolicy.setHeightForWidth(stopScanBtn->sizePolicy().hasHeightForWidth());
        stopScanBtn->setSizePolicy(sizePolicy);
        endScanBtn = new QPushButton(frame);
        endScanBtn->setObjectName(QString::fromUtf8("endScanBtn"));
        endScanBtn->setGeometry(QRect(1330, 20, 101, 41));
        sizePolicy.setHeightForWidth(endScanBtn->sizePolicy().hasHeightForWidth());
        endScanBtn->setSizePolicy(sizePolicy);
        more_Button = new QPushButton(frame);
        more_Button->setObjectName(QString::fromUtf8("more_Button"));
        more_Button->setGeometry(QRect(640, 30, 24, 30));
        more_Button->setMinimumSize(QSize(0, 30));
        more_Button->setMaximumSize(QSize(16777215, 30));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Arial"));
        font2.setPointSize(9);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        more_Button->setFont(font2);
        more_Button->setLayoutDirection(Qt::RightToLeft);
        more_Button->setStyleSheet(QString::fromUtf8(""));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/img/unfold-01.png"), QSize(), QIcon::Normal, QIcon::Off);
        more_Button->setIcon(icon);
        more_Button->setIconSize(QSize(12, 12));
        more_Button->setFlat(true);
        line_3 = new QFrame(frame);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(740, 20, 20, 41));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        DXF_importBut = new QPushButton(frame);
        DXF_importBut->setObjectName(QString::fromUtf8("DXF_importBut"));
        DXF_importBut->setGeometry(QRect(10, 20, 101, 41));
        sizePolicy.setHeightForWidth(DXF_importBut->sizePolicy().hasHeightForWidth());
        DXF_importBut->setSizePolicy(sizePolicy);
        traject_y0 = new QLineEdit(frame);
        traject_y0->setObjectName(QString::fromUtf8("traject_y0"));
        traject_y0->setGeometry(QRect(240, 20, 61, 41));
        setTrajec_start = new QPushButton(frame);
        setTrajec_start->setObjectName(QString::fromUtf8("setTrajec_start"));
        setTrajec_start->setGeometry(QRect(330, 20, 141, 41));
        sizePolicy.setHeightForWidth(setTrajec_start->sizePolicy().hasHeightForWidth());
        setTrajec_start->setSizePolicy(sizePolicy);
        traject_x0 = new QLineEdit(frame);
        traject_x0->setObjectName(QString::fromUtf8("traject_x0"));
        traject_x0->setGeometry(QRect(150, 20, 51, 41));
        V_label_3 = new QLabel(frame);
        V_label_3->setObjectName(QString::fromUtf8("V_label_3"));
        V_label_3->setGeometry(QRect(120, 30, 21, 26));
        V_label_3->setFont(font1);
        V_label_3->setStyleSheet(QString::fromUtf8(""));
        V_label_4 = new QLabel(frame);
        V_label_4->setObjectName(QString::fromUtf8("V_label_4"));
        V_label_4->setGeometry(QRect(210, 30, 21, 26));
        V_label_4->setFont(font1);
        V_label_4->setStyleSheet(QString::fromUtf8(""));
        ascan_but = new QPushButton(frame);
        ascan_but->setObjectName(QString::fromUtf8("ascan_but"));
        ascan_but->setGeometry(QRect(480, 20, 111, 41));
        graphicsView = new TGraphicsViewRefactor(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setGeometry(QRect(11, 111, 1181, 1001));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy1);
        graphicsView->setMinimumSize(QSize(0, 0));
        graphicsView->setMaximumSize(QSize(16777215, 16777215));
        graphicsView->setBaseSize(QSize(0, 0));
        graphicsView->setInteractive(true);
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(1170, 110, 751, 1001));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::West);
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        add_but = new QPushButton(tab_2);
        add_but->setObjectName(QString::fromUtf8("add_but"));
        add_but->setGeometry(QRect(10, 880, 85, 41));
        insertArcPos_but = new QPushButton(tab_2);
        insertArcPos_but->setObjectName(QString::fromUtf8("insertArcPos_but"));
        insertArcPos_but->setGeometry(QRect(260, 880, 201, 41));
        delete_but = new QPushButton(tab_2);
        delete_but->setObjectName(QString::fromUtf8("delete_but"));
        delete_but->setGeometry(QRect(120, 940, 101, 41));
        writePLC_but = new QPushButton(tab_2);
        writePLC_but->setObjectName(QString::fromUtf8("writePLC_but"));
        writePLC_but->setGeometry(QRect(500, 940, 211, 41));
        cleanTable_but = new QPushButton(tab_2);
        cleanTable_but->setObjectName(QString::fromUtf8("cleanTable_but"));
        cleanTable_but->setGeometry(QRect(120, 880, 101, 41));
        insertLinePos_but = new QPushButton(tab_2);
        insertLinePos_but->setObjectName(QString::fromUtf8("insertLinePos_but"));
        insertLinePos_but->setGeometry(QRect(500, 880, 211, 41));
        editPos_but = new QPushButton(tab_2);
        editPos_but->setObjectName(QString::fromUtf8("editPos_but"));
        editPos_but->setGeometry(QRect(10, 940, 85, 41));
        creatG_but = new QPushButton(tab_2);
        creatG_but->setObjectName(QString::fromUtf8("creatG_but"));
        creatG_but->setGeometry(QRect(260, 940, 201, 41));
        tableView = new reason_tbview(tab_2);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(0, 0, 731, 871));
        tabWidget->addTab(tab_2, QString());
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "IP:", nullptr));
        ipLineEdit->setText(QApplication::translate("MainWindow", "192.168.1.88", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Port:", nullptr));
        portLineEdit->setText(QApplication::translate("MainWindow", "502", nullptr));
        connectButton->setText(QApplication::translate("MainWindow", " \350\277\236\346\216\245", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "x\357\274\232", nullptr));
        xCurPos->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "mm", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "z\357\274\232", nullptr));
        zCurPos->setText(QString());
        label_12->setText(QApplication::translate("MainWindow", "mm", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "y\357\274\232", nullptr));
        yCurPos->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "mm", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "r\357\274\232", nullptr));
        rCurPos->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "mm", nullptr));
        xAddBtn_2->setText(QApplication::translate("MainWindow", "X+", nullptr));
        yAddBtn_2->setText(QApplication::translate("MainWindow", "Y+", nullptr));
        zAddBtn_2->setText(QApplication::translate("MainWindow", "Z+", nullptr));
        rAddBtn_2->setText(QApplication::translate("MainWindow", "R+", nullptr));
        xSubBtn_2->setText(QApplication::translate("MainWindow", "X-", nullptr));
        ySubBtn_2->setText(QApplication::translate("MainWindow", "Y-", nullptr));
        zSubBtn_2->setText(QApplication::translate("MainWindow", "Z-", nullptr));
        rSubBtn_2->setText(QApplication::translate("MainWindow", "R-", nullptr));
        V_label_2->setText(QApplication::translate("MainWindow", "Vel: ", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "mm/s\302\262", nullptr));
        dec_vel->setText(QString());
        label_18->setText(QApplication::translate("MainWindow", "mm/s", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "mm/s\302\262", nullptr));
        scan_velocity->setText(QString());
        V_label_6->setText(QApplication::translate("MainWindow", "Dec: ", nullptr));
        acc_vel->setText(QString());
        V_label_5->setText(QApplication::translate("MainWindow", "Acc: ", nullptr));
        V_label_7->setText(QApplication::translate("MainWindow", "ArcVel01: ", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "mm/s", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "mm/s", nullptr));
        scan_velocity_3->setText(QString());
        V_label_8->setText(QApplication::translate("MainWindow", "ArcVel02: ", nullptr));
        scan_velocity_2->setText(QString());
        pushButton->setText(QApplication::translate("MainWindow", "imageProcess", nullptr));
        startScanBtn->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        alarmResetBtn->setText(QApplication::translate("MainWindow", "\346\212\245\350\255\246\345\244\215\344\275\215", nullptr));
        setOriginBtn->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\345\216\237\347\202\271", nullptr));
        stopScanBtn->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        endScanBtn->setText(QApplication::translate("MainWindow", "\347\273\223\346\235\237", nullptr));
        more_Button->setText(QString());
        DXF_importBut->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245DXF", nullptr));
        traject_y0->setText(QApplication::translate("MainWindow", "50", nullptr));
        setTrajec_start->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\350\275\250\350\277\271\350\265\267\347\202\271", nullptr));
        traject_x0->setText(QApplication::translate("MainWindow", "50", nullptr));
        V_label_3->setText(QApplication::translate("MainWindow", "x:", nullptr));
        V_label_4->setText(QApplication::translate("MainWindow", "y:", nullptr));
        ascan_but->setText(QApplication::translate("MainWindow", "Ascan", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "Rect Scan", nullptr));
        add_but->setText(QApplication::translate("MainWindow", "\346\240\267\346\235\241", nullptr));
        insertArcPos_but->setText(QApplication::translate("MainWindow", "\346\217\222\345\205\245\345\234\206\345\274\247", nullptr));
        delete_but->setText(QApplication::translate("MainWindow", "Delete", nullptr));
        writePLC_but->setText(QApplication::translate("MainWindow", " \345\257\204\345\255\230\345\231\250\350\277\220\350\241\214\357\274\210plc\357\274\211", nullptr));
        cleanTable_but->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\350\241\250\346\240\274", nullptr));
        insertLinePos_but->setText(QApplication::translate("MainWindow", "\346\217\222\345\205\245\347\233\264\347\272\277", nullptr));
        editPos_but->setText(QApplication::translate("MainWindow", "Edit", nullptr));
        creatG_but->setText(QApplication::translate("MainWindow", "GCode\350\277\220\350\241\214\357\274\210plc\357\274\211", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Trajectory Scan", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
