/*
 * HtmlParser.cpp
 *
 *  Created on: 2009-4-12
 *      Author: szf
 */
#include <QtNetwork>

#include "HtmlParser.h"

HtmlParser::HtmlParser(QObject *parent)
	: QObject(parent)
{
	buffer = new QBuffer;
	parsing = false;
	connect(&http, SIGNAL(done(bool)), this, SLOT(httpDone(bool)));
}

/// 解析html
bool HtmlParser::parse(int layer, const QString &url, std::vector<Target> &targets,
		bool sameHostLink)
{
	parsing = true;
	QUrl qUrl(url);
	if(!qUrl.isValid()) {
		logger()->error("Error: Invalid URL");
		parsing = false;
		return false;
	}
	if(qUrl.scheme() != "http") {
		logger()->error("Error: URL must start with 'http:'");
		parsing = false;
		return false;
	}
	if(qUrl.path().isEmpty()) {
		qUrl.setPath("/");
	}
	this->host = QString("http://%1").arg(qUrl.host());
	this->dir = this->host + QFileInfo(qUrl.path()).path();
	if(!this->dir.endsWith('/'))
		this->dir += "/";
	this->targets = targets;
	this->layer = layer;
	this->sameHostLink = sameHostLink;

	http.setHost(qUrl.host(), qUrl.port(80));
	buffer->open(QIODevice::WriteOnly);
	http.get(qUrl.path(), buffer);
	http.close();
	return true;
}

void HtmlParser::httpDone(bool error)
{
	if (error) {
		logger()->error("Error: " + http.errorString());
	}
	else
	{
		const QByteArray &html = buffer->data();
		// 解析html
		int ltPos = -1;		// '<'的位置
		for(int i = 0; i < html.size(); ++i) {
			switch(html.at(i))
			{
			case '<':		// 记录位置
				ltPos = i;
				break;
			case '>':		// 分析<>之间的内容
				if(ltPos != -1 && i > (ltPos + 1)) {
					parseString(html.mid(ltPos+1, i - ltPos - 1), targets);
				}
				break;
			default:
				break;
			}
		}
	}
	buffer->close();
	parsing = false;
	// 发送解析完成的信号
	emit done();
}

// 解析<>内的内容
void HtmlParser::parseString(const QString &str, std::vector<Target> &targets)
{
	// 第一个元素是Tag，后面是可能的Attributes
	QStringList tagAndAttrs = str.split(QRegExp("\\s+"), QString::SkipEmptyParts);
	if(tagAndAttrs.size() <= 1) return;		// 忽略没有Attribute的字符串
	foreach(Target target, targets) {
		if(tagAndAttrs[0].compare(target.tag, Qt::CaseInsensitive)) continue;
		// Tag符合，检测Attribute
		for(int i = 1; i < tagAndAttrs.size(); ++i) {
			int posOfEqual = tagAndAttrs[i].indexOf('=');
			if(posOfEqual <= 0) continue;
			if(tagAndAttrs[i].left(posOfEqual).compare(target.attr, Qt::CaseInsensitive)) continue;
			// Attribute符合，检测后缀
			QString value = trimQuote(tagAndAttrs[i].mid(posOfEqual + 1));
			if(target.exts.size() == 0 || endsWithAnyExt(value, target.exts)) {
				// 是绝对路径
				if(value.startsWith('/') || value.startsWith('\\')) {
					value = host + value;
				}
				else if(!value.startsWith("http:", Qt::CaseInsensitive)) {	// 是相对路径
					value = dir + value;
				}
				if(target.isHyperlink()) {
					if(!sameHostLink || value.startsWith(host, Qt::CaseInsensitive)) {
						if(links.indexOf(value) == -1)
							links.append(value);
					}
				}
				else {
					if(targetUrls.indexOf(value) == -1)
						targetUrls.append(value);
				}
				return;		// 找到后返回
			}
		}
	}
}

/// 去除字符串两边的空格、单引号和双引号
QString HtmlParser::trimQuote(const QString &str)
{
	int first = 0, last = str.size();
	for(; first < last; ++first) {
		QChar c = str.at(first);
		if(c != ' '	&& c != '"' && c != '\'')
			break;
	}
	for(--last; first < last; --last) {
		QChar c = str.at(last);
		if(c != ' '	&& c != '"' && c != '\'')
			break;
	}
	return str.mid(first, last - first + 1);
}

/// 检查字符串是否以某一个后缀结束
bool HtmlParser::endsWithAnyExt(const QString& str, const QStringList &exts)
{
	foreach(QString ext, exts) {
		if(!ext.startsWith('.'))
			ext = '.' + ext;
		if(str.endsWith(ext, Qt::CaseInsensitive))
			return true;
	}
	return false;
}

