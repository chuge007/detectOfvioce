#include "mathtool.h"
#include <QDebug>
#include <cmath>
#include <QtMath>
#include <QVector2D>

#include <QtCore>
#include <cmath>
#include <limits>

#define _USE_MATH_DEFINES
mathTool::mathTool()
{

}


bool mathTool::isDirectionSmooth(const QPointF& dir1, const QPointF& dir2, qreal angleTolDeg = 1.0)
{
    qDebug() << "=== isDirectionSmooth DEBUG START ===";
    qDebug() << "dir1:" << dir1 << "dir2:" << dir2;

    // Dot product
    qreal dot = dir1.x() * dir2.x() + dir1.y() * dir2.y();
    qDebug() << "Dot product:" << dot;

    // Vector lengths
    qreal len1 = std::hypot(dir1.x(), dir1.y());
    qreal len2 = std::hypot(dir2.x(), dir2.y());
    qDebug() << "Length of dir1:" << len1 << "Length of dir2:" << len2;

    // Invalid direction if either vector has zero length
    if (len1 == 0 || len2 == 0) {
        qDebug() << "One of the vectors has zero length. Returning false.";
        return false;
    }

    // Cosine of angle between vectors
    qreal cosAngle = dot / (len1 * len2);
    qDebug() << "Raw cos(angle):" << cosAngle;

    // Clamp to avoid domain error in acos
    cosAngle = clamp(cosAngle, -1.0, 1.0);
    qDebug() << "Clamped cos(angle):" << cosAngle;

    // Convert to degrees
    qreal angleDeg = std::acos(cosAngle) * 180.0 / M_PI;
    qDebug() << "Angle between vectors (degrees):" << angleDeg;

    // Check against tolerance
    if (std::abs(angleDeg) <= angleTolDeg || std::abs(angleDeg - 180.0) <= angleTolDeg) {
        qDebug() << "The two vectors are collinear (0° or 180°) within the tolerance.";
        return true;
    }else{

        return false;
    }
}


QPointF mathTool::getArcTangentAtPoint(const QPointF& center, const QPointF& pt)
{
    QPointF radial = pt - center;
    return QPointF(-radial.y(), radial.x());  // 默认逆时针方向切线
}


QPointF mathTool::getCircleCenterFrom3Points(const QPointF& A, const QPointF& B, const QPointF& C)
{
    // 计算边的中点
    QPointF midAB = (A + B) / 2.0;
    QPointF midBC = (B + C) / 2.0;

    // 向量 AB 和 BC
    QPointF vecAB = B - A;
    QPointF vecBC = C - B;

    // 构造中垂线方向（垂直向量）
    QPointF perpAB(-vecAB.y(), vecAB.x());
    QPointF perpBC(-vecBC.y(), vecBC.x());

    // 解交点：midAB + t1 * perpAB = midBC + t2 * perpBC
    double a1 = perpAB.x();
    double b1 = -perpBC.x();
    double c1 = midBC.x() - midAB.x();

    double a2 = perpAB.y();
    double b2 = -perpBC.y();
    double c2 = midBC.y() - midAB.y();

    double D = a1 * b2 - a2 * b1;

    if (std::abs(D) < 1e-6) {
        // 共线或几乎共线，无法确定唯一圆心
        return QPointF(0, 0);
    }

    double t1 = (c1 * b2 - c2 * b1) / D;
    return midAB + t1 * perpAB;
}



