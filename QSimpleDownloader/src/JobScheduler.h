/*
 * JobPerformer.h
 *
 *  Created on: 2009-5-14
 *      Author: szf
 */

#ifndef JOBSCHEDULER_H_
#define JOBSCHEDULER_H_

#include <QTimer>
#include <QStringList>
#include <QList>
#include "log4qt/logger.h"

#include "HtmlParser.h"
#include "HttpGet.h"

using namespace Log4Qt;

typedef struct tagLinkAndLayer
{
	QString link;
	int layer;
	tagLinkAndLayer(const QString &s, int i)
		: link(s), layer(i) {}
} LinkAndLayer;

class JobScheduler : public QObject
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER

public:
	JobScheduler(QObject *parent = 0);
    void start(const QString &url, const QString &dir, int layer,
    		const std::vector<Target> &targets);
    void stop();
    bool isRunning() const { return timer.isActive(); }

    void setMinFileSize(int minFileSize) {
    	this->minFileSize = minFileSize;
    }
	void setSaveInSingleDir(bool saveInSingleDir) {
		this->saveInSingleDir = saveInSingleDir;
	}
	void setFileExistsAction(FileExistsAction fileExistsAction) {
		this->fileExistsAction = fileExistsAction;
	}

private slots:
	void checkList();
	void parserDone();
	void getterDone();

private:
	QTimer timer;
	QString baseUrl, baseDir;
	int baseLayer;
	std::vector<Target> targets;

	int minFileSize;
	bool saveInSingleDir;				// 将所有目标文件保存在基础目录下
	FileExistsAction fileExistsAction;	// 目标文件已存在时采取措施

	QStringList targetList;
	QList<LinkAndLayer> linkList;
	int targetIndex, linkIndex;
	HttpGet httpGet;
	HtmlParser htmlParser;
};

#endif /* JOBPERFORMER_H_ */
