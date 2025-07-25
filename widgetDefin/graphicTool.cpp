
#include "graphicTool.h"
#include <QPainter>
#include <math.h>
#include <QDebug>

#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsItem>
#include <QVector2D>

#define PI 3.14159265
#define MID_ANGLE PI/6


line_item::line_item(const QPointF& startPosition, const QPointF& endPosition,int sort_vaule ,route_worksence *parent)
{
    _end = endPosition;
    _start = startPosition;
    _sortNum=sort_vaule;
    is_hover =false;
    imgbg_scale_f = parent->imgbg_scale_f;


    //this->setFlags ( ItemIsSelectable  | ItemIgnoresTransformations | ItemSendsGeometryChanges);
    this->setFlags ( ItemIsSelectable  | ItemSendsGeometryChanges);
    this->setSelected ( false );
    this->setAcceptHoverEvents ( true );
    this->setZValue ( 1 );
    this->setAcceptedMouseButtons(Qt::LeftButton);

}

void line_item::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{


    painter->setRenderHint(QPainter::Antialiasing, false);
    QPen pen;
    if (this->isSelected()==true) {
        pen.setColor(Qt::red);
    }else if(is_hover) {
        pen.setColor(Qt::green);
    }else{
        pen.setColor(Qt::black);
    }

    pen.setWidth(2);
    painter->setPen(pen);
    QPointF end_pos = QPointF( _end.x() - _start.x() ,_end.y() - _start.y() );

    painter->drawLine( _start, _end );



    // 计算直线属性
    QLineF baseLine(_start, _end);
    double L = baseLine.length();
    if (L <= 0) return;  // 避免零长度情况

    // 缩放因子：以 200 为基准，当 L==200 时 scale=1
    double scale = L / 50.0;
    scale = qBound(0.5, scale, 1.0);


    // 箭头参数
    // 箭头偏移量：以 scale 缩放
    double arrowOffset = 10.0 * scale;
    // 箭头三角形宽度
    double arrowWidth = 10.0 * scale;
    // 箭头尾部线段长度
    double tailLength = 10.0 * scale;

    // 计算直线中点，并向上偏移一定距离（这里向上为 y 值减小），偏移量也根据 scale 缩放
    QPointF midpoint = (_start + _end) / 2.0;
    double offsetDist = 10.0 * scale;
    QPointF arrowCenter = midpoint + QPointF(0, 0);

    // 计算直线方向的单位向量
    double dx = baseLine.dx();
    double dy = baseLine.dy();
    double norm = sqrt(dx * dx + dy * dy);
    double ux = dx / norm;
    double uy = dy / norm;

    // 计算垂直方向的单位向量（用于构造箭头底边）
    QPointF perp(-uy, ux);

    // 构造箭头三角形：
    // 箭头顶点：从 arrowCenter 沿直线方向正向移动 arrowOffset
    QPointF tip = arrowCenter + QPointF(ux * arrowOffset, uy * arrowOffset);
    // 箭头底边中心：从 arrowCenter 向直线反方向移动 arrowOffset
    QPointF baseCenter = arrowCenter - QPointF(ux * arrowOffset, uy * arrowOffset);
    // 底边左右两角
    QPointF leftCorner = baseCenter + perp * (arrowWidth / 2.0);
    QPointF rightCorner = baseCenter - perp * (arrowWidth / 2.0);

    // 构造箭头三角形多边形
    QPolygonF arrowPolygon;
    arrowPolygon << tip << leftCorner << rightCorner;

    // 绘制红色箭头三角形
    QPen arrowPen(Qt::blue, 1);
    painter->setPen(arrowPen);
    painter->setBrush(Qt::blue);
    painter->drawPolygon(arrowPolygon);

    // 绘制箭头尾部的短红线，从 baseCenter 向直线反方向延伸 tailLength
    QPointF tailEnd = baseCenter - QPointF(ux * tailLength, uy * tailLength);
    painter->drawLine(baseCenter, tailEnd);

    // 获取箭头方向角度（以 arrowCenter 到 tip 的方向为准）
    QLineF arrowLine(arrowCenter, tip);
    double angle = arrowLine.angle();  // 角度：水平右为0°，顺时针增加

    // 绘制 _sortNum 数值
    QString sortStr = QString::number(_sortNum);
    painter->save();
    // 将坐标系移动到 arrowCenter
    painter->translate(arrowCenter);
    // 旋转坐标系，使文本与箭头方向一致，注意这里取 -angle
    //painter->rotate(-angle);
    // 定义文本区域，宽度和高度也根据 scale 调整
    QRectF textRect(-15 * scale, -10 * scale, 30 * scale, 20 * scale);
    painter->setPen(Qt::green);
    painter->drawText(textRect, Qt::AlignCenter, sortStr);
    painter->restore();
}

