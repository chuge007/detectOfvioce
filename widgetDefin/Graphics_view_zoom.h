#ifndef GRAPHICS_VIEW_ZOOM_H
#define GRAPHICS_VIEW_ZOOM_H

#include <QObject>
#include <QGraphicsView>

class Graphics_view_zoom : public QObject {
  Q_OBJECT
public:
  Graphics_view_zoom(QGraphicsView* view);
  void gentle_zoom(double factor);
  void set_modifiers(Qt::KeyboardModifiers modifiers);
  void set_zoom_factor_base(double value);
  bool pt_startstop_flag;
  QPointF target_scene_pos;

protected:
    //void enterEvent(QEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent ( QEvent * event );


private:
  bool   PressMs;
  QGraphicsView* _view;
  Qt::KeyboardModifiers _modifiers;
  double _zoom_factor_base;
  QPointF target_viewport_pos,start_move_pos;
  bool eventFilter(QObject* object, QEvent* event);

signals:
  void zoomed();
  void seleft();
  void graphhicsPos(double x, double y);
};

#endif // GRAPHICS_VIEW_ZOOM_H
