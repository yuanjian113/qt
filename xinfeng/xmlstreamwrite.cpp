#include "xmlstreamwrite.h"
#include <QXmlStreamReader>
#include <QMessageBox>
#include <QtXml/QDomDocument>
#include <QtCore/QFile>
#include <QtCore/QTextStream>
#include <QtCore/QDir>
#include <QDomNodeList>
void writeSmsSum(QXmlStreamWriter *xmlWriter, QTreeWidgetItem *item)
{
	xmlWriter->writeStartElement("SmsSum");
	xmlWriter->writeAttribute("term",item->text(0));
	
	for(int i = 0;i < item->childCount();++i)
	{
		xmlWriter->writeStartElement("Sms");
		xmlWriter->writeTextElement("Number",item->child(i)->text(0));
		xmlWriter->writeTextElement("Content",item->child(i)->text(1));
		xmlWriter->writeEndElement();
	}
	xmlWriter->writeEndElement();
}

bool writeXml(const QString &fileName, QTreeWidget *treeWidget)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text)) {
        std::cerr << "Error: Cannot write file "
                  << qPrintable(fileName) << ": "
                  << qPrintable(file.errorString()) << std::endl;
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("SmsCollection");
    for (int i = 1; i < treeWidget->topLevelItemCount(); ++i)
		  writeSmsSum(&xmlWriter,treeWidget->topLevelItem(i));
    xmlWriter.writeEndDocument();

    file.close();
    if (file.error()) {
        std::cerr << "Error: Cannot write file "
                  << qPrintable(fileName) << ": "
                  << qPrintable(file.errorString()) << std::endl;
        return false;
    }
    return true;
}

void addSmsElemt(const QString filename,QString strNumber,QString strContent,QString strTerm,QString strSmsSum)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly)) return ;
	QDomDocument doc;
	if (!doc.setContent(&file))
	{
		file.close();
		return ;
	}
	file.close();
	QDomNodeList list = doc.elementsByTagName("SmsSum");
	//以标签名进行查找
	for(int i=0; i<list.count(); i++)
	{
		QDomElement e = list.at(i).toElement();
		if(e.attribute("term") == strSmsSum)
		{  //如果元素的“编号”属性值与我们所查的相同
		
			QDomElement d = e.toElement();	
			QDomElement book = doc.createElement("Sms");
			QDomAttr id = doc.createAttribute("term");
			QDomElement title = doc.createElement("Number");
			QDomElement author = doc.createElement("Content");
			QDomText text;

			id.setValue(strTerm);
			//我们获得了最后一个孩子结点的编号，然后加1，便是新的编号
			title.setAttributeNode(id);
			text = doc.createTextNode(strNumber);
			title.appendChild(text);
			text = doc.createTextNode(strContent);
			author.appendChild(text);
			book.appendChild(title);
			book.appendChild(author);
			e.appendChild(book);
			break;
		}
	}

	if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
		QTextStream out(&file);
	doc.save(out,4);   //将文档保存到文件，4为子元素缩进字符数
	file.close();
}

void deleteSmsElemt(const QString filename,QString strNumber,QString strContent,QString strTerm)
{
	QFile file(filename);
	if (!file.open(QIODevice::ReadOnly)) return ;
	QDomDocument doc;
	if (!doc.setContent(&file))
	{
		file.close();
		return ;
	}
	file.close();
	QDomNodeList list = doc.elementsByTagName("SmsSum");
	//以标签名进行查找
	for(int i=0; i<list.count(); i++)
	{
		QDomElement e = list.at(i).toElement();
		if(e.attribute("term") == "信息")
		{  
			//如果元素的“编号”属性值与我们所查的相同
			QDomNodeList smsList = list.at(i).childNodes();
			for(int j= 0;j<smsList.count();j++)
			{
				
				QDomNodeList childSmsList = smsList.at(j).childNodes();
				QString strSmsNumber = childSmsList.at(0).toElement().firstChild().nodeValue();
				QString strSmsTerm = childSmsList.at(0).toElement().attribute("term");
				
				if(strSmsNumber.compare(strNumber)==0&&strSmsTerm.compare(strTerm)==0)
				{
					e.removeChild(smsList.at(j));
				//	QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, strNumber,strTerm); 
				//	message->show();
					break;
				}
			}
		}
	}

	if(!file.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
		QTextStream out(&file);
	doc.save(out,4);   //将文档保存到文件，4为子元素缩进字符数
	file.close();
}


//将strfile1的信息部分和strfile2的草稿箱和垃圾箱合并为strfile3
int combineXmlFile(QString strfile1,QString strfile2,QString strfile3)
{
	QFile file1(strfile1);
	QFile file2(strfile2);
	QFile file3(strfile3);
	if (!file1.open(QIODevice::ReadOnly)) return 0;
	if (!file2.open(QIODevice::ReadOnly)) return 0;
	QDomDocument doc1;//文档1
	QDomDocument doc2;//文档2
	if (!doc1.setContent(&file1))
	{
		file1.close();
		return 0;
	}
	if (!doc2.setContent(&file2))
	{
		file2.close();
		return 0;
	}
	QDomElement docElem1 = doc1.documentElement();
	QDomElement docElem2 = doc2.documentElement();
	
	QDomNodeList list1 = doc1.elementsByTagName("SmsSum");
	//以标签名进行查找
	for(int i=0; i<list1.count(); i++)
	{
		QDomElement e = list1.at(i).toElement();
		
		QString str= e.attribute("term");
		if(str.compare("草稿箱")==0||str.compare("垃圾箱")==0)
		{  
			QDomElement root = doc1.documentElement();
			root.removeChild(list1.at(i));
			i --;
		}
	}
	
	QDomNodeList list = doc2.elementsByTagName("SmsSum");
	//以标签名进行查找
	for(int j=0; j< list.count(); j++)
	{
		QDomElement e = list.at(j).toElement();
		
		QString str= e.attribute("term");
		int ret = j;
		QString strSum =QString::number(ret, 10);;
	//	QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, strSum, str); 
	//	message->show();
		if(str.compare("草稿箱")==0||str.compare("垃圾箱")==0)
		{ 
			QDomElement tmp = e.cloneNode(true).toElement();
			docElem1.appendChild(tmp);//如果直接加入以后e时，list内已经删除了容易出错
		}
	}
	
	if(!file3.open(QIODevice::WriteOnly | QIODevice::Truncate)) return 0;
		QTextStream out(&file3);
	doc1.save(out,4);   //将文档保存到文件，4为子元素缩进字符数
	file3.close();
	return 1;
}