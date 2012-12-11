#include <QMessageBox>
#include "ListWidget.h"
#include "xmlstreamreader.h"
#include "xmlstreamwrite.h"
#include "xmlsmsreader.h"
#include "talkdlg.h"
ListWidget::ListWidget(QString strcantactnumber,QWidget *parent)
: QListWidget(parent)
{
	popMenu = new QMenu(this);	
	createActions();
	strMessagePathOpen = "xml/message.xml";
	strCantactNumber = strcantactnumber;
}

ListWidget::~ListWidget()
{
	
}

void ListWidget::setCantactNumber(QString strNumber)
{
	strCantactNumber = strNumber;
}

//鼠标右键单击列表
void ListWidget::contextMenuEvent ( QContextMenuEvent * event )
{
	popMenu->clear();//清除原有菜单

	QListWidgetItem *item = NULL;//获得当前双击对象
	QPoint point = event->pos();//等到窗口坐标
	item = this->itemAt(point);//
	currentClickItem = item;
	if(item==NULL)
	{
		return ;
	}
	
	popMenu->addAction(transpondAction);
	popMenu->addAction(deleteMessageAction);		

	popMenu->exec(QCursor::pos());//菜单出现的位置为当前鼠标的位置
	event->accept();
}

void ListWidget::deleteMessage()
{
	QList<QListWidgetItem*> list = this->selectedItems();	
	if(list.size() == 0)
		return;
	QListWidgetItem* sel = list[0];
	QString strContent = sel->text();
	if (sel)
	{
		int r = this->row(sel);
		this->takeItem(r);
	}
	int length = strContent.length();
	int index = strContent.indexOf(":");
	QString strName = strContent.left(index);
	strContent = strContent.right(length - index-1);//截取信息,分隔符":"	
	QString strNumber = strName;
	
	if(strNumber.compare("自己")==0)
	{
		deleteSmsElemt(strMessagePathOpen,strCantactNumber,strContent,"发送");//信息箱中的短信删除时，需要执行两步，先删除信息，再添加到垃圾箱
		addSmsElemt(strMessagePathOpen,strCantactNumber,strContent,"发送","垃圾箱");
	}
	else
	{
		deleteSmsElemt(strMessagePathOpen,strCantactNumber,strContent,"收到");//信息箱中的短信删除时，需要执行两步，先删除信息，再添加到垃圾箱
		addSmsElemt(strMessagePathOpen,strCantactNumber,strContent,"收到","垃圾箱");
	}
}

void ListWidget::transpondItem()
{
	QListWidgetItem *currentItem = this->currentItem ();
	QString strContent = currentItem->text();
	int length = strContent.length();
	int index = strContent.indexOf(":");
	
	strContent = strContent.right(length - index-1);//截取信息,分隔符":"
	
	TalkDlg *talkdlg = new TalkDlg("");
	talkdlg->textEdit->setPlainText(strContent);
	talkdlg->show();
	if(talkdlg->textEdit->toPlainText().length()>0)
	{
		QString strNumber;
		QString strContent;
		QString strTerm="草稿";
		QString strSmsSum = "草稿箱";
		strContent = talkdlg->textEdit->toPlainText();
		strNumber = talkdlg->strCantactNumber;
		addSmsElemt(strMessagePathOpen,strNumber,strContent,strTerm,strSmsSum);//可能存在没有，发出短信，自动将短信添加到信息草稿箱内
	}
}

void ListWidget::createActions()
{
	deleteMessageAction = new QAction(tr("删除"),this);
	transpondAction = new QAction(tr("转发"),this);	
	
	connect(deleteMessageAction,SIGNAL(triggered(bool)),this,SLOT(deleteMessage()));
	connect(transpondAction,SIGNAL(triggered(bool)),this,SLOT(transpondItem()));
}