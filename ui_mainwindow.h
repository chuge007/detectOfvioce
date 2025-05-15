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
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>
#include <tgraphicsviewrefactor.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTextEdit *messText_lin;
    QFrame *line;
    QFrame *line_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *ip_lin;
    QLabel *label_2;
    QLineEdit *port_lin;
    QPushButton *connect_but;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QLabel *label_6;
    QLabel *xCurPos_lab;
    QLabel *label_8;
    QLabel *label_13;
    QLabel *zCurPos_lab;
    QLabel *label_12;
    QLabel *label_7;
    QLabel *yCurPos_lab;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *rCurPos_lab;
    QLabel *label_10;
    QWidget *layoutWidget2;
    QGridLayout *gridLayout_2;
    QPushButton *xAdd_but;
    QPushButton *yAdd_but;
    QPushButton *zAdd_but;
    QPushButton *rAdd_but;
    QPushButton *xSub_but;
    QPushButton *ySub_but;
    QPushButton *zSub_but;
    QPushButton *rSub_but;
    QWidget *widget;
    QLineEdit *scanVelocity_lin;
    QLabel *label_14;
    QLabel *label_17;
    QLineEdit *AxleVelocity_lin;
    QLabel *lbv3;
    QLabel *label_18;
    QLineEdit *lineVelocity_lin;
    QLabel *label_19;
    QLineEdit *arcVelocity_lin;
    QLabel *label_5;
    QLabel *label_16;
    QLabel *label_20;
    QComboBox *comboBox;
    QLabel *label_21;
    QLineEdit *pointVelocity_lin;
    QLabel *label_23;
    QLabel *label_24;
    QFrame *frame;
    QPushButton *imageProcess_but;
    QPushButton *startScan_But;
    QPushButton *alarmReset_but;
    QPushButton *setOrigin_but;
    QPushButton *stopScan_but;
    QPushButton *endScan_but;
    QFrame *line_3;
    QPushButton *DXFimport_but;
    QLineEdit *traject_y0;
    QPushButton *setTrajecStart_but;
    QLineEdit *traject_x0;
    QLabel *V_label_3;
    QLabel *V_label_4;
    QPushButton *ascan_but;
    QPushButton *moveToPosition_but;
    QFrame *line_4;
    QLabel *V_label_9;
    QLabel *V_label_10;
    QLineEdit *traject_z0;
    QLineEdit *traject_r0;
    QPushButton *writeInPLC_but;
    QPushButton *creatG_but;
    QPushButton *getCurryPoint_but;
    QComboBox *cBworkpiece;
    QPushButton *pbNewPiece;
    QPushButton *pBdeletePiece;
    QLabel *label_4;
    QPushButton *pBbrazing;
    QPushButton *trajectoryOffset_but;
    QComboBox *selectAxitO_cb;
    QFrame *line_7;
    QFrame *frame_2;
    QComboBox *processType_cb;
    QLabel *label_22;
    QPushButton *pbBackO;
    TGraphicsViewRefactor *graphicsView;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QPushButton *moveDirectionNot_but;
    QPushButton *insertArcPos_but;
    QPushButton *delete_but;
    QPushButton *cleanTable_but;
    QPushButton *insertLinePos_but;
    QPushButton *editPos_but;
    QTableView *tableView;
    QPushButton *moveUpTabelRow_btu;
    QPushButton *moveDownTabelRow_btu;
    QComboBox *plcType_cb;
    QLabel *label_3;
    QLabel *label_15;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(2008, 1397);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        messText_lin = new QTextEdit(centralwidget);
        messText_lin->setObjectName(QString::fromUtf8("messText_lin"));
        messText_lin->setGeometry(QRect(11, 51, 519, 41));
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

        ip_lin = new QLineEdit(layoutWidget);
        ip_lin->setObjectName(QString::fromUtf8("ip_lin"));
        ip_lin->setMinimumSize(QSize(0, 32));

        horizontalLayout_2->addWidget(ip_lin);

        label_2 = new QLabel(layoutWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_2->addWidget(label_2);

        port_lin = new QLineEdit(layoutWidget);
        port_lin->setObjectName(QString::fromUtf8("port_lin"));
        port_lin->setMinimumSize(QSize(0, 32));
        port_lin->setMaximumSize(QSize(80, 16777215));

        horizontalLayout_2->addWidget(port_lin);

        connect_but = new QPushButton(layoutWidget);
        connect_but->setObjectName(QString::fromUtf8("connect_but"));
        connect_but->setMinimumSize(QSize(0, 35));

        horizontalLayout_2->addWidget(connect_but);

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

        xCurPos_lab = new QLabel(layoutWidget1);
        xCurPos_lab->setObjectName(QString::fromUtf8("xCurPos_lab"));
        xCurPos_lab->setFont(font);

        gridLayout->addWidget(xCurPos_lab, 0, 1, 1, 1);

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

        zCurPos_lab = new QLabel(layoutWidget1);
        zCurPos_lab->setObjectName(QString::fromUtf8("zCurPos_lab"));
        zCurPos_lab->setFont(font);

        gridLayout->addWidget(zCurPos_lab, 0, 4, 1, 1);

        label_12 = new QLabel(layoutWidget1);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setFont(font1);

        gridLayout->addWidget(label_12, 0, 5, 1, 1);

        label_7 = new QLabel(layoutWidget1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setFont(font);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_7, 1, 0, 1, 1);

        yCurPos_lab = new QLabel(layoutWidget1);
        yCurPos_lab->setObjectName(QString::fromUtf8("yCurPos_lab"));
        yCurPos_lab->setFont(font);

        gridLayout->addWidget(yCurPos_lab, 1, 1, 1, 1);

        label_9 = new QLabel(layoutWidget1);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setFont(font1);

        gridLayout->addWidget(label_9, 1, 2, 1, 1);

        label_11 = new QLabel(layoutWidget1);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setFont(font);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout->addWidget(label_11, 1, 3, 1, 1);

        rCurPos_lab = new QLabel(layoutWidget1);
        rCurPos_lab->setObjectName(QString::fromUtf8("rCurPos_lab"));
        rCurPos_lab->setFont(font);

        gridLayout->addWidget(rCurPos_lab, 1, 4, 1, 1);

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
        xAdd_but = new QPushButton(layoutWidget2);
        xAdd_but->setObjectName(QString::fromUtf8("xAdd_but"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(xAdd_but->sizePolicy().hasHeightForWidth());
        xAdd_but->setSizePolicy(sizePolicy);
        xAdd_but->setAutoRepeat(false);
        xAdd_but->setAutoExclusive(false);

        gridLayout_2->addWidget(xAdd_but, 0, 0, 1, 1);

        yAdd_but = new QPushButton(layoutWidget2);
        yAdd_but->setObjectName(QString::fromUtf8("yAdd_but"));
        sizePolicy.setHeightForWidth(yAdd_but->sizePolicy().hasHeightForWidth());
        yAdd_but->setSizePolicy(sizePolicy);
        yAdd_but->setAutoRepeat(false);
        yAdd_but->setAutoExclusive(false);

        gridLayout_2->addWidget(yAdd_but, 0, 1, 1, 1);

        zAdd_but = new QPushButton(layoutWidget2);
        zAdd_but->setObjectName(QString::fromUtf8("zAdd_but"));
        sizePolicy.setHeightForWidth(zAdd_but->sizePolicy().hasHeightForWidth());
        zAdd_but->setSizePolicy(sizePolicy);
        zAdd_but->setAutoRepeat(false);
        zAdd_but->setAutoExclusive(false);

        gridLayout_2->addWidget(zAdd_but, 0, 2, 1, 1);

        rAdd_but = new QPushButton(layoutWidget2);
        rAdd_but->setObjectName(QString::fromUtf8("rAdd_but"));
        sizePolicy.setHeightForWidth(rAdd_but->sizePolicy().hasHeightForWidth());
        rAdd_but->setSizePolicy(sizePolicy);
        rAdd_but->setAutoRepeat(false);
        rAdd_but->setAutoExclusive(false);

        gridLayout_2->addWidget(rAdd_but, 0, 3, 1, 1);

        xSub_but = new QPushButton(layoutWidget2);
        xSub_but->setObjectName(QString::fromUtf8("xSub_but"));
        sizePolicy.setHeightForWidth(xSub_but->sizePolicy().hasHeightForWidth());
        xSub_but->setSizePolicy(sizePolicy);
        xSub_but->setAutoRepeat(false);
        xSub_but->setAutoExclusive(false);

        gridLayout_2->addWidget(xSub_but, 1, 0, 1, 1);

        ySub_but = new QPushButton(layoutWidget2);
        ySub_but->setObjectName(QString::fromUtf8("ySub_but"));
        sizePolicy.setHeightForWidth(ySub_but->sizePolicy().hasHeightForWidth());
        ySub_but->setSizePolicy(sizePolicy);
        ySub_but->setAutoRepeat(false);
        ySub_but->setAutoExclusive(false);

        gridLayout_2->addWidget(ySub_but, 1, 1, 1, 1);

        zSub_but = new QPushButton(layoutWidget2);
        zSub_but->setObjectName(QString::fromUtf8("zSub_but"));
        sizePolicy.setHeightForWidth(zSub_but->sizePolicy().hasHeightForWidth());
        zSub_but->setSizePolicy(sizePolicy);
        zSub_but->setAutoRepeat(false);
        zSub_but->setAutoExclusive(false);

        gridLayout_2->addWidget(zSub_but, 1, 2, 1, 1);

        rSub_but = new QPushButton(layoutWidget2);
        rSub_but->setObjectName(QString::fromUtf8("rSub_but"));
        sizePolicy.setHeightForWidth(rSub_but->sizePolicy().hasHeightForWidth());
        rSub_but->setSizePolicy(sizePolicy);
        rSub_but->setAutoRepeat(false);
        rSub_but->setAutoExclusive(false);

        gridLayout_2->addWidget(rSub_but, 1, 3, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(0, 1350, 1981, 51));
        scanVelocity_lin = new QLineEdit(widget);
        scanVelocity_lin->setObjectName(QString::fromUtf8("scanVelocity_lin"));
        scanVelocity_lin->setGeometry(QRect(170, 10, 81, 31));
        label_14 = new QLabel(widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(260, 10, 91, 31));
        label_14->setFont(font1);
        label_17 = new QLabel(widget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(620, 10, 71, 31));
        label_17->setFont(font1);
        AxleVelocity_lin = new QLineEdit(widget);
        AxleVelocity_lin->setObjectName(QString::fromUtf8("AxleVelocity_lin"));
        AxleVelocity_lin->setGeometry(QRect(500, 10, 111, 31));
        lbv3 = new QLabel(widget);
        lbv3->setObjectName(QString::fromUtf8("lbv3"));
        lbv3->setGeometry(QRect(650, 10, 131, 26));
        lbv3->setFont(font1);
        lbv3->setStyleSheet(QString::fromUtf8(""));
        label_18 = new QLabel(widget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(1390, 10, 71, 31));
        label_18->setFont(font1);
        lineVelocity_lin = new QLineEdit(widget);
        lineVelocity_lin->setObjectName(QString::fromUtf8("lineVelocity_lin"));
        lineVelocity_lin->setGeometry(QRect(1270, 10, 111, 31));
        label_19 = new QLabel(widget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(1720, 10, 71, 31));
        label_19->setFont(font1);
        arcVelocity_lin = new QLineEdit(widget);
        arcVelocity_lin->setObjectName(QString::fromUtf8("arcVelocity_lin"));
        arcVelocity_lin->setGeometry(QRect(1600, 10, 111, 31));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(90, 11, 101, 31));
        label_16 = new QLabel(widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(1160, 10, 111, 31));
        label_20 = new QLabel(widget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(1490, 10, 111, 31));
        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(10, 10, 61, 31));
        label_21 = new QLabel(widget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(990, 10, 71, 31));
        label_21->setFont(font1);
        pointVelocity_lin = new QLineEdit(widget);
        pointVelocity_lin->setObjectName(QString::fromUtf8("pointVelocity_lin"));
        pointVelocity_lin->setGeometry(QRect(870, 10, 111, 31));
        label_23 = new QLabel(widget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        label_23->setGeometry(QRect(600, 1360, 111, 31));
        label_24 = new QLabel(widget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        label_24->setGeometry(QRect(760, 10, 111, 31));
        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 1130, 1991, 201));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        imageProcess_but = new QPushButton(frame);
        imageProcess_but->setObjectName(QString::fromUtf8("imageProcess_but"));
        imageProcess_but->setGeometry(QRect(1250, 40, 211, 41));
        startScan_But = new QPushButton(frame);
        startScan_But->setObjectName(QString::fromUtf8("startScan_But"));
        startScan_But->setGeometry(QRect(1500, 40, 101, 41));
        sizePolicy.setHeightForWidth(startScan_But->sizePolicy().hasHeightForWidth());
        startScan_But->setSizePolicy(sizePolicy);
        alarmReset_but = new QPushButton(frame);
        alarmReset_but->setObjectName(QString::fromUtf8("alarmReset_but"));
        alarmReset_but->setGeometry(QRect(1860, 40, 111, 41));
        sizePolicy.setHeightForWidth(alarmReset_but->sizePolicy().hasHeightForWidth());
        alarmReset_but->setSizePolicy(sizePolicy);
        setOrigin_but = new QPushButton(frame);
        setOrigin_but->setObjectName(QString::fromUtf8("setOrigin_but"));
        setOrigin_but->setGeometry(QRect(590, 140, 101, 41));
        sizePolicy.setHeightForWidth(setOrigin_but->sizePolicy().hasHeightForWidth());
        setOrigin_but->setSizePolicy(sizePolicy);
        stopScan_but = new QPushButton(frame);
        stopScan_but->setObjectName(QString::fromUtf8("stopScan_but"));
        stopScan_but->setGeometry(QRect(1620, 40, 101, 41));
        sizePolicy.setHeightForWidth(stopScan_but->sizePolicy().hasHeightForWidth());
        stopScan_but->setSizePolicy(sizePolicy);
        endScan_but = new QPushButton(frame);
        endScan_but->setObjectName(QString::fromUtf8("endScan_but"));
        endScan_but->setGeometry(QRect(1740, 40, 101, 41));
        sizePolicy.setHeightForWidth(endScan_but->sizePolicy().hasHeightForWidth());
        endScan_but->setSizePolicy(sizePolicy);
        line_3 = new QFrame(frame);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setGeometry(QRect(1000, 40, 20, 151));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);
        DXFimport_but = new QPushButton(frame);
        DXFimport_but->setObjectName(QString::fromUtf8("DXFimport_but"));
        DXFimport_but->setGeometry(QRect(10, 50, 101, 41));
        sizePolicy.setHeightForWidth(DXFimport_but->sizePolicy().hasHeightForWidth());
        DXFimport_but->setSizePolicy(sizePolicy);
        traject_y0 = new QLineEdit(frame);
        traject_y0->setObjectName(QString::fromUtf8("traject_y0"));
        traject_y0->setGeometry(QRect(320, 40, 91, 41));
        setTrajecStart_but = new QPushButton(frame);
        setTrajecStart_but->setObjectName(QString::fromUtf8("setTrajecStart_but"));
        setTrajecStart_but->setGeometry(QRect(180, 140, 171, 41));
        sizePolicy.setHeightForWidth(setTrajecStart_but->sizePolicy().hasHeightForWidth());
        setTrajecStart_but->setSizePolicy(sizePolicy);
        traject_x0 = new QLineEdit(frame);
        traject_x0->setObjectName(QString::fromUtf8("traject_x0"));
        traject_x0->setGeometry(QRect(180, 40, 91, 41));
        V_label_3 = new QLabel(frame);
        V_label_3->setObjectName(QString::fromUtf8("V_label_3"));
        V_label_3->setGeometry(QRect(150, 50, 21, 26));
        V_label_3->setFont(font1);
        V_label_3->setStyleSheet(QString::fromUtf8(""));
        V_label_4 = new QLabel(frame);
        V_label_4->setObjectName(QString::fromUtf8("V_label_4"));
        V_label_4->setGeometry(QRect(290, 50, 21, 26));
        V_label_4->setFont(font1);
        V_label_4->setStyleSheet(QString::fromUtf8(""));
        ascan_but = new QPushButton(frame);
        ascan_but->setObjectName(QString::fromUtf8("ascan_but"));
        ascan_but->setGeometry(QRect(1030, 40, 201, 41));
        moveToPosition_but = new QPushButton(frame);
        moveToPosition_but->setObjectName(QString::fromUtf8("moveToPosition_but"));
        moveToPosition_but->setGeometry(QRect(180, 90, 171, 41));
        sizePolicy.setHeightForWidth(moveToPosition_but->sizePolicy().hasHeightForWidth());
        moveToPosition_but->setSizePolicy(sizePolicy);
        line_4 = new QFrame(frame);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setGeometry(QRect(120, 30, 20, 151));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);
        V_label_9 = new QLabel(frame);
        V_label_9->setObjectName(QString::fromUtf8("V_label_9"));
        V_label_9->setGeometry(QRect(550, 50, 21, 26));
        V_label_9->setFont(font1);
        V_label_9->setStyleSheet(QString::fromUtf8(""));
        V_label_10 = new QLabel(frame);
        V_label_10->setObjectName(QString::fromUtf8("V_label_10"));
        V_label_10->setGeometry(QRect(420, 50, 21, 26));
        V_label_10->setFont(font1);
        V_label_10->setStyleSheet(QString::fromUtf8(""));
        traject_z0 = new QLineEdit(frame);
        traject_z0->setObjectName(QString::fromUtf8("traject_z0"));
        traject_z0->setGeometry(QRect(450, 40, 91, 41));
        traject_r0 = new QLineEdit(frame);
        traject_r0->setObjectName(QString::fromUtf8("traject_r0"));
        traject_r0->setGeometry(QRect(590, 40, 101, 41));
        writeInPLC_but = new QPushButton(frame);
        writeInPLC_but->setObjectName(QString::fromUtf8("writeInPLC_but"));
        writeInPLC_but->setGeometry(QRect(1250, 140, 211, 41));
        creatG_but = new QPushButton(frame);
        creatG_but->setObjectName(QString::fromUtf8("creatG_but"));
        creatG_but->setGeometry(QRect(1030, 140, 201, 41));
        getCurryPoint_but = new QPushButton(frame);
        getCurryPoint_but->setObjectName(QString::fromUtf8("getCurryPoint_but"));
        getCurryPoint_but->setGeometry(QRect(370, 90, 181, 41));
        sizePolicy.setHeightForWidth(getCurryPoint_but->sizePolicy().hasHeightForWidth());
        getCurryPoint_but->setSizePolicy(sizePolicy);
        cBworkpiece = new QComboBox(frame);
        cBworkpiece->setObjectName(QString::fromUtf8("cBworkpiece"));
        cBworkpiece->setGeometry(QRect(1620, 140, 101, 41));
        pbNewPiece = new QPushButton(frame);
        pbNewPiece->setObjectName(QString::fromUtf8("pbNewPiece"));
        pbNewPiece->setGeometry(QRect(1740, 140, 101, 41));
        pBdeletePiece = new QPushButton(frame);
        pBdeletePiece->setObjectName(QString::fromUtf8("pBdeletePiece"));
        pBdeletePiece->setGeometry(QRect(1860, 140, 111, 41));
        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(1560, 120, 81, 81));
        pBbrazing = new QPushButton(frame);
        pBbrazing->setObjectName(QString::fromUtf8("pBbrazing"));
        pBbrazing->setGeometry(QRect(10, 140, 101, 41));
        trajectoryOffset_but = new QPushButton(frame);
        trajectoryOffset_but->setObjectName(QString::fromUtf8("trajectoryOffset_but"));
        trajectoryOffset_but->setGeometry(QRect(370, 140, 181, 41));
        sizePolicy.setHeightForWidth(trajectoryOffset_but->sizePolicy().hasHeightForWidth());
        trajectoryOffset_but->setSizePolicy(sizePolicy);
        selectAxitO_cb = new QComboBox(frame);
        selectAxitO_cb->addItem(QString());
        selectAxitO_cb->addItem(QString());
        selectAxitO_cb->addItem(QString());
        selectAxitO_cb->addItem(QString());
        selectAxitO_cb->setObjectName(QString::fromUtf8("selectAxitO_cb"));
        selectAxitO_cb->setGeometry(QRect(590, 90, 101, 41));
        selectAxitO_cb->setLayoutDirection(Qt::LeftToRight);
        line_7 = new QFrame(frame);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        line_7->setGeometry(QRect(1470, 30, 20, 151));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);
        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        frame_2->setGeometry(QRect(710, 40, 291, 151));
        frame_2->setStyleSheet(QString::fromUtf8("border: 2px solid rgb(200, 200, 200);\n"
""));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        processType_cb = new QComboBox(frame_2);
        processType_cb->addItem(QString());
        processType_cb->addItem(QString());
        processType_cb->addItem(QString());
        processType_cb->setObjectName(QString::fromUtf8("processType_cb"));
        processType_cb->setGeometry(QRect(10, 100, 151, 41));
        processType_cb->setLayoutDirection(Qt::LeftToRight);
        label_22 = new QLabel(frame_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(20, 50, 141, 31));
        pbBackO = new QPushButton(frame);
        pbBackO->setObjectName(QString::fromUtf8("pbBackO"));
        pbBackO->setGeometry(QRect(1500, 100, 101, 41));
        frame_2->raise();
        imageProcess_but->raise();
        startScan_But->raise();
        alarmReset_but->raise();
        setOrigin_but->raise();
        stopScan_but->raise();
        endScan_but->raise();
        line_3->raise();
        DXFimport_but->raise();
        traject_y0->raise();
        setTrajecStart_but->raise();
        traject_x0->raise();
        V_label_3->raise();
        V_label_4->raise();
        ascan_but->raise();
        moveToPosition_but->raise();
        line_4->raise();
        V_label_9->raise();
        V_label_10->raise();
        traject_z0->raise();
        traject_r0->raise();
        writeInPLC_but->raise();
        creatG_but->raise();
        getCurryPoint_but->raise();
        cBworkpiece->raise();
        pbNewPiece->raise();
        pBdeletePiece->raise();
        label_4->raise();
        pBbrazing->raise();
        trajectoryOffset_but->raise();
        selectAxitO_cb->raise();
        line_7->raise();
        pbBackO->raise();
        graphicsView = new TGraphicsViewRefactor(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setEnabled(true);
        graphicsView->setGeometry(QRect(0, 100, 1161, 1031));
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
        tabWidget->setGeometry(QRect(1150, 110, 841, 1021));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::West);
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        moveDirectionNot_but = new QPushButton(tab_2);
        moveDirectionNot_but->setObjectName(QString::fromUtf8("moveDirectionNot_but"));
        moveDirectionNot_but->setGeometry(QRect(170, 940, 151, 41));
        insertArcPos_but = new QPushButton(tab_2);
        insertArcPos_but->setObjectName(QString::fromUtf8("insertArcPos_but"));
        insertArcPos_but->setGeometry(QRect(380, 880, 171, 41));
        delete_but = new QPushButton(tab_2);
        delete_but->setObjectName(QString::fromUtf8("delete_but"));
        delete_but->setGeometry(QRect(10, 940, 101, 41));
        cleanTable_but = new QPushButton(tab_2);
        cleanTable_but->setObjectName(QString::fromUtf8("cleanTable_but"));
        cleanTable_but->setGeometry(QRect(170, 880, 151, 41));
        insertLinePos_but = new QPushButton(tab_2);
        insertLinePos_but->setObjectName(QString::fromUtf8("insertLinePos_but"));
        insertLinePos_but->setGeometry(QRect(610, 880, 181, 41));
        editPos_but = new QPushButton(tab_2);
        editPos_but->setObjectName(QString::fromUtf8("editPos_but"));
        editPos_but->setGeometry(QRect(10, 880, 101, 41));
        tableView = new QTableView(tab_2);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(0, 0, 811, 871));
        moveUpTabelRow_btu = new QPushButton(tab_2);
        moveUpTabelRow_btu->setObjectName(QString::fromUtf8("moveUpTabelRow_btu"));
        moveUpTabelRow_btu->setGeometry(QRect(380, 940, 171, 41));
        moveDownTabelRow_btu = new QPushButton(tab_2);
        moveDownTabelRow_btu->setObjectName(QString::fromUtf8("moveDownTabelRow_btu"));
        moveDownTabelRow_btu->setGeometry(QRect(610, 940, 181, 41));
        tabWidget->addTab(tab_2, QString());
        plcType_cb = new QComboBox(centralwidget);
        plcType_cb->addItem(QString());
        plcType_cb->addItem(QString());
        plcType_cb->setObjectName(QString::fromUtf8("plcType_cb"));
        plcType_cb->setGeometry(QRect(1780, 40, 111, 41));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(1720, 10, 141, 31));
        label_15 = new QLabel(centralwidget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(390, 1360, 111, 31));
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QApplication::translate("MainWindow", "IP:", nullptr));
        ip_lin->setText(QApplication::translate("MainWindow", "192.168.1.88", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "Port:", nullptr));
        port_lin->setText(QApplication::translate("MainWindow", "502", nullptr));
        connect_but->setText(QApplication::translate("MainWindow", " \350\277\236\346\216\245", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "x\357\274\232", nullptr));
        xCurPos_lab->setText(QString());
        label_8->setText(QApplication::translate("MainWindow", "mm", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "z\357\274\232", nullptr));
        zCurPos_lab->setText(QString());
        label_12->setText(QApplication::translate("MainWindow", "mm", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "y\357\274\232", nullptr));
        yCurPos_lab->setText(QString());
        label_9->setText(QApplication::translate("MainWindow", "mm", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "r\357\274\232", nullptr));
        rCurPos_lab->setText(QString());
        label_10->setText(QApplication::translate("MainWindow", "mm", nullptr));
        xAdd_but->setText(QApplication::translate("MainWindow", "X+", nullptr));
        yAdd_but->setText(QApplication::translate("MainWindow", "Y+", nullptr));
        zAdd_but->setText(QApplication::translate("MainWindow", "Z+", nullptr));
        rAdd_but->setText(QApplication::translate("MainWindow", "R+", nullptr));
        xSub_but->setText(QApplication::translate("MainWindow", "X-", nullptr));
        ySub_but->setText(QApplication::translate("MainWindow", "Y-", nullptr));
        zSub_but->setText(QApplication::translate("MainWindow", "Z-", nullptr));
        rSub_but->setText(QApplication::translate("MainWindow", "R-", nullptr));
        scanVelocity_lin->setText(QString());
        label_14->setText(QApplication::translate("MainWindow", "mm/s", nullptr));
        label_17->setText(QApplication::translate("MainWindow", "mm/s", nullptr));
        AxleVelocity_lin->setText(QString());
        lbv3->setText(QString());
        label_18->setText(QApplication::translate("MainWindow", "mm/s", nullptr));
        lineVelocity_lin->setText(QString());
        label_19->setText(QApplication::translate("MainWindow", "mm/s", nullptr));
        arcVelocity_lin->setText(QString());
        label_5->setText(QApplication::translate("MainWindow", "\350\275\264\351\200\237\345\272\246\357\274\232", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "\347\233\264\347\272\277\351\200\237\345\272\246\357\274\232", nullptr));
        label_20->setText(QApplication::translate("MainWindow", "\345\234\206\345\274\247\351\200\237\345\272\246\357\274\232", nullptr));
        comboBox->setItemText(0, QApplication::translate("MainWindow", "x", nullptr));
        comboBox->setItemText(1, QApplication::translate("MainWindow", "y", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "z", nullptr));
        comboBox->setItemText(3, QApplication::translate("MainWindow", "r", nullptr));

        label_21->setText(QApplication::translate("MainWindow", "mm/s", nullptr));
        pointVelocity_lin->setText(QString());
        label_23->setText(QApplication::translate("MainWindow", "\345\256\232\344\275\215\351\200\237\345\272\246\357\274\232", nullptr));
        label_24->setText(QApplication::translate("MainWindow", "\347\202\271\345\212\250\351\200\237\345\272\246\357\274\232", nullptr));
        imageProcess_but->setText(QApplication::translate("MainWindow", "imageProcess", nullptr));
        startScan_But->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        alarmReset_but->setText(QApplication::translate("MainWindow", "\346\212\245\350\255\246\345\244\215\344\275\215", nullptr));
        setOrigin_but->setText(QApplication::translate("MainWindow", "\350\256\276\350\275\264\345\216\237\347\202\271", nullptr));
        stopScan_but->setText(QApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        endScan_but->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        DXFimport_but->setText(QApplication::translate("MainWindow", "\345\257\274\345\205\245DXF", nullptr));
        traject_y0->setText(QApplication::translate("MainWindow", "0", nullptr));
        setTrajecStart_but->setText(QApplication::translate("MainWindow", "\350\256\276\345\256\232\350\265\267\347\202\271", nullptr));
        traject_x0->setText(QApplication::translate("MainWindow", "0", nullptr));
        V_label_3->setText(QApplication::translate("MainWindow", "x:", nullptr));
        V_label_4->setText(QApplication::translate("MainWindow", "y:", nullptr));
        ascan_but->setText(QApplication::translate("MainWindow", "Ascan", nullptr));
        moveToPosition_but->setText(QApplication::translate("MainWindow", "\347\247\273\345\212\250", nullptr));
        V_label_9->setText(QApplication::translate("MainWindow", "r:", nullptr));
        V_label_10->setText(QApplication::translate("MainWindow", "z:", nullptr));
        traject_z0->setText(QApplication::translate("MainWindow", "0", nullptr));
        traject_r0->setText(QApplication::translate("MainWindow", "0", nullptr));
        writeInPLC_but->setText(QApplication::translate("MainWindow", " \345\257\204\345\255\230\345\231\250\350\277\220\350\241\214\357\274\210plc\357\274\211", nullptr));
        creatG_but->setText(QApplication::translate("MainWindow", "GCode\350\277\220\350\241\214\357\274\210plc\357\274\211", nullptr));
        getCurryPoint_but->setText(QApplication::translate("MainWindow", "\350\216\267\345\217\226\345\210\227\350\241\250\347\202\271", nullptr));
        pbNewPiece->setText(QApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        pBdeletePiece->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\345\267\245\344\273\266\357\274\232", nullptr));
        pBbrazing->setText(QApplication::translate("MainWindow", "\351\222\216\347\204\212", nullptr));
        trajectoryOffset_but->setText(QApplication::translate("MainWindow", "\350\275\250\350\277\271\345\201\217\347\247\273", nullptr));
        selectAxitO_cb->setItemText(0, QApplication::translate("MainWindow", "x", nullptr));
        selectAxitO_cb->setItemText(1, QApplication::translate("MainWindow", "y", nullptr));
        selectAxitO_cb->setItemText(2, QApplication::translate("MainWindow", "z", nullptr));
        selectAxitO_cb->setItemText(3, QApplication::translate("MainWindow", "r", nullptr));

        processType_cb->setItemText(0, QApplication::translate("MainWindow", "\351\200\211\346\213\251g\344\273\243\347\240\201", nullptr));
        processType_cb->setItemText(1, QApplication::translate("MainWindow", "\351\200\211\346\213\251\346\221\251\346\223\246\347\204\212", nullptr));
        processType_cb->setItemText(2, QApplication::translate("MainWindow", "\351\200\211\346\213\251\351\222\216\347\204\212", nullptr));

        label_22->setText(QApplication::translate("MainWindow", "\345\267\245\350\211\272\347\261\273\345\236\213\357\274\232", nullptr));
        pbBackO->setText(QApplication::translate("MainWindow", "\345\233\236\345\216\237\347\202\271", nullptr));
        moveDirectionNot_but->setText(QApplication::translate("MainWindow", "\350\277\220\345\212\250\346\226\271\345\220\221\345\217\215\350\275\254", nullptr));
        insertArcPos_but->setText(QApplication::translate("MainWindow", "\346\217\222\345\205\245\345\234\206\345\274\247", nullptr));
        delete_but->setText(QApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        cleanTable_but->setText(QApplication::translate("MainWindow", "\346\270\205\347\251\272\350\241\250\346\240\274", nullptr));
        insertLinePos_but->setText(QApplication::translate("MainWindow", "\346\217\222\345\205\245\347\233\264\347\272\277", nullptr));
        editPos_but->setText(QApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        moveUpTabelRow_btu->setText(QApplication::translate("MainWindow", "\345\220\221\344\270\212\347\247\273\345\212\250\350\241\214", nullptr));
        moveDownTabelRow_btu->setText(QApplication::translate("MainWindow", "\345\220\221\344\270\213\347\247\273\345\212\250\350\241\214", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "Trajectory Scan", nullptr));
        plcType_cb->setItemText(0, QApplication::translate("MainWindow", "h5u", nullptr));
        plcType_cb->setItemText(1, QApplication::translate("MainWindow", "ac700", nullptr));

        label_3->setText(QApplication::translate("MainWindow", "plc\347\261\273\345\236\213\357\274\232", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "\345\256\232\344\275\215\351\200\237\345\272\246\357\274\232", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
