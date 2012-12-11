#ifndef XMLCANTACTWRITE_H
#define XMLCANTACTWRITE_H

#include <QtXml>
#include <iostream>
#include <QTreeWidget>

//保存联系人信息
void writeCantactSmsSum(QXmlStreamWriter *xmlWriter, QTreeWidgetItem *item);
bool writeCantactXml(const QString &fileName, QTreeWidget *treeWidget);

#endif