bool mathTool::computeSmoothArc(QPointF start1, QPointF end1, QPointF start2, QPointF end2, qreal smoothFactor, ArcInsertResult& result)
{
    qDebug() << "--- computeSmoothArc DEBUG Start ---";
    qDebug() << "Input: start1=" << start1 << ", end1=" << end1;
    qDebug() << "Input: start2=" << start2 << ", end2=" << end2;
    qDebug() << "Input: smoothFactor=" << smoothFactor;

    // 1. 计算方向向量
    QPointF V0 = end1 - start1; // 从 start1 指向 end1 的方向向量
    QPointF V2 = end2 - start2; // 从 start2 指向 end2 的方向向量
    qDebug() << "Step 1: Calculated V0 =" << V0 << ", V2 =" << V2;

    // 2. 检查方向向量是否为零向量
    if (V0.manhattanLength() == 0 || V2.manhattanLength() == 0) {
        qDebug() << "Step 2: Error - One or both direction vectors are zero length. V0 length:" << V0.manhattanLength() << ", V2 length:" << V2.manhattanLength();
        return false;
    }

    // 3. 归一化方向向量
    qreal V0_mag = std::hypot(V0.x(), V0.y());
    qreal V2_mag = std::hypot(V2.x(), V2.y());
    V0 /= V0_mag;
    V2 /= V2_mag;
    qDebug() << "Step 3: Normalized V0 =" << V0 << " (original mag:" << V0_mag << ")";
    qDebug() << "         Normalized V2 =" << V2 << " (original mag:" << V2_mag << ")";

    // 4. 定义圆弧的参考点 P0_ref 和 P2_ref
    // P0_ref 对应前一个图元的终点 (end1)
    QPointF P0_ref = end1;
    // P2_ref 对应后一个图元的起点 (start2)
    QPointF P2_ref = start2;
    qDebug() << "Step 4: P0_ref (reference for Q0) =" << P0_ref;
    qDebug() << "         P2_ref (reference for Q2) =" << P2_ref;


    // 5. 计算圆弧的切点 Q0 和 Q2
    // Q0 是从 P0_ref 沿着 V0 方向 '反向' 延伸 smoothFactor 距离 (因为 P0_ref 是终点)
    QPointF Q0 = P0_ref - V0 * smoothFactor;
    // Q2 是从 P2_ref 沿着 V2 方向 '正向' 延伸 smoothFactor 距离 (因为 P2_ref 是起点)
    QPointF Q2 = P2_ref + V2 * smoothFactor;
    qDebug() << "Step 5: Calculated Q0 (arc start point) =" << Q0;
    qDebug() << "         Calculated Q2 (arc end point) =" << Q2;

    // --- 方向判断逻辑 ---
    QPointF n0, n2; // 定义法线向量
    // 计算 V0 和 V2 的二维叉积
    qreal crossProduct = V0.x() * V2.y() - V0.y() * V2.x();
    qDebug() << "Cross Product (V0 x V2) =" << crossProduct;

    if (crossProduct > 0) {
        // V2 相对 V0 呈逆时针方向，表示向左转弯 (内角在左侧)
        // 两个法线向量都逆时针旋转90度
        n0 = QPointF(-V0.y(), V0.x()); // V0 逆时针90度
        n2 = QPointF(-V2.y(), V2.x()); // V2 逆时针90度
        qDebug() << "Cross Product > 0 (Left Turn): n0 (V0 rotated 90deg CCW) =" << n0;
        qDebug() << "                                 n2 (V2 rotated 90deg CCW) =" << n2;
    } else if (crossProduct < 0) {
        // V2 相对 V0 呈顺时针方向，表示向右转弯 (内角在右侧)
        // 两个法线向量都顺时针旋转90度
        n0 = QPointF(V0.y(), -V0.x()); // V0 顺时针90度
        n2 = QPointF(V2.y(), -V2.x()); // V2 顺时针90度
        qDebug() << "Cross Product < 0 (Right Turn): n0 (V0 rotated 90deg CW) =" << n0;
        qDebug() << "                                  n2 (V2 rotated 90deg CW) =" << n2;
    } else {
        // crossProduct == 0，表示 V0 和 V2 平行或反平行
        qDebug() << "Cross Product == 0: V0 and V2 are parallel or anti-parallel. Cannot form an arc.";
        return false;
    }
    // --- 方向判断逻辑结束 ---

    // 7. 建立线性方程组的系数 (求解圆心)
    // 目标是解方程组： Q0 + t * n0 = Q2 + s * n2
    // 变形为： t * n0 - s * n2 = Q2 - Q0
    //
    // 方程组形式：
    // n0.x * t - n2.x * s = Q2.x - Q0.x
    // n0.y * t - n2.y * s = Q2.y - Q0.y
    //
    // 对应 a1*t + b1*s = c1
    //      a2*t + b2*s = c2
    qreal a1 = n0.x();
    qreal b1 = -n2.x();
    qreal a2 = n0.y();
    qreal b2 = -n2.y();

    qreal c1 = Q2.x() - Q0.x();
    qreal c2 = Q2.y() - Q0.y();
    qDebug() << "Step 7: Linear system coefficients:";
    qDebug() << "         a1 =" << a1 << ", b1 =" << b1 << ", c1 =" << c1;
    qDebug() << "         a2 =" << a2 << ", b2 =" << b2 << ", c2 =" << c2;

    // 8. 计算行列式 (determinant)
    qreal det = a1 * b2 - a2 * b1;
    qDebug() << "Step 8: Determinant (det) =" << det;

    // 9. 检查行列式是否接近于零（即直线平行或重合）
    if (qFuzzyIsNull(det)) {
        qDebug() << "Step 9: Error - Determinant is fuzzy null. Lines are parallel or coincident, cannot find unique center.";
        return false;
    }

    // 10. 使用克莱姆法则求解参数 t
    qreal t = (c1 * b2 - c2 * b1) / det;
    qDebug() << "Step 10: Solved parameter t =" << t;

    // 11. 计算圆心
    QPointF center = Q0 + n0 * t;
    qDebug() << "Step 11: Calculated Center =" << center;

    // 12. 计算半径
    qreal radius = std::hypot(Q0.x() - center.x(), Q0.y() - center.y());
    qDebug() << "Step 12: Calculated Radius =" << radius;

    // 13. 将计算结果存储到 result 结构体
    result.q0 = Q0;
    result.q2 = Q2;
    result.radius = radius;

    if (radius > 0) { // 避免除以零或计算点重合的情况
        QPointF radius_vec_Q0 = Q0 - center;
        QPointF radius_vec_Q2 = Q2 - center;

        // 相加得到指向中点方向的向量，然后归一化
        QPointF mid_direction_vec = radius_vec_Q0 + radius_vec_Q2;
        qreal mid_direction_mag = std::hypot(mid_direction_vec.x(), mid_direction_vec.y());

        if (qFuzzyIsNull(mid_direction_mag)) {
            // 如果两个半径向量相加后长度为0，说明Q0和Q2关于圆心对称，或者Q0/Q2/center重合 (半径为0)
            // 这种情况下，过渡点就是圆心
            result.Transition = center;
            qDebug() << "Step 14: Transition point (special case: radius 0 or symmetric) =" << result.Transition;
        } else {
            mid_direction_vec /= mid_direction_mag;
            // 从圆心沿着中点方向延伸半径距离
            result.Transition = center + mid_direction_vec * radius;
            qDebug() << "Step 14: Calculated Transition Point =" << result.Transition;
        }
    } else {
        // 如果半径为0，圆弧退化为点，过渡点就是圆心 (也是Q0和Q2)
        result.Transition = center;
        qDebug() << "Step 14: Transition point (radius is 0) =" << result.Transition;
    }
    qDebug() << "--- computeSmoothArc DEBUG End ---";
    return true; // 成功计算圆弧
}

