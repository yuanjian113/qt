#include "qsimpledownloader.h"

#include <QtGui>
#include <QApplication>
#include "log4qt/propertyconfigurator.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Log4Qt::PropertyConfigurator::configure(a.applicationDirPath() + "/log4j.properties");
    QTranslator appTranslator;
	appTranslator.load("QSimpleDownloader_" + QLocale::system().name(),
			"translations");
//			qApp->applicationDirPath());
	a.installTranslator(&appTranslator);
    QSimpleDownloader w;
    w.show();
    return a.exec();
}
