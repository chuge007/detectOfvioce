#ifndef BOOLEANDELEGATE_H
#define BOOLEANDELEGATE_H

#include <QStyledItemDelegate>



class BooleanDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    explicit BooleanDelegate(QObject *parent, bool defaultValue=false);

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                const QModelIndex &index) const;

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
                const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
                const QStyleOptionViewItem &option, const QModelIndex &index) const;

private:
    bool defaultValue;
    QRect CheckBoxRect(const QStyleOptionViewItem &view_item_style_options) const;
    bool editorEvent(QEvent *event,QAbstractItemModel *model,
                const QStyleOptionViewItem &option,const QModelIndex &index);

signals:
    void check_change();//const QModelIndex &

};

#endif // BOOLEANDELEGATE_H
