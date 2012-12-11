#ifndef CANTACTTREEWIDGET_H
#define CANTACTTREEWIDGET_H

#include <QtGui/QMainWindow>
#include <qtreewidget.h>
#include <qevent.h>
#include <qmenu.h>
#include <QMap>

class CantactTreeWidget : public QTreeWidget
{
	Q_OBJECT

public:
	CantactTreeWidget(QWidget *parent = 0);
	~CantactTreeWidget();
	void 			createActions();
	QString			strCantactPathOpen;
	QString			strCantactPathSave;
	QString  		strMessagePathOpen;
//	QString			strMessagePathSave;
	QMap<QString,QString> mapNameNumber;
	QTreeWidgetItem	*currentWidgetItem;
public:
	void 			createMapNameNumber();
protected:
	void 			contextMenuEvent ( QContextMenuEvent * event ); 
	void       		mouseDoubleClickEvent(QMouseEvent *event);	
	
public slots:
	void addCantact();//�����ϵ��
	void sendMessage();//������Ϣ
	void editCantact();//�༭��ϵ��
	void deleteCantact();//ɾ����ϵ��
	void recoverCantact();
	
	void moveToBlacklist();//����������
	void StartWhitelist();//����������			

	void moveToWhitelist();//����������
	void StartBlacklist();//����������
private:
	QAction			*addCantactAction;//�����ϵ��
	QAction 		*sendMessageAction;//������Ϣ
	QAction 		*editCantactAction;//�༭��ϵ��
	QAction			*deleteCantactAction;//ɾ����ϵ��
	
	QAction 		*recoverCantactAction;//�ָ���ϵ��
	
	QAction			*editWhitelistAction;//�༭������
	QAction			*deleteWhitelistAction;//ɾ��������
	QAction			*moveToBlacklistAction;//����������
	QAction			*StartWhitelistAction;//����������			
	
	QAction			*editBlacklistAction;//�༭������
	QAction			*deleteBlacklistAction;//ɾ��������
	QAction			*moveToWhitelistAction;//����������
	QAction			*StartBlacklistAction;//����������
	QMenu 			*popMenu;	
	QModelIndex 	curIndex;//��ǰ˫��ѡ��
	
	QTreeWidgetItem *blackTreeItem;
	QTreeWidgetItem *whiteTreeItem;
	QTreeWidgetItem *cantactTreeItem;
	
	bool			whiteliststart;
	bool			blackliststart;
};

#endif