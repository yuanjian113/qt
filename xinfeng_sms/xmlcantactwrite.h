#ifndef XMLCANTACTWRITE_H
#define XMLCANTACTWRITE_H

#include <QtXml>
#include <iostream>
#include <QTreeWidget>

//������ϵ����Ϣ
void writeCantactSmsSum(QXmlStreamWriter *xmlWriter, QTreeWidgetItem *item);
bool writeCantactXml(const QString &fileName, QTreeWidget *treeWidget);

#endif