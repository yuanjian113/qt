#ifndef QSIMPLEDOWNLOADER_H
#define QSIMPLEDOWNLOADER_H

#include <QtGui/QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QListWidget>
#include "log4qt/logger.h"

#include "OptionDlg.h"
#include "JobScheduler.h"

using namespace Log4Qt;

class QSimpleDownloader : public QWidget
{
    Q_OBJECT
    LOG4QT_DECLARE_QCLASS_LOGGER

public:
    QSimpleDownloader(QWidget *parent = 0);
    ~QSimpleDownloader();

private slots:
	void browse();
	void setting();
    void about();
	void download();

private:
	QLabel *labelUrl;
	QLineEdit *editUrl;
	QLabel *labelSaveTo;
	QLineEdit *editSaveTo;
	QPushButton *btnBrowse;
	QPushButton *btnSetting;
	QPushButton *btnAbout;
	QPushButton *btnAboutQt;
	QPushButton *btnDownload;
	QPushButton *btnExit;
	QListWidget *outputList;

	OptionDlg *optionDlg;
	JobScheduler jobScheduler;
};

#endif // QSIMPLEDOWNLOADER_H
