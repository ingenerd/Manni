/*******************************************************************************

 Nearly complety taken over from QT 4.4 tutorial.

 Johannes Beulshausen

*******************************************************************************/

#include <QLCDNumber>
#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QFont>

#include "lcdrange.h"

LCDRange::LCDRange(QWidget *parent)
    : QWidget(parent)
{
    init();
}

LCDRange::LCDRange(int digits, QWidget *parent)
    : QWidget(parent)
{
    init(digits);
}

void LCDRange::init(int digits)
{
    QLCDNumber *lcd = new QLCDNumber(digits);
    lcd->setSegmentStyle(QLCDNumber::Filled);

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(0, 100); //per default
    slider->setValue(0); // per default

    label = new QLabel;
    label->setAlignment(Qt::AlignHCenter | Qt::AlignTop);
    label->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    connect(slider, SIGNAL(valueChanged(int)), lcd, SLOT(display(int)));
    connect(slider, SIGNAL(valueChanged(int)), this, SIGNAL(valueChanged(int)));

    layout = new QVBoxLayout;
    layout->addWidget(lcd);
    layout->addWidget(slider);
    layout->addWidget(label);
    setLayout(layout);

    setFocusProxy(slider);
}

void LCDRange::setValue(int value)
{
    slider->setValue(value);
}

void LCDRange::setRange(int minValue, int maxValue)
{
    slider->setRange(minValue, maxValue);
}

void LCDRange::setText(const QString &text)
{
    label->setText(text);
    label->setFont(QFont("Times", 13, QFont::Bold));
}
