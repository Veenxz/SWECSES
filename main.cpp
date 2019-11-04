#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("土壤风蚀控制服务评估软件");
    w.setWindowIcon(QIcon("calculate.ico"));
    w.show();

    return a.exec();
}
