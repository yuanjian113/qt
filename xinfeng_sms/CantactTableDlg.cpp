#include "CantactTableDlg.h"
#include <QtGui>
#include <QMessageBox>
#include "xmlcantactreader.h"
CantactTableDlg::CantactTableDlg(QWidget *parent)
	:QDialog(parent)
{
	tableWidget = new QTableWidget;
	strMessagePathOpen = "xml/cantact.xml";
	buttonSelect = new QPushButton("ѡ��");
	buttonCancel = new QPushButton("ȡ��");
	
	XmlCantactReader cantactreader(NULL);
	
	cantactreader.createNumber2Name(strMessagePathOpen,&mapNumber2Name);	
	
	
	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	QHBoxLayout *hboxlayout = new QHBoxLayout;
	
	hboxlayout->addWidget(buttonSelect);
	hboxlayout->addWidget(buttonCancel);
	
	mainLayout->addWidget(tableWidget);
	mainLayout->addLayout(hboxlayout);
	
	connect(buttonCancel, SIGNAL(clicked()), this, SLOT(close()));
	connect(buttonSelect,SIGNAL(clicked()),this,SLOT(SelectContact()));
	tableWidget->setRowCount(200);     //��������Ϊ10
    tableWidget->setColumnCount(2);   //��������Ϊ5
     tableWidget->setWindowTitle("QTableWidget & Item");
     tableWidget->resize(350, 200);  //���ñ��
     QStringList header;
     header<<"Month"<<"Description";
     tableWidget->setHorizontalHeaderLabels(header);
	 QMap<QString,QString>::iterator it = mapNumber2Name.begin();
	for(int i=0;it !=mapNumber2Name.end();it++ ,i++)
	{
		//mapname2number.insert(it.value(),it.key());
		tableWidget->setItem(i,0,new QTableWidgetItem(it.key()));
		tableWidget->setItem(i,1,new QTableWidgetItem(it.value()));
	}
   
	 tableWidget->verticalHeader()->setVisible(false); //�����б�ͷ
	 tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //����ѡ�еķ�ʽ
	 tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//����ѡ������
    
	 raw = 0;
	 clickedItem = NULL;
	 setLayout(mainLayout);
}

//ѡ����ϵ��
void CantactTableDlg::SelectContact()
{
	clickedItem = tableWidget->currentItem();
	if(clickedItem==NULL)
	{
		QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, "sfsdf", "dfsdf"); 
		message->show();
		return ;
	}
	raw = clickedItem->row();
	strCantactName = tableWidget->item(raw,0)->text();
	strCantactNumber = tableWidget->item(raw,1)->text();
//	QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, strCantactName, strCantactNumber); 
//	message->show();
	this->close();
}

