#ifndef CANTACTDIALOG_H
#define CANTACTDIALOG_H

#include <QDialog>
#include <QMap>
class QCheckBox;
class QLabel;
class QLineEdit;
class QPushButton;

class CantactDialog : public QDialog
{
    Q_OBJECT

public:
    CantactDialog(const QString strsort,QWidget *parent = 0);
	void writeKey(QMap<QString,QString> map);
	void setEdit(QString strNmae,QString strNumber);
signals:
    void findNext(const QString &str, Qt::CaseSensitivity cs);
    void findPrevious(const QString &str, Qt::CaseSensitivity cs);
	
private slots:
    void FinishClicked();
    void enableFindButton(const QString &text);

public:
    QLabel *labelName;
    QLineEdit *lineNameEdit;
	
	QMap<QString,QString> mapNameNumber;
	QString strSort;
	
	QLabel *labelNumber;
    QLineEdit *lineNumberEdit;
	
    QPushButton *FinishButton;
    QPushButton *closeButton;
};

#endif
