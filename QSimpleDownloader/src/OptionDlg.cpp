/*
 * OptionDlg.cpp
 *
 *  Created on: 2009-5-15
 *      Author: szf
 */
#include <QtGui>
#include <QtXml>
#include <iostream>

#include "OptionDlg.h"

OptionDlg::OptionDlg(QWidget *parent)
	: QDialog(parent)
{
	readConfigure("etc/conf.xml");
	readTargets("etc/targets.xml");

	// 创建控件
	tabWidget = new QTabWidget;
	tabGeneral = new QWidget;
	tabNetwork = new QWidget;
	tabTargets = new QWidget;
	tabWidget->addTab(tabGeneral, tr("General"));
	tabWidget->addTab(tabNetwork, tr("Network"));
	tabWidget->addTab(tabTargets, tr("Targets"));

	// tab general
	labelRecursiveLayer = new QLabel(tr("&Recursive layer:"));
	spinBoxRecursiveLayer = new QSpinBox();
	spinBoxRecursiveLayer->setValue(recursiveLayer);
	labelRecursiveLayer->setBuddy(spinBoxRecursiveLayer);

	labelMinFileSize = new QLabel(tr("&Minimum file size(Kb):"));
	spinBoxMinFileSize = new QSpinBox();
	spinBoxMinFileSize->setValue(minFileSize);
	labelMinFileSize->setBuddy(spinBoxMinFileSize);

	checkBoxSaveInSingleDir = new QCheckBox(tr("&Save targets in single directory"));
	checkBoxSaveInSingleDir->setChecked(saveInSingleDir);

	labelFileExistsAction = new QLabel(tr("&Do what when file exists:"));
	comboBoxFileExistsAction = new QComboBox();
	comboBoxFileExistsAction->addItem(tr("Overwrite"), feaOverwrite);
	comboBoxFileExistsAction->addItem(tr("Ignore"), feaIgnore);
	comboBoxFileExistsAction->setCurrentIndex(fileExistsAction);
	labelFileExistsAction->setBuddy(comboBoxFileExistsAction);

	gridLayoutGeneral = new QGridLayout();
	gridLayoutGeneral->addWidget(labelRecursiveLayer, 0, 0, 1, 1);
	gridLayoutGeneral->addWidget(spinBoxRecursiveLayer, 0, 1, 1, 1);
	gridLayoutGeneral->addWidget(labelMinFileSize, 1, 0, 1, 1);
	gridLayoutGeneral->addWidget(spinBoxMinFileSize, 1, 1, 1, 1);
	gridLayoutGeneral->addWidget(checkBoxSaveInSingleDir, 2, 0, 1, 2);
	gridLayoutGeneral->addWidget(labelFileExistsAction, 3, 0, 1, 1);
	gridLayoutGeneral->addWidget(comboBoxFileExistsAction, 3, 1, 1, 1);

	boxLayoutGeneral = new QVBoxLayout;
	boxLayoutGeneral->addLayout(gridLayoutGeneral);
	boxLayoutGeneral->addStretch();

	tabGeneral->setLayout(boxLayoutGeneral);

	// tab Network
	checkBoxUseProxy = new QCheckBox(tr("&Enable proxy"));
	checkBoxUseProxy->setChecked(useProxy);
	connect(checkBoxUseProxy, SIGNAL(stateChanged(int)), this, SLOT(useProxyOrNot(int)));

	labelHost = new QLabel(tr("&Host:"));
	editHost = new QLineEdit();
	editHost->setText(proxyHost);
	labelHost->setBuddy(editHost);

	labelPort = new QLabel(tr("&Port:"));
	spinBoxPort = new QSpinBox();
	spinBoxPort->setMaximum(65535);
	spinBoxPort->setValue(proxyPort);
	labelPort->setBuddy(spinBoxPort);

	labelUsername = new QLabel(tr("&Username:"));
	editUsername = new QLineEdit();
	editUsername->setText(proxyUsername);
	labelUsername->setBuddy(labelUsername);

	labelPassword = new QLabel(tr("Pass&word:"));
	editPassword = new QLineEdit();
	editPassword->setText(proxyPassword);
	editPassword->setEchoMode(QLineEdit::Password);
	labelPassword->setBuddy(editPassword);

	// 启用不启用代理
	useProxyOrNot(checkBoxUseProxy->checkState());

	gridLayoutNetwork = new QGridLayout();
	gridLayoutNetwork->addWidget(checkBoxUseProxy, 0, 0, 1, 2);
	gridLayoutNetwork->addWidget(labelHost, 1, 0, 1, 1);
	gridLayoutNetwork->addWidget(editHost, 1, 1, 1, 1);
	gridLayoutNetwork->addWidget(labelPort, 2, 0, 1, 1);
	gridLayoutNetwork->addWidget(spinBoxPort, 2, 1, 1, 1);
	gridLayoutNetwork->addWidget(labelUsername, 3, 0, 1, 1);
	gridLayoutNetwork->addWidget(editUsername, 3, 1, 1, 1);
	gridLayoutNetwork->addWidget(labelPassword, 4, 0, 1, 1);
	gridLayoutNetwork->addWidget(editPassword, 4, 1, 1, 1);

	boxLayoutNetwork = new QVBoxLayout;
	boxLayoutNetwork->addLayout(gridLayoutNetwork);
	boxLayoutNetwork->addStretch();

	tabNetwork->setLayout(boxLayoutNetwork);

	// tab targets
	boxLayoutTargets = new QVBoxLayout;
	int i = 1;
	foreach(Target target, targets) {
		QCheckBox *checkBoxTarget = new QCheckBox(
				QString("&%1. %2").arg(i).arg(target.desc));
		if(target.selected)
			checkBoxTarget->setChecked(true);
		boxLayoutTargets->addWidget(checkBoxTarget);
		checkBoxTargets.push_back(checkBoxTarget);
		++i;
	}
	boxLayoutTargets->addStretch();
	tabTargets->setLayout(boxLayoutTargets);

	buttonBox = new QDialogButtonBox;
	buttonBox->setOrientation(Qt::Horizontal);
	buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

	mainLayout = new QVBoxLayout;
	mainLayout->addWidget(tabWidget);
	mainLayout->addWidget(buttonBox);
	this->setLayout(mainLayout);

	this->setMinimumSize(360, 240);
	this->resize(360, 240);

	connect(buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
	connect(buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
}

bool OptionDlg::readConfigure(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		std::cerr << "Error: Cannot read file " << qPrintable(fileName)
				  << ": " << qPrintable(file.errorString())
				  << std::endl;
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;

	QDomDocument doc;
	if(!doc.setContent(&file, &errorStr, &errorLine, &errorColumn)) {
		std::cerr << "Error: Parse error at line " << errorLine << ", "
				  << "column " << errorColumn << ": "
				  << qPrintable(errorStr) << std::endl;
		return false;
	}

	QDomElement root = doc.documentElement();
	if (root.tagName() != "configure") {
		std::cerr << "Error: Not a configure file" << std::endl;
		return false;
	}

	QDomNode child = root.firstChild();
	bool ok;
	while (!child.isNull()) {
		if (child.toElement().tagName() == "RecursiveLayer") {
			recursiveLayer = child.toElement().text().toInt(&ok, 10);
			if(!ok)
				recursiveLayer = 3;
		}
		else if(child.toElement().tagName() == "MinFileSize") {
			minFileSize = child.toElement().text().toInt(&ok, 10);
			if(!ok)
				minFileSize = 30;
		}
		else if(child.toElement().tagName() == "SaveInSingleDir") {
			saveInSingleDir = child.toElement().text().compare("true", Qt::CaseInsensitive) == 0;
		}
		else if(child.toElement().tagName() == "FileExistsAction") {
			int r = child.toElement().text().toInt(&ok, 10);
			if(!ok || (r != feaOverwrite && r != feaIgnore))
				fileExistsAction = feaOverwrite;
			else
				fileExistsAction = (FileExistsAction)r;
		}
		else if(child.toElement().tagName() == "Proxy") {
			parseProxyElement(child.toElement());
		}
		child = child.nextSibling();
	}

	return true;
}

void OptionDlg::parseProxyElement(const QDomElement &element)
{
	useProxy = element.attribute("useProxy").compare("true", Qt::CaseInsensitive) == 0;
	QDomNode child = element.firstChild();
	while (!child.isNull()) {
		if (child.toElement().tagName() == "Host") {
			proxyHost = child.toElement().text();
		}
		else if(child.toElement().tagName() == "Port") {
			bool ok;
			proxyPort = child.toElement().text().toInt(&ok, 10);
			if(!ok)
				proxyPort = 8080;
		}
		else if(child.toElement().tagName() == "Username") {
			proxyUsername = child.toElement().text();
		}
		else if(child.toElement().tagName() == "Password") {
			proxyPassword = child.toElement().text();
		}
		child = child.nextSibling();
	}
}

bool OptionDlg::readTargets(const QString &fileName)
{
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		std::cerr << "Error: Cannot read file " << qPrintable(fileName)
				  << ": " << qPrintable(file.errorString())
				  << std::endl;
		return false;
	}

	QString errorStr;
	int errorLine;
	int errorColumn;

	QDomDocument doc;
	if(!doc.setContent(&file, &errorStr, &errorLine, &errorColumn)) {
		std::cerr << "Error: Parse error at line " << errorLine << ", "
				  << "column " << errorColumn << ": "
				  << qPrintable(errorStr) << std::endl;
		return false;
	}

	QDomElement root = doc.documentElement();
	if (root.tagName() != "targets") {
		std::cerr << "Error: Not a targets file" << std::endl;
		return false;
	}

	QDomNode child = root.firstChild();
	while (!child.isNull()) {
		if (child.toElement().tagName() == "target") {
			parseTargetElement(child.toElement());
		}
		child = child.nextSibling();
	}

	return true;
}

void OptionDlg::parseTargetElement(const QDomElement &element)
{
	Target target;
	target.desc = element.attribute("desc", "no desc");
	target.selected = (element.attribute("selected").compare("true", Qt::CaseInsensitive) == 0);
	QDomNode child = element.firstChild();
	while(!child.isNull()) {
		if(child.toElement().tagName() == "tag") {
			target.tag = child.toElement().text();
		}
		else if(child.toElement().tagName() == "attr") {
			target.attr = child.toElement().text();
		}
		else if(child.toElement().tagName() == "exts") {
			target.exts = child.toElement().text().split(';');
		}
		child = child.nextSibling();
	}
	targets.push_back(target);
}

void OptionDlg::useProxyOrNot(int checkState)
{
	bool useProxy = checkState == Qt::Checked;
	labelHost->setEnabled(useProxy);
	editHost->setEnabled(useProxy);
	labelPort->setEnabled(useProxy);
	spinBoxPort->setEnabled(useProxy);
	labelUsername->setEnabled(useProxy);
	editUsername->setEnabled(useProxy);
	labelPassword->setEnabled(useProxy);
	editPassword->setEnabled(useProxy);
}

void OptionDlg::accept()
{
	recursiveLayer = spinBoxRecursiveLayer->value();
	minFileSize = spinBoxMinFileSize->value();
	saveInSingleDir = checkBoxSaveInSingleDir->checkState() == Qt::Checked;
	fileExistsAction = (FileExistsAction)comboBoxFileExistsAction->itemData(
			comboBoxFileExistsAction->currentIndex()).toInt();

	useProxy = checkBoxUseProxy->checkState() == Qt::Checked;
	proxyHost = editHost->text();
	proxyPort = spinBoxPort->value();
	proxyUsername = editUsername->text();
	proxyPassword = editPassword->text();

	int i = 0;
	for(std::vector<Target>::iterator iter = targets.begin();
		iter != targets.end(); ++iter) {
		iter->selected = checkBoxTargets[i]->checkState() == Qt::Checked;
		++i;
	}

	QDialog::accept();
}
