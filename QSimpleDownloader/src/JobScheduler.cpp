/*
 * JobPerformer.cpp
 *
 *  Created on: 2009-5-14
 *      Author: szf
 */
#include <QtCore>

#include "JobScheduler.h"
#include "Target.h"

JobScheduler::JobScheduler(QObject *parent)
	: QObject(parent)
{
	connect(&httpGet, SIGNAL(done()), this, SLOT(getterDone()));
	connect(&htmlParser, SIGNAL(done()), this, SLOT(parserDone()));
	connect(&timer, SIGNAL(timeout()), this, SLOT(checkList()));
}

void JobScheduler::start(const QString &url, const QString &dir, int layer,
		const std::vector<Target> &targets)
{
	baseUrl = url;
	baseDir = dir;
	targetList.clear();
	linkList.clear();
	targetIndex = 0;
	linkIndex = 0;
	linkList.append(LinkAndLayer(url, layer));
	this->targets = targets;
	timer.start(1000);
}

void JobScheduler::stop()
{
	timer.stop();
	htmlParser.stop();
	httpGet.stop();
}

void JobScheduler::checkList()
{
	// 没有在解析，且有解析任务
	if(!htmlParser.isParsing() && linkIndex < linkList.size()) {
		QString url = linkList[linkIndex].link;
		int layer = linkList[linkIndex].layer;
		++linkIndex;
		logger()->debug(QString(tr("parsing url = %1, layer = %2...")).arg(url).arg(layer));

		// 解析HTML
		htmlParser.parse(layer, url, targets, true);
	}

	// 没有在下载，且有下载任务
	if(!httpGet.isDownloading() && targetIndex < targetList.size()) {
		QUrl qUrl(targetList[targetIndex]);
		++targetIndex;
		QString localFileName = QFileInfo(qUrl.path()).filePath();
		if(saveInSingleDir) {
			for(int i = 1; i < localFileName.size(); ++i) {
				if(localFileName[i] == QChar('/') || localFileName[i] == QChar('\\'))
					localFileName[i] = QChar('.');
			}
		}
		localFileName = baseDir + localFileName;
		if(fileExistsAction == feaIgnore || !QFile::exists(localFileName)) {
			QDir dir = QFileInfo(localFileName).dir();
			if(!dir.exists() && !dir.mkpath(dir.path())) {
				logger()->error("Cant create dir: " + dir.path());
			}
			else {
				httpGet.getFile(qUrl, localFileName, minFileSize);
			}
		}
	}
}

/// 解析完毕
void JobScheduler::parserDone()
{
	QStringList targetUrls = htmlParser.getTargetUrls();
	QStringList links = htmlParser.getLinks();
	int layer = htmlParser.getLayer();
	logger()->debug(QString("   %1 targets and %2 links found")
			.arg(targetUrls.size())
			.arg(links.size()));

	// 目标链接
	foreach(QString targetUrl, targetUrls) {
		if(targetList.indexOf(targetUrl) != -1) continue;
		targetList.append(targetUrl);
	}

	// 超链接
	if(layer > 1) {
		foreach(QString link, links) {
			bool exists = false;
			foreach(LinkAndLayer ll, linkList) {
				if(ll.link == link) {
					exists = true;
					break;
				}
			}
			if(!exists)
				linkList.append(LinkAndLayer(link, layer - 1));
		}
	}
}

/// 下载完毕
void JobScheduler::getterDone()
{
}
