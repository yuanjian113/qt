#include "CantactTreeWidget.h"
#include "xmlcantactreader.h"
#include "xmlcantactwrite.h"
#include "CantactDialog.h"
#include "xmlstreamreader.h"
#include "xmlstreamwrite.h"
#include "xmlsmsreader.h"
#include "talkdlg.h"
#include <QMessageBox>
#include <string>
#include <qlineedit.h>
using std::string;

CantactTreeWidget::CantactTreeWidget(QWidget *parent)
: QTreeWidget(parent)
{
	popMenu = new QMenu(this);
	XmlCantactReader reader(this);
	createActions();
	
	//treeWidget->setWindowTitle("QTreeWidget");  
    //�趨ͷ������  
    this->setHeaderLabels(QStringList()<<""<<"");  

	strMessagePathOpen = "xml/message.xml";
	//strMessagePathSave = "xml/message.xml";
	
	strCantactPathOpen = "xml/cantact.xml";
	strCantactPathSave = "xml/cantact.xml";
	reader.readFile(strCantactPathOpen);
	this->topLevelItem(0)->setIcon(0, QIcon(":/images/Inboximage.png"));
	this->topLevelItem(1)->setIcon(0, QIcon("images/Sendimage.png"));
	this->topLevelItem(2)->setIcon(0, QIcon("images/Draftsimage.png"));
	blackTreeItem = this->topLevelItem(2);
	whiteTreeItem = this->topLevelItem(1);
  	cantactTreeItem = this->topLevelItem(0);
	if(blackTreeItem->text(0).compare("������")==0)
	{
		if(blackTreeItem->text(1).compare("����")==0)
		{
			blackliststart = true;
		}
		else
			blackliststart = false;
	}
	if(whiteTreeItem->text(0).compare("������")==0)
	{
		if(whiteTreeItem->text(1).compare("����")==0)
		{
			whiteliststart = true;
		}
		else
			whiteliststart = false;
	}
}

CantactTreeWidget::~CantactTreeWidget()
{
	writeCantactXml(strCantactPathSave,this);
}

void CantactTreeWidget::contextMenuEvent ( QContextMenuEvent * event )
{
	popMenu->clear();//���ԭ�в˵�
	QTreeWidgetItem *item = NULL;
	QPoint point = event->pos();//�ȵ���������
	
	item = this->itemAt(point);
	if(item == NULL)
	{
		return ;
	}
	currentWidgetItem = item;
	QTreeWidgetItem *parent = item->parent();
	if(parent == NULL)
	{
		if(currentWidgetItem->text(0).compare("������")==0)
		{
			if(currentWidgetItem->text(1).compare("����")==0)
			{
				StartBlacklistAction->setText("�رպ�����");
			}
			else
				StartBlacklistAction->setText("����������");
			popMenu->addAction(StartBlacklistAction);
		}
		else if(currentWidgetItem->text(0).compare("������")==0)
		{
			if(currentWidgetItem->text(1).compare("����")==0)
			{
				StartWhitelistAction->setText("�رհ�����");
			}
			else
				StartWhitelistAction->setText("����������");
			popMenu->addAction(StartWhitelistAction);
		}
		else if(currentWidgetItem->text(0).compare("��ϵ��")==0)
		{
			popMenu->addAction(addCantactAction);
		}
			
	}
	else
	{
		QString strPName = parent->text(0);
		if(QString::compare(strPName,"��ϵ��")==0)
		{	
			popMenu->addAction(sendMessageAction);
			popMenu->addAction(editCantactAction);
			popMenu->addAction(moveToBlacklistAction);
			popMenu->addAction(moveToWhitelistAction);
			popMenu->addAction(deleteCantactAction);
		}
		else if(QString::compare(strPName,"������")==0)
		{
			popMenu->addAction(editBlacklistAction);
			popMenu->addAction(deleteBlacklistAction);
			popMenu->addAction(moveToWhitelistAction);	
			popMenu->addAction(recoverCantactAction);
		}
		else if(QString::compare(strPName,"������")==0)
		{
			popMenu->addAction(editWhitelistAction);
			popMenu->addAction(deleteWhitelistAction);
			popMenu->addAction(moveToBlacklistAction);			
			popMenu->addAction(recoverCantactAction);
		}
	}
	popMenu->exec(QCursor::pos());//�˵����ֵ�λ��Ϊ��ǰ����λ��
	event->accept();
}

void CantactTreeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

	QTreeWidgetItem *item = NULL;
	QPoint point = event->pos();//�ȵ���������	
	item = this->itemAt(point);
	currentWidgetItem = item;
	QTreeWidgetItem *parent=NULL;
	
	if(item!=NULL&&(parent=item->parent())!=NULL)
	{
		emit editCantact();
	}	
}
void CantactTreeWidget::createActions()
{
	addCantactAction = new QAction(tr("�����ϵ��"),this);;//�����ϵ��
	sendMessageAction = new QAction(tr("������Ϣ"),this);;//������Ϣ
	editCantactAction = new QAction(tr("�༭��ϵ��"),this);;//�༭��ϵ��
	moveToBlacklistAction = new QAction(tr("��ӵ�������"),this);;//����������
	moveToWhitelistAction = new QAction(tr("��ӵ�������"),this);;//����������
	deleteCantactAction = new QAction(tr("ɾ����ϵ��"),this);;//ɾ����ϵ��
	
	recoverCantactAction = new QAction(tr("�ָ���ϵ��"),this);
	
	editBlacklistAction = new QAction(tr("�༭������"),this);;//�༭������
	deleteBlacklistAction = new QAction(tr("ɾ��������"),this);;//ɾ��������
	moveToWhitelistAction = new QAction(tr("����������"),this);;//����������
	StartBlacklistAction = new QAction(tr("����������"),this);//����������
	
	editWhitelistAction = new QAction(tr("�༭������"),this);;//�༭������
	deleteWhitelistAction = new QAction(tr("ɾ��������"),this);;//ɾ��������
	moveToBlacklistAction = new QAction(tr("����������"),this);;//����������
	StartWhitelistAction = new QAction(tr("����������"),this);//����������
	
	connect(addCantactAction,SIGNAL(triggered()),this,SLOT(addCantact()));
	connect(sendMessageAction,SIGNAL(triggered()),this,SLOT(sendMessage()));
	connect(editCantactAction,SIGNAL(triggered()),this,SLOT(editCantact()));
	connect(moveToBlacklistAction,SIGNAL(triggered()),this,SLOT(moveToBlacklist()));
	connect(moveToWhitelistAction,SIGNAL(triggered()),this,SLOT(moveToWhitelist()));
	connect(deleteCantactAction,SIGNAL(triggered()),this,SLOT(deleteCantact()));
	connect(recoverCantactAction,SIGNAL(triggered()),this,SLOT(recoverCantact()));
	
	connect(editBlacklistAction,SIGNAL(triggered()),this,SLOT(editCantact()));
	connect(deleteBlacklistAction,SIGNAL(triggered()),this,SLOT(deleteCantact()));
	connect(moveToWhitelistAction,SIGNAL(triggered()),this,SLOT(moveToWhitelist()));
	connect(StartBlacklistAction,SIGNAL(triggered()),this,SLOT(StartBlacklist()));
	
	connect(editWhitelistAction,SIGNAL(triggered()),this,SLOT(editCantact()));
	connect(deleteWhitelistAction,SIGNAL(triggered()),this,SLOT(deleteCantact()));
	connect(moveToBlacklistAction,SIGNAL(triggered()),this,SLOT(moveToBlacklist()));
	connect(StartWhitelistAction,SIGNAL(triggered()),this,SLOT(StartWhitelist()));
}

void CantactTreeWidget::createMapNameNumber()
{
   for (int i = 0; i < this->topLevelItemCount(); ++i)
	{	 
		QTreeWidgetItem *item = this->topLevelItem(i);
		for(int j = 0;j< item->childCount();++j)
		{
			QString strName = item->child(j)->text(0);
			QString strNumber = item->child(j)->text(1);
			mapNameNumber.insert(strName,strNumber);
		}
	}
}

