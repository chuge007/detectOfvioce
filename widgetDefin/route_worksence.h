#ifndef ROUTE_WORKSENCE
#define ROUTE_WORKSENCE
#include <QGraphicsScene>

class route_worksence : public QGraphicsScene
{
    Q_OBJECT
public:
    route_worksence(QObject *parent = 0);
    QRectF  oneimg_theRect;
    float imgbg_scale_f;
    bool set_point_text_visable;

signals:

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);
    int bytesToInt(QByteArray bytes);

    virtual void  drawBackground (QPainter *painter, const QRectF &rect);
private:

};
#endif // ROUTE_WORKSENCE

