#ifndef MotionControl_H
#define MotionControl_H

#include <QMainWindow>
#include <ndtcfgmachine.h>

#include <QModbusTcpClient>
#include <QUdpSocket>
#include <QSqlTableModel>

#include "floatpointdelegate.h"
#include "icondelegate.h"
#include "booleandelegate.h"
#include "addroute_dialog.h"
#include "Graphics_view_zoom.h"
#include "route_worksence.h"
#include "imageprocessing.h"
#include "gcodemodulation.h"
#include "databasemanager.h"
#include "scancontrolabstract.h"
#include "mathtool.h"

#include <QProgressDialog>
#include <QSet>
#include <QScreen>
#include <QWindow>

//using modelDate = ScanControlAbstract::modelDate;

class ascan;  // 前向声明
QT_BEGIN_NAMESPACE
namespace Ui { class MotionControl; }
QT_END_NAMESPACE


class MotionControl : public QMainWindow
{
    Q_OBJECT

public:
    MotionControl(QWidget *parent = nullptr);
    ~MotionControl();

    void closeEvent(QCloseEvent *event) override;


    QSettings *settings;

    DatabaseManager *dbManager;

    struct TargetPos {
        double x;
        double y;
        double z;
        double r;
    };

    struct AxisLimit {
        double min;
        double max;
    };

    AxisLimit limitX;
    AxisLimit limitY;
    AxisLimit limitZ;
    AxisLimit limitR;

    bool getAxisLimits(QWidget *parent,
                       double &xmin, double &xmax,
                       double &ymin, double &ymax,
                       double &zmin, double &zmax,
                       double &rmin, double &rmax);

    static ScanControlAbstract *scanDetectCtrl;

    QString curryWorkpieceName;
    QVector<QString>WorkpieceList;
    QMap<QString, QVector<double>> workPieceSpeedMap;
    double _translationX=0;
    double _translationY=0;
    double _translationR=0;
    double  originR=0;


    int m_lastClickedRow;
    bool m_isSelected ;
    QSqlTableModel*  model;

    std::tuple<double, double, double, double> pbGetCurrentlyPoint();

    bool isSelectChange=true;
    bool isNewPiece=false;
    TargetPos currentTargetPos;  // 用于保存当前目标点
private slots:

    void pbStartScanBtn();

    void modbusStateChange(QModbusDevice::State state);

    void pbAddElliptical();

    void updatePosition(QPointF pos,float cur_r,float cur_z);

    void pbAddSpline();

    void on_delete_but_clicked();

    void on_editPos_but_clicked();

    void pbWriteInPLC();


    void pbAddArcPos();

    void pbAddLinePos();

    //void graphics_view_zoom();

    void pbDXFimportBut();

    void pbsetTrajec_start_clicked();


    void PbCreatGcode();

    void CalculatingAngles();

    void PbImageProcess();

    void PbSetOrigin();

    void PbMoveToPosition();

    void PbtrajectoryOffset();

    void PbsmoothCurve();

    void PbAxleVelocity_lin();
    void PblinVelocity_lin();
    void PbarcVelocity_lin();
    void PbPointVelocity_lin();

    void pbAscan();

    void updateSence();

    void cleanTable();

    void PbModbusConnectBtn();

    void cbSelectPlcType(int index);

    void pbmoveUpForSort();

    void pbmoveDownForSort();

    void sortModelLine();

    void pbGetModelPoint();

    void pbMoveDirectionNot();

    void pBbrazing();

    void selectWorkpiece();

    void selectChange();

    void pbdeletePiece();

    void pbnewPiece();

    void saveSetting();

    void initSetting();


    //_________

public:

    void insertSmoothArcBetween(int id,int prevRow, int nextRow, qreal smoothFactor);

private:

    QSize oldSize;
    QSize newSize;

    QMap<QWidget*, QRect> originalGeometries;
    QMap<QWidget*, double> originalFontSizes;


    QMap<QWidget*, QFont> originalFonts;

    void scaleWidgets(QWidget* parent, double scaleX, double scaleY);

    void resizeEvent(QResizeEvent *event);

    void resetAllWidgetSizes(QWidget* widget);

    void restoreOriginalWidgetStates(QWidget* parent);

    void saveOriginalWidgetStates(QWidget* parent);


private:
    Ui::MotionControl *ui;

    QModbusTcpClient *modbusDevice;
    QUdpSocket *udpSocket;


    imageprocessing *imageProcessingTool;

    gCodeModulation* gcodeEidt;

    ascan* scan;

    QList<QString>  startPoint;
    QString current_db_name;
    QString current_route_name;
    QString current_user;

    int current_weld_row;
    int current_weld_id;

    QList<QString> GlobeUniquePoints;

    double traject_x0,traject_y0;


    void init();


    void createOrSwitchTable(const QString &tableName,bool isCreate);

    addRoute_dialog *addRoute;
    void  updateAddRoute(int arc,int edit,int curRow);

    Graphics_view_zoom* zomm_gview;
    route_worksence *scene;

