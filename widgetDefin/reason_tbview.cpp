#include "reason_tbview.h"
#include <QDebug>

reason_tbview::reason_tbview(QWidget *parent) :
    QTableView(parent)
{
    createAcions();
    //this->setMouseTracking(true);
    //this->setContextMenuPolicy(Qt::ActionsContextMenu);//设置为action菜单模式
}

void reason_tbview::createAcions()
{
//    action_addPassReason = new QAction(this);
//    action_addFailReason = new QAction(this);
//    action_deletePassReason = new QAction(this);
//    action_deleteFailReason = new QAction(this);
//    action_addPassReason->setText(QString("Add Pass Reason"));
//    action_addFailReason->setText(QString("Add Fail Reason"));
//    action_deletePassReason->setText(QString("Delete Slecte Pass Reason"));
//    action_deleteFailReason->setText(QString("Delete Slecte Fail Reason"));
//    action_addPassReason->setIcon(QIcon("://icons/page_add.png"));
//    action_addFailReason->setIcon(QIcon("://icons/add_failreason.png"));
//    action_deletePassReason->setIcon(QIcon("://icons/Delete-01.png"));
//    action_deleteFailReason->setIcon(QIcon("://icons/Delete-01.png"));
//    //qDebug()<<"action";

//    setDragDropMode(DragDrop);
//    setSelectionMode(SingleSelection);
}

void reason_tbview::contextMenuEvent(QContextMenuEvent *event)
{
//    pop_menu = new QMenu;
//    //pop_menu->clear(); //清除原有菜单
//    QPoint point = this->mapFromGlobal(QCursor::pos());//得到窗口坐标
//    int height = this->horizontalHeader()->height();
//    QPoint pt2(0,height);
//    point -= pt2;
//    //ui->userTableView->horizontalHeader()->hide();
//    int curRow = this->indexAt(point).row();
//    if(curRow  >= 0)
//    {
//        pop_menu->addAction(action_addPassReason);
//        pop_menu->addAction(action_addFailReason);
//        pop_menu->addSeparator();
//        pop_menu->addAction(action_deletePassReason);
//        pop_menu->addAction(action_deleteFailReason);

//        //菜单出现的位置为当前鼠标的位置
//        pop_menu->exec(QCursor::pos());
//        event->accept();
//   }
//   else
//   {
//       pop_menu->addAction(action_addPassReason);
//       pop_menu->addAction(action_addFailReason);
//       pop_menu->exec(QCursor::pos());
//       event->accept();
//   }
}

/*void reason_tbview::focusInEvent(QFocusEvent *)
{
     //focus_in_weld_view = true;
}

void reason_tbview::focusOutEvent(QFocusEvent *)
{
      //focus_in_weld_view = false;
    //qDebug()<<"focusOutEvent";
}*/
