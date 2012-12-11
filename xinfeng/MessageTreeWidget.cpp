#include <QMessageBox>
#include <QFileDialog>
#include "MessageTreeWidget.h"
#include "xmlstreamreader.h"
#include "xmlstreamwrite.h"
#include "xmlsmsreader.h"
#include "TalkDlg.h"
#include "xmlcantactreader.h"
MessageTreeWidget::MessageTreeWidget(QWidget *parent)
: QTreeWidget(parent)
{
	popMenu = new QMenu(this);

	this->setHeaderLabels(QStringList()<<"����"<<""); 
	
	createActions();
	strMessagePathOpen = "xml/message.xml";
	strMessagePathSave = "xml/message_save.xml";
	QString strCantactPath = "xml/cantact.xml";
	XmlStreamReader reader(this);
	reader.CreateBlackTerm(&mapblackNumberTerm);
	reader.readFile(strMessagePathOpen);
	XmlCantactReader cantactreader(NULL);
	
	cantactreader.createNumber2Name(strCantactPath,&mapNumber2Name);	
	
	this->SwitchNumber2Name(mapNumber2Name,mapName2Number);
	if(this->columnCount()>=3)
	{
		this->topLevelItem(0)->setIcon(0, QIcon("images/Inboximage.png"));
		this->topLevelItem(1)->setIcon(0, QIcon("images/Draftsimage.png"));
		this->topLevelItem(2)->setIcon(0, QIcon("images/Dustbinimage.png"));
	}
	
	
}

MessageTreeWidget::~MessageTreeWidget()
{
	writeXml(strMessagePathSave,this);
	combineXmlFile(strMessagePathOpen,strMessagePathSave,strMessagePathOpen);
}

void MessageTreeWidget::SwitchNumber2Name(QMap<QString,QString> mapnumber2name,QMap<QString,QString> &mapname2number)
{
	QMap<QString,QString>::iterator it = mapnumber2name.begin();
	for(;it !=mapnumber2name.end();it++ )
	{
		mapname2number.insert(it.value(),it.key());
	}
}

//����Ҽ������б�
void MessageTreeWidget::contextMenuEvent ( QContextMenuEvent * event )
{
	popMenu->clear();//���ԭ�в˵�	
	QString strPName;	
	QTreeWidgetItem *item = NULL;//��õ�ǰ˫������
	QPoint point = event->pos();//�ȵ���������
	item = this->itemAt(point);//
	
	if(item==NULL)
	{
		return ;
	}
	currentClickItem = item;
	QTreeWidgetItem *parent = item->parent();
	
	if(parent==NULL)
	{
		strPName = currentClickItem->text(0);
		if(QString::compare(strPName,"��Ϣ")==0)
		{
			popMenu->addAction(importSmsAction);
			popMenu->exec(QCursor::pos());//�˵����ֵ�λ��Ϊ��ǰ����λ��
			event->accept();
		}
		 return ;
	}
	popMenu->addAction(readMessageAction);//��Ӳ鿴�˵����ò˵���ÿ����Ϣ�����е�
	strPName = parent->text(0);//text�ǻ�õ�ǰ�еĵڼ��е��ı�
	if(QString::compare(strPName,"������")==0)
	{
		popMenu->addAction(recoverAction);	

	}
	popMenu->addAction(deleteMessageAction);		

	popMenu->exec(QCursor::pos());//�˵����ֵ�λ��Ϊ��ǰ����λ��
	event->accept();
}

void MessageTreeWidget::deleteMessage()
{
	QTreeWidgetItem *item = currentClickItem;
	QTreeWidgetItem *parent = item->parent();
	parent->removeChild(currentClickItem);
	currentClickItem = NULL;
}

