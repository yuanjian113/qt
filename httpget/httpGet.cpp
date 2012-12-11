
#include "httpGet.h"
#include <QUrl>
#include <QTextCodec>
#include <QDebug>

HttpGet::HttpGet()
	: QObject()
	, m_http( NULL )
	, m_nLength( 0 )
{
}

HttpGet::~HttpGet()
{
	killHttp();
}

bool HttpGet::get( const QString& strUrl )
{
	QUrl url( strUrl );
	if( url.isEmpty() || !url.isValid() ) {
		qDebug() << QString("url: '%1' is invalid !").arg(strUrl);
		return false;
	}
	else
		m_strUrl = strUrl;

	m_http = new QHttp( url.host(), -1 == url.port() ? 80 : url.port() );
	connect( m_http, SIGNAL(responseHeaderReceived(const QHttpResponseHeader&)), this, SLOT(parseHeader(const QHttpResponseHeader&)) );
	connect( m_http, SIGNAL(done(bool)), this, SLOT(dataDone(bool)) );
	
	if( url.hasQuery() ) {
		QString tmpUrl = url.toString();
		tmpUrl.remove( "http://" );
		tmpUrl.remove( url.host() );
		QHttpRequestHeader header( "GET", tmpUrl );
		header.setValue( "Connection", "keep-alive" );
		header.setValue( "Host", url.host() );
		m_http->request( header );
	}
	else
		m_http->get( url.path() );

	return true;
}

void HttpGet::parseHeader( const QHttpResponseHeader& header )
{
	m_nLength = header.contentLength();

	int statusCode = header.statusCode();
	switch( statusCode ) {
		// url redirection
		case 301:
		case 302:
			{
				killHttp();
				QString strUrl = header.value( "Location" );
				QUrl url( strUrl );
				if( url.isEmpty() || !url.isValid() ) {
					qDebug() << QString("redirection url '%1' is invalid !").arg(strUrl);
					return;
				}
				else {
					m_strUrl = strUrl;

					m_http = new QHttp( url.host(), -1 == url.port() ? 80 : url.port() );
					connect( m_http, SIGNAL(responseHeaderReceived(const QHttpResponseHeader&)), this, SLOT(parseHeader(const QHttpResponseHeader&)) );
					connect( m_http, SIGNAL(done(bool)), this, SLOT(dataDone(bool)) );

					if( url.hasQuery() ) {
						QString tmpUrl = url.toString();
						tmpUrl.remove( "http://" );
						tmpUrl.remove( url.host() );
						QHttpRequestHeader tmpHeader( "GET", tmpUrl );
						tmpHeader.setValue( "Connection", "keep-alive" );
						tmpHeader.setValue( "Host", url.host() );
						m_http->request( tmpHeader );
					}
					else
						m_http->get( url.path() );
				}
			}
			break;

		// invalid url, not found
		case 404:
		case 503:
			{
				killHttp();
				qDebug() << QString("url '%1' is not found !").arg(m_strUrl);
				return;
			}
			break;

		default:
			break;
	}
}

void HttpGet::dataDone( bool bError )
{
	if( QHttp::NoError == m_http->error() )
	{
		m_data += m_http->readAll();
		if( m_data.size() < m_nLength )
		{
			QUrl url( m_strUrl );
			QHttpRequestHeader requestHeader( "GET", url.path() );
			QString range = QString( "bytes=%1-%2" ).arg( m_data.size() ).arg( m_nLength );
			requestHeader.setValue( "Connection", "Keep-Alive" );
			requestHeader.setValue( "Range", range );
			requestHeader.setValue( "Host", url.host() );
			m_http->request( requestHeader );
			return;
		}
	}

	QTextCodec *codecUtf8	= QTextCodec::codecForName( "utf8" );
	QTextCodec *codecGbk	= QTextCodec::codecForName( "gbk" );
	QString		strDataUtf8 = codecUtf8->toUnicode( m_data );
	QString		strDataGbk	= codecGbk->toUnicode( m_data );

	qDebug() << "------------------------ utf8 start ------------------------\r\n";
	qDebug() << strDataUtf8;
	qDebug() << "------------------------- utf8 end -------------------------\r\n";

	qDebug() << "------------------------ gbk start ------------------------\r\n";
	qDebug() << strDataGbk;
	qDebug() << "------------------------- gbk end -------------------------\r\n";

	killHttp();

}

void HttpGet::killHttp()
{
	if( NULL != m_http )
	{
		disconnect( m_http, SIGNAL(done(bool)), this, SLOT(dataDone(bool)) );
		m_http->close();
		QHttp *http = m_http;
		http->deleteLater();
		m_http = NULL;
	}
}
