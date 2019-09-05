#ifndef BOOKCOVERDOWNLOADER_H
#define BOOKCOVERDOWNLOADER_H

#include <QObject>
#include <QByteArray>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>

class BookCoverDownloader : public QObject
{
    Q_OBJECT
public:
    explicit BookCoverDownloader(QString isbn13, QObject *parent = nullptr);
    virtual ~BookCoverDownloader();

    QByteArray DownloadedData() const;

signals:
    void Downloaded(QString);

private slots:
    void BookCoverDownloaded(QNetworkReply* pReply);

    void SaveImageToDisk();
private:
    QNetworkAccessManager m_webCtrl;
    QByteArray m_downloadedData;

    QString isbn13_;

};

#endif // BOOKCOVERDOWNLOADER_H