template<typename T>
T mathTool::clamp(T value, T minVal, T maxVal) {
    return std::max(minVal, std::min(value, maxVal));
}

//_________________________________________________________________________________________________-

// 计算两条直线的交点（无限长），返回是否有交点，交点保存在 intersection
// 直线用起点和方向向量表示：
// line1: p1 + t * d1
// line2: p2 + s * d2

QLineF mathTool::extendLineFromPoint(const QPointF& start1, const QPointF& start2, double extendLength)
{
    QPointF direction = start2 - start1;
    double length = std::hypot(direction.x(), direction.y());
    if (qFuzzyIsNull(length)) {
        // 如果方向向量为 0，返回无效线段
        return QLineF(start2, start2);
    }

    QPointF unitDir = direction / length;
    QPointF extendedEnd = start2 + unitDir * extendLength;
    return QLineF(start2, extendedEnd);
}



bool mathTool::intersectInfiniteLinesByPoints(const QPointF& p1, const QPointF& p2,
                                              const QPointF& p3, const QPointF& p4,
                                              QPointF& intersection)
{
    // 直线1的参数
    double A1 = p2.y() - p1.y();
    double B1 = p1.x() - p2.x();
    double C1 = A1 * p1.x() + B1 * p1.y();

    // 直线2的参数
    double A2 = p4.y() - p3.y();
    double B2 = p3.x() - p4.x();
    double C2 = A2 * p3.x() + B2 * p3.y();

    double det = A1 * B2 - A2 * B1;

    if (std::abs(det) < 1e-10) {
        // 平行或重合，没交点
        return false;
    }

    double x = (C1 * B2 - C2 * B1) / det;
    double y = (A1 * C2 - A2 * C1) / det;

    intersection = QPointF(x, y);
    return true;
}


QPointF mathTool::arcMidPoint(const QPointF& circleCenter, const QPointF& t1, const QPointF& t2)
{
    // 向量：从圆心指向 t1 和 t2
    QVector2D v1(t1 - circleCenter);
    QVector2D v2(t2 - circleCenter);

    // 单位化
    v1.normalize();
    v2.normalize();

    // 计算夹角（通过 atan2）
    double angle1 = std::atan2(v1.y(), v1.x());
    double angle2 = std::atan2(v2.y(), v2.x());

    double angleDiff = angle2 - angle1;

    // 规范化到 [-π, π]
    if (angleDiff > M_PI) angleDiff -= 2 * M_PI;
    if (angleDiff < -M_PI) angleDiff += 2 * M_PI;

    // 如果夹角大于 180°（即角度差为负），换方向：从 angle2 向 angle1 取中间
    double midAngle;
    if (angleDiff > 0) {
        midAngle = angle1 + angleDiff / 2;
    } else {
        midAngle = angle2 + (angle1 - angle2) / 2;
    }

    // 使用任意一个半径计算圆周点
    double radius = QVector2D(t1 - circleCenter).length();

    // 中点坐标 = 圆心 + 半径 * (cos(midAngle), sin(midAngle))
    QPointF midPoint = circleCenter + QPointF(std::cos(midAngle), std::sin(midAngle)) * radius;

    return midPoint;
}

bool mathTool::isSegmentIntersectCircle(const QPointF& A, const QPointF& B, const QPointF& center, double R) {
    QPointF AB = B - A;
    QPointF AC = center - A;
    double t = QPointF::dotProduct(AB, AC) / QPointF::dotProduct(AB, AB);
    t = clamp(t, 0.0, 1.0);
    QPointF P = A + t * AB;
    double d = std::hypot(P.x() - center.x(), P.y() - center.y());
    return d <= R;
}

QLineF mathTool::offsetLineSegment(const QPointF& A, const QPointF& B, double offsetR, bool rotateLeft)
{
    // 计算单位方向向量
    QPointF dir = B - A;
    dir /= std::hypot(dir.x(), dir.y());

    // 根据旋转方向计算法线（垂直方向）向量
    QPointF normal;
    if (rotateLeft) {
        // 左旋90度
        normal = QPointF(-dir.y(), dir.x());
    } else {
        // 右旋90度
        normal = QPointF(dir.y(), -dir.x());
    }

    // 偏移向量
    QPointF offset = normal * offsetR;

    // 返回偏移后的线段
    return QLineF(A + offset, B + offset);
}



