/*******************************************************************************

 Animated mass forces!
 Many parts are taken out of the QT 4.4 tutorial.

 The programm is mainly self explaining and is intended to visualise the theory
 of mass forces.
 The catch 90° button was introduced to explain the rotating and alternating
 amplitudes of a resulting vector. Due to reasons of point calculation accuracy
 the animation does not always stop at the exact angles or even misses a stop
 preferentially at high speeds. It is working well enough though - possibly a
 couple of turns have to be performed.

 Johannes Beulshausen

*******************************************************************************/

#include <QApplication>

#include "desk.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Desk desk;
    desk.setGeometry(10, 30, 850, 704);
    desk.setFixedHeight(desk.height());
    desk.show();
    return app.exec();
}
