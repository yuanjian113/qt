/*
 * HttpGet.cpp
 *
 *  Created on: 2009-5-3
 *      Author: szf
 */
#include <QtNetwork>

#include "HttpGet.h"

HttpGet::HttpGet(QObject *parent)
	: QObject(parent)
{
	downloading = false;
	connect(&http, SIGNAL(done(bool)), this, SLOT(httpDone(bool)));
}

bool HttpGet::getFile(const QUrl &url, const QString &localFileName, int minFileSize)
{
	downloading = true;
	if(!url.isValid()) {
		logger()->error("Error: Invalid URL");
		downloading = false;
		return false;
	}
	if(url.scheme() != "http") {
		logger()->error("Error: URL must start with 'http:'");
		downloading = false;
		return false;
	}
	if(url.path().isEmpty()) {
		logger()->error("Error: URL has no path");
		downloading = false;
		return false;
	}

	file.setFileName(localFileName);
	if(!file.open(QIODevice::WriteOnly)) {
		logger()->error("Error: Cant open file " + file.fileName()
				+ " for writing: " + file.errorString());
		downloading = false;
		return false;
	}
	this->minFileSize = minFileSize;
	http.setHost(url.host(), url.port(80));
	http.get(url.path(), &file);
	http.close();
	return true;
}

void HttpGet::httpDone(bool error)
{
	if (error) {
		logger()->error("Error: " + http.errorString());
	} else {
		logger()->info("File downloaded as " + file.fileName());
	}
	if(file.size() < minFileSize)
		file.remove();
	else
		file.close();
	downloading = false;
	emit done();
}
