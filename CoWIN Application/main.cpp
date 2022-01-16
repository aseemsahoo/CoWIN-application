#include <QApplication>
#include <QTabWidget>
#include <QPushButton>
#include "Login.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     // set the app style sheet
    QFile styleSheetFile(":/qss/Obit.qss");

    // open the stylesheet
    styleSheetFile.open(QFile::ReadOnly);

    // read the contents of qss
    QString styleSheet = QLatin1String(styleSheetFile.readAll());

    // now set the stylesheet for our application
    a.setStyleSheet(styleSheet);

    Login w;            // A widget is never visible when you create it.
    w.show();           // You must call show() to make it visible

    return a.exec();    // This is where main() passes control to Qt,
                        // and exec() will return when the application exits
}