bool mathTool::intersectLineCircle(const QLineF& line, const QPointF& center, double radius, QPointF& result) {
    QPointF p0 = line.p1();
    QPointF d = line.p2() - p0;

    double dx = d.x(), dy = d.y();
    double fx = p0.x() - center.x();
    double fy = p0.y() - center.y();

    double a = dx*dx + dy*dy;
    double b = 2 * (fx*dx + fy*dy);
    double c = fx*fx + fy*fy - radius*radius;

    double discriminant = b*b - 4*a*c;
    if (discriminant < 0)
        return false;

    discriminant = std::sqrt(discriminant);
    double t1 = (-b + discriminant) / (2*a);
    double t2 = (-b - discriminant) / (2*a);

    bool found = false;

    if (t1 >= 0.0 && t1 <= 1.0) {
        result = p0 + d * t1;
        found = true;
    }

    if (!found && t2 >= 0.0 && t2 <= 1.0) {
        result = p0 + d * t2;
        found = true;
    }

    return found;
}

double mathTool::angleBetweenVectors(const QPointF& from1, const QPointF& to1,
                                     const QPointF& from2, const QPointF& to2)
{
    QPointF v1 = to1 - from1;
    QPointF v2 = to2 - from2;

    double dot = QPointF::dotProduct(v1, v2);
    double len1 = std::hypot(v1.x(), v1.y());
    double len2 = std::hypot(v2.x(), v2.y());

    if (qFuzzyIsNull(len1) || qFuzzyIsNull(len2))
        return 0.0;  // 避免除以 0

    double cosAngle = dot / (len1 * len2);
    cosAngle = clamp(cosAngle, -1.0, 1.0);
    return std::acos(cosAngle) * 180.0 / M_PI;
}

QPointF mathTool::projectToLine(const QPointF& P, const QPointF& A, const QPointF& B) {
    QPointF AB = B - A;
    double t = QPointF::dotProduct(P - A, AB) / QPointF::dotProduct(AB, AB);
    return A + AB * t;
}


//____________________________________________________________________________________________________________________________
bool mathTool::isPointOnLeftSide(const QPointF& A, const QPointF& B, const QPointF& C)
{
    QPointF AB = B - A;
    QPointF AC = C - A;

    // 计算二维叉积：AB × AC
    double cross = AB.x() * AC.y() - AB.y() * AC.x();

    if (cross > 0)
        return true;  // 点 C 在向量 AB 的左边
    else
        return false; // 点 C 在向量 AB 的右边或共线
}

constexpr double EPS = 1e-6;
constexpr double PI = 3.14159265358979323846;

bool isAngleOnArc_getArcAndCircleIntersection(double angle, double startAngle, double endAngle) {
    while (endAngle < startAngle) endAngle += 2 * PI;
    while (angle < startAngle) angle += 2 * PI;
    return angle <= endAngle + EPS;
}



bool isSameSideOfLine(const QPointF& lineStart, const QPointF& lineEnd,
                      const QPointF& p1, const QPointF& p2)
{
    QPointF dir = lineEnd - lineStart;
    QPointF v1 = p1 - lineStart;
    QPointF v2 = p2 - lineStart;

    // 计算两个点相对于 line 的叉积符号
    double cross1 = dir.x() * v1.y() - dir.y() * v1.x();
    double cross2 = dir.x() * v2.y() - dir.y() * v2.x();

    return (cross1 * cross2 >= 0);  // 同号 => 同侧
}

QVector<QPointF> mathTool::getArcAndCircleIntersection(
    const QPointF& arcStart,
    const QPointF& arcControl,
    const QPointF& arcEnd,
    double arcRadius,
    double smallRadius,
    ArcCircleAnchor anchor
)
{
    QVector<QPointF> result;

    qDebug() << "======== getArcAndCircleIntersection BEGIN ========";
    qDebug() << "arcStart:" << arcStart;
    qDebug() << "arcControl:" << arcControl;
    qDebug() << "arcEnd:" << arcEnd;
    qDebug() << "arcRadius:" << arcRadius;
    qDebug() << "smallRadius:" << smallRadius;
    qDebug() << "anchor:" << (anchor == ArcCircleAnchor::Start ? "Start" : "End");

    // 1. 求大圆圆心
    QPointF bigCenter = getCircleCenterFrom3Points(arcStart, arcControl, arcEnd);
    qDebug() << "bigCenter:" << bigCenter;

    // 2. 确定小圆圆心
    QPointF smallCenter = (anchor == ArcCircleAnchor::Start) ? arcStart : arcEnd;
    qDebug() << "smallCenter:" << smallCenter;

    // 3. 两圆心之间的 dx, dy, 距离 d
    double dx = bigCenter.x() - smallCenter.x();
    double dy = bigCenter.y() - smallCenter.y();
    double d = std::hypot(dx, dy);
    qDebug() << "dx:" << dx << "dy:" << dy << "distance d:" << d;

    // 4. 检查交点存在性
    if (d > arcRadius + smallRadius || d < std::fabs(arcRadius - smallRadius) || d < EPS) {
        qDebug() << "No intersection: circles too far apart or contained";
        return result;
    }

    // 5. 计算中点与交点的距离 a 和 h
    double a = (smallRadius * smallRadius - arcRadius * arcRadius + d * d) / (2 * d);
    double hSquared = smallRadius * smallRadius - a * a;
    double h = std::sqrt(std::max(0.0, hSquared));
    qDebug() << "a:" << a << "h^2:" << hSquared << "h:" << h;

    // 6. P0 为从小圆心指向大圆心 a 距离的点
    double x0 = smallCenter.x() + a * (dx / d);
    double y0 = smallCenter.y() + a * (dy / d);
    qDebug() << "P0 (base point for perpendicular): (" << x0 << "," << y0 << ")";

    // 7. 垂直方向偏移（交点）
    double rx = -dy * (h / d);
    double ry =  dx * (h / d);

    QPointF p1(x0 + rx, y0 + ry);
    QPointF p2(x0 - rx, y0 - ry);
    qDebug() << "Intersection p1:" << p1;
    qDebug() << "Intersection p2:" << p2;

    // 判断哪个交点和 control 点在同一侧
    bool p1SameSide = isSameSideOfLine(arcStart, arcEnd, arcControl, p1);
    bool p2SameSide = isSameSideOfLine(arcStart, arcEnd, arcControl, p2);

    if (p1SameSide) {
        result.append(p1);
    } else if (p2SameSide) {
        result.append(p2);
    }


    qDebug() << "======== getArcAndCircleIntersection END ==========";
    return result;
}


