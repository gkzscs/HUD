#ifndef APPWND_H
#define APPWND_H

#include "csutils_stable.h"
#include "scalablewgt.h"
#include "hud.h"


class AppWnd : public cs::CSWidget
{
    Q_OBJECT

public:
    AppWnd(QWidget *parent = nullptr);
    virtual ~AppWnd() override;

protected:
    void initMember();
    void initUI();
    void initSignalSlot();

protected:
    void btnMinimizeClickSlot();
    void btnMaximizeClickSlot();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;

protected:
    ScalableWgt *_wgtScalable;
    Hud *_hud;

};

#endif // APPWND_H
