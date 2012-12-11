/*
 * OptionDlg.h
 *
 *  Created on: 2009-5-15
 *      Author: szf
 */

#ifndef OPTIONDLG_H_
#define OPTIONDLG_H_

#include <QtGui/QWidget>
#include <QDialog>
#include <vector>

#include "Target.h"

class QTabWidget;
class QLabel;
class QSpinBox;
class QCheckBox;
class QComboBox;
class QLineEdit;
class QDialogButtonBox;
class QVBoxLayout;
class QGridLayout;

class QDomElement;

class OptionDlg : public QDialog
{
    Q_OBJECT

public:
	OptionDlg(QWidget *parent = 0);

	int getRecursiveLayer() const { return recursiveLayer; }
	int getMinFileSize() const { return minFileSize; }
	bool getSaveInSingleDir() const { return saveInSingleDir; }
	FileExistsAction getFileExistsAction() const { return fileExistsAction; }

	bool getUseProxy() const { return useProxy; }
	QString getProxyHost() const { return proxyHost; }
	int getProxyPort() const { return proxyPort; }
	QString getProxyUsername() const {return proxyUsername;  }
	QString getProxyPassword() const { return proxyPassword; }

	std::vector<Target> getTargets() const { return targets; }

private slots:
	void useProxyOrNot(int checkState);

public slots:
	void accept();

private:
	int recursiveLayer;
	int minFileSize;
	bool saveInSingleDir;
	FileExistsAction fileExistsAction;

	bool useProxy;
	QString proxyHost, proxyUsername, proxyPassword;
	int proxyPort;

	std::vector<Target> targets;

	QTabWidget *tabWidget;
	QWidget *tabGeneral, *tabNetwork, *tabTargets;

	QLabel *labelRecursiveLayer, *labelMinFileSize, *labelFileExistsAction;
	QSpinBox *spinBoxRecursiveLayer, *spinBoxMinFileSize;
	QCheckBox *checkBoxSaveInSingleDir;
	QComboBox *comboBoxFileExistsAction;
	QGridLayout *gridLayoutGeneral;
	QVBoxLayout *boxLayoutGeneral;

	QCheckBox *checkBoxUseProxy;
	QLabel *labelHost, *labelPort, *labelUsername, *labelPassword;
	QLineEdit *editHost, *editUsername, *editPassword;
	QSpinBox *spinBoxPort;
	QGridLayout *gridLayoutNetwork;
	QVBoxLayout *boxLayoutNetwork;

	std::vector<QCheckBox*> checkBoxTargets;
	QVBoxLayout *boxLayoutTargets;

	QDialogButtonBox *buttonBox;

	QVBoxLayout *mainLayout;

	bool readConfigure(const QString &fileName);
	void parseProxyElement(const QDomElement &element);
	bool readTargets(const QString &fileName);
	void parseTargetElement(const QDomElement &element);

};

#endif /* OPTIONDLG_H_ */
