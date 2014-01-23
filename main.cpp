/*
 * Launch the checkers application.
 *
 * @author Yoan DUMAS
 * @version 1.0
 * @date 18/12/2013
 */


#include <QtGui/QApplication>
#include "controller.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);


    // Launch the Checker GUI
    Controller c(0);
    c.show();

    return a.exec();
}

