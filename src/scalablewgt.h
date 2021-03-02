#ifndef SCALABLEWGT_H
#define SCALABLEWGT_H

#include "csutils_stable.h"


class ScalableWgt : public cs::CSWidget
{
    Q_OBJECT

protected:
    enum Direction
    {
        Unknown,
        TopLeft,
        TopRight,
        BottomLeft,
        BottomRight,
        Up,
        Down,
        Left,
        Right
    };

public:
    ScalableWgt(QWidget *parent = nullptr);
    virtual ~ScalableWgt() override;

    void setIndependent(bool flag);
    bool independent() const;

protected:
    void initMember();
    void initUI();
    void initSignalSlot();

protected:
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *e) override;
    virtual void mouseMoveEvent(QMouseEvent *e) override;
    virtual void mouseReleaseEvent(QMouseEvent *e) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *e) override;

protected:
    Direction calcDirection(const QPoint &pos);
    void autoReshapeMouse(const QPoint &pos);
    void autoResize(const QPoint &pos);
    bool isInside(const QPoint &pos);

    void showMenuBarForAMoment();

protected:
    QToolButton *createToolButton(const QString &iconName);

signals:
    void btnMinimizeClickSignal();
    void btnMaximizeClickSignal();

protected slots:
    void btnMinimizeClickSlot();
    void btnMaximizeClickSlot();
//    void btnCloseClickSlot();

protected:
    QWidget *_menuBar;
    QToolButton *_btnMinimize;
    QToolButton *_btnMaximize;
//    QToolButton *_btnClose;

    bool _independent;
    bool _pressed;
    bool _isMaximized;
    Direction _direction;
    QPoint _offset;

    QTimer *_timer;
};


#endif // SCALABLEWGT_H
