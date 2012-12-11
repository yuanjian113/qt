#include <QtGui>

#include "qsimpledownloader.h"

QSimpleDownloader::QSimpleDownloader(QWidget *parent)
    : QWidget(parent)
{
	labelUrl = new QLabel(tr("&URL:"));
	labelUrl->setFixedWidth(60);
	labelUrl->setAlignment(Qt::AlignRight);
	editUrl = new QLineEdit();
	labelUrl->setBuddy(editUrl);
	QHBoxLayout *topLayout = new QHBoxLayout();
	topLayout->addWidget(labelUrl);
	topLayout->addWidget(editUrl);

	labelSaveTo = new QLabel(tr("&Save To:"));
	labelSaveTo->setFixedWidth(60);
	labelSaveTo->setAlignment(Qt::AlignRight);
	editSaveTo = new QLineEdit();
	labelSaveTo->setBuddy(editSaveTo);
	btnBrowse = new QPushButton(tr("&Browse..."));
	QHBoxLayout *midLayout = new QHBoxLayout();
	midLayout->addWidget(labelSaveTo);
	midLayout->addWidget(editSaveTo);
	midLayout->addWidget(btnBrowse);

	btnSetting = new QPushButton(tr("Se&tting..."));
	btnAbout = new QPushButton(tr("&About..."));
	btnAboutQt = new QPushButton(tr("About &Qt..."));
	btnAboutQt->setStatusTip(tr("Show the Qt library's About box"));
	btnDownload = new QPushButton(tr("&Download"));
	btnExit = new QPushButton(tr("E&xit"));
	QHBoxLayout *midLayout2 = new QHBoxLayout();
	midLayout2->addWidget(btnSetting);
	midLayout2->addWidget(btnAbout);
	midLayout2->addWidget(btnAboutQt);
	midLayout2->addStretch();
	midLayout2->addWidget(btnDownload);
	midLayout2->addWidget(btnExit);

	outputList = new QListWidget();

	QVBoxLayout *mainLayout = new QVBoxLayout();
	mainLayout->addLayout(topLayout);
	mainLayout->addLayout(midLayout);
	mainLayout->addLayout(midLayout2);
	mainLayout->addWidget(outputList);
	setLayout(mainLayout);

	setWindowTitle(tr("Qt Simple Downloader"));
	this->resize(600, 480);

	optionDlg = new OptionDlg(this);
	optionDlg->setWindowTitle(tr("Option"));
	optionDlg->resize(480, 320);

	connect(btnBrowse, SIGNAL(clicked()), this, SLOT(browse()));
	connect(btnSetting, SIGNAL(clicked()), this, SLOT(setting()));
	connect(btnAbout, SIGNAL(clicked()), this, SLOT(about()));
	connect(btnAboutQt, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
	connect(btnDownload, SIGNAL(clicked()), this, SLOT(download()));
	connect(btnExit, SIGNAL(clicked()), this, SLOT(close()));
}

QSimpleDownloader::~QSimpleDownloader()
{

}

void QSimpleDownloader::browse()
{
	editSaveTo->setText(QFileDialog::getExistingDirectory(this,
			tr("Select Directory"),
			".",
			QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks));
}

void QSimpleDownloader::setting()
{
	QUrl url(editUrl->text());

	outputList->addItem(QString("isValid = %1").arg(url.isValid() ? "true" : "false"));
	outputList->addItem(QString("isRelative = %1").arg(url.isRelative() ? "true" : "false"));
	outputList->addItem("scheme = " + url.scheme());
	outputList->addItem("host = " + url.host());
	outputList->addItem("path = " + url.path());
	outputList->addItem("toString = " + url.toString());

	QFileInfo fileInfo(url.path());
	outputList->addItem("fileInfo.path = " + fileInfo.path());
	outputList->addItem("fileInfo.fileName = " + fileInfo.fileName());
	outputList->addItem("fileInfo.filePath = " + fileInfo.filePath());

	optionDlg->setModal(true);
	optionDlg->show();
}

void QSimpleDownloader::about()
{
    QMessageBox::about(this, tr("About QSimpleDownloader"),
            tr("<h2>QSimpleDownloader 0.9</h2>"
               "<p>Copyright &copy; 2009 Sun Zhangfeng."
               "<p>QSimpleDownloader is a small application that "
               "parses a URL and returns the target urls and hyperlinks. "
               "The targets will be downloaded and the hyperlinks "
               "will be parsed recursively."));
}

void QSimpleDownloader::download()
{
	if(jobScheduler.isRunning()) {
		jobScheduler.stop();
		btnDownload->setText(tr("&Download"));
	}
	else {
		if(editUrl->text().isEmpty()) {
			QMessageBox::warning(this, tr("Qt Simple Downloader"),
					tr("URL must be not empty"));
			editUrl->setFocus();
			return;
		}
		std::vector<Target> targets, allTargets = optionDlg->getTargets();
		foreach(Target target, allTargets) {
			if(target.selected)
				targets.push_back(target);
		}
		if(targets.size() == 0) {
			QMessageBox::warning(this, tr("Qt Simple Downloader"),
					tr("You must select one target at least to download"));
			setting();
			return;
		}
		targets.push_back(Target("Hyperlink", "a", "href", QStringList()));

		jobScheduler.setMinFileSize(optionDlg->getMinFileSize());
		jobScheduler.setSaveInSingleDir(optionDlg->getSaveInSingleDir());
		jobScheduler.setFileExistsAction(optionDlg->getFileExistsAction());
		jobScheduler.start(editUrl->text(), editSaveTo->text(),
				optionDlg->getRecursiveLayer(), targets);
		btnDownload->setText(tr("Sto&p"));
		outputList->addItem("start downloading...");
	}
}

