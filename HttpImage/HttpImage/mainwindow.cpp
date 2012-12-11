#include "mainwindow.h"


MainWindow::MainWindow(QWidget *parent, Qt::WFlags flags)
	: QDialog(parent, flags)
{
	ui.setupUi(this);

	#ifdef UNICODE
	#define TCHARToQString(char)     QString::fromUtf16((char))
	#else
	#define TCHARToQString(char)     QString::fromLocal8Bit((char))
	#endif

	TCHAR folder[MAX_PATH] = {0};
//	SHGetSpecialFolderPath(NULL, folder, CSIDL_PERSONAL, 0);
	savePath = "";
	savePath += "\\My Pictures";

	http = new QHttp(this);
	connect(http,SIGNAL(requestFinished(int,bool)),this,SLOT(requestFinished(int,bool)));

	QObject::connect(ui.searchBtn,SIGNAL(clicked()),this,SLOT(searchBtn_Clicked()));
	QObject::connect(ui.pathSetBtn,SIGNAL(clicked()),this,SLOT(savePathBtn_Clicked()));
	QObject::connect(ui.saveBtn,SIGNAL(clicked()),this,SLOT(saveBtn_Clicked()));
	QObject::connect(ui.urlLineEdit,SIGNAL(textChanged(QString)),this,SLOT(enableSearchButton()));

	ui.urlLineEdit->setFocus();
	ui.saveBtn->setEnabled(false);
	ui.searchBtn->setEnabled(false);
}

MainWindow::~MainWindow()
{
	
}

void MainWindow::searchBtn_Clicked()
{
	ui.searchBtn->setEnabled(false);
	QString url = ui.urlLineEdit->text().trimmed();
	QNetworkAccessManager *manager = new QNetworkAccessManager(this);
	connect(manager,SIGNAL(finished(QNetworkReply*)),this,SLOT(replayFinished(QNetworkReply*)));
	
	manager->get(QNetworkRequest(url));
}

void MainWindow::savePathBtn_Clicked()
{
	QFileDialog dialog(this,tr("choose save path!"),savePath);
	dialog.setFileMode(QFileDialog::DirectoryOnly);
	if (dialog.exec()==QFileDialog::Accepted)
	{
		savePath = (dialog.selectedFiles())[0];
	}
}

void MainWindow::saveBtn_Clicked()
{
	QDir dir(savePath);
	if (!dir.exists())
	{
		dir.mkdir(savePath);
	}

	ui.saveBtn->setEnabled(false);
	int con = list.count();
	for (int i = 0; i < con;i++)
	{
		QUrl url(list[i]);
		QFileInfo fileInfo(url.path());
		QString fileName = fileInfo.fileName();
		QString str = savePath +"\\"+ fileName;

		HttpGet* getter = new HttpGet(this);
		getter->downloadFile(url,str);
	}
	ui.saveBtn->setEnabled(true);
}

void MainWindow::replayFinished(QNetworkReply *replay)
{
	QString html = tr(replay->readAll());
	html.toLower();
	html.replace('\'','\"');
	
	QRegExp reg("<img.*src *= *['\"](.*)[\"'].*>");
	int pos =0;
	reg.setMinimal(true);

	list.clear();
	standardItemModel = new QStandardItemModel(this);
	while((pos = reg.indexIn(html,pos)) != -1)
	{
		
		QString str = reg.cap(1);
		int end = str.indexOf('\"',1);
		QString s = str.left(end);
		
		if (!list.contains(s,Qt::CaseInsensitive))
		{
			list<<s;
			QStandardItem* item = new QStandardItem(s);
			standardItemModel->appendRow(item);
		}

		pos+=reg.matchedLength();
	}
	
	int count = list.count();
	ui.countLbl->setText(QString(tr("共匹配出%1条记录")).arg(count));
	ui.listView->setModel(standardItemModel);
	if (count > 0)
	{
		ui.saveBtn->setEnabled(true);
	}
	else
	{
		ui.saveBtn->setEnabled(false);
	}

	ui.searchBtn->setEnabled(true);
}


void MainWindow::enableSearchButton()
{
	ui.searchBtn->setEnabled(!ui.urlLineEdit->text().isEmpty());
}