void MessageTreeWidget::readMessageItem()
{	
	QTreeWidgetItem *item = currentClickItem;
	QString str= item->text(0);
	const QString strparent = item->parent()->text(0);
	QString strNumber ;
	TalkDlg *talkdlg=NULL;
	if(strparent=="��Ϣ")
	{
		talkdlg = new TalkDlg(str);
		XmlSmsReader reader(talkdlg->listWidget,str);
		reader.readFile(strMessagePathOpen);
		strNumber = str;
		if(mapName2Number.contains(str))
			strNumber = mapName2Number[str];
		talkdlg->listWidget->setCantactNumber(strNumber);
		
		talkdlg->show();
	}
	else if(strparent=="�ݸ���")
	{
		talkdlg = new TalkDlg(str);
		talkdlg->textEdit->setPlainText(item->text(1));
		talkdlg->show();
	}
	else if(strparent=="������")
	{
		talkdlg = new TalkDlg(str);
		talkdlg->textEdit->setPlainText(item->text(1));
		talkdlg->show();
	}
	str = item->text(1);
	if(talkdlg!=NULL && talkdlg->textEdit->toPlainText().length()>0&&talkdlg->textEdit->toPlainText().compare(str)!=0)
	{
		QString strNumber;
		QString strContent;
		QString strTerm="�ݸ�";
		QString strSmsSum = "�ݸ���";
		strContent = talkdlg->textEdit->toPlainText();
		strNumber = talkdlg->strCantactNumber;
		addSmsElemt(strMessagePathOpen,strNumber,strContent,strTerm,strSmsSum);
	}
	emit updateTreeAllItem();
}

void MessageTreeWidget::recoverMessageItem()
{
	QString strName= currentClickItem->text(0);
	QString strContent = currentClickItem->text(1);
	QString strNumber = strName;
	QString strTerm = "����";
	if(mapName2Number.contains(strName))
	{
		strNumber = mapName2Number[strName];
	}
	if(mapblackNumberTerm.contains(strName))
	{
		strTerm = mapblackNumberTerm[strName];
	}
//	QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, strNumber, strTerm); 
//	message->show();
	QString strSmsSum = "��Ϣ";
	addSmsElemt(strMessagePathOpen,strNumber,strContent,strTerm,strSmsSum);
	QTreeWidgetItem *item = currentClickItem;
	QTreeWidgetItem *parent = item->parent();
	parent->removeChild(currentClickItem);
	currentClickItem = NULL;
	writeXml(strMessagePathSave,this);
	emit updateTreeAllItem();
}

void MessageTreeWidget::transpondItem()
{
	TalkDlg *talkdlg = new TalkDlg("");
	
	talkdlg->textEdit->setPlainText(currentClickItem->text(1));
	talkdlg->show();
	QString str = currentClickItem->text(1);
	if(talkdlg->textEdit->toPlainText().length()>0&&talkdlg->textEdit->toPlainText().compare(str)!=0)
	{
		QString strNumber;
		QString strContent;
		QString strTerm="�ݸ�";
		QString strSmsSum = "�ݸ���";
		strContent = talkdlg->textEdit->toPlainText();
		strNumber = talkdlg->strCantactNumber;
		addSmsElemt(strMessagePathOpen,strNumber,strContent,strTerm,strSmsSum);
	}
	writeXml(strMessagePathSave,this);
	emit updateTreeAllItem();
}
/**/
//������˫���б����Ϊ�鿴�¼�
void MessageTreeWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
	QTreeWidgetItem *item = NULL;
	QPoint point = event->pos();//�ȵ���������	
	item = this->itemAt(point);//
	currentClickItem = item;
	QTreeWidgetItem *parent=NULL;
		
	if(item!=NULL&&(parent=item->parent())!=NULL)
	{
		QModelIndex   index = this->currentIndex();//��õ�ǰ˫������
		curIndex = index;
		QString curTitle = item->text(0);//index.data().toString();
		readMessageItem();	
	}
	emit updateTreeAllItem();
}

void MessageTreeWidget::updateTreeAllItem()
{
	this->clear();
	this->setHeaderLabels(QStringList()<<"����"<<""); 
	
	QString strCantactPath = "xml/cantact.xml";
	XmlStreamReader reader(this);
	reader.CreateBlackTerm(&mapblackNumberTerm);
	reader.readFile(strMessagePathOpen);
	XmlCantactReader cantactreader(NULL);
	
	cantactreader.createNumber2Name(strCantactPath,&mapNumber2Name);	
	
	this->SwitchNumber2Name(mapNumber2Name,mapName2Number);
	this->topLevelItem(0)->setIcon(0, QIcon("images/Inboximage.png"));
	this->topLevelItem(1)->setIcon(0, QIcon("images/Draftsimage.png"));
	this->topLevelItem(2)->setIcon(0, QIcon("images/Dustbinimage.png"));
}

