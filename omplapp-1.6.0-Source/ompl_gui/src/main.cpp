#include <QApplication>
#include "MainWindow.h"
#include <QDebug>
#include <cstdio>

void myMessageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    QByteArray localMsg = msg.toLocal8Bit();
    // Print all messages to stderr
    fprintf(stderr, "%s\n", localMsg.constData());
    fflush(stderr);
}

int main(int argc, char *argv[])
{
    qInstallMessageHandler(myMessageHandler); // Install our custom handler
    
    QApplication app(argc, argv);

    MainWindow w;
    w.show();

    return app.exec();
}
