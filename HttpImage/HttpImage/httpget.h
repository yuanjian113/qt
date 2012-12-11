#ifndef HTTPGET_H
#define HTTPGET_H

#include <QObject>
#include "QUrl"
#include <QHttp>
#include "QFile"
#include "iostream"
#include "QString"

class HttpGet : public QObject
{
	Q_OBJECT

public:
	HttpGet(QObject *parent);
	~HttpGet();

	void downloadFile(const QUrl &url,const QString &path);

private:

	QHttp* http;
	QFile* file;

signals:
	void finished();
private slots:
		void requestFinished(int id,bool error);
		void done(bool error);
	
};

#endif // HTTPGET_H
