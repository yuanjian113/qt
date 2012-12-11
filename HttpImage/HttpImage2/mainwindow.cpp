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

	nam = new QNetworkAccessManager(this);  
    QObject::connect(nam, SIGNAL(finished(QNetworkReply*)),  
             this, SLOT(finishedSlot(QNetworkReply*)));  
	QObject::connect(ui.searchBtn,SIGNAL(clicked()),this,SLOT(searchBtn_Clicked()));
//	QObject::connect(ui.pathSetBtn,SIGNAL(clicked()),this,SLOT(savePathBtn_Clicked()));
//	QObject::connect(ui.saveBtn,SIGNAL(clicked()),this,SLOT(saveBtn_Clicked()));
	QObject::connect(ui.urlLineEdit,SIGNAL(textChanged(QString)),this,SLOT(enableSearchButton()));

	ui.urlLineEdit->setFocus();

}

MainWindow::~MainWindow()
{

}

void MainWindow::searchBtn_Clicked()
{
	ui.searchBtn->setEnabled(false);
	QString surl = ui.urlLineEdit->text().trimmed();
	QUrl url(surl);  
    QNetworkReply* reply = nam->get(QNetworkRequest(url));  
}

void MainWindow::finishedSlot(QNetworkReply *reply)  
{  
#if 1  
     // Reading attributes of the reply  
     // e.g. the HTTP status code  
     QVariant statusCodeV =  
     reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);  
     // Or the target URL if it was a redirect:  
     QVariant redirectionTargetUrl =  
     reply->attribute(QNetworkRequest::RedirectionTargetAttribute);  
     // see CS001432 on how to handle this  
  
     // no error received?  
     if (reply->error() == QNetworkReply::NoError)  
     {  
         // read data from QNetworkReply here  
  
         // Example 1: Creating QImage from the reply  
         //QImageReader imageReader(reply);  
         //QImage pic = imageReader.read();  
  
         // Example 2: Reading bytes form the reply  
         QByteArray bytes = reply->readAll();  // bytes  
         //QString string(bytes); // string  
         QString string = QString::fromUtf8(bytes);  
  
         ui.textBrowser->setText(string);  
     }  
     // Some http error received  
     else  
     {  
         // handle errors here  
     }  
  
     // We receive ownership of the reply object  
     // and therefore need to handle deletion.  
     reply->deleteLater();  
#endif  
}  

void MainWindow::enableSearchButton()
{
	ui.searchBtn->setEnabled(!ui.urlLineEdit->text().isEmpty());
}