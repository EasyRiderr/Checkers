/*
 * Launch the checkers application.
 *
 * @author Yoan DUMAS
 * @version 1.0
 * @date 18/12/2013
 */


#include <QtGui/QApplication>
#include <iostream>
#include <string>
#include <QStringList>
#include "controller.h"


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);


    // Test du controler
    Controller c;
    c.display();
    std::cout << "Syntax = source-destination, for example : 65-74" << std::endl;
    std::string userQuerry;
    position_t src, dst;
    do {
        std::cout << "Remaining white pieces = " << c.getWhitePiecesNumber() << std::endl;
        std::cout << "Remaining black pieces = " << c.getBlackPiecesNumber() << std::endl;
        std::cout << "Move ?";
        std::cin >> userQuerry;

        QStringList list = QString(userQuerry.c_str()).split("-");
        if(list.length() != 2) {
            std::cerr << "Error, syntax = source-destination, for example : 65-74" << std::endl;
        } else {
            src.i = list[0].toInt() / 10;
            src.j = list[0].toInt() % 10;

            dst.i = list[1].toInt() / 10;
            dst.j = list[1].toInt() % 10;

            try {
                c.move(src, dst);
            } catch(std::exception & e) {
                std::cerr << "Error : " << e.what() << std::endl;
            }
        }
        c.display();
    } while(!c.isEnd() && strcmp(userQuerry.c_str(), "stop"));

    if(c.getBlackPiecesNumber() == 0) {
        std::cout << "White wins the game !" << std::endl;
    }
    if( c.getWhitePiecesNumber() == 0) {
        std::cout << "Bhite wins the game !" << std::endl;
    }

    //return a.exec();
    return 0;
}
