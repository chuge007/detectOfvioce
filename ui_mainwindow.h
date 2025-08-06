/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>
#include <tgraphicsviewrefactor.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_5;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QGridLayout *gridLayout;
    QPushButton *moveDownTabelRow_btu;
    QPushButton *editPos_but;
    QPushButton *insertLinePos_but;
    QPushButton *insertArcPos_but;
    QPushButton *moveUpTabelRow_btu;
    QPushButton *cleanTable_but;
    QPushButton *moveDirectionNot_but;
    QTableView *tableView;
    QPushButton *delete_but;
    TGraphicsViewRefactor *graphicsView;
    QFrame *frame;
    QGridLayout *gridLayout_2;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pBdeletePiece;
    QLabel *V_label_4;
    QSpacerItem *horizontalSpacer_17;
    QSpacerItem *horizontalSpacer_23;
    QPushButton *smooth_but;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_19;
    QLabel *label_4;
    QPushButton *setOrigin_but;
    QLineEdit *traject_z0;
    QFrame *line_7;
    QPushButton *stopScan_but;
    QPushButton *setTrajecStart_but;
    QLineEdit *traject_x0;
    QSpacerItem *horizontalSpacer_24;
    QSpacerItem *horizontalSpacer_21;
    QPushButton *pbNewPiece;
    QSpacerItem *horizontalSpacer_11;
    QPushButton *creatG_but;
    QSpacerItem *horizontalSpacer_13;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *endScan_but;
    QPushButton *ascan_but;
    QDoubleSpinBox *smoothX_dsb;
    QSpacerItem *horizontalSpacer_12;
    QSpacerItem *horizontalSpacer_16;
    QLabel *V_label_10;
    QLabel *V_label_9;
    QLabel *V_label_3;
    QSpacerItem *horizontalSpacer_20;
    QSpacerItem *horizontalSpacer_6;
    QLineEdit *traject_r0;
    QPushButton *pbBackO;
    QPushButton *startScan_But;
    QComboBox *selectAxitO_cb;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *alarmReset_but;
    QPushButton *pBbrazing;
    QPushButton *getCurryPoint_but;
    QPushButton *moveToPosition_but;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *horizontalSpacer_22;
    QPushButton *trajectoryOffset_but;
    QPushButton *DXFimport_but;
    QFrame *frame_2;
    QGridLayout *gridLayout_3;
    QLabel *label_22;
    QComboBox *processType_cb;
    QFrame *line_3;
    QSpacerItem *horizontalSpacer;
    QFrame *line_4;
    QPushButton *PoseCalculation_but;
    QSpacerItem *horizontalSpacer_14;
    QSpacerItem *horizontalSpacer_18;
    QComboBox *cBworkpiece;
    QLineEdit *traject_y0;
    QPushButton *imageProcess_but;
    QPushButton *writeInPLC_but;
    QSpacerItem *horizontalSpacer_25;
    QFrame *frame_3;
    QGridLayout *gridLayout_4;
    QPushButton *zSub_but;
    QLineEdit *port_lin;
    QLabel *label_2;
    QPushButton *xAdd_but;
    QPushButton *yAdd_but;
    QPushButton *rSub_but;
    QLabel *label_10;
    QFrame *line;
    QLabel *label_12;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *rCurPos_lab;
    QLabel *label_9;
    QPushButton *xSub_but;
    QLabel *zCurPos_lab;
    QPushButton *ySub_but;
    QLabel *label;
    QComboBox *plcType_cb;
    QLabel *xCurPos_lab;
    QPushButton *connect_but;
    QLineEdit *ip_lin;
    QLabel *label_13;
    QPushButton *rAdd_but;
    QLabel *label_3;
    QPushButton *zAdd_but;
    QLabel *yCurPos_lab;
    QLabel *label_7;
    QLabel *label_11;
    QLabel *disMess_lab;
    QWidget *widget;
    QHBoxLayout *horizontalLayout_2;
    QComboBox *comboBox;
    QLabel *label_5;
    QLineEdit *scanVelocity_lin;
    QLabel *label_14;
    QLabel *label_23;
    QLineEdit *AxleVelocity_lin;
    QLabel *label_17;
    QLabel *label_24;
    QLineEdit *pointVelocity_lin;
    QLabel *label_21;
    QLabel *label_16;
    QLineEdit *lineVelocity_lin;
    QLabel *label_18;
    QLabel *label_20;
    QLineEdit *arcVelocity_lin;
    QLabel *label_19;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1379, 1307);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(0, 0));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_5 = new QGridLayout(centralwidget);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(0, 0));
        tabWidget->setLayoutDirection(Qt::LeftToRight);
        tabWidget->setTabPosition(QTabWidget::West);
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        gridLayout = new QGridLayout(tab_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        moveDownTabelRow_btu = new QPushButton(tab_2);
        moveDownTabelRow_btu->setObjectName(QString::fromUtf8("moveDownTabelRow_btu"));
        sizePolicy.setHeightForWidth(moveDownTabelRow_btu->sizePolicy().hasHeightForWidth());
        moveDownTabelRow_btu->setSizePolicy(sizePolicy);
        moveDownTabelRow_btu->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(moveDownTabelRow_btu, 2, 3, 1, 1);

        editPos_but = new QPushButton(tab_2);
        editPos_but->setObjectName(QString::fromUtf8("editPos_but"));
        sizePolicy.setHeightForWidth(editPos_but->sizePolicy().hasHeightForWidth());
        editPos_but->setSizePolicy(sizePolicy);
        editPos_but->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(editPos_but, 1, 0, 1, 1);

        insertLinePos_but = new QPushButton(tab_2);
        insertLinePos_but->setObjectName(QString::fromUtf8("insertLinePos_but"));
        sizePolicy.setHeightForWidth(insertLinePos_but->sizePolicy().hasHeightForWidth());
        insertLinePos_but->setSizePolicy(sizePolicy);
        insertLinePos_but->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(insertLinePos_but, 1, 3, 1, 1);

        insertArcPos_but = new QPushButton(tab_2);
        insertArcPos_but->setObjectName(QString::fromUtf8("insertArcPos_but"));
        sizePolicy.setHeightForWidth(insertArcPos_but->sizePolicy().hasHeightForWidth());
        insertArcPos_but->setSizePolicy(sizePolicy);
        insertArcPos_but->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(insertArcPos_but, 1, 2, 1, 1);

        moveUpTabelRow_btu = new QPushButton(tab_2);
        moveUpTabelRow_btu->setObjectName(QString::fromUtf8("moveUpTabelRow_btu"));
        sizePolicy.setHeightForWidth(moveUpTabelRow_btu->sizePolicy().hasHeightForWidth());
        moveUpTabelRow_btu->setSizePolicy(sizePolicy);
        moveUpTabelRow_btu->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(moveUpTabelRow_btu, 2, 2, 1, 1);

        cleanTable_but = new QPushButton(tab_2);
        cleanTable_but->setObjectName(QString::fromUtf8("cleanTable_but"));
        sizePolicy.setHeightForWidth(cleanTable_but->sizePolicy().hasHeightForWidth());
        cleanTable_but->setSizePolicy(sizePolicy);
        cleanTable_but->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(cleanTable_but, 1, 1, 1, 1);

        moveDirectionNot_but = new QPushButton(tab_2);
        moveDirectionNot_but->setObjectName(QString::fromUtf8("moveDirectionNot_but"));
        sizePolicy.setHeightForWidth(moveDirectionNot_but->sizePolicy().hasHeightForWidth());
        moveDirectionNot_but->setSizePolicy(sizePolicy);
        moveDirectionNot_but->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(moveDirectionNot_but, 2, 1, 1, 1);

        tableView = new QTableView(tab_2);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        sizePolicy.setHeightForWidth(tableView->sizePolicy().hasHeightForWidth());
        tableView->setSizePolicy(sizePolicy);
        tableView->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(tableView, 0, 0, 1, 4);

        delete_but = new QPushButton(tab_2);
        delete_but->setObjectName(QString::fromUtf8("delete_but"));
        sizePolicy.setHeightForWidth(delete_but->sizePolicy().hasHeightForWidth());
        delete_but->setSizePolicy(sizePolicy);
        delete_but->setMinimumSize(QSize(0, 0));

        gridLayout->addWidget(delete_but, 2, 0, 1, 1);

        gridLayout->setRowStretch(0, 15);
        tabWidget->addTab(tab_2, QString());

        gridLayout_5->addWidget(tabWidget, 1, 1, 1, 1);

        graphicsView = new TGraphicsViewRefactor(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setEnabled(true);
        sizePolicy.setHeightForWidth(graphicsView->sizePolicy().hasHeightForWidth());
        graphicsView->setSizePolicy(sizePolicy);
        graphicsView->setMinimumSize(QSize(0, 0));
        graphicsView->setMaximumSize(QSize(16777215, 16777215));
        graphicsView->setBaseSize(QSize(0, 0));
        graphicsView->setInteractive(true);

        gridLayout_5->addWidget(graphicsView, 1, 0, 1, 1);

        frame = new QFrame(centralwidget);
        frame->setObjectName(QString::fromUtf8("frame"));
        sizePolicy.setHeightForWidth(frame->sizePolicy().hasHeightForWidth());
        frame->setSizePolicy(sizePolicy);
        frame->setMinimumSize(QSize(0, 0));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        gridLayout_2 = new QGridLayout(frame);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 19, 1, 1);

        pBdeletePiece = new QPushButton(frame);
        pBdeletePiece->setObjectName(QString::fromUtf8("pBdeletePiece"));
        sizePolicy.setHeightForWidth(pBdeletePiece->sizePolicy().hasHeightForWidth());
        pBdeletePiece->setSizePolicy(sizePolicy);
        pBdeletePiece->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(pBdeletePiece, 4, 42, 1, 1);

        V_label_4 = new QLabel(frame);
        V_label_4->setObjectName(QString::fromUtf8("V_label_4"));
        sizePolicy.setHeightForWidth(V_label_4->sizePolicy().hasHeightForWidth());
        V_label_4->setSizePolicy(sizePolicy);
        V_label_4->setMinimumSize(QSize(0, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("SansSerif"));
        font.setPointSize(11);
        V_label_4->setFont(font);
        V_label_4->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(V_label_4, 0, 5, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_17, 0, 35, 1, 1);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_23, 0, 28, 1, 1);

        smooth_but = new QPushButton(frame);
        smooth_but->setObjectName(QString::fromUtf8("smooth_but"));
        sizePolicy.setHeightForWidth(smooth_but->sizePolicy().hasHeightForWidth());
        smooth_but->setSizePolicy(sizePolicy);
        smooth_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(smooth_but, 4, 10, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_7, 0, 22, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_9, 0, 26, 1, 1);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_19, 0, 25, 1, 1);

        label_4 = new QLabel(frame);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(label_4, 4, 39, 1, 1);

        setOrigin_but = new QPushButton(frame);
        setOrigin_but->setObjectName(QString::fromUtf8("setOrigin_but"));
        sizePolicy.setHeightForWidth(setOrigin_but->sizePolicy().hasHeightForWidth());
        setOrigin_but->setSizePolicy(sizePolicy);
        setOrigin_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(setOrigin_but, 4, 8, 1, 1);

        traject_z0 = new QLineEdit(frame);
        traject_z0->setObjectName(QString::fromUtf8("traject_z0"));
        sizePolicy.setHeightForWidth(traject_z0->sizePolicy().hasHeightForWidth());
        traject_z0->setSizePolicy(sizePolicy);
        traject_z0->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(traject_z0, 0, 8, 1, 1);

        line_7 = new QFrame(frame);
        line_7->setObjectName(QString::fromUtf8("line_7"));
        sizePolicy.setHeightForWidth(line_7->sizePolicy().hasHeightForWidth());
        line_7->setSizePolicy(sizePolicy);
        line_7->setMinimumSize(QSize(0, 0));
        line_7->setFrameShape(QFrame::VLine);
        line_7->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_7, 0, 27, 5, 1);

        stopScan_but = new QPushButton(frame);
        stopScan_but->setObjectName(QString::fromUtf8("stopScan_but"));
        sizePolicy.setHeightForWidth(stopScan_but->sizePolicy().hasHeightForWidth());
        stopScan_but->setSizePolicy(sizePolicy);
        stopScan_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(stopScan_but, 0, 40, 1, 1);

        setTrajecStart_but = new QPushButton(frame);
        setTrajecStart_but->setObjectName(QString::fromUtf8("setTrajecStart_but"));
        sizePolicy.setHeightForWidth(setTrajecStart_but->sizePolicy().hasHeightForWidth());
        setTrajecStart_but->setSizePolicy(sizePolicy);
        setTrajecStart_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(setTrajecStart_but, 4, 4, 1, 1);

        traject_x0 = new QLineEdit(frame);
        traject_x0->setObjectName(QString::fromUtf8("traject_x0"));
        sizePolicy.setHeightForWidth(traject_x0->sizePolicy().hasHeightForWidth());
        traject_x0->setSizePolicy(sizePolicy);
        traject_x0->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(traject_x0, 0, 4, 1, 1);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_24, 0, 23, 1, 1);

        horizontalSpacer_21 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_21, 0, 31, 1, 1);

        pbNewPiece = new QPushButton(frame);
        pbNewPiece->setObjectName(QString::fromUtf8("pbNewPiece"));
        sizePolicy.setHeightForWidth(pbNewPiece->sizePolicy().hasHeightForWidth());
        pbNewPiece->setSizePolicy(sizePolicy);
        pbNewPiece->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(pbNewPiece, 4, 41, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_11, 0, 33, 1, 1);

        creatG_but = new QPushButton(frame);
        creatG_but->setObjectName(QString::fromUtf8("creatG_but"));
        sizePolicy.setHeightForWidth(creatG_but->sizePolicy().hasHeightForWidth());
        creatG_but->setSizePolicy(sizePolicy);
        creatG_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(creatG_but, 4, 14, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_13, 0, 30, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_15, 0, 17, 1, 1);

        endScan_but = new QPushButton(frame);
        endScan_but->setObjectName(QString::fromUtf8("endScan_but"));
        sizePolicy.setHeightForWidth(endScan_but->sizePolicy().hasHeightForWidth());
        endScan_but->setSizePolicy(sizePolicy);
        endScan_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(endScan_but, 0, 41, 1, 1);

        ascan_but = new QPushButton(frame);
        ascan_but->setObjectName(QString::fromUtf8("ascan_but"));
        sizePolicy.setHeightForWidth(ascan_but->sizePolicy().hasHeightForWidth());
        ascan_but->setSizePolicy(sizePolicy);
        ascan_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(ascan_but, 0, 14, 1, 1);

        smoothX_dsb = new QDoubleSpinBox(frame);
        smoothX_dsb->setObjectName(QString::fromUtf8("smoothX_dsb"));
        sizePolicy.setHeightForWidth(smoothX_dsb->sizePolicy().hasHeightForWidth());
        smoothX_dsb->setSizePolicy(sizePolicy);
        smoothX_dsb->setValue(5.000000000000000);

        gridLayout_2->addWidget(smoothX_dsb, 2, 10, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_12, 0, 32, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_16, 0, 29, 1, 1);

        V_label_10 = new QLabel(frame);
        V_label_10->setObjectName(QString::fromUtf8("V_label_10"));
        sizePolicy.setHeightForWidth(V_label_10->sizePolicy().hasHeightForWidth());
        V_label_10->setSizePolicy(sizePolicy);
        V_label_10->setMinimumSize(QSize(0, 0));
        V_label_10->setFont(font);
        V_label_10->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(V_label_10, 0, 7, 1, 1);

        V_label_9 = new QLabel(frame);
        V_label_9->setObjectName(QString::fromUtf8("V_label_9"));
        sizePolicy.setHeightForWidth(V_label_9->sizePolicy().hasHeightForWidth());
        V_label_9->setSizePolicy(sizePolicy);
        V_label_9->setMinimumSize(QSize(0, 0));
        V_label_9->setFont(font);
        V_label_9->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(V_label_9, 0, 9, 1, 1);

        V_label_3 = new QLabel(frame);
        V_label_3->setObjectName(QString::fromUtf8("V_label_3"));
        sizePolicy.setHeightForWidth(V_label_3->sizePolicy().hasHeightForWidth());
        V_label_3->setSizePolicy(sizePolicy);
        V_label_3->setMinimumSize(QSize(0, 0));
        V_label_3->setFont(font);
        V_label_3->setStyleSheet(QString::fromUtf8(""));

        gridLayout_2->addWidget(V_label_3, 0, 3, 1, 1);

        horizontalSpacer_20 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_20, 0, 38, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_6, 0, 21, 1, 1);

        traject_r0 = new QLineEdit(frame);
        traject_r0->setObjectName(QString::fromUtf8("traject_r0"));
        sizePolicy.setHeightForWidth(traject_r0->sizePolicy().hasHeightForWidth());
        traject_r0->setSizePolicy(sizePolicy);
        traject_r0->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(traject_r0, 0, 10, 1, 1);

        pbBackO = new QPushButton(frame);
        pbBackO->setObjectName(QString::fromUtf8("pbBackO"));
        sizePolicy.setHeightForWidth(pbBackO->sizePolicy().hasHeightForWidth());
        pbBackO->setSizePolicy(sizePolicy);
        pbBackO->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(pbBackO, 2, 39, 1, 1);

        startScan_But = new QPushButton(frame);
        startScan_But->setObjectName(QString::fromUtf8("startScan_But"));
        sizePolicy.setHeightForWidth(startScan_But->sizePolicy().hasHeightForWidth());
        startScan_But->setSizePolicy(sizePolicy);
        startScan_But->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(startScan_But, 0, 39, 1, 1);

        selectAxitO_cb = new QComboBox(frame);
        selectAxitO_cb->addItem(QString());
        selectAxitO_cb->addItem(QString());
        selectAxitO_cb->addItem(QString());
        selectAxitO_cb->addItem(QString());
        selectAxitO_cb->setObjectName(QString::fromUtf8("selectAxitO_cb"));
        sizePolicy.setHeightForWidth(selectAxitO_cb->sizePolicy().hasHeightForWidth());
        selectAxitO_cb->setSizePolicy(sizePolicy);
        selectAxitO_cb->setMinimumSize(QSize(0, 0));
        selectAxitO_cb->setLayoutDirection(Qt::LeftToRight);

        gridLayout_2->addWidget(selectAxitO_cb, 2, 8, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_10, 0, 36, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_8, 0, 24, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_5, 0, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 0, 13, 1, 1);

        alarmReset_but = new QPushButton(frame);
        alarmReset_but->setObjectName(QString::fromUtf8("alarmReset_but"));
        sizePolicy.setHeightForWidth(alarmReset_but->sizePolicy().hasHeightForWidth());
        alarmReset_but->setSizePolicy(sizePolicy);
        alarmReset_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(alarmReset_but, 0, 42, 1, 1);

        pBbrazing = new QPushButton(frame);
        pBbrazing->setObjectName(QString::fromUtf8("pBbrazing"));
        sizePolicy.setHeightForWidth(pBbrazing->sizePolicy().hasHeightForWidth());
        pBbrazing->setSizePolicy(sizePolicy);
        pBbrazing->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(pBbrazing, 4, 0, 1, 1);

        getCurryPoint_but = new QPushButton(frame);
        getCurryPoint_but->setObjectName(QString::fromUtf8("getCurryPoint_but"));
        sizePolicy.setHeightForWidth(getCurryPoint_but->sizePolicy().hasHeightForWidth());
        getCurryPoint_but->setSizePolicy(sizePolicy);
        getCurryPoint_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(getCurryPoint_but, 2, 6, 1, 1);

        moveToPosition_but = new QPushButton(frame);
        moveToPosition_but->setObjectName(QString::fromUtf8("moveToPosition_but"));
        sizePolicy.setHeightForWidth(moveToPosition_but->sizePolicy().hasHeightForWidth());
        moveToPosition_but->setSizePolicy(sizePolicy);
        moveToPosition_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(moveToPosition_but, 2, 4, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 4, 38, 1, 1);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_22, 0, 16, 1, 1);

        trajectoryOffset_but = new QPushButton(frame);
        trajectoryOffset_but->setObjectName(QString::fromUtf8("trajectoryOffset_but"));
        sizePolicy.setHeightForWidth(trajectoryOffset_but->sizePolicy().hasHeightForWidth());
        trajectoryOffset_but->setSizePolicy(sizePolicy);
        trajectoryOffset_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(trajectoryOffset_but, 4, 6, 1, 1);

        DXFimport_but = new QPushButton(frame);
        DXFimport_but->setObjectName(QString::fromUtf8("DXFimport_but"));
        sizePolicy.setHeightForWidth(DXFimport_but->sizePolicy().hasHeightForWidth());
        DXFimport_but->setSizePolicy(sizePolicy);
        DXFimport_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(DXFimport_but, 0, 0, 1, 1);

        frame_2 = new QFrame(frame);
        frame_2->setObjectName(QString::fromUtf8("frame_2"));
        sizePolicy.setHeightForWidth(frame_2->sizePolicy().hasHeightForWidth());
        frame_2->setSizePolicy(sizePolicy);
        frame_2->setMinimumSize(QSize(0, 0));
        frame_2->setStyleSheet(QString::fromUtf8("border: 2px solid rgb(200, 200, 200);\n"
""));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        gridLayout_3 = new QGridLayout(frame_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_22 = new QLabel(frame_2);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy);
        label_22->setMinimumSize(QSize(0, 0));

        gridLayout_3->addWidget(label_22, 0, 0, 1, 1);

        processType_cb = new QComboBox(frame_2);
        processType_cb->addItem(QString());
        processType_cb->addItem(QString());
        processType_cb->addItem(QString());
        processType_cb->setObjectName(QString::fromUtf8("processType_cb"));
        sizePolicy.setHeightForWidth(processType_cb->sizePolicy().hasHeightForWidth());
        processType_cb->setSizePolicy(sizePolicy);
        processType_cb->setMinimumSize(QSize(0, 0));
        processType_cb->setLayoutDirection(Qt::LeftToRight);

        gridLayout_3->addWidget(processType_cb, 1, 0, 1, 1);


        gridLayout_2->addWidget(frame_2, 2, 11, 3, 1);

        line_3 = new QFrame(frame);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        sizePolicy.setHeightForWidth(line_3->sizePolicy().hasHeightForWidth());
        line_3->setSizePolicy(sizePolicy);
        line_3->setMinimumSize(QSize(0, 0));
        line_3->setFrameShape(QFrame::VLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_3, 0, 12, 5, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 37, 1, 1);

        line_4 = new QFrame(frame);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        sizePolicy.setHeightForWidth(line_4->sizePolicy().hasHeightForWidth());
        line_4->setSizePolicy(sizePolicy);
        line_4->setMinimumSize(QSize(0, 0));
        line_4->setFrameShape(QFrame::VLine);
        line_4->setFrameShadow(QFrame::Sunken);

        gridLayout_2->addWidget(line_4, 0, 2, 5, 1);

        PoseCalculation_but = new QPushButton(frame);
        PoseCalculation_but->setObjectName(QString::fromUtf8("PoseCalculation_but"));
        sizePolicy.setHeightForWidth(PoseCalculation_but->sizePolicy().hasHeightForWidth());
        PoseCalculation_but->setSizePolicy(sizePolicy);
        PoseCalculation_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(PoseCalculation_but, 0, 11, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_14, 0, 18, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_18, 0, 20, 1, 1);

        cBworkpiece = new QComboBox(frame);
        cBworkpiece->setObjectName(QString::fromUtf8("cBworkpiece"));
        sizePolicy.setHeightForWidth(cBworkpiece->sizePolicy().hasHeightForWidth());
        cBworkpiece->setSizePolicy(sizePolicy);
        cBworkpiece->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(cBworkpiece, 4, 40, 1, 1);

        traject_y0 = new QLineEdit(frame);
        traject_y0->setObjectName(QString::fromUtf8("traject_y0"));
        sizePolicy.setHeightForWidth(traject_y0->sizePolicy().hasHeightForWidth());
        traject_y0->setSizePolicy(sizePolicy);
        traject_y0->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(traject_y0, 0, 6, 1, 1);

        imageProcess_but = new QPushButton(frame);
        imageProcess_but->setObjectName(QString::fromUtf8("imageProcess_but"));
        sizePolicy.setHeightForWidth(imageProcess_but->sizePolicy().hasHeightForWidth());
        imageProcess_but->setSizePolicy(sizePolicy);
        imageProcess_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(imageProcess_but, 0, 15, 1, 1);

        writeInPLC_but = new QPushButton(frame);
        writeInPLC_but->setObjectName(QString::fromUtf8("writeInPLC_but"));
        sizePolicy.setHeightForWidth(writeInPLC_but->sizePolicy().hasHeightForWidth());
        writeInPLC_but->setSizePolicy(sizePolicy);
        writeInPLC_but->setMinimumSize(QSize(0, 0));

        gridLayout_2->addWidget(writeInPLC_but, 4, 15, 1, 1);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_25, 0, 34, 1, 1);

        gridLayout_2->setRowStretch(0, 1);
        imageProcess_but->raise();
        startScan_But->raise();
        alarmReset_but->raise();
        stopScan_but->raise();
        endScan_but->raise();
        line_3->raise();
        DXFimport_but->raise();
        traject_y0->raise();
        traject_x0->raise();
        V_label_3->raise();
        V_label_4->raise();
        ascan_but->raise();
        line_4->raise();
        V_label_9->raise();
        V_label_10->raise();
        traject_z0->raise();
        traject_r0->raise();
        writeInPLC_but->raise();
        creatG_but->raise();
        cBworkpiece->raise();
        pbNewPiece->raise();
        pBdeletePiece->raise();
        pBbrazing->raise();
        line_7->raise();
        pbBackO->raise();
        frame_2->raise();
        PoseCalculation_but->raise();
        smooth_but->raise();
        setOrigin_but->raise();
        selectAxitO_cb->raise();
        trajectoryOffset_but->raise();
        getCurryPoint_but->raise();
        setTrajecStart_but->raise();
        moveToPosition_but->raise();
        label_4->raise();
        smoothX_dsb->raise();

        gridLayout_5->addWidget(frame, 3, 0, 1, 2);

        frame_3 = new QFrame(centralwidget);
        frame_3->setObjectName(QString::fromUtf8("frame_3"));
        sizePolicy.setHeightForWidth(frame_3->sizePolicy().hasHeightForWidth());
        frame_3->setSizePolicy(sizePolicy);
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        gridLayout_4 = new QGridLayout(frame_3);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout_4->setHorizontalSpacing(6);
        gridLayout_4->setVerticalSpacing(0);
        gridLayout_4->setContentsMargins(-1, -1, -1, 0);
        zSub_but = new QPushButton(frame_3);
        zSub_but->setObjectName(QString::fromUtf8("zSub_but"));
        sizePolicy.setHeightForWidth(zSub_but->sizePolicy().hasHeightForWidth());
        zSub_but->setSizePolicy(sizePolicy);
        zSub_but->setMinimumSize(QSize(0, 0));
        zSub_but->setAutoRepeat(false);
        zSub_but->setAutoExclusive(false);

        gridLayout_4->addWidget(zSub_but, 5, 13, 1, 1);

        port_lin = new QLineEdit(frame_3);
        port_lin->setObjectName(QString::fromUtf8("port_lin"));
        sizePolicy.setHeightForWidth(port_lin->sizePolicy().hasHeightForWidth());
        port_lin->setSizePolicy(sizePolicy);
        port_lin->setMinimumSize(QSize(0, 0));
        port_lin->setMaximumSize(QSize(16777215, 16777215));

        gridLayout_4->addWidget(port_lin, 2, 3, 1, 1);

        label_2 = new QLabel(frame_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setMinimumSize(QSize(0, 0));

        gridLayout_4->addWidget(label_2, 2, 2, 1, 1);

        xAdd_but = new QPushButton(frame_3);
        xAdd_but->setObjectName(QString::fromUtf8("xAdd_but"));
        sizePolicy.setHeightForWidth(xAdd_but->sizePolicy().hasHeightForWidth());
        xAdd_but->setSizePolicy(sizePolicy);
        xAdd_but->setMinimumSize(QSize(0, 0));
        xAdd_but->setAutoRepeat(false);
        xAdd_but->setAutoExclusive(false);

        gridLayout_4->addWidget(xAdd_but, 2, 11, 1, 1);

        yAdd_but = new QPushButton(frame_3);
        yAdd_but->setObjectName(QString::fromUtf8("yAdd_but"));
        sizePolicy.setHeightForWidth(yAdd_but->sizePolicy().hasHeightForWidth());
        yAdd_but->setSizePolicy(sizePolicy);
        yAdd_but->setMinimumSize(QSize(0, 0));
        yAdd_but->setAutoRepeat(false);
        yAdd_but->setAutoExclusive(false);

        gridLayout_4->addWidget(yAdd_but, 2, 12, 1, 1);

        rSub_but = new QPushButton(frame_3);
        rSub_but->setObjectName(QString::fromUtf8("rSub_but"));
        sizePolicy.setHeightForWidth(rSub_but->sizePolicy().hasHeightForWidth());
        rSub_but->setSizePolicy(sizePolicy);
        rSub_but->setMinimumSize(QSize(0, 0));
        rSub_but->setAutoRepeat(false);
        rSub_but->setAutoExclusive(false);

        gridLayout_4->addWidget(rSub_but, 5, 14, 1, 1);

        label_10 = new QLabel(frame_3);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        sizePolicy.setHeightForWidth(label_10->sizePolicy().hasHeightForWidth());
        label_10->setSizePolicy(sizePolicy);
        label_10->setMinimumSize(QSize(0, 0));
        label_10->setFont(font);

        gridLayout_4->addWidget(label_10, 5, 10, 1, 1);

        line = new QFrame(frame_3);
        line->setObjectName(QString::fromUtf8("line"));
        sizePolicy.setHeightForWidth(line->sizePolicy().hasHeightForWidth());
        line->setSizePolicy(sizePolicy);
        line->setMinimumSize(QSize(0, 0));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line, 6, 5, 1, 1);

        label_12 = new QLabel(frame_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        sizePolicy.setHeightForWidth(label_12->sizePolicy().hasHeightForWidth());
        label_12->setSizePolicy(sizePolicy);
        label_12->setMinimumSize(QSize(0, 0));
        label_12->setFont(font);

        gridLayout_4->addWidget(label_12, 2, 10, 1, 1);

        label_6 = new QLabel(frame_3);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
        label_6->setMinimumSize(QSize(0, 0));
        QFont font1;
        font1.setFamily(QString::fromUtf8("3ds"));
        font1.setPointSize(11);
        label_6->setFont(font1);
        label_6->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_6, 2, 5, 1, 1);

        label_8 = new QLabel(frame_3);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
        label_8->setMinimumSize(QSize(0, 0));
        label_8->setFont(font);

        gridLayout_4->addWidget(label_8, 2, 7, 1, 1);

        rCurPos_lab = new QLabel(frame_3);
        rCurPos_lab->setObjectName(QString::fromUtf8("rCurPos_lab"));
        sizePolicy.setHeightForWidth(rCurPos_lab->sizePolicy().hasHeightForWidth());
        rCurPos_lab->setSizePolicy(sizePolicy);
        rCurPos_lab->setMinimumSize(QSize(0, 0));
        rCurPos_lab->setFont(font1);

        gridLayout_4->addWidget(rCurPos_lab, 5, 9, 1, 1);

        label_9 = new QLabel(frame_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        sizePolicy.setHeightForWidth(label_9->sizePolicy().hasHeightForWidth());
        label_9->setSizePolicy(sizePolicy);
        label_9->setMinimumSize(QSize(0, 0));
        label_9->setFont(font);

        gridLayout_4->addWidget(label_9, 5, 7, 1, 1);

        xSub_but = new QPushButton(frame_3);
        xSub_but->setObjectName(QString::fromUtf8("xSub_but"));
        sizePolicy.setHeightForWidth(xSub_but->sizePolicy().hasHeightForWidth());
        xSub_but->setSizePolicy(sizePolicy);
        xSub_but->setMinimumSize(QSize(0, 0));
        xSub_but->setAutoRepeat(false);
        xSub_but->setAutoExclusive(false);

        gridLayout_4->addWidget(xSub_but, 5, 11, 1, 1);

        zCurPos_lab = new QLabel(frame_3);
        zCurPos_lab->setObjectName(QString::fromUtf8("zCurPos_lab"));
        sizePolicy.setHeightForWidth(zCurPos_lab->sizePolicy().hasHeightForWidth());
        zCurPos_lab->setSizePolicy(sizePolicy);
        zCurPos_lab->setMinimumSize(QSize(0, 0));
        zCurPos_lab->setFont(font1);

        gridLayout_4->addWidget(zCurPos_lab, 2, 9, 1, 1);

        ySub_but = new QPushButton(frame_3);
        ySub_but->setObjectName(QString::fromUtf8("ySub_but"));
        sizePolicy.setHeightForWidth(ySub_but->sizePolicy().hasHeightForWidth());
        ySub_but->setSizePolicy(sizePolicy);
        ySub_but->setMinimumSize(QSize(0, 0));
        ySub_but->setAutoRepeat(false);
        ySub_but->setAutoExclusive(false);

        gridLayout_4->addWidget(ySub_but, 5, 12, 1, 1);

        label = new QLabel(frame_3);
        label->setObjectName(QString::fromUtf8("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMinimumSize(QSize(0, 0));

        gridLayout_4->addWidget(label, 2, 0, 1, 1);

        plcType_cb = new QComboBox(frame_3);
        plcType_cb->addItem(QString());
        plcType_cb->addItem(QString());
        plcType_cb->setObjectName(QString::fromUtf8("plcType_cb"));
        sizePolicy.setHeightForWidth(plcType_cb->sizePolicy().hasHeightForWidth());
        plcType_cb->setSizePolicy(sizePolicy);
        plcType_cb->setMinimumSize(QSize(0, 0));

        gridLayout_4->addWidget(plcType_cb, 5, 15, 1, 1);

        xCurPos_lab = new QLabel(frame_3);
        xCurPos_lab->setObjectName(QString::fromUtf8("xCurPos_lab"));
        sizePolicy.setHeightForWidth(xCurPos_lab->sizePolicy().hasHeightForWidth());
        xCurPos_lab->setSizePolicy(sizePolicy);
        xCurPos_lab->setMinimumSize(QSize(0, 0));
        xCurPos_lab->setFont(font1);

        gridLayout_4->addWidget(xCurPos_lab, 2, 6, 1, 1);

        connect_but = new QPushButton(frame_3);
        connect_but->setObjectName(QString::fromUtf8("connect_but"));
        sizePolicy.setHeightForWidth(connect_but->sizePolicy().hasHeightForWidth());
        connect_but->setSizePolicy(sizePolicy);
        connect_but->setMinimumSize(QSize(0, 0));

        gridLayout_4->addWidget(connect_but, 2, 4, 1, 1);

        ip_lin = new QLineEdit(frame_3);
        ip_lin->setObjectName(QString::fromUtf8("ip_lin"));
        sizePolicy.setHeightForWidth(ip_lin->sizePolicy().hasHeightForWidth());
        ip_lin->setSizePolicy(sizePolicy);
        ip_lin->setMinimumSize(QSize(0, 0));

        gridLayout_4->addWidget(ip_lin, 2, 1, 1, 1);

        label_13 = new QLabel(frame_3);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        sizePolicy.setHeightForWidth(label_13->sizePolicy().hasHeightForWidth());
        label_13->setSizePolicy(sizePolicy);
        label_13->setMinimumSize(QSize(0, 0));
        label_13->setFont(font1);
        label_13->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_13, 2, 8, 1, 1);

        rAdd_but = new QPushButton(frame_3);
        rAdd_but->setObjectName(QString::fromUtf8("rAdd_but"));
        sizePolicy.setHeightForWidth(rAdd_but->sizePolicy().hasHeightForWidth());
        rAdd_but->setSizePolicy(sizePolicy);
        rAdd_but->setMinimumSize(QSize(0, 0));
        rAdd_but->setAutoRepeat(false);
        rAdd_but->setAutoExclusive(false);

        gridLayout_4->addWidget(rAdd_but, 2, 14, 1, 1);

        label_3 = new QLabel(frame_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setMinimumSize(QSize(0, 0));

        gridLayout_4->addWidget(label_3, 2, 15, 1, 1);

        zAdd_but = new QPushButton(frame_3);
        zAdd_but->setObjectName(QString::fromUtf8("zAdd_but"));
        sizePolicy.setHeightForWidth(zAdd_but->sizePolicy().hasHeightForWidth());
        zAdd_but->setSizePolicy(sizePolicy);
        zAdd_but->setMinimumSize(QSize(0, 0));
        zAdd_but->setAutoRepeat(false);
        zAdd_but->setAutoExclusive(false);

        gridLayout_4->addWidget(zAdd_but, 2, 13, 1, 1);

        yCurPos_lab = new QLabel(frame_3);
        yCurPos_lab->setObjectName(QString::fromUtf8("yCurPos_lab"));
        sizePolicy.setHeightForWidth(yCurPos_lab->sizePolicy().hasHeightForWidth());
        yCurPos_lab->setSizePolicy(sizePolicy);
        yCurPos_lab->setMinimumSize(QSize(0, 0));
        yCurPos_lab->setFont(font1);

        gridLayout_4->addWidget(yCurPos_lab, 5, 6, 1, 1);

        label_7 = new QLabel(frame_3);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
        label_7->setMinimumSize(QSize(0, 0));
        label_7->setFont(font1);
        label_7->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_7, 5, 5, 1, 1);

        label_11 = new QLabel(frame_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        sizePolicy.setHeightForWidth(label_11->sizePolicy().hasHeightForWidth());
        label_11->setSizePolicy(sizePolicy);
        label_11->setMinimumSize(QSize(0, 0));
        label_11->setFont(font1);
        label_11->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_4->addWidget(label_11, 5, 8, 1, 1);

        disMess_lab = new QLabel(frame_3);
        disMess_lab->setObjectName(QString::fromUtf8("disMess_lab"));
        sizePolicy.setHeightForWidth(disMess_lab->sizePolicy().hasHeightForWidth());
        disMess_lab->setSizePolicy(sizePolicy);

        gridLayout_4->addWidget(disMess_lab, 5, 0, 1, 4);


        gridLayout_5->addWidget(frame_3, 0, 0, 1, 2);

        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setMinimumSize(QSize(0, 0));
        horizontalLayout_2 = new QHBoxLayout(widget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        comboBox = new QComboBox(widget);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);
        comboBox->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(comboBox);

        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(label_5);

        scanVelocity_lin = new QLineEdit(widget);
        scanVelocity_lin->setObjectName(QString::fromUtf8("scanVelocity_lin"));
        sizePolicy.setHeightForWidth(scanVelocity_lin->sizePolicy().hasHeightForWidth());
        scanVelocity_lin->setSizePolicy(sizePolicy);
        scanVelocity_lin->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(scanVelocity_lin);

        label_14 = new QLabel(widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        sizePolicy.setHeightForWidth(label_14->sizePolicy().hasHeightForWidth());
        label_14->setSizePolicy(sizePolicy);
        label_14->setMinimumSize(QSize(0, 0));
        label_14->setFont(font);

        horizontalLayout_2->addWidget(label_14);

        label_23 = new QLabel(widget);
        label_23->setObjectName(QString::fromUtf8("label_23"));
        sizePolicy.setHeightForWidth(label_23->sizePolicy().hasHeightForWidth());
        label_23->setSizePolicy(sizePolicy);
        label_23->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(label_23);

        AxleVelocity_lin = new QLineEdit(widget);
        AxleVelocity_lin->setObjectName(QString::fromUtf8("AxleVelocity_lin"));
        sizePolicy.setHeightForWidth(AxleVelocity_lin->sizePolicy().hasHeightForWidth());
        AxleVelocity_lin->setSizePolicy(sizePolicy);
        AxleVelocity_lin->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(AxleVelocity_lin);

        label_17 = new QLabel(widget);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        sizePolicy.setHeightForWidth(label_17->sizePolicy().hasHeightForWidth());
        label_17->setSizePolicy(sizePolicy);
        label_17->setMinimumSize(QSize(0, 0));
        label_17->setFont(font);

        horizontalLayout_2->addWidget(label_17);

        label_24 = new QLabel(widget);
        label_24->setObjectName(QString::fromUtf8("label_24"));
        sizePolicy.setHeightForWidth(label_24->sizePolicy().hasHeightForWidth());
        label_24->setSizePolicy(sizePolicy);
        label_24->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(label_24);

        pointVelocity_lin = new QLineEdit(widget);
        pointVelocity_lin->setObjectName(QString::fromUtf8("pointVelocity_lin"));
        sizePolicy.setHeightForWidth(pointVelocity_lin->sizePolicy().hasHeightForWidth());
        pointVelocity_lin->setSizePolicy(sizePolicy);
        pointVelocity_lin->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(pointVelocity_lin);

        label_21 = new QLabel(widget);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        sizePolicy.setHeightForWidth(label_21->sizePolicy().hasHeightForWidth());
        label_21->setSizePolicy(sizePolicy);
        label_21->setMinimumSize(QSize(0, 0));
        label_21->setFont(font);

        horizontalLayout_2->addWidget(label_21);

        label_16 = new QLabel(widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        sizePolicy.setHeightForWidth(label_16->sizePolicy().hasHeightForWidth());
        label_16->setSizePolicy(sizePolicy);
        label_16->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(label_16);

        lineVelocity_lin = new QLineEdit(widget);
        lineVelocity_lin->setObjectName(QString::fromUtf8("lineVelocity_lin"));
        sizePolicy.setHeightForWidth(lineVelocity_lin->sizePolicy().hasHeightForWidth());
        lineVelocity_lin->setSizePolicy(sizePolicy);
        lineVelocity_lin->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(lineVelocity_lin);

        label_18 = new QLabel(widget);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        sizePolicy.setHeightForWidth(label_18->sizePolicy().hasHeightForWidth());
        label_18->setSizePolicy(sizePolicy);
        label_18->setMinimumSize(QSize(0, 0));
        label_18->setFont(font);

        horizontalLayout_2->addWidget(label_18);

        label_20 = new QLabel(widget);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        sizePolicy.setHeightForWidth(label_20->sizePolicy().hasHeightForWidth());
        label_20->setSizePolicy(sizePolicy);
        label_20->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(label_20);

        arcVelocity_lin = new QLineEdit(widget);
        arcVelocity_lin->setObjectName(QString::fromUtf8("arcVelocity_lin"));
        sizePolicy.setHeightForWidth(arcVelocity_lin->sizePolicy().hasHeightForWidth());
        arcVelocity_lin->setSizePolicy(sizePolicy);
        arcVelocity_lin->setMinimumSize(QSize(0, 0));

        horizontalLayout_2->addWidget(arcVelocity_lin);

        label_19 = new QLabel(widget);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        sizePolicy.setHeightForWidth(label_19->sizePolicy().hasHeightForWidth());
        label_19->setSizePolicy(sizePolicy);
        label_19->setMinimumSize(QSize(0, 0));
        label_19->setFont(font);

        horizontalLayout_2->addWidget(label_19);


        gridLayout_5->addWidget(widget, 4, 0, 1, 2);

        gridLayout_5->setRowStretch(1, 15);
        gridLayout_5->setColumnStretch(0, 5);
        gridLayout_5->setColumnStretch(1, 3);
        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        moveDownTabelRow_btu->setText(QCoreApplication::translate("MainWindow", "\345\220\221\344\270\213\347\247\273\345\212\250\350\241\214", nullptr));
        editPos_but->setText(QCoreApplication::translate("MainWindow", "\347\274\226\350\276\221", nullptr));
        insertLinePos_but->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\347\233\264\347\272\277", nullptr));
        insertArcPos_but->setText(QCoreApplication::translate("MainWindow", "\346\217\222\345\205\245\345\234\206\345\274\247", nullptr));
        moveUpTabelRow_btu->setText(QCoreApplication::translate("MainWindow", "\345\220\221\344\270\212\347\247\273\345\212\250\350\241\214", nullptr));
        cleanTable_but->setText(QCoreApplication::translate("MainWindow", "\346\270\205\347\251\272\350\241\250\346\240\274", nullptr));
        moveDirectionNot_but->setText(QCoreApplication::translate("MainWindow", "\350\277\220\345\212\250\346\226\271\345\220\221\345\217\215\350\275\254", nullptr));
        delete_but->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Trajectory Scan", nullptr));
        pBdeletePiece->setText(QCoreApplication::translate("MainWindow", "\345\210\240\351\231\244", nullptr));
        V_label_4->setText(QCoreApplication::translate("MainWindow", "y:", nullptr));
        smooth_but->setText(QCoreApplication::translate("MainWindow", "\344\270\200\351\224\256\351\241\272\346\273\221", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\345\267\245\344\273\266\357\274\232", nullptr));
        setOrigin_but->setText(QCoreApplication::translate("MainWindow", "\350\256\276\350\275\264\345\216\237\347\202\271", nullptr));
        traject_z0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        stopScan_but->setText(QCoreApplication::translate("MainWindow", "\346\232\202\345\201\234", nullptr));
        setTrajecStart_but->setText(QCoreApplication::translate("MainWindow", "\350\256\276\345\256\232\350\265\267\347\202\271", nullptr));
        traject_x0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pbNewPiece->setText(QCoreApplication::translate("MainWindow", "\346\226\260\345\273\272", nullptr));
        creatG_but->setText(QCoreApplication::translate("MainWindow", "GCode\350\277\220\350\241\214\357\274\210plc\357\274\211", nullptr));
        endScan_but->setText(QCoreApplication::translate("MainWindow", "\345\201\234\346\255\242", nullptr));
        ascan_but->setText(QCoreApplication::translate("MainWindow", "Ascan", nullptr));
        V_label_10->setText(QCoreApplication::translate("MainWindow", "z:", nullptr));
        V_label_9->setText(QCoreApplication::translate("MainWindow", "r:", nullptr));
        V_label_3->setText(QCoreApplication::translate("MainWindow", "x:", nullptr));
        traject_r0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        pbBackO->setText(QCoreApplication::translate("MainWindow", "\345\233\236\345\216\237\347\202\271", nullptr));
        startScan_But->setText(QCoreApplication::translate("MainWindow", "\345\220\257\345\212\250", nullptr));
        selectAxitO_cb->setItemText(0, QCoreApplication::translate("MainWindow", "x", nullptr));
        selectAxitO_cb->setItemText(1, QCoreApplication::translate("MainWindow", "y", nullptr));
        selectAxitO_cb->setItemText(2, QCoreApplication::translate("MainWindow", "z", nullptr));
        selectAxitO_cb->setItemText(3, QCoreApplication::translate("MainWindow", "r", nullptr));

        alarmReset_but->setText(QCoreApplication::translate("MainWindow", "\346\212\245\350\255\246\345\244\215\344\275\215", nullptr));
        pBbrazing->setText(QCoreApplication::translate("MainWindow", "\351\222\216\347\204\212", nullptr));
        getCurryPoint_but->setText(QCoreApplication::translate("MainWindow", "\350\216\267\345\217\226\345\210\227\350\241\250\347\202\271", nullptr));
        moveToPosition_but->setText(QCoreApplication::translate("MainWindow", "\347\247\273\345\212\250", nullptr));
        trajectoryOffset_but->setText(QCoreApplication::translate("MainWindow", "\350\275\250\350\277\271\345\201\217\347\247\273", nullptr));
        DXFimport_but->setText(QCoreApplication::translate("MainWindow", "\345\257\274\345\205\245DXF", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\345\267\245\350\211\272\347\261\273\345\236\213\357\274\232", nullptr));
        processType_cb->setItemText(0, QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251g\344\273\243\347\240\201", nullptr));
        processType_cb->setItemText(1, QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\346\221\251\346\223\246\347\204\212", nullptr));
        processType_cb->setItemText(2, QCoreApplication::translate("MainWindow", "\351\200\211\346\213\251\351\222\216\347\204\212", nullptr));

        PoseCalculation_but->setText(QCoreApplication::translate("MainWindow", "\345\247\277\346\200\201\350\256\241\347\256\227", nullptr));
        traject_y0->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        imageProcess_but->setText(QCoreApplication::translate("MainWindow", "imageProcess", nullptr));
        writeInPLC_but->setText(QCoreApplication::translate("MainWindow", " \345\257\204\345\255\230\345\231\250\350\277\220\350\241\214\357\274\210plc\357\274\211", nullptr));
        zSub_but->setText(QCoreApplication::translate("MainWindow", "Z-", nullptr));
        port_lin->setText(QCoreApplication::translate("MainWindow", "502", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Port:", nullptr));
        xAdd_but->setText(QCoreApplication::translate("MainWindow", "X+", nullptr));
        yAdd_but->setText(QCoreApplication::translate("MainWindow", "Y+", nullptr));
        rSub_but->setText(QCoreApplication::translate("MainWindow", "R-", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "x\357\274\232", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        rCurPos_lab->setText(QString());
        label_9->setText(QCoreApplication::translate("MainWindow", "mm", nullptr));
        xSub_but->setText(QCoreApplication::translate("MainWindow", "X-", nullptr));
        zCurPos_lab->setText(QString());
        ySub_but->setText(QCoreApplication::translate("MainWindow", "Y-", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "IP:", nullptr));
        plcType_cb->setItemText(0, QCoreApplication::translate("MainWindow", "h5u", nullptr));
        plcType_cb->setItemText(1, QCoreApplication::translate("MainWindow", "ac700", nullptr));

        xCurPos_lab->setText(QString());
        connect_but->setText(QCoreApplication::translate("MainWindow", " \350\277\236\346\216\245", nullptr));
        ip_lin->setText(QCoreApplication::translate("MainWindow", "192.168.1.88", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "z\357\274\232", nullptr));
        rAdd_but->setText(QCoreApplication::translate("MainWindow", "R+", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "plc\347\261\273\345\236\213\357\274\232", nullptr));
        zAdd_but->setText(QCoreApplication::translate("MainWindow", "Z+", nullptr));
        yCurPos_lab->setText(QString());
        label_7->setText(QCoreApplication::translate("MainWindow", "y\357\274\232", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "r\357\274\232", nullptr));
        disMess_lab->setText(QString());
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "x", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "y", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "z", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "r", nullptr));

        label_5->setText(QCoreApplication::translate("MainWindow", "\350\275\264\351\200\237\345\272\246\357\274\232", nullptr));
        scanVelocity_lin->setText(QString());
        scanVelocity_lin->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\233\236\350\275\246\347\241\256\350\256\244", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "mm/s", nullptr));
        label_23->setText(QCoreApplication::translate("MainWindow", "\345\256\232\344\275\215\351\200\237\345\272\246\357\274\232", nullptr));
        AxleVelocity_lin->setText(QString());
        AxleVelocity_lin->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\233\236\350\275\246\347\241\256\350\256\244", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "mm/s", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "\347\202\271\345\212\250\351\200\237\345\272\246\357\274\232", nullptr));
        pointVelocity_lin->setText(QString());
        pointVelocity_lin->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\233\236\350\275\246\347\241\256\350\256\244", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "mm/s", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\347\233\264\347\272\277\351\200\237\345\272\246\357\274\232", nullptr));
        lineVelocity_lin->setText(QString());
        lineVelocity_lin->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\233\236\350\275\246\347\241\256\350\256\244", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "mm/s", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "\345\234\206\345\274\247\351\200\237\345\272\246\357\274\232", nullptr));
        arcVelocity_lin->setText(QString());
        arcVelocity_lin->setPlaceholderText(QCoreApplication::translate("MainWindow", "\345\233\236\350\275\246\347\241\256\350\256\244", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "mm/s", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
