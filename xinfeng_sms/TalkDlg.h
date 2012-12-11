#ifndef TALKDLG_H
#define TALKDLG_H

#include <QDialog>
#include <QMap>
#include <QTextEdit>
#include <QLabel>
#include "ListWidget.h"
#include<QDesktopServices>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>
class QDialogButtonBox;
class QIcon;
class QListWidget;

class TalkDlg : public QDialog
{
    Q_OBJECT

public:
	ListWidget *listWidget;
	QString		strCantactName;	
	QString		strCantactNumber;	
	QTextEdit	*textEdit;
	QTextEdit   *textContact;
	QPushButton *buttonAddContact;

	QString strMessagePathOpen;
public:
    TalkDlg(const QString strName,const QString strID,QWidget *parent);
	int selectedId() const { return id; }
    void done(int result);

	public slots:
	void send_slot();
	void recv_slot();
	void AddContact();
private:

    QPushButton *buttonSend;
	QPushButton *buttonCancel;	
    int id;
	
};

#endif