    void tableSelectionChanged();
    void graphicsSelectionChanged();



    QString generateGCode();

     NdtCfgMachine &config;

    QProgressDialog *progressDialog;


signals:
    void x_velocity_editingFinished(float arg);
    void y_velocity_editingFinished(float arg);
    void jog_velocity_editingFinished(float arg);
    void x_lenght_editingFinished(float arg);
    void y_lenght_editingFinished(float arg);
    void y_step_editingFinished(float arg);

    void backOrigin_velocity_editingFinished(float arg);
    void scan_velocity_editingFinished(float arg);
    void jog_add_sub_velocity_editingFinished(float arg);

    void movePosition(double x, double y);

    void targetReached();   // 当目标点达到后发出
};
#endif // MotionControl_H










    //IconDelegate* ico_delegate;
//floatpointdelegate *fdelegate;
//BooleanDelegate *b_delegate;
//SN_Dialog * getsn_dialog;
//openDefaut_tested_dialog *default_tested_dialog;
//    QList<QByteArray> splitByFour(const QByteArray &data);
    //QList<int> convertToDecimal(const QByteArray &data);
//    QList<float> convertToReal(const QByteArray &data);
//    void pbIpLineEdit(const QString &arg1);
//    void readPendingDatagrams();
//    float readModbusFloatData(int v1, int v2);

//   QByteArray createModbusRequest(int registerAddress);

//    void onStateChanged(QModbusDevice::State state);
//    void onModbusError(QModbusDevice::Error error);
//    void pbModbusConnect();
//    QString parseModbusResponse(const QByteArray &response);
#if 0
// 轨迹结构体，包含直线和圆弧
struct Trajectory {
    enum Type { Line, Arc } type;

    struct Line {
        double x1, y1, x2, y2;
    } line;

    struct Arc {
        double centerX, centerY;
        double radius;
        double startAngle;
        double endAngle;
    } arc;
};

// DXFReader类，用于解析DXF并生成图形项
class DXFReader : public DRW_Interface {
public:
    QList<QGraphicsItem*> graphicsItems;  // 存储解析后的图形项
    DXFReader(QGraphicsScene* scene);

    void addLine(const DRW_Line &line) override {
        QGraphicsLineItem *lineItem = new QGraphicsLineItem(QLineF(line.basePoint.x, line.basePoint.y, line.secPoint.x, line.secPoint.y));
        graphicsItems.append(lineItem);
    }

    void addArc(const DRW_Arc &arc) override {
        QRectF rect(arc.basePoint.x - arc.radious, arc.basePoint.y - arc.radious, 2 * arc.radious, 2 * arc.radious);
        QGraphicsEllipseItem *arcItem = new QGraphicsEllipseItem(rect);
        arcItem->setStartAngle(arc.staangle * 16);  // 转换为 16 倍单位
        arcItem->setSpanAngle((arc.endangle - arc.staangle) * 16);  // 角度转换
        graphicsItems.append(arcItem);
    }


    void addHeader(const DRW_Header *) override {}
    void addLType(const DRW_LType &) override {}
    void addLayer(const DRW_Layer &) override {}
    void addDimStyle(const DRW_Dimstyle &) override {}
    void addVport(const DRW_Vport &) override {}
    void addTextStyle(const DRW_Textstyle &) override {}
    void addAppId(const DRW_AppId &) override {}
    void addBlock(const DRW_Block &) override {}
    void setBlock(const int ) override {}
    void endBlock() override {}
    void addPoint(const DRW_Point &) override {}
    void addCircle(const DRW_Circle &) override {}
    void addSolid(const DRW_Solid &) override {}
    void addTrace(const DRW_Trace &) override {}
    void addText(const DRW_Text &) override {}
    void addMText(const DRW_MText &) override {}
    void addDimAlign(const DRW_DimAligned *) override {}
    void addDimLinear(const DRW_DimLinear *) override {}
    void addDimRadial(const DRW_DimRadial *) override {}
    void addDimDiametric(const DRW_DimDiametric *) override {}
    void addDimAngular(const DRW_DimAngular *) override {}
    void addDimOrdinate(const DRW_DimOrdinate *) override {}
    void addLeader(const DRW_Leader *) override {}
    void addHatch(const DRW_Hatch *) override {}
    void addSpline(const DRW_Spline *) override {}
    void addInsert(const DRW_Insert &) override {}
    void add3dFace(const DRW_3Dface &) override {}
    void addLWPolyline(const DRW_LWPolyline &) override {}
    void addPolyline(const DRW_Polyline &) override {}
    void addEllipse(const DRW_Ellipse &) override {}
    void addImage(const DRW_Image *) override {}
    void linkImage(const DRW_ImageDef *) override {}
    void writeHeader(DRW_Header &) override {}
    void writeBlocks() override {}
    void writeLineTypes() {}
    void writeLayers() override {}
    void writeTextstyles() override {}
    void writeVports() override {}
    void writeDimstyles() override {}
    void writeAppId() override {}
    void writeEntities() override {}

};
#endif
