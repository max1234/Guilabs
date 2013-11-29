#include <QApplication>
#include "dialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog dialog;

    dialog.setWindowTitle("Labs");
    dialog.show();

    return a.exec();
}

