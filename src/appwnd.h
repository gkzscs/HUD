#ifndef APPWND_H
#define APPWND_H

#include "csutils_stable.h"
#include "scalablewgt.h"


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
    ScalableWgt *_wgtScalable;

};

#endif // APPWND_H
