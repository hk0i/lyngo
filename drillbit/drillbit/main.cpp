#include <QApplication>
#include "imp_drillbit.h"

int main(int argc, char **argv)
{
	QApplication app(argc, argv);
	Imp_drillbit driller;
	driller.show();

	return app.exec();

	return 0;
}
