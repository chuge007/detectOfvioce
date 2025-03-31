#ifndef REASON_TBVIEW
#define REASON_TBVIEW
#include <QMenu>
#include <QTableView>
#include <QHeaderView>
#include <QContextMenuEvent>

class reason_tbview : public QTableView
{
    Q_OBJECT

public:
    explicit reason_tbview(QWidget *parent = 0);
    QAction *action_addPassReason;
    QAction *action_addFailReason;
    QAction *action_deleteFailReason;
    QAction *action_deletePassReason;

private:
    QMenu *pop_menu;
    void contextMenuEvent(QContextMenuEvent *event);
    void createAcions();

protected:
    //virtual void focusInEvent(QFocusEvent *e);
    //virtual void focusOutEvent(QFocusEvent *e);

    //void mousePressEvent (QMouseEvent *event);
};
#endif // REASON_TBVIEW

