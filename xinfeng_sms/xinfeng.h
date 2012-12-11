#ifndef XINFENG_H
#define XINFENG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QFileInfo;
class QTabWidget;
QT_END_NAMESPACE

//! [0]
class MessageTab : public QWidget
{
    Q_OBJECT
public:
    MessageTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};
//! [0]


//! [1]
class CantactTab : public QWidget
{
    Q_OBJECT

public:
    CantactTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};
//! [1]


//! [2]
class ControlTab : public QWidget
{
    Q_OBJECT

public:
    ControlTab(const QFileInfo &fileInfo, QWidget *parent = 0);
};
//! [2]


//! [3]
class TabDialog : public QDialog
{
    Q_OBJECT

public:
    TabDialog(const QString &fileName, QWidget *parent = 0);
public slots:
	void control();

private:
    QTabWidget *tabWidget;
    QDialogButtonBox *buttonBox;
	QPushButton *controlbtn;
};
//! [3]

#endif
