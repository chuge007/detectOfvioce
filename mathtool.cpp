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

QLineF mathTool::offsetLineSegment(const QPointF& A, const QPointF& B, const QPointF& circleCenter, double offsetR, bool towardCenter)
{
    QPointF dir = B - A;
    dir /= std::hypot(dir.x(), dir.y());  // 单位方向向量

    QPointF normal(-dir.y(), dir.x());    // 左旋90°得到垂直向量

    QPointF mid = (A + B) / 2.0;
    QPointF toCenter = circleCenter - mid;

    bool isToward = (QPointF::dotProduct(toCenter, normal) >= 0);

    // 如果用户要求朝向圆心（默认），但当前方向不是朝向圆心，则反转
    // 如果用户要求远离圆心，但当前方向是朝向圆心，也反转
    if (isToward != towardCenter) {
        normal = -normal;
    }

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

// ---------- 主函数：返回三点构成圆弧 ---------------
bool mathTool::computeTransitionArc(const QPointF& start1, const QPointF& end1,
                                    const QPointF& start2, const QPointF& tran2, const QPointF& end2,
                                    double r, QPointF& t1, QPointF& control, QPointF& t2)
{

    QPointF circleCenter =getCircleCenterFrom3Points(start2, tran2, end2);
    double angle = mathTool::angleBetweenVectors(end1, circleCenter, end1, start1);

    qDebug()<<"angle"<<angle;
    double newR;
    QLineF lineC;
    double circleR = std::hypot(circleCenter.x() - start2.x(), circleCenter.y() - start2.y());

    if (circleR < 0) return false;
    if(angle<90){

        bool intersect = isSegmentIntersectCircle(start1, end1, circleCenter, circleR);
        newR = intersect ? (circleR - r) : (circleR + r);
        if (newR <= 0) return false;

        lineC = offsetLineSegment(start1, end1, circleCenter, r,true);

    }else {
        bool intersect = isSegmentIntersectCircle(start1, end1, circleCenter, circleR);
        newR = intersect ? (circleR + r) : (circleR - r);
        if (newR <= 0) return false;

        lineC = offsetLineSegment(start1, end1, circleCenter, r,false);
    }


    // 求交点
    QPointF smoothCircleCenter;
    if (!intersectLineCircle(lineC, circleCenter, newR, smoothCircleCenter))
        return false;


    // 得到 t1: f 到线段a 的垂足
    t1 = projectToLine(smoothCircleCenter, start1, end1);

    // 得到 t2: f → 圆心方向 与圆b的交点
    QPointF dir = smoothCircleCenter-circleCenter;


    QLineF lineToCircle(circleCenter,  dir * 1e8);
    if (!intersectLineCircle(lineToCircle, circleCenter, circleR, t2))
        return false;

    // 控制点为圆心方向外凸点（中间）
    QLineF lineS=extendLineFromPoint(start1, start2, 1e6);

    control = computeControlPoint(t2, smoothCircleCenter, circleCenter, lineS, r);

   qDebug()<<"smoothCircleCenter-circleCenter  "<<dir;

    qDebug()<<"lineC  "<<lineC;

    qDebug()<<"circleCenter  "<<circleCenter;

    qDebug()<<"intersectLineCircle  "<<smoothCircleCenter;

    qDebug()<<"t1  "<<t1;

    qDebug()<<"control  "<<control;

    qDebug()<<"t2  "<<t2;
    return true;
}
//____________________________________________________________________________________________________________________________


mathTool::CircleInfo mathTool::findCircleFromThreePoints(const PointF& p1, const PointF& p2, const PointF& p3) {
    double x1 = p1.x, y1 = p1.y;
    double x2 = p2.x, y2 = p2.y;
    double x3 = p3.x, y3 = p3.y;

    // 使用叉积（三角形面积的两倍）检查共线性
    double collinearity_check = (x2 - x1) * (y3 - y1) - (x3 - x1) * (y2 - y1);
    if (std::abs(collinearity_check) < EPSILON) { // 点共线
        return CircleInfo{PointF(), 0.0, false};
    }

    // 线性方程组的系数，用于求解 2g 和 2f
    // Eq A: 2g(x1 - x2) + 2f(y1 - y2) = (x2^2 + y2^2) - (x1^2 + y1^2)
    double A_coeff1 = 2 * (x1 - x2);
    double B_coeff1 = 2 * (y1 - y2);
    double C_const1 = (x2*x2 + y2*y2) - (x1*x1 + y1*y1);

    // Eq B: 2g(x2 - x3) + 2f(y2 - y3) = (x3^2 + y3^2) - (x2^2 + y2^2)
    double A_coeff2 = 2 * (x2 - x3);
    double B_coeff2 = 2 * (y2 - y3);
    double C_const2 = (x3*x3 + y3*y3) - (x2*x2 + y2*y2);

    // 使用克莱默法则求解 2x2 线性系统
    double det = A_coeff1 * B_coeff2 - A_coeff2 * B_coeff1;
    if (std::abs(det) < EPSILON) { // 鲁棒性检查，应已被共线性检查捕获
        return CircleInfo{PointF(), 0.0, false};
    }

    double _2g = (B_coeff1 * C_const2 - B_coeff2 * C_const1) / det;
    double _2f = (A_coeff2 * C_const1 - A_coeff1 * C_const2) / det;

    double center_x = -_2g / 2.0;
    double center_y = -_2f / 2.0;

    // 从一般圆方程 x^2 + y^2 + 2gx + 2fy + c = 0 找到 c
    // c = -(x1^2 + y1^2 + 2gx1 + 2fy1)
    double c = -(x1*x1 + y1*y1 + _2g * x1 + _2f * y1);

    // 半径平方 = g^2 + f^2 - c
    double radius_sq = (center_x*center_x + center_y*center_y) - c;

    if (radius_sq < -EPSILON) { // 允许浮点精度导致的微小负值
        return CircleInfo{PointF(), 0.0, false}; // 没有实际的圆
    }

    double radius = std::sqrt(std::max(0.0, radius_sq)); // 确保非负值以进行平方根运算
    return CircleInfo{PointF(center_x, center_y), radius, true};
}



std::vector<mathTool::TangentArcSolution> mathTool::calculateTangentArcCSolutions(
    const PointF& line_start, const PointF& line_end,
    const PointF& arc_b_p1, const PointF& arc_b_p2, const PointF& arc_b_p3,
    double R_c) {


    std::vector<TangentArcSolution> solutions;

    // 1. 确定直线 'a' 的方程 (Ax + By + C = 0)
    // A = y2 - y1
    // B = x1 - x2
    // C = -A*x1 - B*y1
    double A_line = line_end.y - line_start.y;
    double B_line = line_start.x - line_end.x;
    double C_line = -A_line * line_start.x - B_line * line_start.y;

    // 归一化直线 'a' 的系数
    double K = std::hypot(A_line, B_line);
    if (K < EPSILON) { // 直线是点，输入无效
        return solutions;
    }
    double A_u = A_line / K;
    double B_u = B_line / K;
    double C_u = C_line / K;

    // 2. 确定圆弧 'b' 的圆心和半径
    CircleInfo arc_b_info = findCircleFromThreePoints(arc_b_p1, arc_b_p2, arc_b_p3);
    if (!arc_b_info.isValid) { // 圆弧 'b' 的点共线或无效
        return solutions;
    }
    PointF C_b = arc_b_info.center;
    double R_b = arc_b_info.radius;

    // 3. 计算 C_b 到直线 'a' 的有符号距离
    double S_val_b = A_u * C_b.x + B_u * C_b.y + C_u;

    // 确定偏移直线的配置 (圆弧 'c' 的圆心将位于其上)
    // 使用 std::copysign 确保即使 S_val_b 接近零也能得到正确的符号
    // 如果 S_val_b 接近零，默认使用正向偏移，这在几何上通常意味着选择一个任意侧
    double sign_S_val_b = (std::abs(S_val_b) > EPSILON)? std::copysign(1.0, S_val_b) : 1.0;

    std::vector<std::pair<double, std::string>> offset_line_configs;
    // 选项 A：同侧相切
    offset_line_configs.push_back({C_u - sign_S_val_b * R_c, "与圆弧b同侧"});
    // 选项 B：异侧相切
    offset_line_configs.push_back({C_u + sign_S_val_b * R_c, "与圆弧b异侧"});

    // 确定相切圆弧 'c' 与圆弧 'b' 的相切类型
    std::vector<std::pair<double, std::string>> arc_tangency_configs;
    // 选项 A：外切
    arc_tangency_configs.push_back({R_b + R_c, "外切"});
    // 选项 B：内切
    arc_tangency_configs.push_back({std::abs(R_b - R_c), "内切"});

    // 遍历所有 4 种组合 (偏移直线类型 x 相切类型)
    for (const auto& line_config : offset_line_configs) {
        double C_offset = line_config.first;
        std::string line_offset_side = line_config.second;

        for (const auto& arc_config : arc_tangency_configs) {
            double R_b_prime = arc_config.first;
            std::string arc_tangency_type = arc_config.second;

            // 特殊情况：内切且 R_b == R_c，此时 R_b_prime 为 0，C_c 必须与 C_b 重合
            if (arc_tangency_type == "内切" && std::abs(R_b_prime) < EPSILON) {
                // 检查 C_b 是否位于偏移直线上
                if (std::abs(A_u * C_b.x + B_u * C_b.y + C_offset) < EPSILON) {
                    PointF C_c = C_b; // 圆心 C_c 与 C_b 重合

                    // 计算相切点和控制点
                    // 切点与直线 'a' (作为圆弧 'c' 的起点)
                    double d_cc_to_line_a = A_u * C_c.x + B_u * C_c.y + C_u;
                    PointF tangent_point_line(C_c.x - d_cc_to_line_a * A_u,
                                                  C_c.y - d_cc_to_line_a * B_u);

                    // 切点与圆弧 'b' (作为圆弧 'c' 的终点)
                    // 当 R_b = R_c 且内切时，圆弧 c 与圆弧 b 完全重合。
                    // 此时切点可以认为是圆弧 b 上的任意一点。
                    // 为了与输入保持一致，我们使用 arc_b_p1 投影到圆弧 b 的圆周上作为切点。
                    PointF tangent_point_arc = C_b + (arc_b_p1 - C_b).normalized() * R_b;

                    // 控制点 for arc c (作为圆弧 'c' 的控制点)
                    // 如果圆弧 c 与圆弧 b 重合，则可以使用圆弧 b 的控制点 arc_b_p2
                    PointF control_point_arc_c = arc_b_p2;

                    solutions.push_back({C_c, R_c, line_offset_side, arc_tangency_type,
                                        tangent_point_line, tangent_point_arc, control_point_arc_c});
                }
                continue;
            }

            std::vector<PointF> current_C_c_candidates;

            if (std::abs(B_u) > EPSILON) { // 直线不是垂直的，以 x 为变量求解
                double a_quad = 1.0;
                double b_quad = -2 * C_b.x * B_u*B_u + 2 * A_u * (C_offset + B_u * C_b.y);
                double c_quad = C_b.x*C_b.x * B_u*B_u + (C_offset + B_u * C_b.y)*(C_offset + B_u * C_b.y) - R_b_prime*R_b_prime * B_u*B_u;

                double discriminant = b_quad*b_quad - 4 * a_quad * c_quad;

                if (discriminant >= -EPSILON) {
                    if (discriminant < 0) discriminant = 0;

                    double sqrt_discriminant = std::sqrt(discriminant);

                    double x_sol1 = (-b_quad + sqrt_discriminant) / (2 * a_quad);
                    double y_sol1 = (-A_u * x_sol1 - C_offset) / B_u;
                    current_C_c_candidates.push_back(PointF(x_sol1, y_sol1));

                    if (discriminant > EPSILON) {
                        double x_sol2 = (-b_quad - sqrt_discriminant) / (2 * a_quad);
                        double y_sol2 = (-A_u * x_sol2 - C_offset) / B_u;
                        current_C_c_candidates.push_back(PointF(x_sol2, y_sol2));
                    }
                }
            } else if (std::abs(A_u) > EPSILON) { // 直线是垂直的，以 y 为变量求解 (x = -C_offset / A_u)
                double x_fixed = -C_offset / A_u;

                double rhs_sq = R_b_prime*R_b_prime - (x_fixed - C_b.x)*(x_fixed - C_b.x);

                if (rhs_sq >= -EPSILON) {
                    if (rhs_sq < 0) rhs_sq = 0;

                    double sqrt_rhs = std::sqrt(rhs_sq);

                    double y_sol1 = C_b.y + sqrt_rhs;
                    current_C_c_candidates.push_back(PointF(x_fixed, y_sol1));

                    if (rhs_sq > EPSILON) {
                        double y_sol2 = C_b.y - sqrt_rhs;
                        current_C_c_candidates.push_back(PointF(x_fixed, y_sol2));
                    }
                }
            } else { // A_u 和 B_u 都为零，直线无效
                continue;
            }

            for (const auto& C_c : current_C_c_candidates) {
                // 计算相切圆弧 'c' 与直线 'a' 的切点 (tangent_point_line)
                // 切点是圆心 C_c 到直线 'a' 的投影点
                double d_cc_to_line_a = A_u * C_c.x + B_u * C_c.y + C_u;
                PointF tangent_point_line_val(C_c.x - d_cc_to_line_a * A_u,
                                              C_c.y - d_cc_to_line_a * B_u);

                // 计算相切圆弧 'c' 与圆弧 'b' 的切点 (tangent_point_arc)
                PointF tangent_point_arc_val;
                PointF vec_Cb_to_Cc = C_c - C_b;
                double dist_Cb_Cc = vec_Cb_to_Cc.length();

                if (dist_Cb_Cc < EPSILON) { // C_c 和 C_b 重合，通常发生在 R_b_prime = 0 的特殊情况，但这里是通用处理
                    // 理论上不应该进入这里，因为 R_b_prime=0 的情况已在前面处理
                    // 如果进入，表示 R_b_prime!= 0 但 C_c == C_b，这是矛盾的
                    // 此时切点不明确，可以返回错误或选择一个默认点
                    tangent_point_arc_val = C_b; // 默认值，表示异常情况
                } else {
                    // 切点 P_b 位于 C_b 和 C_c 连线上，距离 C_b 为 R_b
                    tangent_point_arc_val = C_b + vec_Cb_to_Cc.normalized() * R_b;
                }

                // 计算相切圆弧 'c' 的控制点 (control_point_arc_c)
                // 假设控制点是切点 tangent_point_line 和 tangent_point_arc 之间的圆弧中点
                PointF control_point_arc_c_val;
                PointF vec_Cc_to_Pa = tangent_point_line_val - C_c;
                PointF vec_Cc_to_Pb = tangent_point_arc_val - C_c;

                double angle_Pa = std::atan2(vec_Cc_to_Pa.y, vec_Cc_to_Pa.x);
                double angle_Pb = std::atan2(vec_Cc_to_Pb.y, vec_Cc_to_Pb.x);

                // 调整角度，确保选择的是劣弧（角度差最小的弧）的中点
                double angle_diff = angle_Pb - angle_Pa;
                // Normalize angle_diff to be in (-PI, PI]
                while (angle_diff <= -M_PI) angle_diff += 2 * M_PI;
                while (angle_diff > M_PI) angle_diff -= 2 * M_PI;

                double mid_angle = angle_Pa + angle_diff / 2.0;

                control_point_arc_c_val.x = C_c.x + R_c * std::cos(mid_angle);
                control_point_arc_c_val.y = C_c.y + R_c * std::sin(mid_angle);

                solutions.push_back({C_c, R_c, line_offset_side, arc_tangency_type,
                                    tangent_point_line_val, tangent_point_arc_val, control_point_arc_c_val});
            }
        }
        return solutions;
    }
}



