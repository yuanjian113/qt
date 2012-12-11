#ifndef XMLSTREAMWRITE_H
#define XMLSTREAMWRITE_H

#include <QtXml>
#include <iostream>
#include <QTreeWidget>
void writeSmsSum(QXmlStreamWriter *xmlWriter, QTreeWidgetItem *item);//将短信写入相应类型中
bool writeXml(const QString &fileName, QTreeWidget *treeWidget);//保存草稿箱和垃圾箱短信
void addSmsElemt(const QString filename,QString strNumber,QString strContent,QString strTerm,QString strSmsSum);//将不同类型的信息添加到相应的信箱里
void deleteSmsElemt(const QString filename,QString strNumber,QString strContent,QString strTerm);//通过给定的信息确定删除目标短信

int combineXmlFile(QString strfile1,QString strfile2,QString strfile3);//将strfile1的信息部分和strfile2的草稿箱和垃圾箱合并为strfile3
#endif