QRectF line_item::boundingRect() const
{
    // 计算直线的起点和终点所在的矩形区域
    QRectF rect(_start, _end);
    rect = rect.normalized();

    // 增加额外的边距（例如 4 像素），以确保包括笔宽和悬停区域
    qreal extra = 4;
    return rect.adjusted(-extra, -extra, extra, extra);
}

QPainterPath line_item::shape() const{
    // 创建一个路径，并将直线添加进去
    QPainterPath path;
    path.moveTo(_start);
    path.lineTo(_end);

    // 使用 QPainterPathStroker 将路径扩宽
    QPainterPathStroker stroker;
    stroker.setWidth(8);  // 设置宽度，值可以根据需要调整
    return stroker.createStroke(path);
}

void line_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event); // 调用基类事件处理
    qDebug()<<"**mousePressEvent**"<<this->isSelected();
}

void line_item::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event); // 调用基类事件处理
    is_hover=true;
    qDebug()<<"**hoverEnterEvent**";
}

void line_item::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event); // 调用基类事件处理
    is_hover=false;
}






arc_item::arc_item(const QPointF& startPosition, const QPointF& transPosition, const QPointF& endPosition ,int sortValue,route_worksence *parent)
{
    _end = endPosition;
    _start = startPosition;
    _trans =transPosition;
    _sortNum=sortValue;
    is_hover=false;
    imgbg_scale_f = parent->imgbg_scale_f;

    //this->setFlags ( ItemIsSelectable  | ItemIgnoresTransformations | ItemSendsGeometryChanges);
    this->setFlags ( ItemIsSelectable  | ItemSendsGeometryChanges);
    this->setSelected ( false );
    this->setAcceptHoverEvents ( true );
    this->setZValue ( 1 );
    this->setAcceptedMouseButtons(Qt::LeftButton);

}

