#include "booleandelegate.h"
#include "centeredcheckboxwidget.h"
#include <QtGui>
#include <QStyle>
#include <QApplication>


//extern bool weld_edit_mode;
//extern bool focus_in_weld_view;

BooleanDelegate::BooleanDelegate(QObject *parent, bool defaultValue) :
    QStyledItemDelegate(parent), defaultValue(defaultValue)
{qDebug()<<"QStyledItemDelegate";
}

void BooleanDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                        const QModelIndex &index) const
{
    QVariant value=index.data();
    if(!value.isValid())
    {
        QStyledItemDelegate::paint(painter, option, index);
    }
    else
    {
        if (value.isValid() )
        {
            bool boolVal = value.isValid() ? value.toBool() : defaultValue;
            //qDebug("BooleanDelegate::paint boolVal=%d",boolVal);
            //qDebug()<<"value="<<value.toString();
            //qDebug("defaultValue=%d",defaultValue);
            QStyle *style=QApplication::style();

            QRect checkBoxRect=style->subElementRect(QStyle::SE_CheckBoxIndicator, &option);
            int chkWidth=checkBoxRect.width();
            int chkHeight=checkBoxRect.height();

            int centerX=option.rect.left() + qMax(option.rect.width()/2-chkWidth/2, 0);
            int centerY=option.rect.top() + qMax(option.rect.height()/2-chkHeight/2, 0);
            QStyleOptionViewItem modifiedOption(option);
            modifiedOption.rect.moveTo(centerX, centerY);
            modifiedOption.rect.setSize(QSize(chkWidth, chkHeight));
            modifiedOption.state |= QStyle::State_Enabled;
            //modifiedOption.state |= QStyle::State_Off;
            //根据值判断是否选中
            if(boolVal )//&& focus_in_weld_view
            {
                modifiedOption.state |= QStyle::State_On;
            }
            else
            {
                modifiedOption.state |= QStyle::State_Off;
            }
            if ((option.state & QStyle::State_Selected ) )
            {
                if( ( option.state & QStyle::State_Active) )// && weld_edit_mode
                {
                    painter->fillRect(option.rect, option.palette.highlight());
                }
                else
                {
                    painter->fillRect(option.rect, option.palette.background());
                }
            }
                style->drawPrimitive(QStyle::PE_IndicatorItemViewItemCheck, &modifiedOption, painter);
        }
        else
        {
                QStyledItemDelegate::paint(painter, option, index);
        }
    }
qDebug()<<"QStyledItemDelegate";
}

QWidget *BooleanDelegate::createEditor(QWidget *parent,
                                    const QStyleOptionViewItem & /*option*/ ,
                                    const QModelIndex & /*index*/ ) const
{
    CenteredCheckBoxWidget *editor=new CenteredCheckBoxWidget(parent);
    editor->checkBox()->setChecked(false);//defaultValue
    editor->installEventFilter(const_cast<BooleanDelegate*>(this));

    return editor;
qDebug()<<"QStyledItemDelegate";
}

void BooleanDelegate::setEditorData(QWidget *editor,
                            const QModelIndex &index) const
{
    QVariant data=index.model()->data(index, Qt::EditRole);
    bool value;
    if(!data.isNull())
    {
        if(data.toInt() == 1)
        {
            value= true;
        }
        else
        {
            value= false;
        }
        //value=data.toBool();
    }
    else
    {
        value=defaultValue;
    }
    CenteredCheckBoxWidget *checkBoxWidget = static_cast<CenteredCheckBoxWidget*>(editor);
    checkBoxWidget->checkBox()->setChecked(value);
qDebug()<<"QStyledItemDelegate";
}

void BooleanDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
                                    const QModelIndex &index) const
{
    CenteredCheckBoxWidget *checkBoxWidget = static_cast<CenteredCheckBoxWidget*>(editor);
    bool value = checkBoxWidget->checkBox()->isChecked();
    int sqliteboolv = 1 ? value : 0;
    model->setData(index, sqliteboolv, Qt::EditRole);
qDebug()<<"QStyledItemDelegate";

}

void BooleanDelegate::updateEditorGeometry(QWidget *editor,
                            const QStyleOptionViewItem &option, const QModelIndex &/* index */) const
{
    CenteredCheckBoxWidget *checkBoxWidget = static_cast<CenteredCheckBoxWidget*>(editor);

    QSize size=checkBoxWidget->sizeHint();
    editor->setMinimumHeight(size.height());
    editor->setMinimumWidth(size.width());
    editor->setGeometry(option.rect);
qDebug()<<"QStyledItemDelegate";
 }


QRect BooleanDelegate::CheckBoxRect(const QStyleOptionViewItem &viewItemStyleOptions)const
{

    //绘制按钮所需要的参数
    QStyleOptionButton checkBoxStyleOption;
    //按照给定的风格参数 返回元素子区域
    QRect checkBoxRect = QApplication::style()->subElementRect( QStyle::SE_CheckBoxIndicator, &checkBoxStyleOption);
    //返回QCheckBox坐标
    QPoint checkBoxPoint(viewItemStyleOptions.rect.x() + viewItemStyleOptions.rect.width() / 2 - checkBoxRect.width() / 2,
                         viewItemStyleOptions.rect.y() + viewItemStyleOptions.rect.height() / 2 - checkBoxRect.height() / 2);
    //返回QCheckBox几何形状
    return QRect(checkBoxPoint, checkBoxRect.size());
qDebug()<<"QStyledItemDelegate";
}

bool BooleanDelegate::editorEvent(QEvent *event,QAbstractItemModel *model,
                                   const QStyleOptionViewItem &option,const QModelIndex &index)
{

//if(weld_edit_mode)
{
             //
    if((event->type() == QEvent::MouseButtonRelease) ||
        (event->type() == QEvent::MouseButtonPress))
    {
        QMouseEvent *mouse_event = static_cast<QMouseEvent*>(event);
        if(mouse_event->button() != Qt::LeftButton     ||
           !option.rect.contains(mouse_event->pos()))//!CheckBoxRect(option).contains(mouse_event->pos())
        {
            return false;
        }

        if(event->type() == QEvent::MouseButtonRelease)//  MouseButtonDblClick)!!!!!!!!!!!!!!!!!!!!
        {
            return true;

        }
    }
    else if(event->type() == QEvent::KeyPress)
    {
        if(static_cast<QKeyEvent*>(event)->key() != Qt::Key_Space &&
           static_cast<QKeyEvent*>(event)->key() != Qt::Key_Select)
        {
            return false;
        }
    }
    else
    {
        return false;
    }


    bool checked = index.model()->data(index, Qt::DisplayRole).toBool();
    int  sqliteboolv =0;
    if(! checked)
    {
       sqliteboolv = 1;
    }
    bool setmoe_v = model->setData(index, sqliteboolv, Qt::EditRole);//!checked
    emit check_change();
    return setmoe_v;
qDebug()<<"QStyledItemDelegate";
    }
/*else
{
    return true;
}*/
}


