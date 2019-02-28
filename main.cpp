#include "cuterecorder.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CuteRecorder w;
    w.show();

    return a.exec();
}