void arc_item::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
{



    painter->setRenderHint(QPainter::Antialiasing, false);
    QPen pen(Qt::black, 0);
    if (this->isSelected()==true) {
        pen.setColor(Qt::red);
    }else if(is_hover) {
        pen.setColor(Qt::green);
    }else{
        pen.setColor(Qt::black);
    }

    pen.setWidth(2);
    pen.setCosmetic(true);      // 始终 1px，且随缩放变换包围盒
    painter->setPen(pen);


    QPointF A, B, C;
    A=_start;
    B=_trans;
    C=_end;
    // A = {450, 100}, B = {200, 200}, C = {359, 349};
    auto s_ab = A + B;
    auto s_bc = B + C;
    auto m_ab = A - B;
    auto m_bc = B - C;
    double mat[2][2]{{m_bc.rx() * -2, m_bc.ry() * -2},
                     {m_ab.rx() * -2, m_ab.ry() * -2}};
    auto det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    if (std::abs(det) < std::numeric_limits<double>::epsilon()) {
        // 3 points on the same line,
        painter->drawLine(A, B);
        painter->drawLine(B, C);
        return;
    }
    double b[2]{-(s_bc.rx() * m_bc.rx() + s_bc.ry() * m_bc.ry()),
                -(s_ab.rx() * m_ab.rx() + s_ab.ry() * m_ab.ry())};
    auto O = QPointF{
            (b[0] * mat[1][1] - b[1] * mat[0][1]) / det,
            (b[1] * mat[0][0] - b[0] * mat[1][0]) / det
};

auto vr = A - O;
auto r = std::sqrt(vr.rx() * vr.rx() + vr.ry() * vr.ry());

auto &&on_rect = [&]() {
    return QRectF{O - QPointF{r, r}, O + QPointF{r, r}};
};

auto &&on_ang = [&](const QPointF &p) {
    auto s = p - O;
    auto a = std::acos(s.rx() / r) * (s.ry() > 0 ? -1 : 1);
    return a / PI * 180 * 16;
};

auto &&on_span = [&](double a1, double a2, double a3) {
    if ((a3 - a1) * (a3 - a2) > 0) {
        return a2 - a1;
    } else {
        return (360 * 16 - std::abs(a2 - a1)) * (a2 - a1 > 0 ? -1 : 1);
    }
};

auto ang_A = on_ang(A), ang_B = on_ang(B), ang_C = on_ang(C);
get_rect= QRectF(on_rect());
painter->drawArc(on_rect(), ang_A, on_span(ang_A, ang_B, ang_C));
painter->drawArc(on_rect(), ang_B, on_span(ang_B, ang_C, ang_A));

painter->drawEllipse(A, 3, 3);
painter->drawText(A + QPointF(10, 10), "A");
painter->drawEllipse(B, 3, 3);
painter->drawText(B + QPointF(10, 10), "B");
painter->drawEllipse(C, 3, 3);
painter->drawText(C + QPointF(10, 10), "C");



// 计算直线属性
QLineF baseLine(_start, _end);
double L = baseLine.length();
if (L <= 0) return;  // 避免零长度情况

// 缩放因子：以 200 为基准，当 L==200 时 scale=1
double scale = L / 50.0;
scale = qBound(0.5, scale, 1.0);

// 箭头参数
// 箭头偏移量：以 scale 缩放
double arrowOffset = 10.0 * scale;
// 箭头三角形宽度
double arrowWidth = 10.0 * scale;
// 箭头尾部线段长度
double tailLength = 10.0 * scale;

double offsetDist = 10.0 * scale;
QPointF arrowCenter = _trans + QPointF(0, 0);

// 计算直线方向的单位向量
double dx = baseLine.dx();
double dy = baseLine.dy();
double norm = sqrt(dx * dx + dy * dy);
double ux = dx / norm;
double uy = dy / norm;

// 计算垂直方向的单位向量（用于构造箭头底边）
QPointF perp(-uy, ux);

// 构造箭头三角形：
// 箭头顶点：从 arrowCenter 沿直线方向正向移动 arrowOffset
QPointF tip = arrowCenter + QPointF(ux * arrowOffset, uy * arrowOffset);
// 箭头底边中心：从 arrowCenter 向直线反方向移动 arrowOffset
QPointF baseCenter = arrowCenter - QPointF(ux * arrowOffset, uy * arrowOffset);
// 底边左右两角
QPointF leftCorner = baseCenter + perp * (arrowWidth / 2.0);
QPointF rightCorner = baseCenter - perp * (arrowWidth / 2.0);

// 构造箭头三角形多边形
QPolygonF arrowPolygon;
arrowPolygon << tip << leftCorner << rightCorner;

// 绘制红色箭头三角形
QPen arrowPen(Qt::blue, 1);
painter->setPen(arrowPen);
painter->setBrush(Qt::blue);
painter->drawPolygon(arrowPolygon);

// 绘制箭头尾部的短红线，从 baseCenter 向直线反方向延伸 tailLength
QPointF tailEnd = baseCenter - QPointF(ux * tailLength, uy * tailLength);
painter->drawLine(baseCenter, tailEnd);

// 获取箭头方向角度（以 arrowCenter 到 tip 的方向为准）
QLineF arrowLine(arrowCenter, tip);
double angle = arrowLine.angle();  // 角度：水平右为0°，顺时针增加

// 绘制 _sortNum 数值
QString sortStr = QString::number(_sortNum);
painter->save();
// 将坐标系移动到 arrowCenter
painter->translate(arrowCenter);
// 旋转坐标系，使文本与箭头方向一致，注意这里取 -angle
//painter->rotate(-angle);
// 定义文本区域，宽度和高度也根据 scale 调整
QRectF textRect(-15 * scale, -10 * scale, 30 * scale, 20 * scale);
painter->setPen(Qt::green);
painter->drawText(textRect, Qt::AlignCenter, sortStr);
painter->restore();
}

