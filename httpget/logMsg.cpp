#include <QFile>
#include <QMutex>
#include <QMutexLocker>
#include <QString>
#include <QDateTime>

#define		MAX_LOG_SIZE	(10 * 1024 * 1024)
#define		LOG_FILE_NAME	"myLog.log"

static QFile	*s_fpLog	= NULL;
static QMutex	*s_fpLock	= NULL;

void myMsgLog( QtMsgType msgType, const char *msg )
{
	if( NULL == s_fpLock )
		s_fpLock = new QMutex();

	QMutexLocker locker( s_fpLock );
	if( NULL != s_fpLog && s_fpLog->size() > MAX_LOG_SIZE )
	{
		s_fpLog->close();
		delete s_fpLog;
		s_fpLog = NULL;
	}

	if( NULL == s_fpLog )
	{
		s_fpLog = new QFile( LOG_FILE_NAME );
		if( NULL == s_fpLog )
			return;
		s_fpLog->open( QIODevice::WriteOnly );
	}

	QString strText = QString( "%1 - %2 : %3\r\n" )
		.arg( QDateTime::currentDateTime().toString("hh:mm:ss.zzz") )
		.arg( msgType )
		.arg( QString(msg) );
	s_fpLog->write( strText.toUtf8() );
	s_fpLog->flush();
}
