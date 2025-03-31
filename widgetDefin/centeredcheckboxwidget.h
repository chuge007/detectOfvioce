#ifndef CENTEREDCHECKBOXWIDGET_H
#define CENTEREDCHECKBOXWIDGET_H
#include <QWidget>

#include <QCheckBox>
#include <QtGui>
#include <QHeaderView>
#include <QStyleOptionButton>
#include <QStyle>

class CenteredCheckBoxWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CenteredCheckBoxWidget(QWidget *parent = 0);

    QCheckBox *checkBox() const;

private:
    QCheckBox *checkbox;

};
#endif // CENTEREDCHECKBOXWIDGET_H