QRectF arc_item::boundingRect() const
{

    QPointF A = _start;
    QPointF B = _trans;
    QPointF C = _end;

    qDebug() << "BoudingRect Calc Debug: Input points: A=" << A << ", B=" << B << ", C=" << C;

    auto s_ab = A + B;
    auto s_bc = B + C;
    auto m_ab = A - B;
    auto m_bc = B - C;
    double mat[2][2]{{m_bc.rx() * -2, m_bc.ry() * -2},
                     {m_ab.rx() * -2, m_ab.ry() * -2}};
    auto det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];

    qDebug() << "BoudingRect Calc Debug: det=" << det;

    const double GEOMETRY_EPSILON = 0.5; // 与 shape() 使用相同的几何阈值

    if (std::abs(det) < GEOMETRY_EPSILON) {
        qDebug() << "BoudingRect Calc Debug: Points are collinear or near-collinear. Returning bounding rect of all points.";
        QRectF rect(A, C);
        rect = rect.united(QRectF(B, B)).normalized(); // 确保包含 B 点
        qreal extra = 8; // 增加额外边距，与期望的像素宽度一致
        QRectF finalRect = rect.adjusted(-extra, -extra, extra, extra);
        qDebug() << "BoudingRect Calc Debug: Collinear rect:" << finalRect;
        return finalRect;
    }

    double b[2]{-(s_bc.rx() * m_bc.rx() + s_bc.ry() * m_bc.ry()),
                -(s_ab.rx() * m_ab.rx() + s_ab.ry() * m_ab.ry())};
    auto O = QPointF{
            (b[0] * mat[1][1] - b[1] * mat[0][1]) / det,
            (b[1] * mat[0][0] - b[0] * mat[1][0]) / det
};
qDebug() << "BoudingRect Calc Debug: Calculated center O=" << O;

auto vr = A - O;
auto r = std::sqrt(vr.rx() * vr.rx() + vr.ry() * vr.ry());
qDebug() << "BoudingRect Calc Debug: Calculated radius r=" << r;

// 半径无效或过小的情况
if (std::isnan(r) || std::isinf(r) || r < GEOMETRY_EPSILON) {
    qDebug() << "BoudingRect Calc Debug: Radius is invalid or too small. Returning bounding rect of all points.";
    QRectF rect(A, C);
    rect = rect.united(QRectF(B, B)).normalized(); // 确保包含 B 点
    qreal extra = 8;
    QRectF finalRect = rect.adjusted(-extra, -extra, extra, extra);
    qDebug() << "BoudingRect Calc Debug: Invalid radius rect:" << finalRect;
    return finalRect;
}

// 对于有效的圆弧，计算其包含整个圆的包围盒。
// 这通常比精确的圆弧包围盒要大，但对于 boundingRect 来说是安全的。
QRectF circleBoundingRect(O.x() - r, O.y() - r, 2 * r, 2 * r);
qreal extra = 8; // 增加额外边距，与 shape 笔触宽度对应，确保点击区域足够
QRectF finalRect = circleBoundingRect.adjusted(-extra, -extra, extra, extra);

