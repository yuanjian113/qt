#include <QtGui>

#include "TalkDlg.h"
#include <QSpacerItem>
#include "xmlstreamwrite.h"
#include "CantactTableDlg.h"
TalkDlg::TalkDlg(const QString strCanName="",const QString strCanID="", QWidget *parent=NULL)
    : QDialog(parent)
{
    id = -1;//用于记录最后选择的ID
	
    listWidget = new ListWidget(strCanName);
	strCantactName = strCanName;
    listWidget->setIconSize(QSize(20, 20));
	strCantactNumber = strCanID;
	strMessagePathOpen = "xml/message.xml";
	
	QSize dlgsize(480,320);
	this->resize(dlgsize);
    buttonSend = new QPushButton("发送");
	buttonCancel = new QPushButton("取消");
	buttonAddContact = new QPushButton("添加联系人");
	textEdit = new QTextEdit;
	textContact = new QTextEdit;
    QVBoxLayout *vmainLayout = new QVBoxLayout;
	QHBoxLayout *heditLayout = new QHBoxLayout;
	QHBoxLayout *hContactLayout = new QHBoxLayout;
	QHBoxLayout *hlistLayout = new QHBoxLayout;
	QVBoxLayout *vbtnLayout = new QVBoxLayout;
	if(strCantactName.compare("")==0)
	{
		hContactLayout->addWidget(textContact);
		hContactLayout->addWidget(buttonAddContact);
	}
	vmainLayout->addLayout(hContactLayout);
	hlistLayout->addWidget(listWidget);
    vmainLayout->addLayout(hlistLayout);
	heditLayout->addWidget(textEdit);
	vbtnLayout->addWidget(buttonSend);
	vbtnLayout->addWidget(buttonCancel);
	heditLayout->addLayout(vbtnLayout);
	vmainLayout->addLayout(heditLayout);
	if(strCantactName.compare("")==0)
	{
		vmainLayout->setStretchFactor(hContactLayout,1);
		vmainLayout->setStretchFactor(hlistLayout,9);
		vmainLayout->setStretchFactor(heditLayout,3);
	}
	else
	{
		vmainLayout->setStretchFactor(hlistLayout,3);
		vmainLayout->setStretchFactor(heditLayout,1);
	}
	
    setLayout(vmainLayout);

	
	connect(buttonSend,SIGNAL(clicked()),this,SLOT(send_slot()));
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(reject()));
	connect(buttonAddContact,SIGNAL(clicked()),this,SLOT(AddContact()));
	
	QString strTitle;
	strTitle = "与"+strCantactName+"聊天";
    setWindowTitle(strTitle);
}


void TalkDlg::send_slot()
{
	const QString strText = textEdit -> toPlainText();
	QString strNumber;
	QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, strCantactNumber, strCantactName+strText); 
	message->show();
	if(strText.size()>0)
	{
		QString strID = strCantactNumber;
		QString strSms ="&m=" + strText;
		QString strurl = "http://quanapi.sinaapp.com/fetion.php?u=18858298271&p=wang113.&to=" + strID + strSms;
		QUrl url(strurl);
		QNetworkAccessManager *manager = new QNetworkAccessManager();
		manager->get(QNetworkRequest(url));
		int num = 2;
		QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, strCantactNumber, strurl); 
		message->show();
		if(num!=-1)
		{
			textEdit->setPlainText("");
			QString str="自己："+strText;
			QListWidgetItem *item = new QListWidgetItem(str,listWidget);
			listWidget->addItem(item);			
			addSmsElemt(strMessagePathOpen,strCantactNumber,strText,"发送","信息");
		}
		else
		{			
		}
	}
}

void TalkDlg::recv_slot()
{
	qDebug()<<"in recv_slot()";
	char buffer[4096];
//	udpSocket->readDatagram(buffer,4096,0,0);
	QString str(buffer);
	if(str.length()>0)
	{
		QString strContent = str;
		str=strCantactName+":"+str;
		QListWidgetItem *item = new QListWidgetItem(str,listWidget);
		listWidget->addItem(item);
		addSmsElemt(strMessagePathOpen,strCantactNumber,strContent,"收到","信息");
	}	
}

void TalkDlg::AddContact()
{
	CantactTableDlg *cantacttalbedlg = new CantactTableDlg;
	cantacttalbedlg->exec();
	{
		this->textContact->setPlainText(cantacttalbedlg->strCantactName);
		this->strCantactNumber = cantacttalbedlg->strCantactNumber;
		this->strCantactName = cantacttalbedlg->strCantactName;
		QString strTitle;
		strTitle = "与"+strCantactName+"聊天";
		setWindowTitle(strTitle);
	//	QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, strCantactNumber, strCantactName); 
	//	message->show();
	}	
}

void TalkDlg::done(int result)
{
    id = -1;
    if (result == QDialog::Accepted) 
	{
        QListWidgetItem *item = listWidget->currentItem();
        if (item)
            id = item->data(Qt::UserRole).toInt();
    }
    QDialog::done(result);
}