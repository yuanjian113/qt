#include "xmlcantactwrite.h"

void writeCantactSmsSum(QXmlStreamWriter *xmlWriter, QTreeWidgetItem *item)
{
	xmlWriter->writeStartElement("SmsSum");
	xmlWriter->writeAttribute("term",item->text(0));
	xmlWriter->writeAttribute("switch",item->text(1));
	for(int i = 0;i < item->childCount();++i)
	{
		xmlWriter->writeStartElement("Sms");
		xmlWriter->writeTextElement("Number",item->child(i)->text(1));
		xmlWriter->writeTextElement("Name",item->child(i)->text(0));
		xmlWriter->writeEndElement();
	}
	xmlWriter->writeEndElement();
}

bool writeCantactXml(const QString &fileName, QTreeWidget *treeWidget)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly | QFile::Text))
	{
        std::cerr << "Error: Cannot write file "
                  << qPrintable(fileName) << ": "
                  << qPrintable(file.errorString()) << std::endl;
        return false;
    }

    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("SmsCollection");
    for (int i = 0; i < treeWidget->topLevelItemCount(); ++i)
		  writeCantactSmsSum(&xmlWriter,treeWidget->topLevelItem(i));
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