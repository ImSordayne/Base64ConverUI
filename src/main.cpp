#include "Base64ConverUI.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    Base64UI window;
    window.show();
    return app.exec();
}
