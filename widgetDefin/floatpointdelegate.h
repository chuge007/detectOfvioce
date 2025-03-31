#ifndef FLOATPOINTDELEGATE_H
#define FLOATPOINTDELEGATE_H
#include <QStyledItemDelegate>
//#include <QFontMetrics>
#include <QModelIndex>
#include <QSize>

class QAbstractItemModel;
class QObject;
class QPainter;

class floatpointdelegate : public QStyledItemDelegate /* 浮点数取小数点后一位显示 */
{
    Q_OBJECT

public:
    floatpointdelegate(QObject *parent = 0)
        : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index ) const;
  //  bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index);

//signals:
   // void checkicon_press(const QModelIndex &);

};
#endif // FLOATPOINTDELEGATE_H

