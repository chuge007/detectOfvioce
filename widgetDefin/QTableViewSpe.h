#ifndef HEADER_QTABLEVIEWSPE
#define HEADER_QTABLEVIEWSPE

#include <QTableView>
#include <QKeyEvent>
#include <QMessageBox>
#include <QClipboard>
#include <QModelIndexList>
#include <QModelIndex>
#include <QItemSelectionModel>
#include <QApplication>


class QTableViewSpe: public QTableView
{
    Q_OBJECT
    public:
        QTableViewSpe(QWidget *parent = 0);
        void keyPressEvent(QKeyEvent *event);
        void welds_setselection(const QRect &rect, QItemSelectionModel::SelectionFlags command);

    public slots:

        void loadCol(const QModelIndex& indy);
        void eraseCol(const QModelIndex& indy);



    protected:
        void copierTableauInvers(QModelIndexList& myList, int numCol);
        void copierTableauNormal(QModelIndexList& myList, int numCol);
        int numColSelect();
        int numColMin;
        int numColMax;

        virtual void focusOutEvent(QFocusEvent *e);
        //void mousePressEvent(QMouseEvent *event);
signals:
    void allwelds_lostfocus();

};

#endif
