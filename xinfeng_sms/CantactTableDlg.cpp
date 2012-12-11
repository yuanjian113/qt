#include "CantactTableDlg.h"
#include <QtGui>
#include <QMessageBox>
#include "xmlcantactreader.h"
CantactTableDlg::CantactTableDlg(QWidget *parent)
	:QDialog(parent)
{
	tableWidget = new QTableWidget;
	strMessagePathOpen = "xml/cantact.xml";
	buttonSelect = new QPushButton("选择");
	buttonCancel = new QPushButton("取消");
	
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
	tableWidget->setRowCount(200);     //设置行数为10
    tableWidget->setColumnCount(2);   //设置列数为5
     tableWidget->setWindowTitle("QTableWidget & Item");
     tableWidget->resize(350, 200);  //设置表格
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
   
	 tableWidget->verticalHeader()->setVisible(false); //隐藏行表头
	 tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //整行选中的方式
	 tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);//单击选中整行
    
	 raw = 0;
	 clickedItem = NULL;
	 setLayout(mainLayout);
}

//选择联系人
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

