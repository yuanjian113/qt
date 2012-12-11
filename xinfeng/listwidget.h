#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QtGui/QMainWindow>
#include <QListWidget>
#include <qevent.h>
#include <QMenu>
#include <QMap>
class ListWidget : public QListWidget
{
	Q_OBJECT
	
public:
	ListWidget(QString strcantactnumber,QWidget *parent = 0);
	~ListWidget();
	void 			createActions();
	QModelIndex  	getCurIndex();//获得当前双击选项

	QString 		strCantactNumber;//记录当前对方号码
	void            setCantactNumber(QString strNumber);
private slots:
	void			deleteMessage();//删除短信
	void			transpondItem();//转发短信
signals:
	//鼠标双击
protected:
	void 			contextMenuEvent ( QContextMenuEvent * event );  //添加右键菜单
private:
	QAction 		*deleteMessageAction;//删除信息
	QAction			*transpondAction;//转发
	QMenu 			*popMenu;
	QModelIndex 	curIndex;//当前双击选项
	QString			strMessagePathOpen;
//	QString			strMessagePathSave;
	QListWidgetItem *currentClickItem;
};

#endif