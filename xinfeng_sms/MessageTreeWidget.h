#ifndef MESSAGETREEWIDGET_H
#define MESSAGETREEWIDGET_H

#include <QtGui/QMainWindow>
#include <QTreeWidget>
#include <qevent.h>
#include <QMenu>
#include <QMap>
class MessageTreeWidget : public QTreeWidget
{
	Q_OBJECT
	
public:
	QMap<QString,QString> mapblackNumberTerm;
	QMap<QString,QString> mapName2Number;
	QMap<QString,QString> mapNumber2Name;
public:
	MessageTreeWidget(QWidget *parent = 0);
	~MessageTreeWidget();
	void 			createActions();
	QModelIndex  	getCurIndex();//��õ�ǰ˫��ѡ��
	void 			SwitchNumber2Name(QMap<QString,QString> mapnumber2name,QMap<QString,QString> &mapname2number);
private slots:
	void			deleteMessage();
	void 			readMessageItem();
	void 			recoverMessageItem();
	void			transpondItem();
	void 			updateTreeAllItem();
	void 			importSms();
	
protected:
	void 			contextMenuEvent ( QContextMenuEvent * event );  
	void       		mouseDoubleClickEvent(QMouseEvent *event);
	
private:
	QAction 		*readMessageAction;//�鿴��Ϣ
	QAction 		*deleteMessageAction;//ɾ����Ϣ
	QAction 		*recoverAction;//�ָ�
	QAction			*transpondAction;//ת��
	QAction			*importSmsAction;//�������
	
	QMenu 			*popMenu;
	QModelIndex 	curIndex;//��ǰ˫��ѡ��
	QString			strMessagePathOpen;
	QString			strMessagePathSave;
	QTreeWidgetItem *currentClickItem;
};

#endif