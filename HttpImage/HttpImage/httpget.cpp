#include "httpget.h"
#include "qDebug"

HttpGet::HttpGet(QObject *parent)
	: QObject(parent)
{
	http = new QHttp(this);
	connect(http,SIGNAL(requestFinished(int,bool)),this,SLOT(requestFinished(int,bool)));
	connect(http,SIGNAL(done(bool)),this,SLOT(done(bool)));
}

HttpGet::~HttpGet()
{

}

void HttpGet::downloadFile(const QUrl &url,const QString &path)
{
	qDebug()<<url.path();
	file = new QFile(path);
	if (!file->open(QIODevice::WriteOnly))
	{
		delete file;
		file = 0;
		return;
	}

	QHttp::ConnectionMode mode = url.scheme().toLower() == "https" ? QHttp::ConnectionModeHttps : QHttp::ConnectionModeHttp;
	http->setHost(url.host(),mode,url.port()==-1? 0:url.port());
	http->get(url.path(),file);
	http->close();
}

void HttpGet::requestFinished(int id,bool error)
{	
	file->flush();
	file->close();
	emit finished();
}

void HttpGet::done(bool error)
{
	file->flush();
	file->close();
	delete file;
	file = 0;
	emit finished();
}
