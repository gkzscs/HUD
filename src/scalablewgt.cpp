#include "scalablewgt.h"


ScalableWgt::ScalableWgt(QWidget *parent)
    : cs::CSWidget(parent)
{
    initMember();
    initUI();
    initSignalSlot();
}

ScalableWgt::~ScalableWgt()
{

}

void ScalableWgt::setIndependent(bool flag)
{
    if (flag) setParent(nullptr);

    _independent = flag;
}

bool ScalableWgt::independent() const
{
    return _independent;
}

void ScalableWgt::initMember()
{
    _menuBar = new QWidget(this);
    _independent = (parent() == nullptr ? true : false);
    _btnMinimize = createToolButton("minimize");
    _btnMaximize = createToolButton("maximize");
//    _btnClose = createToolButton("close");

    _pressed = false;
    _isMaximized = false;
    _direction = Unknown;

    // Set object name
    _btnMinimize->setObjectName("btn_minimize");
    _btnMaximize->setObjectName("btn_maximize");
//    _btnClose->setObjectName("btn_close");
}

void ScalableWgt::initUI()
{
    // Set attribute
    resize(800, 600);
    setWindowFlag(Qt::FramelessWindowHint);
    setMouseTracking(true);

    // Set style sheet
    setStyleSheet("background-color: green;");
}

void ScalableWgt::initSignalSlot()
{
    connect(_btnMinimize, &QToolButton::clicked, this, &ScalableWgt::btnMinimizeClickSlot);
    connect(_btnMaximize, &QToolButton::clicked, this, &ScalableWgt::btnMaximizeClickSlot);
//    connect(_btnClose, &QToolButton::clicked, this, &ScalableWgt::btnCloseClickSlot);
}

void ScalableWgt::resizeEvent(QResizeEvent *event)
{
    cs::CSWidget::resizeEvent(event);

    const int space = 10;

//    _btnClose->move(width()-space-_btnClose->width(), space);
    _btnMaximize->move(width()-space-space-_btnMaximize->width(), space);
    _btnMinimize->move(_btnMaximize->x()-space-_btnMinimize->width(), space);
}

void ScalableWgt::mousePressEvent(QMouseEvent *e)
{
    const auto pos = e->pos();

    _pressed = true;

    _direction = calcDirection(pos);
    if (_direction == Unknown) _offset = pos;
}

void ScalableWgt::mouseMoveEvent(QMouseEvent *e)
{
    // Check the independent attribute
    if (!_independent) return;

    const auto pos = e->pos();

    if (!_pressed)
    {
        autoReshapeMouse(pos);
        return;
    }

    // If pressed mouse button
    if (_direction != Unknown)
    {
        autoResize(pos);
    }
    else
    {
        // Drag
        auto globalPos = mapToGlobal(pos);
        move(globalPos - _offset);
    }
}

void ScalableWgt::mouseReleaseEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

    _pressed = false;
    _direction = Unknown;
}

void ScalableWgt::mouseDoubleClickEvent(QMouseEvent *e)
{
    Q_UNUSED(e)

    // Check the `_independent` attribute
    if (!_independent) return;

    if (_isMaximized) showNormal();
    else showMaximized();

    _isMaximized = !_isMaximized;
}

ScalableWgt::Direction ScalableWgt::calcDirection(const QPoint &pos)
{
    const int diff = 10;
    const auto rect = this->rect();
    Direction tmpDir = Unknown;

    if (abs(rect.top() - pos.y()) < diff)
    {
        if (abs(rect.left() - pos.x()) < diff) tmpDir = TopLeft;
        else if (abs(rect.right() - pos.x()) < diff) tmpDir = TopRight;
        else tmpDir = Up;
    }
    else if (abs(rect.bottom() - pos.y()) < diff)
    {
        if (abs(rect.left() - pos.x()) < diff) tmpDir = BottomLeft;
        else if (abs(rect.right() - pos.x()) < diff) tmpDir = BottomRight;
        else tmpDir = Down;
    }
    else if (abs(rect.left() - pos.x()) < diff)
    {
        tmpDir = Left;
    }
    else if (abs(rect.right() - pos.x()) < diff)
    {
        tmpDir = Right;
    }

    return tmpDir;
}

void ScalableWgt::autoReshapeMouse(const QPoint &pos)
{
    auto tmpDir = calcDirection(pos);
    Qt::CursorShape shape;

    switch (tmpDir)
    {
    case TopLeft:
    case BottomRight:
        shape = Qt::SizeFDiagCursor;
        break;
    case TopRight:
    case BottomLeft:
        shape = Qt::SizeBDiagCursor;
        break;
    case Up:
    case Down:
        shape = Qt::SizeVerCursor;
        break;
    case Left:
    case Right:
        shape = Qt::SizeHorCursor;
        break;
    default:
        shape = Qt::ArrowCursor;
    }

    setCursor(shape);
}

void ScalableWgt::autoResize(const QPoint &pos)
{
    auto globalPos = mapToGlobal(pos);
    QRect r;

    // Reset the geometry of widget by Direction
    switch (_direction)
    {
    case TopLeft:
        r = QRect(globalPos.x(), globalPos.y(), x()+width()-globalPos.x(), y()+height()-globalPos.y());
        break;
    case TopRight:
        r = QRect(x(), globalPos.y(), globalPos.x()-x(), y()+height()-globalPos.y());
        break;
    case BottomLeft:
        r = QRect(globalPos.x(), y(), x()+width()-globalPos.x(), globalPos.y()-y());
        break;
    case BottomRight:
        r = QRect(x(), y(), globalPos.x()-x(), globalPos.y()-y());
        break;
    case Up:
        r = QRect(x(), globalPos.y(), width(), y()+height()-globalPos.y());
        break;
    case Down:
        r = QRect(x(), y(), width(), globalPos.y()-y());
        break;
    case Left:
        r = QRect(globalPos.x(), y(), x()+width()-globalPos.x(), height());
        break;
    case Right:
        r = QRect(x(), y(), globalPos.x()-x(), height());
        break;
    default:
        break;
    }

    setGeometry(r);
}

bool ScalableWgt::isInside(const QPoint &pos)
{
    return this->rect().contains(pos);
}

QToolButton *ScalableWgt::createToolButton(const QString &iconName)
{
    auto btn = new QToolButton(this);
    btn->setToolButtonStyle(Qt::ToolButtonIconOnly);
    btn->resize(24, 24);
    btn->setIconSize(btn->size());
    btn->setIcon(QIcon(":/icon/" + iconName));
    btn->setAutoRaise(true);

    return btn;
}

void ScalableWgt::btnMinimizeClickSlot()
{
    emit btnMinimizeClickSignal();

//    if (!_independent) return;

//    showMinimized();
}

void ScalableWgt::btnMaximizeClickSlot()
{
    emit btnMaximizeClickSignal();

    if (!_independent) return;

    if (_isMaximized) showNormal();
    else showMaximized();

    _isMaximized = !_isMaximized;
}

//void ScalableWgt::btnCloseClickSlot()
//{
//    if (!_independent) return;

////    close();
//}
