/*******************************************************************************

 Nearly complety taken over from QT 4.4 tutorial.

 Johannes Beulshausen

*******************************************************************************/

#ifndef LCDRANGE_H
#define LCDRANGE_H

#include <QWidget>
#include <QVBoxLayout>

class QLabel;
class QSlider;
class QCheckbox;

class LCDRange : public QWidget
{
    Q_OBJECT

public:
    LCDRange(QWidget *parent = 0);
    LCDRange(int digits, QWidget *parent = 0);

public slots:
    void setValue(int value);
    void setRange(int minValue, int maxValue);
    void setText(const QString &text);

signals:
    void valueChanged(int newValue);

private:
    void init(int digits = 3);

    QSlider *slider;
    QLabel *label;
    QVBoxLayout *layout;
};

#endif
