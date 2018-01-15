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

 #include <QPaintEvent>
 #include <QPainter>
 #include <QPen>
 #include <QLineF>
 #include <QPointF>
 #include <QPolygonF>
 #include <QTimer>
 #include <QFont>

 #include <math.h>

 #include "paper.h"

Paper::Paper(QWidget *parent)
    : QWidget(parent)
{
    // constant data for program
    posL     = 160.0;
    negL     = 160.0;
    arrowLen = 10.0;
    arrowAng = 50*M_PI/180;
    omega0 = 0.02; // this value makes up a reasonable speed
    deltaT = 1; // in milli seconds (a smoother appearance is not possible)

    // for convenience
    VKAgray       = QColor(196,196,196);
    QtLightGreen  = QColor(122,193, 66);
    QtDarkGreen   = QColor(  7, 99, 36);
    LightBordeaux = QColor(128,  0,  0);
    DarkBordeaux  = QColor( 64,  0,  0);

    posColor = Qt::blue;
    negColor = QtLightGreen;
    resColor = LightBordeaux;
    posLableColor = Qt::darkBlue;
    negLableColor = QtDarkGreen;
    resLableColor= DarkBordeaux;
    systColor = Qt::darkGray;
    paraColor = Qt::black;

    totalZeit = new QTimer(this);
    connect(totalZeit, SIGNAL(timeout()), this, SLOT(setAlpha()));

    initData();

    vkaPic = new QPixmap(":/images/vkaLogoGelb.png");
    QtPic  = new QPixmap(":/images/QtLogoGelb.png" );

    setPalette(QPalette(QColor(250, 250, 200)));
    setAutoFillBackground(true);
}

void Paper::setAlpha()
{
    // because a speed adjustment is implemented, the last angle has to be saved
    alphaP  = alpha0 + alpha_i + omega * double(deltaT);
    alphaN  = alpha0 - alpha_i - omega * double(deltaT);
    alpha_i = alphaP - alpha0; // save last alpha w/o alpha0;
    update();
}

void Paper::timerGo()
{
    if (totalZeit->isActive())
    {
        totalZeit->stop();
        update();
        return;
    }
    totalZeit->start(deltaT);
}

void Paper::initData()
{
    // range data
    posMag   = 50;
    negMag   = 50;
    speedMag = 50;
    alpha0   = 0.0;

    omega    = omega0 * speedMag / 100;

    // angle data
    alphaP   = 0.0;
    alphaN   = 0.0;
    alpha_i  = 0.0; // = vorangegangenes alpha

    // start points for first visualisation on screen
    Ppos = QPointF(0,-posL*posMag/100.0);
    Pneg = QPointF(0,-negL*negMag/100.0);
    Pres = Ppos + Pneg;

    // checkbos states
    setPosYes(Qt::Checked);
    setNegYes(Qt::Checked);
    setResYes(Qt::Checked);
    setLableYes(Qt::Unchecked);
    setSystYes(Qt::Checked);
    setParaYes(Qt::Unchecked);

    // to stop the animation when the reset event is chosen
    if (totalZeit->isActive()) totalZeit->stop();

    update();
}

void Paper::setPosMag(int newPos)
{
    if (posMag == newPos) return;
    posMag = newPos;
    if (!totalZeit->isActive()) update();
}

void Paper::setNegMag(int newNeg)
{
    if (negMag == newNeg) return;
    negMag = newNeg;
    if (!totalZeit->isActive()) update();
}

void Paper::setSpeed(int newSpeedMag)
{
    if (speedMag == newSpeedMag) return;
    speedMag = newSpeedMag;
    omega = omega0*double(newSpeedMag)/100.0;
    if (!totalZeit->isActive()) update();
}

void Paper::setAlpha0(int newAlpha0)
{
    if (alpha0 == double(newAlpha0)*M_PI/180) return;
    alpha0 = double(newAlpha0)*M_PI/180;
    if (!totalZeit->isActive())
    {
        alphaP  = alpha0 + alpha_i;
        alphaN  = alpha0 - alpha_i;
        update();
    }
}

void Paper::setPosYes(int state)
{
     posYes = state;
     if (!totalZeit->isActive()) update();
}

void Paper::setNegYes(int state)
{
     negYes = state;
     if (!totalZeit->isActive()) update();
}

void Paper::setResYes(int state)
{
     resYes = state;
     if (!totalZeit->isActive()) update();
}

void Paper::setLableYes(int state)
{
     lableYes = state;
     if (!totalZeit->isActive()) update();
}

void Paper::setParaYes(int state)
{
     paraYes = state;
     if (!totalZeit->isActive()) update();
}

void Paper::setSystYes(int state)
{
     systYes = state;
     if (!totalZeit->isActive()) update();
}

void Paper::setCatchYes(int state)
{
     catchYes = state;
     if (!totalZeit->isActive()) update();
}

