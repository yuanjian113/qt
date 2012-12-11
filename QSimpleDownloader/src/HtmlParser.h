/*
 * HtmlParser.h
 *
 *  Created on: 2009-4-12
 *      Author: szf
 */

#ifndef HTMLPARSER_H_
#define HTMLPARSER_H_

#include <QHttp>
#include <QStringList>
#include <QBuffer>
#include <vector>
#include "log4qt/logger.h"

#include "Target.h"

class HtmlParser : public QObject
{
	Q_OBJECT
	LOG4QT_DECLARE_QCLASS_LOGGER

public:
	HtmlParser(QObject *parent = 0);
	~HtmlParser() { delete buffer; }
	bool parse(int layer, const QString &url, std::vector<Target> &targets,
			bool sameHostLink = false);
	QStringList getTargetUrls() const { return targetUrls; }
	QStringList getLinks() const { return links; }
	int getLayer() const { return layer; }
	void stop() { if(parsing) http.abort(); }
	bool isParsing() const { return parsing; }

signals:
	void done();

private slots:
	void httpDone(bool error);

private:
	int layer;
	QString host, dir;
	std::vector<Target> targets;
	bool sameHostLink;				// 只取相同站点的超链接
	QHttp http;
	QBuffer *buffer;
	QStringList targetUrls;
	QStringList links;
	bool parsing;
	void parseString(const QString &str, std::vector<Target> &targets);
	QString trimQuote(const QString &str);
	bool endsWithAnyExt(const QString& str, const QStringList &exts);
};

#endif /* HTMLPARSER_H_ */
