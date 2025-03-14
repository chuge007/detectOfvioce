/***************************************************************************
 *   copyright       : (C) 2003-2007 by Pascal Brachet                     *
 *   http://www.xm1math.net/texmaker/                                      *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include <QtGui>
//#include <QAbstractItemModel>
//#include <QPainter>
#include <QApplication>
#include "icondelegate.h"

void IconDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const{

    QByteArray value = index.data(Qt::DisplayRole) .toByteArray() ;
    QPixmap p;
    if(value.isNull())
    {
        QStyledItemDelegate::paint(painter, option, index);
        return;
    }
    else
    {
        // qDebug()<<index.data(Qt::DisplayRole).toByteArray();
        p.loadFromData( value ,"PNG");
    }
    if ((option.state & QStyle::State_Selected ) )
    {
#ifdef Q_OS_LINUX  /*Q_OS_LINUX 的显示不激活时仍高亮 */
           painter->fillRect(option.rect, option.palette.highlight());
#else
        if(option.state & QStyle::State_Active)
        {
            painter->fillRect(option.rect, option.palette.highlight());
        }
        else
        {
            painter->fillRect(option.rect, option.palette.background());
        }
#endif
    }
    if(!p.isNull())
    {
        QPixmap scaledPixmap = p.scaled(option.rect.size(), Qt::KeepAspectRatio);//按比例缩放:
        QApplication::style()->drawItemPixmap(painter,option.rect,Qt::AlignHCenter,scaledPixmap );
    }
}

QSize IconDelegate::sizeHint(const QStyleOptionViewItem &option,
                              const QModelIndex &/*index*/) const
{
    return option.rect.size();//(pixmapRect).size();
}
/*
bool IconDelegate::editorEvent(QEvent *event, QAbstractItemModel *, const QStyleOptionViewItem &, const QModelIndex &index)
{
    if (event->type() == QEvent::MouseButtonDblClick)
    {
        emit usericon_press(index);
        return true;
    }
    else
    return false;
}
*/

