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
	void addCantact();//添加联系人
	void sendMessage();//发送信息
	void editCantact();//编辑联系人
	void deleteCantact();//删除联系人
	void recoverCantact();
	
	void moveToBlacklist();//移至黑名单
	void StartWhitelist();//开启白名单			

	void moveToWhitelist();//移至白名单
	void StartBlacklist();//开启黑名单
private:
	QAction			*addCantactAction;//添加联系人
	QAction 		*sendMessageAction;//发送信息
	QAction 		*editCantactAction;//编辑联系人
	QAction			*deleteCantactAction;//删除联系人
	
	QAction 		*recoverCantactAction;//恢复联系人
	
	QAction			*editWhitelistAction;//编辑白名单
	QAction			*deleteWhitelistAction;//删除白名单
	QAction			*moveToBlacklistAction;//移至黑名单
	QAction			*StartWhitelistAction;//开启白名单			
	
	QAction			*editBlacklistAction;//编辑黑名单
	QAction			*deleteBlacklistAction;//删除黑名单
	QAction			*moveToWhitelistAction;//移至白名单
	QAction			*StartBlacklistAction;//开启黑名单
	QMenu 			*popMenu;	
	QModelIndex 	curIndex;//当前双击选项
	
	QTreeWidgetItem *blackTreeItem;
	QTreeWidgetItem *whiteTreeItem;
	QTreeWidgetItem *cantactTreeItem;
	
	bool			whiteliststart;
	bool			blackliststart;
};

#endif