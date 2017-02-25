#include "Beginner.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);

	Beginner *begin = new Beginner();
	begin->show();

    return a.exec();
}