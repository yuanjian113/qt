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
#include "QStandardItem"
#include "QStandardItemModel"
#include <QNetworkReply>  
#include <QNetworkRequest>  
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
	QNetworkAccessManager *nam;
private slots:
	void searchBtn_Clicked();

//	void replayFinished(QNetworkReply*);
	void enableSearchButton();
	void finishedSlot(QNetworkReply *reply)  ;
};

#endif // MAINWINDOW_H
