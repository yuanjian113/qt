#include <QtGui>
#include <QMessageBox>
#include "CantactDialog.h"

CantactDialog::CantactDialog(const QString strsort,QWidget *parent)
    : QDialog(parent)
{
	strSort = strsort;
	
    labelName = new QLabel(tr("������"));
    lineNameEdit = new QLineEdit;
	labelNumber = new QLabel(tr("�绰��"));
    lineNumberEdit = new QLineEdit;

   
    FinishButton = new QPushButton(tr("���"));
    FinishButton->setDefault(true);
    FinishButton->setEnabled(false);

    closeButton = new QPushButton(tr("ȡ��"));

    connect(lineNameEdit, SIGNAL(textChanged(const QString &)),
           this, SLOT(enableFindButton(const QString &)));
	connect(lineNumberEdit, SIGNAL(textChanged(const QString &)),
           this, SLOT(enableFindButton(const QString &)));
    connect(FinishButton, SIGNAL(clicked()),
            this, SLOT(FinishClicked()));
    connect(closeButton, SIGNAL(clicked()),
            this, SLOT(close()));

    QHBoxLayout *topLeftLayout = new QHBoxLayout;
    topLeftLayout->addWidget(labelName);
    topLeftLayout->addWidget(lineNameEdit);
	
	QHBoxLayout *downLeftLayout = new QHBoxLayout;
    downLeftLayout->addWidget(labelNumber);
    downLeftLayout->addWidget(lineNumberEdit);
	
    QVBoxLayout *leftLayout = new QVBoxLayout;
    leftLayout->addLayout(topLeftLayout);
    leftLayout->addLayout(downLeftLayout);
  
    QVBoxLayout *rightLayout = new QVBoxLayout;
    rightLayout->addWidget(FinishButton);
    rightLayout->addWidget(closeButton);
    rightLayout->addStretch();

    QHBoxLayout *mainLayout = new QHBoxLayout;
    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);
    setLayout(mainLayout);

    setWindowTitle(tr("��ϵ��"));
    setFixedHeight(sizeHint().height());
}

void CantactDialog::FinishClicked()
{
	
	QMap<QString,QString>::Iterator it;
	for(it = mapNameNumber.begin();it != mapNameNumber.end();++it )
	{
		if(it.key()==lineNameEdit->text()||it.value()==lineNumberEdit->text())
		{
		    QMessageBox *message=new QMessageBox(QMessageBox::NoIcon, "����", "�������ϵ�˵�������绰�Ѵ��ڣ�����������"); 
			message->show();
			return ;
		}
	}
	this->close();
}

void CantactDialog::setEdit(QString strName,QString strNumber)
{
	lineNameEdit->setText(strName);
	lineNumberEdit->setText(strNumber);
}

void CantactDialog::writeKey(QMap<QString,QString> map)
{
	mapNameNumber = map;
}

void CantactDialog::enableFindButton(const QString &text)
{
	QString strName = lineNameEdit->text();
	QString strNumber = lineNumberEdit->text();
    FinishButton->setEnabled(!strName.isEmpty()&&!strNumber.isEmpty());
}