void CantactTreeWidget::addCantact()
{
	CantactDialog *cantactDlg = new CantactDialog("��ϵ��");
	createMapNameNumber();
	cantactDlg->writeKey(mapNameNumber);
	cantactDlg->setWindowTitle("�����ϵ��");	
	cantactDlg->exec(); 
	
	QString strName = cantactDlg->lineNameEdit->text();
	QString strNumber = cantactDlg->lineNumberEdit->text();
	if(strName.length()>0&&strNumber.length()>0)
	{
		QTreeWidgetItem* child = new QTreeWidgetItem(currentWidgetItem);
		child->setText(0,strName);
		child->setText(1,strNumber);
	}		
}

void CantactTreeWidget::sendMessage()
{
	TalkDlg *talkdlg = new TalkDlg(currentWidgetItem->text(0),currentWidgetItem->text(1),NULL);
	XmlSmsReader read(talkdlg->listWidget,currentWidgetItem->text(0));
	read.readFile(strMessagePathOpen);
	talkdlg->show();
	
	
}
void CantactTreeWidget::editCantact()
{
	CantactDialog *cantactDlg = new CantactDialog("��ϵ��");
	createMapNameNumber();
	cantactDlg->writeKey(mapNameNumber);
	cantactDlg->setEdit(currentWidgetItem->text(0),currentWidgetItem->text(1));
	cantactDlg->setWindowTitle("�༭��ϵ��");	
	cantactDlg->exec(); 	
	QString strName = cantactDlg->lineNameEdit->text();
	QString strNumber = cantactDlg->lineNumberEdit->text();
	if(strName.length()>0&&strNumber.length()>0)
	{
		currentWidgetItem->setText(0,strName);
		currentWidgetItem->setText(1,strNumber);
	}		
}
void CantactTreeWidget::deleteCantact()
{
	int ret = QMessageBox::warning(NULL, "warning", "ȷ��Ҫɾ������ϵ����", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
	if(ret == QMessageBox::Yes)
	{
		QTreeWidgetItem *item = currentWidgetItem;
		QTreeWidgetItem *parent = item->parent();
		parent->removeChild(currentWidgetItem);
		currentWidgetItem = NULL;
	}
}

void CantactTreeWidget::moveToBlacklist()
{
	if(currentWidgetItem != NULL)
	{
		QTreeWidgetItem *item = new QTreeWidgetItem(blackTreeItem);
		item->setText(0,currentWidgetItem->text(0));
		item->setText(1,currentWidgetItem->text(1)); 
		QTreeWidgetItem *parent = currentWidgetItem->parent();	
		parent->removeChild(currentWidgetItem);
		currentWidgetItem = NULL;
	}
}

void CantactTreeWidget::recoverCantact()//
{
	if(currentWidgetItem != NULL)
	{
		QTreeWidgetItem *item = new QTreeWidgetItem(cantactTreeItem);
		item->setText(0,currentWidgetItem->text(0));
		item->setText(1,currentWidgetItem->text(1)); 
		QTreeWidgetItem *parent = currentWidgetItem->parent();	
		parent->removeChild(currentWidgetItem);
		currentWidgetItem = NULL;
	}
}

//���ð���������״̬
void CantactTreeWidget::StartWhitelist()
{
	if(whiteTreeItem->text(1).compare("����")==0)
	{
		whiteTreeItem->setText(1,"�ر�");
		whiteliststart = false;
	}
	else
	{
		whiteTreeItem->setText(1,"����");
		whiteliststart = true;
	}
}			

void CantactTreeWidget::moveToWhitelist()
{
	if(currentWidgetItem != NULL)
	{
		QTreeWidgetItem *item = new QTreeWidgetItem(whiteTreeItem);
		item->setText(0,currentWidgetItem->text(0));
		item->setText(1,currentWidgetItem->text(1)); 	
		QTreeWidgetItem *parent = currentWidgetItem->parent();	
		parent->removeChild(currentWidgetItem);
		currentWidgetItem = NULL;
	}
}

//���ú���������״̬
void CantactTreeWidget::StartBlacklist()
{
	if(blackTreeItem->text(1).compare("����")==0)
	{
		blackTreeItem->setText(1,"�ر�");
		blackliststart = false;
	}
	else
	{
		blackTreeItem->setText(1,"����");
		blackliststart = true;
	}
}