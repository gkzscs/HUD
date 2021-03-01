#include <QApplication>
#include "appwnd.h"


int main(int argc, char **argv)
{
    QApplication app(argc, argv);
    AppWnd wnd;
    wnd.show();
    return app.exec();
}
