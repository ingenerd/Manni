/*******************************************************************************

 The paper contains the drawings, timer and calculations.
 If the timer is active, every couple miliseconds the new angles are calculated.
 This is done in the method: setAlpha. The whole screen is updated then.
 The highest resolution with QT is a calculation call every millisecond.
 Apparently, QT needs more time to do all computations within one
 millisecond, which can be seen in bad accuracy for the 90° catcher.
 Surely another approach without QT would yield a better result.

 Johannes Beulshausen

*******************************************************************************/

#ifndef PAPER_H
#define PAPER_H

#include <QWidget>
#include <QColor>
#include <QPointF>

class QTimer;

class Paper : public QWidget
{
    Q_OBJECT

public:
    Paper(QWidget *parent = 0);

public slots:
    void setAlpha();
    void timerGo();
    void initData();

    void setPosMag(int);
    void setNegMag(int);
    void setSpeed(int);
    void setAlpha0(int);

    void setPosYes(int);
    void setNegYes(int);
    void setResYes(int);
    void setLableYes(int);
    void setParaYes(int);
    void setSystYes(int);
    void setCatchYes(int);

protected:
    void paintEvent(QPaintEvent *event);

private:

    int posMag, negMag, maxMag, speedMag; // scale factors
    double posL, negL; // length of vectors
    double arrowLen, arrowAng; // geometry of arrows

    /* private member data,
    - just so the points do not need to be recalculated for each vector itself*/
    QPointF Ppos, Pneg, Pres;

    // checkbox state variables
    int posYes, negYes, resYes, lableYes, paraYes, systYes, catchYes;

    double alpha0, alphaP, alphaN, alpha_i, omega; // angle variables

    double omega0; // to be able to scale the speed
    int deltaT; // timestep in milli seconds

    QTimer *totalZeit;

    // functions
    QPointF setPoint(double angle, double length);
    double getPointAngle (QPointF point);
    void catch90();

     // pictures have also be defined in .qrc file
     QPixmap *vkaPic, *QtPic;

     // to match the vector colors with picture colors
     QColor posColor, negColor, resColor, posLableColor, negLableColor, resLableColor, systColor, paraColor;
     QColor VKAgray, QtLightGreen, QtDarkGreen, LightBordeaux, DarkBordeaux;

    // paint calls
    void paintVec  (QPainter &painter, QPointF point, double angle,
                    int thickness, QColor color);
    void paintSyst (QPainter &painter);
    void paintPara (QPainter &painter);
    void paintLable(QPainter &painter);
};

#endif

