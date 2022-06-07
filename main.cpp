#include "MyCamera.h"
#include <iostream>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyCamera w;
	w.show();

	
	return a.exec();
}