bool mathTool::computeTransitionArc(const QPointF& start1, const QPointF& end1,
                                    const QPointF& start2, const QPointF& tran2, const QPointF& end2,
                                    double r, QPointF& t1, QPointF& control, QPointF& t2,bool isLine2arc)
{
    // ⭐ 保证线段方向统一为从圆弧方向切出
    QPointF s1 = start1;
    QPointF e1 = end1;

    if (start1 == end2) {
        s1 = end1;
        e1 = start1;
    }

    QPointF circleCenter = getCircleCenterFrom3Points(start2, tran2, end2);
    double angle = mathTool::angleBetweenVectors(e1, circleCenter, e1, s1);

    double newR;
    QLineF lineC;
    double circleR = std::hypot(circleCenter.x() - start2.x(), circleCenter.y() - start2.y());
    if (circleR < 0) return false;



    qDebug() << "angle*************************************************" << angle;
    qDebug() << "tran2*************************************************" << tran2;
    qDebug() << "end2*************************************************" << end2;
    qDebug() << "arcRadius*************************************************" << circleR;
    qDebug() << "smallRadius*************************************************" << r;
    if (angle < 90) {
        ArcCircleAnchor anchor = isLine2arc ? ArcCircleAnchor::Start : ArcCircleAnchor::End;

        QVector<QPointF>  directionPoint=getArcAndCircleIntersection(start2,tran2,end2,circleR,r,anchor);
        bool onLeft = isPointOnLeftSide(s1, e1, directionPoint[0]);
        qDebug() << "directionPoint[0]***************onLeft**********************************" << directionPoint[0]<<"  "<<onLeft;
        lineC = offsetLineSegment(s1, e1, r, onLeft);  // 向左偏移
        newR = (circleR - r);
    } else {
        ArcCircleAnchor anchor = isLine2arc ? ArcCircleAnchor::Start : ArcCircleAnchor::End;
        QVector<QPointF>  directionPoint=getArcAndCircleIntersection(start2,tran2,end2,circleR,r,anchor);
        bool onLeft = isPointOnLeftSide(s1, e1, directionPoint[0]);
        qDebug() << "directionPoint[0]***************onLeft**********************************" << directionPoint[0]<<"  "<<onLeft;
        lineC = offsetLineSegment(s1, e1, r, onLeft);
        newR = (circleR + r);
    }

    if (newR <= 0) return false;

    // 求圆心
    QPointF smoothCircleCenter;
    if (!intersectLineCircle(lineC, circleCenter, newR, smoothCircleCenter))
        return false;

    // t1：圆心到直线段的垂足
    t1 = projectToLine(smoothCircleCenter, s1, e1);

    // t2：从平滑圆心朝向原圆心方向，与原圆交点
    QPointF dir = smoothCircleCenter - circleCenter;
    //QLineF lineToCircle(circleCenter, circleCenter + dir * 1e8);
    QLineF lineToCircle(circleCenter, smoothCircleCenter+ dir * r);
    if (!intersectLineCircle(lineToCircle, circleCenter, circleR, t2))
        return false;

    // 控制点
    control=arcMidPoint(smoothCircleCenter,t1,t2);
    // 调试信息
    qDebug() << "smoothCircleCenter - circleCenter: " << dir;
    qDebug() << "lineC: " << lineC;
    qDebug() << "circleCenter: " << circleCenter;
    qDebug() << "smoothCircleCenter: " << smoothCircleCenter;
    qDebug() << "t1: " << t1;
    qDebug() << "control: " << control;
    qDebug() << "t2: " << t2;

    return true;
}

//_____________________________________________________________________________


enum ArcContainment {
    CONTAIN_NONE,
    CONTAIN_1_IN_2,
    CONTAIN_2_IN_1,
    CONTAIN_EQUAL
};

