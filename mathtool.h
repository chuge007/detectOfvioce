#ifndef MATHTOOL_H
#define MATHTOOL_H

#include <QPointF>
#include <QLineF>
#include <cmath>
#include <vector>
#include <cmath>    // For std::hypot, std::copysign, std::sqrt, std::abs
#include <string>
#include <algorithm> // For std::max
#include <iostream>  // For example usage output

#define M_PI 3.14159265358979323846
// 圆弧插入结果结构体
struct ArcInsertResult {
    QPointF q0;           // 圆弧起点
    QPointF q2;           // 圆弧终点
    QPointF Transition;   // 圆弧上的过渡点（可用于绘图或路径插值）
    qreal radius;         // 圆弧半径
};


constexpr double EPSILON = 1e-9;


class mathTool
{
public:
    mathTool();

    // 判断两个方向是否平滑（夹角在一定容差内）
    bool isDirectionSmooth(const QPointF& dir1, const QPointF& dir2, qreal angleTolDeg);

    // 求圆上某点的切线方向（默认逆时针）
    QPointF getArcTangentAtPoint(const QPointF& center, const QPointF& pt);

    // 通过三点计算圆心
    QPointF getCircleCenterFrom3Points(const QPointF& A, const QPointF& B, const QPointF& C);

    // 平滑过渡圆弧计算
    bool computeSmoothArc(QPointF start1, QPointF end1,
                          QPointF start2, QPointF end2,
                          qreal smoothFactor,
                          struct ArcInsertResult& result);

    template<typename T>
    T clamp(T value, T minVal, T maxVal);

    //________________________________________________________

    QLineF extendLineFromPoint(const QPointF& start1, const QPointF& start2, double extendLength);

    bool intersectInfiniteLinesByPoints(const QPointF& p1, const QPointF& p2,
                                        const QPointF& p3, const QPointF& p4,
                                        QPointF& intersection);
    double angleBetweenVectors(const QPointF& from1, const QPointF& to1,
                               const QPointF& from2, const QPointF& to2);

    QPointF computeControlPoint(const QPointF& t2, const QPointF& f, const QPointF& circleCenter,
                                const QLineF& lineC, double weir);

    // 判断线段是否与圆相交
    bool isSegmentIntersectCircle(const QPointF& A, const QPointF& B, const QPointF& center, double R);

    // 将线段向法线方向偏移指定半径
    QLineF offsetLineSegment(const QPointF& A, const QPointF& B, const QPointF& circleCenter, double offsetR, bool towardCenter);

    // 求直线与圆的交点（取较近或精度内匹配的交点）
    bool intersectLineCircle(const QLineF& line, const QPointF& center, double radius, QPointF& result);

    // 点到线段的投影（垂足）
    QPointF projectToLine(const QPointF& P, const QPointF& A, const QPointF& B);

    // 主函数：计算三点圆弧过渡
    bool computeTransitionArc(const QPointF& start1, const QPointF& end1,
                              const QPointF& start2, const QPointF& tran2, const QPointF& end2,
                              double r, QPointF& t1, QPointF& control, QPointF& t2);
    //___________________________________________________________________________




    struct PointF {
        double x, y;
        PointF(double x_val = 0.0, double y_val = 0.0) : x(x_val), y(y_val) {}

        PointF operator+(const PointF& other) const { return PointF(x + other.x, y + other.y); }
        PointF operator-(const PointF& other) const { return PointF(x - other.x, y - other.y); }
        PointF operator*(double scalar) const { return PointF(x * scalar, y * scalar); }
        double length() const { return std::hypot(x, y); }
        PointF normalized() const {
            double len = length();
            return (len > EPSILON) ? PointF(x / len, y / len) : PointF(0.0, 0.0);
        }
    };


    // 用于存储圆的信息`
    struct CircleInfo {
        PointF center;
        double radius;
        bool isValid; // 指示是否找到有效圆
    };

    // 用于存储相切圆弧的解决方案
    struct TangentArcSolution {
        PointF center;
        double radius;
        std::string line_offset_side;    // 例如 "与圆弧b同侧" 或 "与圆弧b异侧"
        std::string arc_tangency_type;   // 例如 "外切" 或 "内切"
        PointF tangent_point_line;       // 相切圆弧 'c' 与直线 'a' 的切点 (作为圆弧 'c' 的起点)
        PointF tangent_point_arc;        // 相切圆弧 'c' 与圆弧 'b' 的切点 (作为圆弧 'c' 的终点)
        PointF control_point_arc_c;      // 相切圆弧 'c' 的控制点 (例如，圆弧中点)
    };


    CircleInfo findCircleFromThreePoints(const PointF& p1, const PointF& p2, const PointF& p3);

    std::vector<mathTool::TangentArcSolution> calculateTangentArcCSolutions(
        const PointF& line_start, const PointF& line_end,
        const PointF& arc_b_p1, const PointF& arc_b_p2, const PointF& arc_b_p3,
        double R_c);
};



#endif // MATHTOOL_H
