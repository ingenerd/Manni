/*******************************************************************************

 The desk is the main frame of the program and contains the layout.
 It includes the controls and the paper, on which the drawings are implemented.
 The angle calculations are conducted in the paper object.

 Johannes Beulshausen

*******************************************************************************/

#include <QApplication>
#include <QFont>
#include <QLCDNumber>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QWidget>

#include "paper.h"
#include "desk.h"
#include "lcdrange.h"

Desk::Desk(QWidget *parent)
    : QWidget(parent)
{
    paper = new Paper;

    startstop = new QPushButton("Start/Stop");
    startstop->setFont(QFont("Times", 13, QFont::Bold));
    connect(startstop, SIGNAL(clicked()), paper, SLOT(timerGo()));

    reset = new QPushButton("Reset");
    reset->setFont(QFont("Times", 13, QFont::Bold));
    connect(reset, SIGNAL(clicked()), this, SLOT(resetControls()));
    connect(reset, SIGNAL(clicked()), paper, SLOT(initData()));

    posRange = new LCDRange(3);
    posRange->setRange(0,100);
    posRange->setText("Pos %");
    posRange->setValue(50);
    connect(posRange, SIGNAL(valueChanged(int)), paper, SLOT(setPosMag(int)));

    negRange = new LCDRange(3);
    negRange->setRange(0,100);
    negRange->setText("Neg %");
    negRange->setValue(50);
    connect(negRange, SIGNAL(valueChanged(int)), paper, SLOT(setNegMag(int)));

    speed = new LCDRange(3);
    speed->setRange(1,100);
    speed->setText("Speed %");
    speed->setValue(50);
    connect(speed, SIGNAL(valueChanged(int)), paper, SLOT(setSpeed(int)));

    globalAngle = new LCDRange(3);
    globalAngle->setRange(0,360);
    globalAngle->setText("Angle in °");
    globalAngle->setValue(0);
    connect(globalAngle, SIGNAL(valueChanged(int)),
            paper, SLOT(setAlpha0(int)));

    posBox = new QCheckBox("Pos");
    posBox->setFont(QFont("Times", 13, QFont::Bold));
    posBox->setCheckState(Qt::Checked);
    connect(posBox, SIGNAL(stateChanged(int)), paper, SLOT(setPosYes(int)));

    negBox = new QCheckBox("Neg");
    negBox->setFont(QFont("Times", 13, QFont::Bold));
    negBox->setCheckState(Qt::Checked);
    connect(negBox, SIGNAL(stateChanged(int)), paper, SLOT(setNegYes(int)));

    resBox = new QCheckBox("Res");
    resBox->setFont(QFont("Times", 13, QFont::Bold));
    resBox->setCheckState(Qt::Checked);
    connect(resBox, SIGNAL(stateChanged(int)), paper, SLOT(setResYes(int)));

    lableBox = new QCheckBox("Lable");
    lableBox->setFont(QFont("Times", 13, QFont::Bold));
    lableBox->setCheckState(Qt::Unchecked);
    connect(lableBox, SIGNAL(stateChanged(int)), paper, SLOT(setLableYes(int)));

    paraBox = new QCheckBox("Connect");
    paraBox->setFont(QFont("Times", 13, QFont::Bold));
    paraBox->setCheckState(Qt::Unchecked);
    connect(paraBox, SIGNAL(stateChanged(int)), paper, SLOT(setParaYes(int)));

    systBox = new QCheckBox("System");
    systBox->setFont(QFont("Times", 13, QFont::Bold));
    systBox->setCheckState(Qt::Checked);
    connect(systBox, SIGNAL(stateChanged(int)), paper, SLOT(setSystYes(int)));

    catchBox = new QCheckBox("Catch 90°");
    catchBox->setFont(QFont("Times", 13, QFont::Bold));
    catchBox->setCheckState(Qt::Unchecked);
    connect(catchBox, SIGNAL(stateChanged(int)), paper, SLOT(setCatchYes(int)));

    QVBoxLayout *tasks = new QVBoxLayout;
    tasks->addWidget(startstop);
    tasks->addWidget(reset);
    tasks->addWidget(posRange);
    tasks->addWidget(negRange);
    tasks->addWidget(speed);
    tasks->addWidget(globalAngle);
    tasks->addWidget(posBox);
    tasks->addWidget(negBox);
    tasks->addWidget(resBox);
    tasks->addWidget(lableBox);
    tasks->addWidget(systBox);
    tasks->addWidget(paraBox);
    tasks->addWidget(catchBox);

    QHBoxLayout *deskLayout = new QHBoxLayout;
    deskLayout->addLayout(tasks);
    deskLayout->addWidget(paper);

    // this command is not fully understood
    deskLayout->setStretchFactor(paper, 1);
    setLayout(deskLayout);

    posRange->setFocus();
}

void Desk::resetControls()
{
    posRange->setValue(50);
    negRange->setValue(50);
    speed->setValue(50);
    globalAngle->setValue(0);
    posBox->setCheckState(Qt::Checked);
    negBox->setCheckState(Qt::Checked);
    resBox->setCheckState(Qt::Checked);
    lableBox->setCheckState(Qt::Unchecked);
    paraBox->setCheckState(Qt::Unchecked);
    systBox->setCheckState(Qt::Checked);
    catchBox->setCheckState(Qt::Unchecked);
}