QPointF getCircleCenter(const QPointF& A, const QPointF& B, const QPointF& C) {
    double a1 = B.x() - A.x();
    double b1 = B.y() - A.y();
    double c1 = (a1 * (A.x() + B.x()) + b1 * (A.y() + B.y())) / 2.0;

    double a2 = C.x() - B.x();
    double b2 = C.y() - B.y();
    double c2 = (a2 * (B.x() + C.x()) + b2 * (B.y() + C.y())) / 2.0;

    double d = a1 * b2 - a2 * b1;
    if (std::abs(d) < 1e-6) {
        return QPointF(0, 0); // 三点共线，不构成圆
    }

    double x = (c1 * b2 - c2 * b1) / d;
    double y = (a1 * c2 - a2 * c1) / d;
    return QPointF(x, y);
}

double distance(const QPointF& p1, const QPointF& p2) {
    return std::hypot(p1.x() - p2.x(), p1.y() - p2.y());
}

double normalizeAngle(double angle) {
    while (angle < 0) angle += 2 * M_PI;
    while (angle >= 2 * M_PI) angle -= 2 * M_PI;
    return angle;
}

static bool isAngleOnArc(double theta, double start, double end) {
    theta = normalizeAngle(theta);
    start = normalizeAngle(start);
    end = normalizeAngle(end);
    if (start <= end)
        return (theta >= start && theta <= end);
    else
        return (theta >= start || theta <= end);
}

bool areAnyPointsOnArc1InsideArc2(const QPointF& start1, const QPointF& tran1, const QPointF& end1,
                                  double radius1,
                                  const QPointF& center2, double radius2) {
    if (radius1 <= 0 || radius2 <= 0) {
        qDebug() << "无效半径，返回 false";
        return false;
    }

    // 计算圆心
    QPointF center1 = getCircleCenter(start1, tran1, end1);
    qDebug() << "arc1 center:" << center1 << "radius:" << radius1;
    qDebug() << "arc1 start1:" << start1 << "  tran1:" << tran1 << " end1" << end1;
    qDebug() << "arc2 center:" << center2 << "radius2:" << radius2;

    // 起止角度
    QPointF vStart1 = start1 - center1;
    QPointF vEnd1   = end1   - center1;
    double thetaStart1 = normalizeAngle(std::atan2(vStart1.y(), vStart1.x()));
    double thetaEnd1   = normalizeAngle(std::atan2(vEnd1.y(), vEnd1.x()));
    double cross = vStart1.x() * vEnd1.y() - vStart1.y() * vEnd1.x();
    if (cross < 0) std::swap(thetaStart1, thetaEnd1);
    if (thetaEnd1 <= thetaStart1) thetaEnd1 += 2 * M_PI;

    // 判断控制点是否在当前弧段上
    QPointF vTran1 = tran1 - center1;
    double thetaT = normalizeAngle(std::atan2(vTran1.y(), vTran1.x()));
    double thetaS = thetaStart1;
    double thetaE = thetaEnd1;
    if (!(thetaT > thetaS && thetaT < thetaE)) {
        // 控制点不在当前采样弧段上，说明我们取错方向了，自动修正
        qDebug() << QString::fromLocal8Bit("⚠️ 控制点不在弧段上，自动反转采样方向");
        std::swap(thetaStart1, thetaEnd1);
        thetaStart1 = normalizeAngle(thetaStart1);
        thetaEnd1   = normalizeAngle(thetaEnd1);
        if (thetaEnd1 <= thetaStart1) thetaEnd1 += 2 * M_PI;
    }

    qDebug() << "arc1 angles: thetaStart1 =" << thetaStart1
             << ", thetaEnd1 =" << thetaEnd1 << ", cross =" << cross;

    // 采样
    // 根据圆弧长度动态采样
    double arcLength = radius1 * (thetaEnd1 - thetaStart1); // 弧长 = r × Δθ
    double sampleSpacing = 5.0; // 每隔 5 单位长度采一个点（可调）
    int steps = std::max(3, static_cast<int>(arcLength / sampleSpacing));
    qDebug() << QString::fromLocal8Bit("自动采样点数 steps = %1").arg(steps);

    for (int i = 1; i < steps; ++i) {
        double theta = thetaStart1 + (thetaEnd1 - thetaStart1) * i / steps;
        QPointF pt(center1.x() + radius1 * std::cos(theta),
                   center1.y() + radius1 * std::sin(theta));

        double dist = QLineF(pt, center2).length();

        qDebug() << QString::fromLocal8Bit("采样点 %1: pt=(%2, %3), dist(center2)=%4")
                    .arg(i).arg(pt.x()).arg(pt.y()).arg(dist);

        if (dist <= radius2 + 1e-4) {
            qDebug() << QString::fromLocal8Bit("✅ 采样点在圆2内，返回 true");
            return true;
        }
    }

    qDebug() << QString::fromLocal8Bit("❌ 没有采样点落入圆2内，返回 false");
    return false;
}




