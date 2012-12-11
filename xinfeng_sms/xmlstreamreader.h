#ifndef XMLSTREAMREADER_H
#define XMLSTREAMREADER_H

#include <QXmlStreamReader>
#include <QMap>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class QTreeWidget;
class QTreeWidgetItem;

class XmlStreamReader
{

public:	
	XmlStreamReader(QTreeWidget *tree);
	bool isExitSmsNum(QString strNum, QMap<QString,int> mapNumSmsSum);
    bool readFile(const QString &fileName);
	void AddSmsItem(QTreeWidgetItem *item,QString strNum,QString strContent);
	void AddSmsDDItem(QTreeWidgetItem *item,QString strNum,QString strContent);//
	void CreateBlackTerm(QMap<QString,QString> *mapblackterm);//´´½¨À¬»øÏäµÄÓ³Éä
public:
	QMap<QString,int> mapNumSmsSum;
	QMap<QString,QString> mapNumName;
	QMap<QString,QString> *mapBlackTerm;
private:
    void readBookindexElement();
	void readSmsSCollctionElement();
    void readEntryElement(QTreeWidgetItem *parent);
    void readPageElement(QTreeWidgetItem *parent);
    void skipUnknownElement();
	void readSmsSumElement(QTreeWidgetItem *parent);
	void readSmsElement(QTreeWidgetItem *parent);
    QTreeWidget *treeWidget;
    QXmlStreamReader reader;
	
};

#endif
