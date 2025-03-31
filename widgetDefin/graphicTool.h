/****************************************************************************
**
** FreeSCH - Free SCHematic drawing program for electronic circuits.
**
** Copyright 2012 Warren Free
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of version 2 of the GNU General Public
** License as published by the Free Software Foundation.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>
**
****************************************************************************/
#ifndef LINE_ITEM_H
#define LINE_ITEM_H

#include <QGraphicsItem>
#include "route_worksence.h"




class line_item : public QGraphicsItem
{
public:
    line_item(const QPointF& startPosition, const QPointF& endPosition ,int sort_vaule,route_worksence *parent = 0 );
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    int _sortNum;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent( QGraphicsSceneHoverEvent*event);

protected:
    QPointF _end,_start;

    float imgbg_scale_f ,arrow_length ;

private:
    QRectF shape_rect;
    bool is_hover;
};



#endif // LINE_ITEM_H


/****************************************************************************
**
** FreeSCH - Free SCHematic drawing program for electronic circuits.
**
** Copyright 2012 Warren Free
**
** This program is free software; you can redistribute it and/or
** modify it under the terms of version 2 of the GNU General Public
** License as published by the Free Software Foundation.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, see <http://www.gnu.org/licenses/>
**
****************************************************************************/
#ifndef ARC_ITEM_H
#define ARC_ITEM_H

#include <QGraphicsItem>
#include "route_worksence.h"



class arc_item : public QGraphicsItem
{
public:
    arc_item(const QPointF& startPosition, const QPointF& transPosition , const QPointF& endPosition ,int sortValue,route_worksence *parent = 0 );
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;
    QPainterPath shape() const;
    int _sortNum;

    void mousePressEvent(QGraphicsSceneMouseEvent *event) ;
    void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
    void hoverLeaveEvent( QGraphicsSceneHoverEvent*event);

protected:
    QPointF _end,_start,_trans;
    float imgbg_scale_f ,arrow_length ;

private:
    bool is_hover;
     QRectF get_rect ;
};



#endif // LINE_ITEM_H
