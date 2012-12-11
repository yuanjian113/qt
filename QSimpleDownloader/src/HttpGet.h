/*
 * HttpGet.h
 *
 *  Created on: 2009-5-3
 *      Author: szf
 */

#ifndef HTTPGET_H_
#define HTTPGET_H_

#include <QHttp>
#include <QFile>
#include "log4qt/logger.h"

class QUrl;

class HttpGet : public QObject {
	Q_OBJECT
	LOG4QT_DECLARE_QCLASS_LOGGER

public:
	HttpGet(QObject *parent = 0);
	bool getFile(const QUrl &url, const QString &localFileName, int minFileSize);
	void stop() { if(downloading) http.abort(); }
	bool isDownloading() const { return downloading; }

signals:
	void done();

private slots:
	void httpDone(bool error);

private:
	QHttp http;
	QFile file;
	int minFileSize;
	bool downloading;
};

#endif /* HTTPGET_H_ */
