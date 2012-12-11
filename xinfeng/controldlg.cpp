#include <QtGui>
#include"controldlg.h"
#include <QtXml>
#include <iostream>
#include <QMessageBox>
bool writeXml(const QString &fileName,QString strName,QString strNumber,QString strEmail,QString strAddress);
bool readxml(const QString &fileName,QString &strName,QString &strNumber,QString &strEmail,QString &strAddress);

ControlDlg::ControlDlg(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    connect(pushButtonUpadte, SIGNAL(clicked()), this, SLOT(UpadteControl()));
    connect(pushButtonCancel, SIGNAL(clicked()), this, SLOT(reject()));
	QString strName;
	QString strNumber;
	QString strEmail;
	QString strAddress;
	readxml("xml/control.xml",strName, strNumber, strEmail, strAddress);
	textEditName->setPlainText(strName );
	textEditNumber->setPlainText(strNumber);
	textEditEmail->setPlainText(strEmail);
	textEditAddress->setPlainText(strAddress);
}

void ControlDlg::UpadteControl()
{
	
	QString strName = textEditName->toPlainText();
	QString strNumber= textEditNumber->toPlainText();
	QString strEmail= textEditEmail->toPlainText();
	QString strAddress= textEditAddress->toPlainText();
	writeXml("xml/control.xml",strName, strNumber, strEmail, strAddress);
	emit close();
}

bool readxml(const QString &fileName,QString &strName,QString &strNumber,QString &strEmail,QString &strAddress)
{
	QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                  << ": " << qPrintable(file.errorString())
                  << std::endl;
        return false;
    }
	QXmlStreamReader reader;
    reader.setDevice(&file);

    reader.readNext();
    while (!reader.atEnd()) 
	{
		 if (reader.isEndElement())
		{
			reader.readNext();				
		}
        if (reader.isStartElement()) 
		{
			if(reader.name()=="name")
				strName = reader.readElementText();
			else if(reader.name()=="number")
				strNumber = reader.readElementText();
			else if(reader.name()=="email")
				strEmail = reader.readElementText();
			else if(reader.name()=="address")
				strAddress = reader.readElementText();  
			else 
				reader.readNext();			
        }
		else 
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

bool writeXml(const QString &fileName,QString strName,QString strNumber,QString strEmail,QString strAddress)
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
    xmlWriter.writeStartElement("info");
    xmlWriter.writeTextElement("name",strName);
	xmlWriter.writeTextElement("number",strNumber);
	xmlWriter.writeTextElement("email",strEmail);
	xmlWriter.writeTextElement("address",strAddress);
	xmlWriter.writeEndElement();
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