//�������

bool keydetect(QString send_message)       //True:keys   False:No keys
{
    QStringList keys;                   //get the key words
    QFile file("./key.txt");
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        qDebug()<<"file open failed!";
        return false;
    }
    QTextStream stream(&file);
    QString key;

    while(!stream.atEnd())
    {
        key = stream.readLine();
        keys +=key;                 //put the key words to QstringList veriable
    }
    file.close();

    QString string_cmp = send_message;
    for(int i=0;i <keys.count();i++)        //replace the key words
    {
        QString replace_str = "";
        for(int j=0; j<keys[i].length(); j++)
            replace_str +="*";

        string_cmp.replace(keys[i],replace_str);
    }
    if(QString::compare(string_cmp,send_message) == 0)
       { return false;}
    else
       { return  true;}
}

void MessageTreeWidget::importSms()
{
	QString filename = QFileDialog::getOpenFileName(NULL, "Open File",".","Sms (*.xml)");
	if(!filename.isEmpty())
	{
		QFile file1(strMessagePathOpen);
		QFile file2(filename);
		QFile file3(strMessagePathOpen);
		if (!file1.open(QIODevice::ReadOnly)) return ;
		if (!file2.open(QIODevice::ReadOnly)) return ;
		QDomDocument doc1;//�ĵ�1
		QDomDocument doc2;//�ĵ�2
		if (!doc1.setContent(&file1))
		{
			file1.close();
			return;
		}
		if (!doc2.setContent(&file2))
		{
			file2.close();
			return ;
		}
		QDomElement docElem1 = doc1.documentElement();
		QDomElement docElem2 = doc2.documentElement();
		
		QDomNodeList list1 = doc1.elementsByTagName("SmsSum");
		//�Ա�ǩ�����в���
		QDomElement firstElement;
		for(int i=0; i<list1.count(); i++)
		{
			QDomElement e = list1.at(i).toElement();
			
			QString str= e.attribute("term");
			if(str.compare("��Ϣ")==0)
			{  
				firstElement = e;
				break;
			}
		}
		
		QDomNodeList list = doc2.elementsByTagName("Sms");
		//�Ա�ǩ�����в���
		for(int j=0; j< list.count(); j++)
		{
			QDomElement e = list.at(j).toElement();
			QDomElement tmp = e.cloneNode(true).toElement();
			QString strContent = tmp.text();
			bool key = keydetect(strContent);
			if(!key)
				firstElement.appendChild(tmp);//�����Ժ�list ���Ѿ�ɾ����
		}		
		if(!file3.open(QIODevice::WriteOnly | QIODevice::Truncate)) return ;
			QTextStream out(&file3);
		doc1.save(out,4);   //���ĵ����浽�ļ���4Ϊ��Ԫ�������ַ���
		file3.close();
		emit updateTreeAllItem();
		QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, "�������", "����ɹ�"); 
		message->show();
		
	}
}


void MessageTreeWidget::createActions()
{
	readMessageAction = new QAction(tr("�鿴"),this);
	recoverAction = new QAction(tr("�ָ�"),this);
	deleteMessageAction = new QAction(tr("ɾ��"),this);
	transpondAction = new QAction(tr("ת��"),this);	
	importSmsAction = new QAction(tr("�������"),this);
	
	connect(readMessageAction,SIGNAL(triggered(bool)), this,SLOT(readMessageItem()));
	connect(deleteMessageAction,SIGNAL(triggered(bool)),this,SLOT(deleteMessage()));
	connect(recoverAction,SIGNAL(triggered(bool)),this,SLOT(recoverMessageItem()));
	connect(transpondAction,SIGNAL(triggered(bool)),this,SLOT(transpondItem()));
	connect(importSmsAction,SIGNAL(triggered(bool)),this,SLOT(importSms()));
	
}