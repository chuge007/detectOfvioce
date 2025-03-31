#include <QApplication>
#include <QPainter>
#include "floatpointdelegate.h"

void floatpointdelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const
{

    double value = index.data(Qt::DisplayRole).toDouble() ;
     QModelIndex  index_dnormal = index.model()->index(index.row(),12);///////////////////////?????
   // // double d_nornaml = index_dnormal.data(Qt::DisplayRole).toDouble() ; /*后续在次格显示合格范围用 */


    if ((option.state & QStyle::State_Selected ) )
    {
#ifdef Q_OS_LINUX
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


    QApplication::style()->drawItemText(painter,option.rect,Qt::AlignCenter,  QApplication::palette(), true,QString::number(value, 'f', 3) );//浮点数取小数点后一位显示


}

QSize floatpointdelegate::sizeHint(const QStyleOptionViewItem &option,
                              const QModelIndex &/*index*/) const
{
    return option.rect.size();//(pixmapRect).size();
}
