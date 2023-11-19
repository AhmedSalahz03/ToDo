#include "ToDo.h"
#include <QtWidgets/QApplication>


void customMessageHandler(QtMsgType type, const QMessageLogContext& context, const QString& msg) {
    // You can customize the behavior here, for instance, outputting to console
    QTextStream(stdout) << msg <<"     ";
}
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ToDo w;
    w.show();
    qInstallMessageHandler(customMessageHandler);
    return a.exec();
}
