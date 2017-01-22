#include "arimageconver.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	ARImageConver w;
	w.show();
	return a.exec();
}
