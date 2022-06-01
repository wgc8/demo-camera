#include "MyCamera.h"
#include "config.h"
#include <iostream>
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MyCamera w;
	w.show();

	std::cout << giWaitTime << std::endl;
	
	return a.exec();
}
