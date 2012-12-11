#include <QApplication>

#include <QTextCodec>
#include "xinfeng.h"

int main(int argc, char *argv[])
{
	Q_INIT_RESOURCE(xinfeng);
    QApplication app(argc, argv);
	//中文支持
	QTextCodec *codec = QTextCodec::codecForName("System"); //获取系统编码 
	QTextCodec::setCodecForLocale(codec); 
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	
    QString fileName;
	
    if (argc >= 2)
        fileName = argv[1];
    else
        fileName = ".";

    TabDialog tabdialog(fileName);
	int iWidth = 250;//设置窗体初始化大小
	int iHeight = 450;
	tabdialog.resize(iWidth,iHeight);
    tabdialog.show();

    return app.exec();
}
