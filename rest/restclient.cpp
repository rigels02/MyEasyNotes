#include "restclient.h"

RestClient::RestClient(QString schema, QString host, int port, QString basePath)
{
  url.setScheme(schema);
  url.setHost(host);
  url.setPort(port);
  this->basePath= basePath;
  url.setPath(basePath);
}

QString RestClient::hi(QString path, bool &ok)
{
    lastError ="";
    ok=false;
    m_aborted= false;
    m_busyOnRequest= true;
    QNetworkRequest request;
    url.setPath(basePath+path);
    request.setUrl(url);
    request.setHeader(
                QNetworkRequest::ContentTypeHeader,
                "text/html");
    m_response = m_client.get(request);

    while(!m_response->isFinished()){
        //m_response->abort();

        //if(m_aborted) return "";
        qApp->processEvents();
    }
    if( m_response->error()==QNetworkReply::NoError){
    QString txt = m_response->readAll();
    m_response->deleteLater();
    ok=true;
    m_busyOnRequest=false;
    return txt;
    }

    lastError= m_response->errorString();
    m_response->deleteLater();
    m_busyOnRequest= false;
    return lastError;
}

QList<Header> RestClient::getHeaders(QString path,bool &ok){
    ok=false;
    m_busyOnRequest=true;
    m_aborted =false;
    QNetworkRequest request;
    url.setPath(basePath+path);
    request.setUrl(url);
    request.setHeader(
                QNetworkRequest::ContentTypeHeader,
                "application/json");
     m_response = m_client.get(request);

    while(!m_response->isFinished()){

        qApp->processEvents();
    }
    if( m_response->error()==QNetworkReply::NoError){
    QJsonDocument jsonDoc = QJsonDocument::fromJson(m_response->readAll());
        m_response->deleteLater();
        //ImpoExpoJson::fromJsonArrayDoc(jsonDoc);
        ok=true;
        m_busyOnRequest=false;
        return Header::fromJsonArrayDoc(jsonDoc);
    }
    lastError= m_response->errorString();
    m_response->deleteLater();
    m_busyOnRequest=false;
    return QList<Header>();
}

QList<INote> RestClient::getNotes(QString path)
{
    QNetworkRequest request;
    url.setPath(basePath+path);
    request.setUrl(url);
    request.setHeader(
                QNetworkRequest::ContentTypeHeader,
                "application/json");
    m_busyOnRequest=true;
    m_response = m_client.get(request);

    while(!m_response->isFinished()){

        qApp->processEvents();
    }
    QJsonDocument jsonDoc = QJsonDocument::fromJson(m_response->readAll());
        m_response->deleteLater();
        m_busyOnRequest=false;
        //ImpoExpoJson::fromJsonArrayDoc(jsonDoc);
        return Header::fromJsonArrayNotesDoc(jsonDoc);

}

bool RestClient::postNotes(QString path,QList<Note> notes)
{
    QNetworkRequest request;
    url.setPath(basePath+path);
    request.setUrl(url);

    //QList<INote> inotes= Header::convertNotesList(notes);
    QJsonDocument doc = Header::toJsonArrayNotesDoc(notes);

    //QJsonDocument::fromVariant(feed).toJson();
    //more human readable format - Indented
    //QByteArray data = doc.toJson(QJsonDocument::JsonFormat::Indented);
    QByteArray data = doc.toJson(QJsonDocument::JsonFormat::Compact);
    //QByteArray data1 = doc.toBinaryData();

    //qDebug()<< QVariant(doc).toJsonDocument();
    //qDebug().noquote()<<"JSON_1: "<<data;
    //qDebug()<<"JSON_2: "<<QString::fromUtf8(data);
    qDebug()<< QVariant(data).toByteArray();
    m_busyOnRequest=true;
    request.setHeader(
                QNetworkRequest::ContentTypeHeader,
                "application/json");
    m_response = m_client.post(request,data);

    while(!m_response->isFinished()){


        qApp->processEvents();
    }
    if(m_response->error()!= QNetworkReply::NoError){

        m_response->deleteLater();
        m_busyOnRequest=false;
        return false;
    }
    m_response->deleteLater();
    m_busyOnRequest=false;
    return true;
}

NotesBook RestClient::getBook(QString path,bool &ok)
{
    ok=false;
    m_busyOnRequest=true;
    QNetworkRequest request;
    url.setPath(basePath+path);
    request.setUrl(url);
    request.setHeader(
                QNetworkRequest::ContentTypeHeader,
                "application/json");
    m_response = m_client.get(request);

    while(!m_response->isFinished()){

        qApp->processEvents();
    }
    if( m_response->error()==QNetworkReply::NoError){
    QJsonDocument jsonDoc = QJsonDocument::fromJson(m_response->readAll());
        m_response->deleteLater();
        ok=true;
        m_busyOnRequest=false;
        //ImpoExpoJson::fromJsonArrayDoc(jsonDoc);
        return NotesBook::fromJsonDoc(jsonDoc);
    }
    lastError= m_response->errorString();
        m_response->deleteLater();
        m_busyOnRequest=false;
        return NotesBook();
}

bool RestClient::postBook(QString path, NotesBook book)
{
    QNetworkRequest request;
    url.setPath(basePath+path);
    request.setUrl(url);

    //QList<INote> inotes= Header::convertNotesList(notes);
    QJsonDocument doc = NotesBook::toJsonDoc(book);

    //QJsonDocument::fromVariant(feed).toJson();
    //more human readable format - Indented
    //QByteArray data = doc.toJson(QJsonDocument::JsonFormat::Indented);
    QByteArray data = doc.toJson(QJsonDocument::JsonFormat::Compact);
    //QByteArray data1 = doc.toBinaryData();

    //qDebug()<< QVariant(doc).toJsonDocument();
    //qDebug().noquote()<<"JSON_1: "<<data;
    //qDebug()<<"JSON_2: "<<QString::fromUtf8(data);
    qDebug()<< QVariant(data).toByteArray();
    m_busyOnRequest=true;
    request.setHeader(
                QNetworkRequest::ContentTypeHeader,
                "application/json");
    m_response = m_client.post(request,data);

    while(!m_response->isFinished()){

        qApp->processEvents();
    }
    if(m_response->error()!= QNetworkReply::NoError){
        lastError = m_response->errorString();
        m_response->deleteLater();
        m_busyOnRequest=false;
        return false;
    }
    m_response->deleteLater();
    m_busyOnRequest=false;
    return true;
}

QString RestClient::getLastError() const
{
    return lastError;
}

bool RestClient::busyOnRequest(){
    return m_busyOnRequest;
}
void RestClient::abort()
{
    if( !m_response->isFinished()){
            m_response->abort();
            m_aborted=true;
     }


}
