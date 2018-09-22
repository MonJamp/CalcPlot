#include <QApplication>
#include <QCommandLineParser>
#include <QCommandLineOption>

#include "GUI/MainWindow.h"

int main(int argc, char *argv[])
{
	QApplication app(argc, argv);
	QCoreApplication::setOrganizationName("Filjo Abraham");
	QCoreApplication::setApplicationName("CalcPlot");
	QCoreApplication::setApplicationVersion("0.0.9");

	QCommandLineParser parser;
	parser.setApplicationDescription("Open source alternative to WinPlot");
	parser.addHelpOption();
	parser.addVersionOption();
	parser.process(app);

	MainWindow mainWin;

	return app.exec();
}
