#ifndef XMLSMSREADER_H
#define XMLSMSREADER_H

#include <QXmlStreamReader>
#include <QMap>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class QListWidget;
class QListWidgetItem;

class XmlSmsReader
{

public:	
	XmlSmsReader(QListWidget* listwidget,QString strName);
	bool isExitSmsNum(QString strNum, QMap<QString,int> mapNumSmsSum);
	bool findNumToName(QString strNum,QMap<QString,QString> mapNumName,QString strName);
    bool readFile(const QString &fileName);
	void AddSmsItem(QTreeWidgetItem *item,QString strNum,QString strContent);
public:
	QMap<QString,int> mapNumSmsSum;
	QMap<QString,QString> mapNumName;
	QString strSmsSum;
	QString strSmsName;
private:
    void readBookindexElement();
	void readSmsSCollctionElement();
    void readEntryElement();
    void readPageElement();
    void skipUnknownElement();
	void readSmsSumElement();
	void readSmsElement();
    QListWidget *listWidget;
    QXmlStreamReader reader;
	
};

#endif
