#include "AReMu_GBA.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	AReMu_GBA w;
	w.show();
	return a.exec();
}
