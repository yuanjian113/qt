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
    //设定头项名称  
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
	if(blackTreeItem->text(0).compare("黑名单")==0)
	{
		if(blackTreeItem->text(1).compare("开启")==0)
		{
			blackliststart = true;
		}
		else
			blackliststart = false;
	}
	if(whiteTreeItem->text(0).compare("白名单")==0)
	{
		if(whiteTreeItem->text(1).compare("开启")==0)
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
	popMenu->clear();//清除原有菜单
	QTreeWidgetItem *item = NULL;
	QPoint point = event->pos();//等到窗口坐标
	
	item = this->itemAt(point);
	if(item == NULL)
	{
		return ;
	}
	currentWidgetItem = item;
	QTreeWidgetItem *parent = item->parent();
	if(parent == NULL)
	{
		if(currentWidgetItem->text(0).compare("黑名单")==0)
		{
			if(currentWidgetItem->text(1).compare("开启")==0)
			{
				StartBlacklistAction->setText("关闭黑名单");
			}
			else
				StartBlacklistAction->setText("开启黑名单");
			popMenu->addAction(StartBlacklistAction);
		}
		else if(currentWidgetItem->text(0).compare("白名单")==0)
		{
			if(currentWidgetItem->text(1).compare("开启")==0)
			{
				StartWhitelistAction->setText("关闭白名单");
			}
			else
				StartWhitelistAction->setText("开启白名单");
			popMenu->addAction(StartWhitelistAction);
		}
		else if(currentWidgetItem->text(0).compare("联系人")==0)
		{
			popMenu->addAction(addCantactAction);
		}
			
	}
	else
	{
		QString strPName = parent->text(0);
		if(QString::compare(strPName,"联系人")==0)
		{	
			popMenu->addAction(sendMessageAction);
			popMenu->addAction(editCantactAction);
			popMenu->addAction(moveToBlacklistAction);
			popMenu->addAction(moveToWhitelistAction);
			popMenu->addAction(deleteCantactAction);
		}
		else if(QString::compare(strPName,"黑名单")==0)
		{
			popMenu->addAction(editBlacklistAction);
			popMenu->addAction(deleteBlacklistAction);
			popMenu->addAction(moveToWhitelistAction);	
			popMenu->addAction(recoverCantactAction);
		}
		else if(QString::compare(strPName,"白名单")==0)
		{
			popMenu->addAction(editWhitelistAction);
			popMenu->addAction(deleteWhitelistAction);
			popMenu->addAction(moveToBlacklistAction);			
			popMenu->addAction(recoverCantactAction);
		}
	}
	popMenu->exec(QCursor::pos());//菜单出现的位置为当前鼠标的位置
	event->accept();
}

void CantactTreeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{

	QTreeWidgetItem *item = NULL;
	QPoint point = event->pos();//等到窗口坐标	
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
	addCantactAction = new QAction(tr("添加联系人"),this);;//添加联系人
	sendMessageAction = new QAction(tr("发送信息"),this);;//发送信息
	editCantactAction = new QAction(tr("编辑联系人"),this);;//编辑联系人
	moveToBlacklistAction = new QAction(tr("添加到黑名单"),this);;//移至黑名单
	moveToWhitelistAction = new QAction(tr("添加到白名单"),this);;//移至白名单
	deleteCantactAction = new QAction(tr("删除联系人"),this);;//删除联系人
	
	recoverCantactAction = new QAction(tr("恢复联系人"),this);
	
	editBlacklistAction = new QAction(tr("编辑黑名单"),this);;//编辑黑名单
	deleteBlacklistAction = new QAction(tr("删除黑名单"),this);;//删除黑名单
	moveToWhitelistAction = new QAction(tr("移至白名单"),this);;//移至白名单
	StartBlacklistAction = new QAction(tr("开启黑名单"),this);//开启黑名单
	
	editWhitelistAction = new QAction(tr("编辑白名单"),this);;//编辑白名单
	deleteWhitelistAction = new QAction(tr("删除白名单"),this);;//删除白名单
	moveToBlacklistAction = new QAction(tr("移至黑名单"),this);;//移至黑名单
	StartWhitelistAction = new QAction(tr("开启白名单"),this);//开启白名单
	
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
	CantactDialog *cantactDlg = new CantactDialog("联系人");
	createMapNameNumber();
	cantactDlg->writeKey(mapNameNumber);
	cantactDlg->setWindowTitle("添加联系人");	
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
	CantactDialog *cantactDlg = new CantactDialog("联系人");
	createMapNameNumber();
	cantactDlg->writeKey(mapNameNumber);
	cantactDlg->setEdit(currentWidgetItem->text(0),currentWidgetItem->text(1));
	cantactDlg->setWindowTitle("编辑联系人");	
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
	int ret = QMessageBox::warning(NULL, "warning", "确定要删除该联系人吗？", QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);
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

//设置白名单开关状态
void CantactTreeWidget::StartWhitelist()
{
	if(whiteTreeItem->text(1).compare("开启")==0)
	{
		whiteTreeItem->setText(1,"关闭");
		whiteliststart = false;
	}
	else
	{
		whiteTreeItem->setText(1,"开启");
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

//设置黑名单开关状态
void CantactTreeWidget::StartBlacklist()
{
	if(blackTreeItem->text(1).compare("开启")==0)
	{
		blackTreeItem->setText(1,"关闭");
		blackliststart = false;
	}
	else
	{
		blackTreeItem->setText(1,"开启");
		blackliststart = true;
	}
}