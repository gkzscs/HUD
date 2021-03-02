#include "appwnd.h"


AppWnd::AppWnd(QWidget *parent)
    : cs::CSWidget(parent)
{
    initMember();
    initUI();
    initSignalSlot();
}

AppWnd::~AppWnd()
{

}

void AppWnd::initMember()
{
    _wgtScalable = new ScalableWgt(this);
}

void AppWnd::initUI()
{
    // Set attribute
    resize(800, 600);
    setMouseTracking(true);

    _wgtScalable->setIndependent(true);
    _wgtScalable->show();
}

void AppWnd::initSignalSlot()
{
    connect(_wgtScalable, &ScalableWgt::btnMinimizeClickSignal, this, &AppWnd::btnMinimizeClickSlot);
    connect(_wgtScalable, &ScalableWgt::btnMaximizeClickSignal, this, &AppWnd::btnMaximizeClickSlot);
}

void AppWnd::btnMinimizeClickSlot()
{
    if (!_wgtScalable->independent()) return;

    _wgtScalable->setIndependent(false);
    _wgtScalable->setParent(this);
    _wgtScalable->setGeometry(rect());
    _wgtScalable->show();
}

void AppWnd::btnMaximizeClickSlot()
{
    if (_wgtScalable->independent()) return;

    _wgtScalable->setIndependent(true);
    _wgtScalable->show();
}
