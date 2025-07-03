#ifndef MATHTOOL_H
#define MATHTOOL_H

#include <QPointF>
#include <QLineF>
#include <cmath>



// 圆弧插入结果结构体
struct ArcInsertResult {
    QPointF q0;           // 圆弧起点
    QPointF q2;           // 圆弧终点
    QPointF Transition;   // 圆弧上的过渡点（可用于绘图或路径插值）
    qreal radius;         // 圆弧半径
};

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

};



#endif // MATHTOOL_H
