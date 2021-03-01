#include "hud.h"


Hud::Hud(QWidget *parent)
    : cs::CSWidget(parent)
{
    initMember();
    initUI();
    initSignalSlot();
}

Hud::~Hud()
{

}

void Hud::initMember()
{
    _heading = 0;
    _roll = 0;
    _pitch = 0;
    _airSpeed = 0;
    _groundSpeed = 0;
    _roc = 0;
    _height = 0;

    _eas = 0;
    _gs = 0;
    _amsl = 0;
    _rfh = 0;
}

void Hud::initUI()
{
    // Set attribute
    resize(600, 600);
    setWindowFlag(Qt::FramelessWindowHint);
}

void Hud::initSignalSlot()
{

}

void Hud::paintEvent(QPaintEvent *event)
{
    cs::CSWidget::paintEvent(event);

    QPainter p(this);
    drawHeading(p);
    drawRollAngle(p);
    drawPitchAngle(p);
    drawAirSpeed(p);
    drawGroundSpeed(p);
    drawRateOfClimb(p);
    drawHeight(p);

    drawLabels(p);
}

void Hud::drawHeading(QPainter &p)
{

}

void Hud::drawRollAngle(QPainter &p)
{

}

void Hud::drawPitchAngle(QPainter &p)
{

}

void Hud::drawAirSpeed(QPainter &p)
{

}

void Hud::drawGroundSpeed(QPainter &p)
{

}

void Hud::drawRateOfClimb(QPainter &p)
{

}

void Hud::drawHeight(QPainter &p)
{

}

void Hud::drawLabels(QPainter &p)
{

}


