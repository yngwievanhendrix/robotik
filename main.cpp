#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
       MainWindow w;
       w.show();
       /* Testen */
       //FM_propagationMesh mesh;


       /*End Testen*/
       return a.exec();



}

