#ifndef XMLSTREAMWRITE_H
#define XMLSTREAMWRITE_H

#include <QtXml>
#include <iostream>
#include <QTreeWidget>
void writeSmsSum(QXmlStreamWriter *xmlWriter, QTreeWidgetItem *item);//������д����Ӧ������
bool writeXml(const QString &fileName, QTreeWidget *treeWidget);//����ݸ�������������
void addSmsElemt(const QString filename,QString strNumber,QString strContent,QString strTerm,QString strSmsSum);//����ͬ���͵���Ϣ��ӵ���Ӧ��������
void deleteSmsElemt(const QString filename,QString strNumber,QString strContent,QString strTerm);//ͨ����������Ϣȷ��ɾ��Ŀ�����

int combineXmlFile(QString strfile1,QString strfile2,QString strfile3);//��strfile1����Ϣ���ֺ�strfile2�Ĳݸ����������ϲ�Ϊstrfile3
#endif