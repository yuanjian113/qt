#ifndef __httpGet_h__
#define __httpGet_h__

#include <QObject>
#include <QString>
#include <QHttp>
#include <QUrl>
#include <QByteArray>

class HttpGet : public QObject
{
	Q_OBJECT

public:
	HttpGet();
	~HttpGet();

	bool	get	( const QString& strUrl );

private slots:
	void	parseHeader	( const QHttpResponseHeader& header );
	void	dataDone	( bool bError );

private:
	void	killHttp	();

	QString		m_strUrl;
	QHttp		*m_http;
	int			m_nLength;
	QByteArray	m_data;
};

#endif // __httpGet_h__
