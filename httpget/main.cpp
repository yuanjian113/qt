#include "httpGet.h"
#include <QtCore/QCoreApplication>
#include <iostream>
#include <QTextCodec>

extern void myMsgLog( QtMsgType msgType, const char *msg );

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	QTextCodec::setCodecForLocale	( QTextCodec::codecForName("UTF-8") );
	QTextCodec::setCodecForTr		( QTextCodec::codecForName("UTF-8") );
	QTextCodec::setCodecForCStrings	( QTextCodec::codecForName("UTF-8") );

	qInstallMsgHandler( myMsgLog );

	char s[256] = { 0 };
	std::cout << "please input the url: ";
	std::cin >> s;

	HttpGet httpGet;
	httpGet.get( "www.baidu.com" );
	QObject::connect(&getter,SIGNAL(done()),&app,SLOT(quit()));
	return a.exec();
}
