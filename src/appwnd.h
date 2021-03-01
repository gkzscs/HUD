#ifndef APPWND_H
#define APPWND_H

#include "csutils_stable.h"


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

};

#endif // APPWND_H