void Paper::paintEvent(QPaintEvent * /* event */)
{
    // calculate vector points
    Ppos = setPoint (alphaP, posL*posMag/100);
    Pneg = setPoint (alphaN, negL*negMag/100);
    Pres = Ppos + Pneg;

    QPainter painter(this);
    painter.translate(this->size().width()/2, this->size().height()/2);

    painter.drawPixmap(-int(2*posL), -int(2*posL), *vkaPic);
    painter.drawPixmap( int(0.9*posL),  int(1.5*posL)+15, *QtPic);

    if (systYes  != 0) paintSyst (painter);
    if (paraYes  != 0) paintPara (painter);
    if (posYes   != 0) paintVec  (painter, Ppos, alphaP, 5, posColor);
    if (negYes   != 0) paintVec  (painter, Pneg, alphaN, 5, negColor);
    if (resYes   != 0) paintVec  (painter, Pres, getPointAngle(Pres), 5,
                                  resColor);
    if (lableYes != 0) paintLable(painter);
    if (catchYes != 0) catch90(); /*this function tries to check, whether the
    vectors lie on each other or point in different directions*/
}

QPointF Paper::setPoint(double angle, double length)
{
    QPointF Pfunct( sin(angle)*length, -cos(angle)*length );
    return (Pfunct);
}

double Paper::getPointAngle (QPointF point)
{
    if ( point.isNull() ) return (M_PI/2);
    if ( point.y() < 0.0)
        return ( - acos( point.x()/sqrt( point.x()*point.x() +
                         point.y()*point.y() ) ) + M_PI/2 );
    else
        return (   acos( point.x()/sqrt( point.x()*point.x() +
                         point.y()*point.y() ) ) + M_PI/2 );
}

void Paper::catch90 ()
{
    /*remain is the remainder to all multiples of 90°
    - the % operator can not be used, since it works only for int types*/
    double remain = (alphaP-alpha0) - int( (alphaP-alpha0)/(M_PI/2) )*M_PI/2 ;
    /*the rounding errors are caught depending on the rotating speed
    - it is a compromise*/
    if (remain < (0.0002 * speedMag) ) totalZeit->stop();
}

void Paper::paintVec (QPainter &painter, QPointF point, double angle,
                      int thickness, QColor color)
{
    QPen vecPen(color, thickness, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);

    // vector top points
    QPointF P1( point.x() - sin(angle+arrowAng/2)*arrowLen , point.y() +
                            cos(angle+arrowAng/2)*arrowLen );
    QPointF P2( point.x() - sin(angle-arrowAng/2)*arrowLen , point.y() +
                            cos(angle-arrowAng/2)*arrowLen );

    QPointF P0(0,0);

    QVector<QPointF> topDef;
    topDef.append(P1);
    topDef.append(point);
    topDef.append(P2);
    QPolygonF top(topDef);

    QLineF body(P0, point);

    painter.setPen(vecPen);
    painter.drawLine(body);
    if (body.length() >= arrowLen) painter.drawPolyline(top);
}

void Paper::paintSyst(QPainter &painter)
{
    // 3 is the thickness
    QPen systPen(systColor, 3, Qt::SolidLine, Qt::RoundCap, Qt::MiterJoin);

    QPointF P0(0,0), PX(-posL*1.5,0.0), PY(0.0,posL*1.5), PXadd(1,0), PYadd(0,1);

    painter.setPen(systPen);
    painter.drawEllipse(P0, posL+5, posL+5);

    QVector<QPointF> topDef;

    topDef.append(PX+15*PXadd-8*PYadd);
    topDef.append(PX);
    topDef.append(PX+15*PXadd+8*PYadd);
    QPolygonF topX(topDef);
    QLineF bodyX(-PX, PX);
    painter.drawLine(bodyX);
    painter.drawPolyline(topX);

    topDef.clear();

    topDef.append(-PY+8*PXadd+15*PYadd);
    topDef.append(-PY);
    topDef.append(-PY-8*PXadd+15*PYadd);
    QPolygonF topY(topDef);
    QLineF bodyY(-PY, PY);
    painter.drawLine(bodyY);
    painter.drawPolyline(topY);

    topDef.clear();

    painter.drawArc( -40, -190, 80, 20, 30*16, 120*16 );
    QPointF PendArc(38,-184);
    topDef.append(PendArc-12*PXadd-11*PYadd);
    topDef.append(PendArc);
    topDef.append(PendArc-15*PXadd+3*PYadd);
    QPolygonF topArc(topDef);
    painter.drawPolyline(topArc);

    QFont lableFont("Times", 25, QFont::Bold);
    painter.setFont(lableFont);

    painter.drawText( PX+20*PXadd+30*PYadd, "y");
    painter.drawText(-PY+20*PXadd+20*PYadd, "x");


}

void Paper::paintPara(QPainter &painter)
{
    // 2 is the thickness
    QPen paraPen(paraColor, 2, Qt::DashLine, Qt::RoundCap, Qt::MiterJoin);

    QLineF lineNeg(Pneg, Pres);
    QLineF linePos(Ppos, Pres);

    painter.setPen(paraPen);
    if (resYes != 0)
    {
        if (posYes != 0) painter.drawLine(linePos);
        if (negYes != 0) painter.drawLine(lineNeg);
    }
}

void Paper::paintLable(QPainter &painter)
{
    QFont lableFont("Times", 12, QFont::Bold);
    painter.setFont(lableFont);

    QPen lablePen(posLableColor);
    painter.setPen(lablePen);
    if (posYes   != 0) painter.drawText(Ppos, "POS");

    lablePen.setColor(negLableColor);
    painter.setPen(lablePen);
    if (negYes   != 0) painter.drawText(Pneg, "NEG");

    lablePen.setColor(resLableColor);
    painter.setPen(lablePen);
    if (resYes   != 0) painter.drawText(Pres, "RES");
}
