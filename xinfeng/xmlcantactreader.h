#ifndef XMLCANTACTREADER_H
#define XMLCANTACTREADER_H

#include <QXmlStreamReader>
#include <QMap>
class QTreeWidget;
class QTreeWidgetItem;

class XmlCantactReader
{
public:
    XmlCantactReader(QTreeWidget *tree);
    bool readFile(const QString &fileName);
	bool createNumber2Name(const QString &fileName,QMap<QString,QString> *mapnumber2name);
private:
    void readBookindexElement();
	void readSmsSCollctionElement();
    void readEntryElement(QTreeWidgetItem *parent);
    void readPageElement(QTreeWidgetItem *parent);
    void skipUnknownElement();
	void readSmsSumElement(QTreeWidgetItem *parent);
	void readSmsElement(QTreeWidgetItem *parent);
   
	void readSmsElement2();
	void readSmsSumElement2();
	void readSmsSCollctionElement2(); 
public:
	QTreeWidget *treeWidget;
    QXmlStreamReader reader;
	QMap<QString,QString> *mapNumber2Name;
};

#endif
