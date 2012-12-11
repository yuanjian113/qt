#ifndef CANTACTTABLEDLG_H
#define CANTACTTABLEDLG_H

#include <QDialog>
#include <QMap>
#include <QTextEdit>
#include <QLabel>
#include <QTableWidgetItem>

class QTableWidget;
class QDialogButtonBox;
class QIcon;

class CantactTableDlg : public QDialog
{
    Q_OBJECT

public:
	QTableWidget *tableWidget;
	QString 	strCantactName;
	QString 	strCantactNumber;
	QString strMessagePathOpen;
	QTableWidgetItem  *clickedItem;
	int raw;
	QMap<QString,QString> mapNumber2Name;
public:
    CantactTableDlg(QWidget *parent = 0);

public slots:
	
	void SelectContact();

private:

    QPushButton *buttonSelect;
	QPushButton *buttonCancel;	
};

#endif
