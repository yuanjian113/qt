#include <QtGui>
#include <QtXml>
#include <iostream>
#include <QMessageBox>
#include "xmlstreamreader.h"
#include <QMessageBox>
XmlStreamReader::XmlStreamReader(QTreeWidget *tree)
{
    treeWidget = tree;
}

void XmlStreamReader::CreateBlackTerm(QMap<QString,QString> *mapblackterm)
{
	mapBlackTerm = mapblackterm;
}

bool XmlStreamReader::readFile(const QString &fileName)
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
    while (!reader.atEnd())
	{
        if (reader.isStartElement())
		{
            if (reader.name() == "SmsCollection")
			{
                readSmsSCollctionElement();
            } else 
			{
                reader.raiseError(QObject::tr("Not a bookindex file"));
            }
        } else 
		{
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
void XmlStreamReader::readSmsSCollctionElement()
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

void XmlStreamReader::readSmsSumElement(QTreeWidgetItem *parent)
{
	QTreeWidgetItem *item = new QTreeWidgetItem(parent);
    item->setText(0, reader.attributes().value("term").toString());
    reader.readNext();
    while (!reader.atEnd()) 
	{
        if (reader.isStartElement()) 
		{
			if (reader.name() == "SmsSum") 
			{
                readSmsSumElement(treeWidget->invisibleRootItem());
            } 
            if (reader.name() == "Sms"  ) 
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

void XmlStreamReader::readSmsElement(QTreeWidgetItem *parent)
{	
	reader.readNext();
	QString strTerm = parent->text(0);
	QString strNumberTerm;
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
				strNumberTerm = reader.attributes().value("term").toString();
				QString strSmsNum = reader.readElementText();
				reader.readNext();		
				
				while(!reader.isStartElement())		
				{
					reader.readNext();
				}					
				if(reader.isStartElement()&&reader.name()=="Content")
				{
					QString strContent = reader.readElementText();
					if(strTerm.compare("ÐÅÏ¢")==0)
					{
						AddSmsItem(parent,strSmsNum,strContent);		
					}	
					else if(strTerm.compare("²Ý¸åÏä")==0)
					{
						AddSmsDDItem(parent,strSmsNum,strContent);		
					}
					else if(strTerm.compare("À¬»øÏä")==0)
					{
						if(mapBlackTerm!=NULL)
						{
							mapBlackTerm->insert(strSmsNum,strNumberTerm);
						//	QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, strSmsNum, strNumberTerm); 
						//	message->show();
						}
						AddSmsDDItem(parent,strSmsNum,strContent);		
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

void XmlStreamReader::AddSmsDDItem(QTreeWidgetItem *item,QString strNum,QString strContent)
{
	QString strName;
	QTreeWidgetItem *childitem = new QTreeWidgetItem(item);								
	strName=strNum;
	if(mapNumName.contains(strNum))
	{							
		strName = mapNumName.value(strNum);								
	}
	childitem->setText(0,strName);
	childitem->setText(1,strContent);							
}

void XmlStreamReader::AddSmsItem(QTreeWidgetItem *item,QString strNum,QString strContent)
{
	bool bfind = false;
	QString strName;
	QTreeWidgetItem* itemtmp = NULL;
	int i;
	if(mapNumSmsSum.contains(strNum))
	{
		bfind = true;	
	}
	if(!bfind)
	{
		QTreeWidgetItem *childitem = new QTreeWidgetItem(item);						
		{							
			strName=strNum;
			if(mapNumName.contains(strNum))
			{							
				strName = mapNumName.value(strNum);								
			}
			mapNumSmsSum.insert(strNum,1);
			childitem->setText(0,strName);
			childitem->setText(1,"(1)");							
		}
	}
	else
	{
		QTreeWidgetItem * parentItem = item;
		if(parentItem==NULL)
			return ;
		for(i = 0;i < parentItem->childCount();i++)
		{
			itemtmp = parentItem->child(i);
			strName=strNum;
			if(mapNumName.contains(strNum))
			{							
				strName = mapNumName.value(strNum);								
			}
			if(itemtmp->text(0).compare(strName)==0)
				break;
		}
		if(i>= parentItem->childCount())
		{
			//QDebug<<" AddSmsItem error";
		}
		else
		{
			mapNumSmsSum[strNum] ++;
			QString s = "("+QString::number(mapNumSmsSum[strNum], 10)+")"; 
			itemtmp->setText(1,s);		
		}
	} 
}

bool XmlStreamReader::isExitSmsNum(QString strNum, QMap<QString,int> mapNumSmsSum)
{
	return false;
}

void XmlStreamReader::skipUnknownElement()
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