// 再次检查最终矩形的有效性，以防计算结果导致非有限值或空矩形
if (!finalRect.isValid() || finalRect.isEmpty() || !qIsFinite(finalRect.left()) || !qIsFinite(finalRect.top())) {
    qDebug() << "BoudingRect Calc Debug: Final circleBoundingRect is invalid/empty/non-finite. Falling back to points bounding rect.";
    QRectF rect(A, C);
    rect = rect.united(QRectF(B, B)).normalized(); // 确保包含 B 点
    finalRect = rect.adjusted(-extra, -extra, extra, extra);
}
qDebug() << "BoudingRect Calc Debug: Final returned rect:" << finalRect;
return finalRect;

}

QPainterPath arc_item::shape() const{

    QPointF A = _start;
    QPointF B = _trans;
    QPointF C = _end;

    qDebug() << "Shape Calc Debug: Input points: A=" << A << ", B=" << B << ", C=" << C;

    auto s_ab = A + B;
    auto s_bc = B + C;
    auto m_ab = A - B;
    auto m_bc = B - C;
    double mat[2][2]{{m_bc.rx() * -2, m_bc.ry() * -2},
                     {m_ab.rx() * -2, m_ab.ry() * -2}};
    auto det = mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
    qDebug() << "Shape Calc Debug: det=" << det;

    const double GEOMETRY_EPSILON = 0.5; // 请根据实际坐标范围调整，可尝试 0.1 或 1.0

    // 共线或接近共线的情况
    if (std::abs(det) < GEOMETRY_EPSILON) {
        qDebug() << "Shape Calc Debug: Points are collinear or near-collinear. Returning straight line shape.";
        QPainterPath path;
        path.moveTo(A);
        path.lineTo(C); // 直接从 A 到 C 的直线
        QPainterPathStroker stroker;
        // 计算缩放因子并设置笔触宽度，确保在屏幕上可见
        QTransform itemToSceneTransform = this->sceneTransform();
        qreal currentScale = 1.0;
        if (!itemToSceneTransform.isIdentity()) {
            QVector2D mappedX = QVector2D(itemToSceneTransform.map(QPointF(1, 0)));
            QVector2D mappedY = QVector2D(itemToSceneTransform.map(QPointF(0, 1)));
            currentScale = (mappedX.length() + mappedY.length()) / 2.0;
        }
        if (qFuzzyIsNull(currentScale) || currentScale == 0) {
            currentScale = 1.0;
        }
        const qreal desiredScreenPixelWidth = 8.0; // 期望在屏幕上的像素宽度
        qreal strokeWidth = desiredScreenPixelWidth / currentScale;
        stroker.setWidth(qMax(strokeWidth, 2.0)); // 最小宽度为 2.0，防止太细
        qDebug() << "Shape Calc Debug: Collinear branch: currentScale=" << currentScale << ", stroker.setWidth=" << stroker.width();

        QPainterPath strokedPath = stroker.createStroke(path);
        qDebug() << "Shape Calc Debug: Collinear strokedPath.isEmpty():" << strokedPath.isEmpty();
        qDebug() << "Shape Calc Debug: Collinear strokedPath.boundingRect():" << strokedPath.boundingRect();
        return strokedPath;
    }

    double b[2]{-(s_bc.rx() * m_bc.rx() + s_bc.ry() * m_bc.ry()),
                -(s_ab.rx() * m_ab.rx() + s_ab.ry() * m_ab.ry())};
    auto O = QPointF{
            (b[0] * mat[1][1] - b[1] * mat[0][1]) / det,
            (b[1] * mat[0][0] - b[0] * mat[1][0]) / det
};
qDebug() << "Shape Calc Debug: Calculated center O=" << O;

auto vr = A - O;
auto r = std::sqrt(vr.rx() * vr.rx() + vr.ry() * vr.ry());
qDebug() << "Shape Calc Debug: Calculated radius r=" << r;

// 半径无效或过小的情况
if (std::isnan(r) || std::isinf(r) || r < GEOMETRY_EPSILON) {
    qDebug() << "Shape Calc Debug: Radius is invalid or too small. Returning fallback straight line shape.";
    QPainterPath fallbackPath;
    // Fallback to a path that covers the points
    fallbackPath.moveTo(A);
    fallbackPath.lineTo(C);
    QPainterPathStroker stroker;
    // 同样计算缩放因子
    QTransform itemToSceneTransform = this->sceneTransform();
    qreal currentScale = 1.0;
    if (!itemToSceneTransform.isIdentity()) {
        QVector2D mappedX = QVector2D(itemToSceneTransform.map(QPointF(1, 0)));
        QVector2D mappedY = QVector2D(itemToSceneTransform.map(QPointF(0, 1)));
        currentScale = (mappedX.length() + mappedY.length()) / 2.0;
    }
    if (qFuzzyIsNull(currentScale) || currentScale == 0) {
        currentScale = 1.0;
    }
    const qreal desiredScreenPixelWidth = 8.0;
    qreal strokeWidth = desiredScreenPixelWidth / currentScale;
    stroker.setWidth(qMax(strokeWidth, 2.0));
    qDebug() << "Shape Calc Debug: Invalid radius branch: currentScale=" << currentScale << ", stroker.setWidth=" << stroker.width();

    QPainterPath strokedPath = stroker.createStroke(fallbackPath);
    qDebug() << "Shape Calc Debug: Invalid radius fallback strokedPath.isEmpty():" << strokedPath.isEmpty();
    qDebug() << "Shape Calc Debug: Invalid radius fallback strokedPath.boundingRect():" << strokedPath.boundingRect();
    return strokedPath;
}

// 定义圆弧的外切矩形
QRectF circleRect(O.x() - r, O.y() - r, 2 * r, 2 * r);
qDebug() << "Shape Calc Debug: circleRect=" << circleRect << " isValid:" << circleRect.isValid();

// 确保 circleRect 有效，否则 arcTo 可能失败
if (!circleRect.isValid() || circleRect.isEmpty() || !qIsFinite(circleRect.left()) || !qIsFinite(circleRect.top())) {
    qDebug() << "Shape Calc Debug: circleRect is invalid, empty or contains non-finite values. Returning fallback straight line shape.";
    QPainterPath fallbackPath;
    fallbackPath.moveTo(A);
    fallbackPath.lineTo(C);
    QPainterPathStroker stroker;
    QTransform itemToSceneTransform = this->sceneTransform();
    qreal currentScale = 1.0;
    if (!itemToSceneTransform.isIdentity()) {
        QVector2D mappedX = QVector2D(itemToSceneTransform.map(QPointF(1, 0)));
        QVector2D mappedY = QVector2D(itemToSceneTransform.map(QPointF(0, 1)));
        currentScale = (mappedX.length() + mappedY.length()) / 2.0;
    }
    if (qFuzzyIsNull(currentScale) || currentScale == 0) {
        currentScale = 1.0;
    }
    const qreal desiredScreenPixelWidth = 8.0;
    qreal strokeWidth = desiredScreenPixelWidth / currentScale;
    stroker.setWidth(qMax(strokeWidth, 2.0));
    qDebug() << "Shape Calc Debug: Invalid circleRect branch: currentScale=" << currentScale << ", stroker.setWidth=" << stroker.width();

    QPainterPath strokedPath = stroker.createStroke(fallbackPath);
    qDebug() << "Shape Calc Debug: Invalid circleRect fallback strokedPath.isEmpty():" << strokedPath.isEmpty();
    qDebug() << "Shape Calc Debug: Invalid circleRect fallback strokedPath.boundingRect():" << strokedPath.boundingRect();
    return strokedPath;
}


// 角度计算 lambda 函数
auto &&on_ang = [&](const QPointF &p) {
    auto s = p - O;
    qreal cos_val = s.rx() / r;
    if (cos_val > 1.0) cos_val = 1.0; // 钳制在 [-1, 1] 范围内
    if (cos_val < -1.0) cos_val = -1.0;
    auto a = std::acos(cos_val) * (s.ry() > 0 ? -1 : 1); // 调整 Y 轴方向，Qt 坐标系 Y 轴向下
    return a / PI * 180 * 16; // 转换为 1/16 度
};

// 跨度计算 lambda 函数
auto &&on_span = [&](double a1, double a2, double a3) {
    double span = a2 - a1;
    // 确保跨度在正确方向上，并且不超过 360 度
    if (std::abs(span) > 180 * 16) {
        span = (360 * 16 - std::abs(span)) * (span > 0 ? -1 : 1);
    }
    return span;
};

auto ang_A = on_ang(A);
auto ang_B = on_ang(B);
auto ang_C = on_ang(C);
qDebug() << "Shape Calc Debug: ang_A=" << ang_A << ", ang_B=" << ang_B << ", ang_C=" << ang_C;

QPainterPath path;
path.moveTo(A); // 从 A 点开始绘制
// 绘制从 A 到 B 的弧
path.arcTo(circleRect, ang_A, on_span(ang_A, ang_B, ang_C)); // 这里应根据您的逻辑，绘制到 B
qDebug() << "Shape Calc Debug: Path after first arcTo. currentPoint:" << path.currentPosition() << " isEmpty:" << path.isEmpty() << " boundingRect:" << path.boundingRect();

// 如果您希望绘制的是连接 A-B 和 B-C 的两条弧，则此逻辑不变
// 如果您希望绘制的是一条从 A 到 C 经过 B 的弧，则需要重新考虑 on_span 的逻辑
path.moveTo(B); // 移动到 B 点，开始绘制第二段弧
path.arcTo(circleRect, ang_B, on_span(ang_B, ang_C, ang_A)); // 绘制从 B 到 C 的弧
qDebug() << "Shape Calc Debug: Path after second arcTo. currentPoint:" << path.currentPosition() << " isEmpty:" << path.isEmpty() << " boundingRect:" << path.boundingRect();

// QPainterPathStroker 逻辑
QPainterPathStroker stroker;
QTransform itemToSceneTransform = this->sceneTransform();
qreal currentScale = 1.0;
if (!itemToSceneTransform.isIdentity()) {
    QVector2D mappedX = QVector2D(itemToSceneTransform.map(QPointF(1, 0)));
    QVector2D mappedY = QVector2D(itemToSceneTransform.map(QPointF(0, 1)));
    currentScale = (mappedX.length() + mappedY.length()) / 2.0;
}
if (qFuzzyIsNull(currentScale) || currentScale == 0) {
    currentScale = 1.0;
}

const qreal desiredScreenPixelWidth = 8.0; // 期望在屏幕上的像素宽度，用于碰撞检测
qreal strokeWidth = desiredScreenPixelWidth / currentScale;
stroker.setWidth(qMax(strokeWidth, 2.0)); // 确保最小宽度，防止过小无法点击
qDebug() << "Shape Calc Debug: stroker.setWidth=" << stroker.width();

QPainterPath strokedPath = stroker.createStroke(path);
qDebug() << "Shape Calc Debug: FINAL strokedPath.isEmpty():" << strokedPath.isEmpty();
qDebug() << "Shape Calc Debug: FINAL strokedPath.boundingRect():" << strokedPath.boundingRect();

return strokedPath;
}

void arc_item::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsItem::mousePressEvent(event); // 调用基类事件处理
    //qDebug()<<"**mousePressEvent**"<<this->isSelected();
}

void arc_item::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverEnterEvent(event); // 调用基类事件处理
    is_hover=true;
    qDebug()<<"**hoverEnterEvent**";
}

void arc_item::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverLeaveEvent(event); // 调用基类事件处理
    is_hover=false;
}
