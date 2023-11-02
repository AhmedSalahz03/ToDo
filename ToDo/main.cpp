#include "ToDo.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToDo w;
    w.show();
    return a.exec();
}
