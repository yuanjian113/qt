#include <QtGui>
#include <QtXml>
#include <iostream>
#include <QMessageBox>
#include "xmlcantactreader.h"

XmlCantactReader::XmlCantactReader(QTreeWidget *tree)
{
    treeWidget = tree;
}

bool XmlCantactReader::readFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                  << ": " << qPrintable(file.errorString())
                  << std::endl;
        return false;
    }

    reader.setDevice(&file);

    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            if (reader.name() == "SmsCollection") {
                readSmsSCollctionElement();
            } else {
                reader.raiseError(QObject::tr("Not a bookindex file"));
            }
        } else {
            reader.readNext();
        }
    }

    file.close();
    if (reader.hasError()) {
        std::cerr << "Error: Failed to parse file "
                  << qPrintable(fileName) << ": "
                  << qPrintable(reader.errorString()) << std::endl;
        return false;
    } else if (file.error() != QFile::NoError) {
        std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                  << ": " << qPrintable(file.errorString())
                  << std::endl;
        return false;
    }
    return true;
}

bool XmlCantactReader::createNumber2Name(const QString &fileName,QMap<QString,QString> *mapnumber2name)
{
	mapNumber2Name = mapnumber2name;
	QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                  << ": " << qPrintable(file.errorString())
                  << std::endl;
        return false;
    }

    reader.setDevice(&file);

    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isStartElement()) {
            if (reader.name() == "SmsCollection") {
                readSmsSCollctionElement2();
            } else {
                reader.raiseError(QObject::tr("Not a bookindex file"));
            }
        } else {
            reader.readNext();
        }
    }

    file.close();
    if (reader.hasError()) {
        std::cerr << "Error: Failed to parse file "
                  << qPrintable(fileName) << ": "
                  << qPrintable(reader.errorString()) << std::endl;
        return false;
    } else if (file.error() != QFile::NoError) {
        std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                  << ": " << qPrintable(file.errorString())
                  << std::endl;
        return false;
    }
    return true;
}

void XmlCantactReader::readSmsSCollctionElement2()
{
	reader.readNext();
    while (!reader.atEnd()) 
	{
        if (reader.isEndElement())
		{
            reader.readNext();
            break;
        }

        if (reader.isStartElement())
		{
            if (reader.name() == "SmsSum") 
			{
                readSmsSumElement2();
            } else 
			{
                skipUnknownElement();
            }
        } 
		else 
		{
            reader.readNext();
        }
    }
}


void XmlCantactReader::readSmsSumElement2()
{
    reader.readNext();
    while (!reader.atEnd()) 
	{
        if (reader.isStartElement()) 
		{
			if (reader.name() == "SmsSum") 
			{
                readSmsSumElement2();
            } 
            if (reader.name() == "Sms") 
			{
                readSmsElement2();
            } 
			else 
			{
                skipUnknownElement();
            }
        }
		else 
		{
            reader.readNext();
        }
    }
}


void XmlCantactReader::readSmsElement2()
{
	QString strName;
	QString strNumber;
	reader.readNext();
	while(!reader.atEnd())
		{
			if(reader.isEndElement())
			{
				reader.readNext();
				break;
			}
			if(reader.isStartElement())
			{
				if(reader.name()=="Number")
				{	
					strNumber = reader.readElementText();
					reader.readNext();							
					while(!reader.isStartElement())		
					{
						reader.readNext();
					}
					if(reader.isStartElement())
					{
						if(reader.name()=="Name")
						{
							strName = reader.readElementText();
							mapNumber2Name->insert(strNumber,strName);
						//	QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, strNumber, strName); 
						//	message->show();
						}
						break;
					}
				}
				else 
				{
					skipUnknownElement();
				}
			}
			else
			{
				reader.readNext();
			}
		}
}


void XmlCantactReader::readSmsSCollctionElement()
{
	reader.readNext();
    while (!reader.atEnd()) 
	{
        if (reader.isEndElement())
		{
            reader.readNext();
            break;
        }

        if (reader.isStartElement())
		{
            if (reader.name() == "SmsSum") 
			{
                readSmsSumElement(treeWidget->invisibleRootItem());
            } else 
			{
                skipUnknownElement();
            }
        } 
		else 
		{
            reader.readNext();
        }
    }
}

void XmlCantactReader::readSmsSumElement(QTreeWidgetItem *parent)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(parent);
	QString strTerm=reader.attributes().value("term").toString();
    item->setText(0, strTerm);
	//QMessageBox::warning(NULL, "warning", strTerm, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if(strTerm.compare("白名单")==0||strTerm.compare("黑名单")==0)
	{
		strTerm = reader.attributes().value("switch").toString();
		item->setText(1,strTerm);
	}	
    reader.readNext();
    while (!reader.atEnd()) 
	{
        if (reader.isStartElement()) 
		{
			if (reader.name() == "SmsSum") 
			{
                readSmsSumElement(treeWidget->invisibleRootItem());
            } 
            if (reader.name() == "Sms") 
			{
                readSmsElement(item);
            } 
			else 
			{
                skipUnknownElement();
            }
        }
		else 
		{
            reader.readNext();
        }
    }
}

void XmlCantactReader::readSmsElement(QTreeWidgetItem *parent)
{
		QTreeWidgetItem *item = new QTreeWidgetItem(parent);
		reader.readNext();
		while(!reader.atEnd())
		{
			if(reader.isEndElement())
			{
				reader.readNext();
				break;
			}
			if(reader.isStartElement())
			{
				if(reader.name()=="Number")
				{	
					item->setText(1,reader.readElementText());
					reader.readNext();							
					while(!reader.isStartElement())		
					{
						reader.readNext();
					}
					if(reader.isStartElement())
					{
						if(reader.name()=="Name")
							item->setText(0,reader.readElementText());
						break;
					}
				}
				else 
				{
					skipUnknownElement();
				}
			}
			else
			{
				reader.readNext();
			}
		}
}


void XmlCantactReader::skipUnknownElement()
{
    reader.readNext();
    while (!reader.atEnd()) {
        if (reader.isEndElement()) {
            reader.readNext();
            break;
        }

        if (reader.isStartElement()) {
            skipUnknownElement();
        } else {
            reader.readNext();
        }
    }
}
