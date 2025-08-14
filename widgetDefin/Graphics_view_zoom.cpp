#include "Graphics_view_zoom.h"
#include <QMouseEvent>
#include <QApplication>
#include <QScrollBar>
#include <qmath.h>
#include <QDebug>

void Graphics_view_zoom::mouseReleaseEvent(QMouseEvent *event)
{
    Q_UNUSED(event)

}

void Graphics_view_zoom::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
}

void Graphics_view_zoom::enterEvent(QEvent *event)
{
    Q_UNUSED(event)

}

Graphics_view_zoom::Graphics_view_zoom(QGraphicsView* view)
    : QObject(view), _view(view)
{
    _view->viewport()->installEventFilter(this);
    _view->setMouseTracking(true);
    _modifiers = Qt::ControlModifier;
    _zoom_factor_base = 1.04427;
    pt_startstop_flag = false;
}

void Graphics_view_zoom::gentle_zoom(double factor)
{
    if( _view->scene()->backgroundBrush().isOpaque() )
    {
        double viewfactor = sqrt(_view->transform().det());//qDebug()<<"gentle_zoom****viewfactor="<<viewfactor<<"factor="<<factor;

        //qDebug()<<"_view->scene()->BackgroundLayer" <<_view->scene()->backgroundBrush().isOpaque();

        if( ( viewfactor > 25  && factor < 1.0)  || ( (viewfactor < 0.04 ) && (factor > 1.0 )) || (viewfactor < 25 && (viewfactor > 0.04) ) )
        {
            _view->scale(factor, factor);
            _view->centerOn(target_scene_pos);
            QPointF delta_viewport_pos = target_viewport_pos - QPointF(_view->viewport()->width() / 2.0,
                                                                       _view->viewport()->height() / 2.0);
            QPointF viewport_center = _view->mapFromScene(target_scene_pos) - delta_viewport_pos;
            _view->centerOn(_view->mapToScene(viewport_center.toPoint()));
            emit zoomed();
        }
    }

}

void Graphics_view_zoom::set_modifiers(Qt::KeyboardModifiers modifiers) {

    _modifiers = modifiers;
}

void Graphics_view_zoom::set_zoom_factor_base(double value) {
    _zoom_factor_base = value;
}

bool Graphics_view_zoom::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress){
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            PressMs=true;
            emit seleft();
        }
    }else if(event->type() == QEvent::MouseButtonRelease){
        QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
        if (mouseEvent->button() == Qt::LeftButton) {
            PressMs=false;
            emit seleft();
        }
    }

    if (event->type() == QEvent::MouseMove)
    {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        QPointF delta = target_viewport_pos - mouse_event->pos();
        if (qAbs(delta.x()) > 5 || qAbs(delta.y()) > 5)
        {
            target_viewport_pos = mouse_event->pos();
            target_scene_pos = _view->mapToScene(mouse_event->pos());
        }
        if (mouse_event->buttons() & Qt::MidButton)//RightButton
        {
            QPointF pt = _view->mapToScene ( mouse_event->pos() );
            QPointF offset = pt - start_move_pos;
            QPoint viewCenter (_view->viewport()->width()/2, _view->viewport()->height()/2);
            QPointF sceneCenter = _view->mapToScene(viewCenter);
            QPointF target = sceneCenter - offset;
            _view->centerOn(target);
            return true;
        }

        if(PressMs){
            emit graphhicsPos(target_scene_pos.x(),target_scene_pos.y());
            //qDebug()<<"emit graphhicsPos(target_scene_pos.x(),target_scene_pos.y());"<<PressMs;
        }

    }
    else if (event->type() == QEvent::Wheel)
    {
        QWheelEvent* wheel_event = static_cast<QWheelEvent*>(event);
        if (QApplication::keyboardModifiers() == _modifiers)
        {
            if (wheel_event->orientation() == Qt::Vertical)
            {
                double angle = wheel_event->delta()/16;//  delta().y();
                double factor = qPow(_zoom_factor_base, angle);
                gentle_zoom(factor);
                return true;
            }
        }
    }
    else if(event->type() == QEvent::MouseButtonRelease)
    {
        {
            _view->setCursor(Qt::ArrowCursor);

        }
    }
    else if((event->type() == QEvent::MouseButtonPress) )
    {
        QMouseEvent* mouse_event = static_cast<QMouseEvent*>(event);
        if(mouse_event->buttons() & Qt::MidButton)//RightButton
        {
            _view->setCursor(Qt::OpenHandCursor);
            start_move_pos = _view->mapToScene ( mouse_event->pos() );;
        }
    }
    Q_UNUSED(object)
    return false;
}
