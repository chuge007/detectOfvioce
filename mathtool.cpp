#include "mathtool.h"
#include <QDebug>
#include <cmath>
#include <QtMath>

#include <QtCore>
#include <cmath>
#include <limits>

#define _USE_MATH_DEFINES
mathTool::mathTool()
{

}


bool mathTool::isDirectionSmooth(const QPointF& dir1, const QPointF& dir2, qreal angleTolDeg = 5.0)
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

//________________________________________________________

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

QPointF mathTool::computeControlPoint(const QPointF& t2, const QPointF& f, const QPointF& circleCenter,
                            const QLineF& lineC, double weir)
{
    // 方向向量 dir = t2 - circleCenter
    QPointF dir = t2 - circleCenter;
    qDebug() << "dir (t2 - circleCenter):" << dir;

    // 法线向量 normal，垂直于 dir，左旋90度
    QPointF normal(-dir.y(), dir.x());
    qDebug() << "normal (perpendicular to dir):" << normal;

    // lineC 两端点
    QPointF p1 = lineC.p1();
    QPointF p2 = lineC.p2();
    qDebug() << "lineC points p1:" << p1 << "p2:" << p2;

    // perpLine 两点，起点 t2，终点 t2 + normal * 任意大值，比如 1e6 使其成为长直线
    QPointF p3 = t2;
    QPointF p4 = t2 + normal * 1e6;
    qDebug() << "perpLine points p3:" << p3 << "p4:" << p4;

    // 计算交点
    QPointF P;
    if (!intersectInfiniteLinesByPoints(p1, p2, p3, p4, P)) {
        qDebug() << "No intersection found between lineC and perpLine";
        return QPointF(std::numeric_limits<double>::quiet_NaN(),
                       std::numeric_limits<double>::quiet_NaN());
    }

    qDebug()<<"intersectInfiniteLines p "<<P;
    QPointF fP = P - f;
    double lengthFP = std::hypot(fP.x(), fP.y());
    if (qFuzzyIsNull(lengthFP)) return QPointF();

    double t = weir / lengthFP;
    return f + fP * t;
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

QLineF mathTool::offsetLineSegment(const QPointF& A, const QPointF& B, const QPointF& circleCenter, double offsetR) {
    QPointF dir = B - A;
    dir /= std::hypot(dir.x(), dir.y());
    QPointF normal(-dir.y(), dir.x());

    QPointF mid = (A + B) / 2.0;
    QPointF toCenter = circleCenter - mid;
    if (QPointF::dotProduct(toCenter, normal) < 0)
        normal = -normal;

    QPointF offset = normal * offsetR;
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

QPointF mathTool::projectToLine(const QPointF& P, const QPointF& A, const QPointF& B) {
    QPointF AB = B - A;
    double t = QPointF::dotProduct(P - A, AB) / QPointF::dotProduct(AB, AB);
    return A + AB * t;
}

// ---------- 主函数：返回三点构成圆弧 ---------------
bool mathTool::computeTransitionArc(const QPointF& start1, const QPointF& end1,
                                    const QPointF& start2, const QPointF& tran2, const QPointF& end2,
                                    double r, QPointF& t1, QPointF& control, QPointF& t2)
{

    QPointF circleCenter =getCircleCenterFrom3Points(start2, tran2, end2);

    double R = std::hypot(circleCenter.x() - start2.x(), circleCenter.y() - start2.y());
    if (R < 0) return false;

    qDebug()<<"circleCenter  "<<circleCenter;

    qDebug()<<"R  "<<circleCenter;
    bool intersect = isSegmentIntersectCircle(start1, end1, circleCenter, R);
    double newR = intersect ? (R - r) : (R + r);
    if (newR <= 0) return false;

    qDebug()<<"intersect  "<<intersect;
    // 偏移直线段
    QLineF lineC = offsetLineSegment(start1, end1, circleCenter, r);

    qDebug()<<"lineC  "<<lineC;
    // 求交点
    QPointF f;
    if (!intersectLineCircle(lineC, circleCenter, newR, f))
        return false;


    qDebug()<<"intersectLineCircle  "<<f;
    // 得到 t1: f 到线段a 的垂足
    t1 = projectToLine(f, start1, end1);

    // 得到 t2: f → 圆心方向 与圆b的交点
    QPointF dir = f-circleCenter;
    qDebug()<<"dir  "<<dir;

    QLineF lineToCircle(circleCenter,  dir * 1e8);
    if (!intersectLineCircle(lineToCircle, circleCenter, R, t2))
        return false;

    // 控制点为圆心方向外凸点（中间）
   QLineF lineS=extendLineFromPoint(start1, start2, 1e6);
   control = computeControlPoint(t2, f, circleCenter, lineS, r);

    qDebug()<<"t1  "<<t1;
    qDebug()<<"control  "<<control;
    qDebug()<<"t2  "<<t2;
    return true;
}
