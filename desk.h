/*******************************************************************************

 The desk is the main frame of the program and contains the layout.
 It includes the controls and the paper, on which the drawings are implemented.
 The angle calculations are conducted in the paper object.

 Johannes Beulshausen

*******************************************************************************/

#ifndef DESK_H
#define DESK_H

#include <QWidget>
#include <QPushButton>
#include <QCheckBox>
#include <QLabel>

class LCDRange;

class Paper;

class Desk : public QWidget
{
    Q_OBJECT

public:
    Desk(QWidget *parent = 0);

public slots:
    void resetControls();

private:
    QPushButton *startstop;
    QPushButton *reset;
    LCDRange *posRange;
    LCDRange *negRange;
    LCDRange *speed;
    LCDRange *globalAngle;
    QCheckBox *posBox;
    QCheckBox *negBox;
    QCheckBox *resBox;
    QCheckBox *lableBox;
    QCheckBox *systBox;
    QCheckBox *paraBox;
    QCheckBox *catchBox;

    Paper *paper;
};

#endif
