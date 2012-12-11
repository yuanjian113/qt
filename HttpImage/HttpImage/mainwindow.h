#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QDialog>
#include "ui_mainwindow.h"
#include <QtNetwork>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
#include "qDebug"
#include "QStringList"
#include <shlobj.h>
#include "QFileDialog"
#include "QDir"
#include "QHttp"
#include "QUrl"
#include "QFileInfo"
#include "QFile"
#include "QIODevice"
#include "httpget.h"
#include "QStandardItem"
#include "QStandardItemModel"

class MainWindow : public QDialog
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~MainWindow();

private:
	Ui::MainWindowClass ui;
	QString savePath;
	QHttp* http;
	QStringList list;
	QFile* file;
	QStandardItemModel* standardItemModel;
	
private slots:
	void searchBtn_Clicked();
	void savePathBtn_Clicked();
	void saveBtn_Clicked();
	void replayFinished(QNetworkReply*);
	void enableSearchButton();
};

#endif // MAINWINDOW_H