ArcContainment checkArcContainment(const QPointF& start1, const QPointF& tran1, const QPointF& end1,
                                   const QPointF& start2, const QPointF& tran2, const QPointF& end2,
                                   double r, QPointF& t1, QPointF& control, QPointF& t2) {
    Q_UNUSED(t1)
    Q_UNUSED(control)
    Q_UNUSED(t2)

    QPointF center1 = getCircleCenter(start1, tran1, end1);
    QPointF center2 = getCircleCenter(start2, tran2, end2);

    double radius1 = distance(center1, start1);
    double radius2 = distance(center2, start2);

    bool all1in2 = areAnyPointsOnArc1InsideArc2(start1, tran1, end1, radius1,center2,radius2);
    bool all2in1 = areAnyPointsOnArc1InsideArc2(start2, tran2, end2, radius2,center1,radius1);

    if (all1in2 && all2in1) {
        return CONTAIN_EQUAL;
    } else if (all1in2) {
        return CONTAIN_1_IN_2;
    } else if (all2in1) {
        return CONTAIN_2_IN_1;
    } else {
        return CONTAIN_NONE;
    }
}

bool getTangentPoint(const QPointF& center1, double r1,
                     const QPointF& center2, double r2,
                     QPointF& tangentPoint,
                     double epsilon = 1e-1) {
    double dx = center2.x() - center1.x();
    double dy = center2.y() - center1.y();
    double d = std::hypot(dx, dy);  // 计算两圆圆心距离

    qDebug() << QString::fromLocal8Bit("👉 圆1圆心：") << center1 << " r1 =" << r1;
    qDebug() << QString::fromLocal8Bit("👉 圆2圆心：") << center2 << " r2 =" << r2;
    qDebug() << QString::fromLocal8Bit("👉 向量 dx =") << dx << ", dy =" << dy;
    qDebug() << QString::fromLocal8Bit("👉 圆心距离 d =") << d;

    if (d < epsilon) {
        qDebug() << QString::fromLocal8Bit("❌ 圆心距离太近（认为重合），不存在唯一切点");
        return false;
    }

    // 外部相切：距离等于 r1 + r2
    if (std::abs(d - (r1 + r2)) < epsilon) {
        qDebug() << QString::fromLocal8Bit("✅ 外部相切：两圆外部接触，存在一个切点");
        double t = r1 / (r1 + r2);
        tangentPoint = QPointF(center1.x() + t * dx, center1.y() + t * dy);
        qDebug() << QString::fromLocal8Bit("📍 切点比例 t =") << t;
        qDebug() << QString::fromLocal8Bit("📍 切点坐标 =") << tangentPoint;
        return true;
    }

    // 内部相切：距离等于 |r1 - r2|
    if (std::abs(d - std::abs(r1 - r2)) < epsilon) {
        qDebug() << QString::fromLocal8Bit("✅ 内部相切：一圆在另一圆内部边缘接触，存在一个切点");
        if (std::abs(r1 - r2) < epsilon) {
            qDebug() << QString::fromLocal8Bit("⚠️ 半径相等，可能重合或分母为零，跳过计算");
            return false;
        }

        double t = r1 / (r1 - r2);
        tangentPoint = QPointF(center1.x() + t * dx, center1.y() + t * dy);
        qDebug() << QString::fromLocal8Bit("📍 切点比例 t =") << t;
        qDebug() << QString::fromLocal8Bit("📍 切点坐标 =") << tangentPoint;
        return true;
    }

    qDebug() << QString::fromLocal8Bit("r1 + r2 =") << r1 + r2
             << QString::fromLocal8Bit(" |r1 - r2| =") << std::abs(r1 - r2);
    qDebug() << QString::fromLocal8Bit("差值 |d - (r1 + r2)| =") << std::abs(d - (r1 + r2));
    qDebug() << QString::fromLocal8Bit("差值 |d - |r1 - r2|| =") << std::abs(d - std::abs(r1 - r2));


    qDebug() << QString::fromLocal8Bit("❌ 两圆既不外切也不内切，无唯一切点（可能相交或分离）");
    return false;
}

bool getCircleIntersections(const QPointF& center1, double r1,
                            const QPointF& center2, double r2,
                            QPointF& inter1, QPointF& inter2) {
    double dx = center2.x() - center1.x();
    double dy = center2.y() - center1.y();
    double d = std::hypot(dx, dy);

    // 圆心重合或无交点
    if (d < 1e-6 || d > r1 + r2 || d < std::abs(r1 - r2)) {
        return false;
    }

    // 中间点到两个圆心的距离 a
    double a = (r1*r1 - r2*r2 + d*d) / (2*d);
    double h = std::sqrt(std::max(0.0, r1*r1 - a*a));

    // 点 P2 是两圆连线上的交点基准
    double x2 = center1.x() + a * (dx / d);
    double y2 = center1.y() + a * (dy / d);

    // 正交方向向量
    double rx = -dy * (h / d);
    double ry =  dx * (h / d);

    // 两个交点
    inter1 = QPointF(x2 + rx, y2 + ry);
    inter2 = QPointF(x2 - rx, y2 - ry);

    return true;
}

