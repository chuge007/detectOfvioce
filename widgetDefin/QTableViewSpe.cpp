#include "QTableViewSpe.h"
#include <QDebug>
#include <QtGui>

QTableViewSpe::QTableViewSpe(QWidget *parent):QTableView(parent)
{
    //initialisation du mode de séléction des items ici par item et contigus
    setSelectionBehavior(QAbstractItemView::SelectItems);
    setSelectionMode(QAbstractItemView::ContiguousSelection);
    connect(this, SIGNAL(entered (QModelIndex)), this, SLOT(loadCol(QModelIndex)));
    connect(this, SIGNAL(pressed (QModelIndex)), this, SLOT(eraseCol(QModelIndex)));



}


void QTableViewSpe::welds_setselection(const QRect &rect, QItemSelectionModel::SelectionFlags command)
{
    setSelection (rect,command);
}

//ceci est lancé lorsque une touche de clavier est pressé
void QTableViewSpe::keyPressEvent(QKeyEvent *event)
{
    //      CTRL + C
    if (event->key() == Qt::Key_C && event->modifiers() & Qt::ControlModifier)
    {
        QItemSelectionModel* pSelectedItems = selectionModel();
        QModelIndexList SelectedItemList = pSelectedItems->selectedIndexes();
        copierTableauNormal(SelectedItemList, numColSelect());   //copie normale
    }
    //     CTRL + I
else if (event->modifiers() & Qt::ControlModifier && event->key() == Qt::Key_I)
    {
        QItemSelectionModel* pSelectedItems = selectionModel();
        QModelIndexList SelectedItemList = pSelectedItems->selectedIndexes();
        copierTableauInvers(SelectedItemList, numColSelect());   // copie inverse
    }
    else {
        QTableView::keyPressEvent(event);
    }
}

//le code la copie normale   l'algo permettant de placé les index dans le bon sens
void QTableViewSpe::copierTableauNormal(QModelIndexList& myList, int numCol)
{
    QString valTab = "";
    int valTemp = myList.count()/ numCol;
    qDebug()<<"valTemp = "<<valTemp <<"numCol=" << numCol <<"myList.count()="<<myList.count();


    for (int i=0; i<valTemp; i++)//valTemp
    {
        valTab += myList.at(i).data().toString();
        for (int j=2; j<=numCol; j++)//numCol
        {
            int pos = ((valTemp * (j-1))+i);
            valTab += " \t " + myList.at(pos).data().toString();
        }
        if(i != (valTemp-1))
            valTab += " \n ";
    }

    QClipboard* copier = QApplication::clipboard();
    copier->setText(valTab);

}

//le code la copie normale   l'algo permettant de placé les index dans le mauvais sens
void QTableViewSpe::copierTableauInvers(QModelIndexList& myList, int numCol)
{

    QString valTab = "";
    int valTemp = ((myList.count())/(numCol));
    for (int i=0; i<myList.count(); i++)
    {
        QModelIndex val= myList.at(i);
        if(i==0)
        {
            valTab += val.data().toString();
        }else if((i)%valTemp == 0)
            {
                valTab += " \n "+val.data().toString();
            }else{
                valTab += " \t "+ val.data().toString();
            }
    }
    QClipboard* copier = QApplication::clipboard();
    copier->setText(valTab);

}

// ceci un est un slot chargé de calclulé le nombre de colonne selectionné c'est le coté lourd du programme    --> SIGNAL - entered
void QTableViewSpe::loadCol(const QModelIndex& indy)
{
    if(indy.column() < numColMin )
    {
        numColMin = indy.column();
    }else if(indy.column() > numColMax){
        numColMax = indy.column();
    }
}

// ceci remet les valeurs a zéro lorsque l'on commence une autre selection    --> SIGNAL - pressed
void QTableViewSpe::eraseCol(const QModelIndex& indy)
{
    numColMin = numColMax = indy.column();
    loadCol(indy);
}

//   petit calcul permettant de précisé le nombre de colonne avec nos 2 variables
int QTableViewSpe::numColSelect()
{
    return (numColMax - numColMin +1);
}

void QTableViewSpe::focusOutEvent(QFocusEvent */*e*/)
{
    qDebug()<<"******allwelds_lostfocus";
    emit allwelds_lostfocus();
}



