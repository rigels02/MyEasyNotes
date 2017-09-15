#ifndef RESTCLIENT_H
#define RESTCLIENT_H

#include <QtNetwork>

#include "rest/notesbook.h"

/**
 * @brief The RestClient class
 * Used to consume restful services exposed by noteBookJPA spring-boot application
 */
class RestClient
{
public:
    RestClient(QString schema="http", QString host="localhost",int port=8080,QString basePath="/notesbook");

    QString hi(QString path, bool &ok);
    QList<Header> getHeaders(QString path, bool &ok);
    QList<INote> getNotes(QString path);
    bool postNotes(QString path, QList<Note> notes);
    NotesBook getBook(QString path, bool &ok);
    bool postBook(QString path, NotesBook book);

    QString getLastError() const;
    void abort();

    bool busyOnRequest();
private:
    QNetworkReply *m_response;
    bool m_busyOnRequest;
    bool m_aborted;
    QNetworkAccessManager m_client;
    QUrl url;
    QString basePath;
    QString lastError;
};

#endif // RESTCLIENT_H