bool mathTool::computeTransitionArcArc(const QPointF& start1,const QPointF& tran1, const QPointF& end1,
                                       const QPointF& start2, const QPointF& tran2, const QPointF& end2,
                                       double r, QPointF& t1, QPointF& control, QPointF& t2){

    QPointF center1 = getCircleCenter(start1, tran1, end1);
    QPointF center2 = getCircleCenter(start2, tran2, end2);
    QPointF center3;

    double radius1 = distance(center1, start1);
    double radius2 = distance(center2, start2);
    std::cout<< "radius1 "<<radius1<<"\n";
    std::cout<< "radius2 "<<radius2<<"\n";
    std::cout<< "r "<<r<<"\n";
    ArcContainment result = checkArcContainment(start1, tran1, end1, start2, tran2, end2, r, t1, control, t2);

    switch (result) {
    case CONTAIN_EQUAL: {
        std::cout<< "两个圆弧互相包含\n";
        radius1-=r;
        radius2-=r;
        QPointF p1, p2;

        getCircleIntersections(center1, radius1, center2, radius2, p1, p2);

        double d1 = std::hypot(p1.x() - end1.x(), p1.y() - end1.y());
        double d2 = std::hypot(p2.x() - end1.x(), p2.y() - end1.y());

        center3 = (d1 < d2) ? p1 : p2;
        getTangentPoint(center3, r, center1, radius1+=r, t1);
        getTangentPoint(center3, r, center2, radius2+=r, t2);

        control=arcMidPoint(center3,t1,t2);
        break;
    }


    case CONTAIN_1_IN_2:{
        std::cout << "圆弧1的三个点在圆弧2的完整圆范围内\n";
        radius1+=r;
        radius2-=r;
        QPointF p1, p2;

        getCircleIntersections(center1, radius1, center2, radius2, p1, p2);

        double d1 = std::hypot(p1.x() - end1.x(), p1.y() - end1.y());
        double d2 = std::hypot(p2.x() - end1.x(), p2.y() - end1.y());

        center3 = (d1 < d2) ? p1 : p2;
        getTangentPoint(center3, r, center1, radius1-=r, t1);
        getTangentPoint(center3, r, center2, radius2+=r, t2);

        control=arcMidPoint(center3,t2,t1);

        break;
    }

    case CONTAIN_2_IN_1:{
        std::cout << "圆弧2的三个点在圆弧1的完整圆范围内\n";
        radius1-=r;
        radius2+=r;
        QPointF p1, p2;

        getCircleIntersections(center1, radius1, center2, radius2, p1, p2);

        double d1 = std::hypot(p1.x() - end1.x(), p1.y() - end1.y());
        double d2 = std::hypot(p2.x() - end1.x(), p2.y() - end1.y());

        center3 = (d1 < d2) ? p1 : p2;
        getTangentPoint(center3, r, center1, radius1+=r, t1);
        getTangentPoint(center3, r, center2, radius2-=r, t2);

        control=arcMidPoint(center3,t2,t1);

        break;
    }


    case CONTAIN_NONE:
        std::cout << "两个圆弧的三点不在对方圆范围内\n";
        radius1+=r;
        radius2+=r;
        QPointF p1, p2;

        getCircleIntersections(center1, radius1, center2, radius2, p1, p2);

        double d1 = std::hypot(p1.x() - end1.x(), p1.y() - end1.y());
        double d2 = std::hypot(p2.x() - end1.x(), p2.y() - end1.y());

        center3 = (d1 < d2) ? p1 : p2;
        getTangentPoint(center3, r, center1, radius1-=r, t1);
        getTangentPoint(center3, r, center2, radius2-=r, t2);

        control=arcMidPoint(center3,t2,t1);

        break;
    }

    return  true;
}
//________________________________________________________________________________



// 判断角度a是否在角度区间[start, end)内，区间可跨0点
bool angleInRange(double a, double start, double end) {
    a = normalizeAngle(a);
    start = normalizeAngle(start);
    end = normalizeAngle(end);

    if (start < end)
        return a >= start && a < end;
    else  // 跨0点区间
        return a >= start || a < end;
}



QPointF getPointOnCircle(const QPointF& center, double radius, double angle) {
    return QPointF(center.x() + radius * qCos(angle),
                   center.y() + radius * qSin(angle));
}

QPointF mathTool::getReverseControlPoint(const QPointF& A_start, const QPointF& A_tran, const QPointF& A_end) {
    QPointF C = getCircleCenter(A_start, A_tran, A_end);
    if (C.isNull()) {
        qWarning() << "圆心计算失败";
        return QPointF();
    }

    double radius = std::hypot(A_start.x() - C.x(), A_start.y() - C.y());

    // 极角
    double angle_start = std::atan2(A_start.y() - C.y(), A_start.x() - C.x());
    double angle_end = std::atan2(A_end.y() - C.y(), A_end.x() - C.x());

    // 顺时针弧：从 angle_start 到 angle_end 的反方向
    double angle_diff = angle_end - angle_start;

    // 如果原弧是逆时针（差值为正，或跨越0点），我们取顺时针
    if (angle_diff > 0) {
        angle_diff = angle_diff - 2 * M_PI;
    }

    // 中间角度（在另一段弧方向上的中点）
    double mid_angle = angle_start + angle_diff / 2;

    // 得到圆上的控制点（弧的中点）
    QPointF A_tran_rev = getPointOnCircle(C, radius, mid_angle);

    return A_tran_rev;
}
