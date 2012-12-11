#include <QtGui>
#include <QtXml>
#include <iostream>
#include <QMessageBox>
#include "xmlsmsreader.h"
#include <QMessageBox>
XmlSmsReader::XmlSmsReader(QListWidget* listwidget,QString strName)
{
	listWidget = listwidget;
	strSmsName = strName;
}

bool XmlSmsReader::readFile(const QString &fileName)
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

void XmlSmsReader::readSmsSCollctionElement()
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
                readSmsSumElement();
				break;
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

void XmlSmsReader::readSmsSumElement()
{
	QString strTerm = reader.attributes().value("term").toString();
    reader.readNext();
    while (!reader.atEnd()) 
	{
        if (reader.isStartElement()) 
		{
			if (reader.name() == "Sms" ) 
			{
                readSmsElement();
			//	break;
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

void XmlSmsReader::readSmsElement()
{
	reader.readNext();
	QString strItem;
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
				QString strNumberTerm = reader.attributes().value("term").toString();
				QString strSmsNum = reader.readElementText();
				QString str = strSmsNum;
				
				findNumToName(strSmsNum,mapNumName,str);
				if(str.compare(strSmsName)==0)
				{
					reader.readNext();							
					while(!reader.isStartElement())		
					{
						reader.readNext();
					}					
					if(reader.isStartElement()&&reader.name()=="Content")
					{
						QString strContent = reader.readElementText();	
						if(strNumberTerm.compare("·¢ËÍ")==0)
						{
							strItem="×Ô¼º:"+strContent;
						}
						else
						{
							strItem=str+":"+strContent;
						}
						QListWidgetItem *item = new QListWidgetItem(strItem,listWidget);
						listWidget->addItem(item);
					}			
				}
					
			}
			else if(reader.name()=="Sms")
			{
				readSmsElement();
			}
			else if(reader.name()=="SmsSum")
			{
				break;
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

void XmlSmsReader::AddSmsItem(QTreeWidgetItem *item,QString strNum,QString strContent)
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
			childitem->setText(1,"1");							
		}
	}
	else
	{
		QTreeWidgetItem * parentItem = item;
		if(parentItem==NULL)
			return ;
	//	QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, "Title", "1"); 
	//	message->show();
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
			QString s = QString::number(mapNumSmsSum[strNum], 10); 
			itemtmp->setText(1,s);		
		}
	} 
}

bool XmlSmsReader::isExitSmsNum(QString strNum, QMap<QString,int> mapNumSmsSum)
{
	return false;
}

bool XmlSmsReader::findNumToName(QString strNum,QMap<QString,QString> mapNumName,QString strName)
{
	return false;
}
void XmlSmsReader::skipUnknownElement()
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
