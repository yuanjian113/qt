#include <QApplication>
#include<QLabel>
#include <QTextCodec>
#include <QList>
#include <QUrl>
#include <QNetworkRequest>
#include<QDesktopServices>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <vector>
#include<iostream>
using namespace std;
int main(int argc, char *argv[])
{
	
    QApplication app(argc, argv);
	//����֧��
	QTextCodec *codec = QTextCodec::codecForName("System"); //��ȡϵͳ���� 
	QTextCodec::setCodecForLocale(codec); 
	QTextCodec::setCodecForCStrings(codec);
	QTextCodec::setCodecForTr(codec);
	
    QString fileName;
	
    if (argc >= 2)
        fileName = argv[1];
    else
        fileName = "."; 
	QUrl url("http://quanapi.sinaapp.com/fetion.php?u=18858298271&p=wang113.&to=18858298271&m=hello world");
    QNetworkAccessManager *manager = new QNetworkAccessManager();

	QString str = url.fragment();
	QLabel *label = new QLabel("��");
	label->show();
	manager->get(QNetworkRequest(url));
    return app.exec();
}