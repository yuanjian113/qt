#include <QtGui>
#include "xinfeng.h"
#include "MessageTreeWidget.h"
#include "CantactTreeWidget.h"
#include <QtXml>
#include <iostream>
#include <QMessageBox>
#include "controldlg.h"
//! [0]
TabDialog::TabDialog(const QString &fileName, QWidget *parent)
    : QDialog(parent)
{
    QFileInfo fileInfo(fileName);
    tabWidget = new QTabWidget;
    tabWidget->addTab(new MessageTab(fileInfo), tr("信息"));
    tabWidget->addTab(new CantactTab(fileInfo), tr("联系人"));
  //  tabWidget->addTab(new ControlTab(fileInfo), tr("设置"));
//! [0]

//! [1] //! [2]
    buttonBox = new QDialogButtonBox( QDialogButtonBox::Cancel);
	controlbtn = new QPushButton("set");
 //   connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
	connect(controlbtn, SIGNAL(clicked()), this, SLOT(control()));
//! [2] //! [3]
	
//! [4]
    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->setSizeConstraint(QLayout::SetNoConstraint);
    mainLayout->addWidget(tabWidget);
    QHBoxLayout *hlayout = new QHBoxLayout;
	hlayout->addWidget(controlbtn);
	hlayout->addWidget(buttonBox);
	mainLayout->addLayout(hlayout);
	
    setLayout(mainLayout);
//! [4]

//! [5]
    setWindowTitle(tr("信风"));
}
//! [5]

//! [6]
MessageTab::MessageTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent)
{
	MessageTreeWidget* messagetreeWidget = new MessageTreeWidget;    	
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(messagetreeWidget);
	setLayout(mainLayout);
}
//! [6]

//! [7]
CantactTab::CantactTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent)
{
	CantactTreeWidget* cantacttreeWidget = new CantactTreeWidget;  
	QVBoxLayout *mainLayout = new QVBoxLayout;
	mainLayout->addWidget(cantacttreeWidget);
	setLayout(mainLayout);
}
//! [7]

//! [8]
ControlTab::ControlTab(const QFileInfo &fileInfo, QWidget *parent)
    : QWidget(parent)
{
    QLabel *topLabel = new QLabel(tr("Open with:"));

    QListWidget *applicationsListBox = new QListWidget;
    QStringList applications;

    for (int i = 1; i <= 30; ++i)
        applications.append(tr("Application %1").arg(i));
    applicationsListBox->insertItems(0, applications);

    QCheckBox *alwaysCheckBox;

    if (fileInfo.suffix().isEmpty())
        alwaysCheckBox = new QCheckBox(tr("Always use this application to "
            "open this type of file"));
    else
        alwaysCheckBox = new QCheckBox(tr("Always use this application to "
            "open files with the extension '%1'").arg(fileInfo.suffix()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(topLabel);
    layout->addWidget(applicationsListBox);
    layout->addWidget(alwaysCheckBox);
    setLayout(layout);
}
//! [8]
void TabDialog::control()
{
	ControlDlg *dialog = new ControlDlg;
    dialog->exec();
}