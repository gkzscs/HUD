#ifndef HUD_H
#define HUD_H

#include "csutils_stable.h"


class Hud : public cs::CSWidget
{
    Q_OBJECT

public:
    Hud(QWidget *parent = nullptr);
    virtual ~Hud() override;

protected:
    void initMember();
    void initUI();
    void initSignalSlot();

protected:
    virtual void paintEvent(QPaintEvent *event) override;

protected:
    void drawHeading(QPainter &p);
    void drawRollAngle(QPainter &p);
    void drawPitchAngle(QPainter &p);
    void drawAirSpeed(QPainter &p);
    void drawGroundSpeed(QPainter &p);
    void drawRateOfClimb(QPainter &p);
    void drawHeight(QPainter &p);

    void drawLabels(QPainter &p);

protected:
    double _heading;
    double _roll;
    double _pitch;
    double _airSpeed;
    double _groundSpeed;
    double _roc;
    double _height;

    double _eas;
    double _gs;
    double _amsl;
    double _rfh;

};

#endif // HUD_H
