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
	QModelIndex  	getCurIndex();//��õ�ǰ˫��ѡ��

	QString 		strCantactNumber;//��¼��ǰ�Է�����
	void            setCantactNumber(QString strNumber);
private slots:
	void			deleteMessage();//ɾ������
	void			transpondItem();//ת������
signals:
	//���˫��
protected:
	void 			contextMenuEvent ( QContextMenuEvent * event );  //����Ҽ��˵�
private:
	QAction 		*deleteMessageAction;//ɾ����Ϣ
	QAction			*transpondAction;//ת��
	QMenu 			*popMenu;
	QModelIndex 	curIndex;//��ǰ˫��ѡ��
	QString			strMessagePathOpen;
//	QString			strMessagePathSave;
	QListWidgetItem *currentClickItem;
};

#endif