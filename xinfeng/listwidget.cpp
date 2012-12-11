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

//����Ҽ������б�
void ListWidget::contextMenuEvent ( QContextMenuEvent * event )
{
	popMenu->clear();//���ԭ�в˵�

	QListWidgetItem *item = NULL;//��õ�ǰ˫������
	QPoint point = event->pos();//�ȵ���������
	item = this->itemAt(point);//
	currentClickItem = item;
	if(item==NULL)
	{
		return ;
	}
	
	popMenu->addAction(transpondAction);
	popMenu->addAction(deleteMessageAction);		

	popMenu->exec(QCursor::pos());//�˵����ֵ�λ��Ϊ��ǰ����λ��
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
	strContent = strContent.right(length - index-1);//��ȡ��Ϣ,�ָ���":"	
	QString strNumber = strName;
	
	if(strNumber.compare("�Լ�")==0)
	{
		deleteSmsElemt(strMessagePathOpen,strCantactNumber,strContent,"����");//��Ϣ���еĶ���ɾ��ʱ����Ҫִ����������ɾ����Ϣ������ӵ�������
		addSmsElemt(strMessagePathOpen,strCantactNumber,strContent,"����","������");
	}
	else
	{
		deleteSmsElemt(strMessagePathOpen,strCantactNumber,strContent,"�յ�");//��Ϣ���еĶ���ɾ��ʱ����Ҫִ����������ɾ����Ϣ������ӵ�������
		addSmsElemt(strMessagePathOpen,strCantactNumber,strContent,"�յ�","������");
	}
}

void ListWidget::transpondItem()
{
	QListWidgetItem *currentItem = this->currentItem ();
	QString strContent = currentItem->text();
	int length = strContent.length();
	int index = strContent.indexOf(":");
	
	strContent = strContent.right(length - index-1);//��ȡ��Ϣ,�ָ���":"
	
	TalkDlg *talkdlg = new TalkDlg("");
	talkdlg->textEdit->setPlainText(strContent);
	talkdlg->show();
	if(talkdlg->textEdit->toPlainText().length()>0)
	{
		QString strNumber;
		QString strContent;
		QString strTerm="�ݸ�";
		QString strSmsSum = "�ݸ���";
		strContent = talkdlg->textEdit->toPlainText();
		strNumber = talkdlg->strCantactNumber;
		addSmsElemt(strMessagePathOpen,strNumber,strContent,strTerm,strSmsSum);//���ܴ���û�У��������ţ��Զ���������ӵ���Ϣ�ݸ�����
	}
}

void ListWidget::createActions()
{
	deleteMessageAction = new QAction(tr("ɾ��"),this);
	transpondAction = new QAction(tr("ת��"),this);	
	
	connect(deleteMessageAction,SIGNAL(triggered(bool)),this,SLOT(deleteMessage()));
	connect(transpondAction,SIGNAL(triggered(bool)),this,SLOT(transpondItem()));
}