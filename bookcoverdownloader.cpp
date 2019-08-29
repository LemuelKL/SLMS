#include "bookcoverdownloader.h"
#include <constant.h>

#include <QDir>
#include <QCoreApplication>
#include <QPixmap>

BookCoverDownloader::BookCoverDownloader(QString isbn13, QObject *parent) :
    QObject(parent)
{
    QString image_url = "http://covers.openlibrary.org/b/isbn/" + isbn13 + "-M.jpg";
    QUrl url = image_url;
    isbn13_ = isbn13;
    qDebug() << "Downloading from" << url.toString();

    connect(
    &m_WebCtrl, SIGNAL (finished(QNetworkReply*)),
    this, SLOT (BookCoverDownloaded(QNetworkReply*))
    );

    QNetworkRequest request(image_url);
    m_WebCtrl.get(request);
}

BookCoverDownloader::~BookCoverDownloader() { }

void BookCoverDownloader::BookCoverDownloaded(QNetworkReply* pReply)
{
    QByteArray bytes = pReply->readAll();
    QString str = QString::fromUtf8(bytes.data(), bytes.size());
    int statusCode = pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "Request's statue code:" << QVariant(statusCode).toString();

    if(statusCode == 302)
    {
        QUrl new_url = pReply->attribute(QNetworkRequest::RedirectionTargetAttribute).toUrl();
        qDebug() << "Redirected to " + new_url.toString();
        QNetworkRequest new_request(new_url);
        m_WebCtrl.get(new_request);
        return;
    }

    qDebug() << pReply->error();
    m_DownloadedData = bytes;
    qDebug() << "Downloaded:" << m_DownloadedData.size() << "Bytes";
    SaveImageToDisk();
    pReply->deleteLater();
}

void BookCoverDownloader::SaveImageToDisk()
{
    QString save_path = QCoreApplication::applicationDirPath() + QDir::separator();
    save_path += BOOK_COVER_DIR_NAME;
    save_path += QDir::separator();
    save_path += isbn13_;
    save_path += ".jpg";
    QPixmap book_cover;
    book_cover.loadFromData(m_DownloadedData);
    qDebug() << isbn13_ + ".jpg" << book_cover;
    qDebug() << "Saving" << isbn13_ + ".jpg" << "at" << save_path << book_cover.save(save_path);
}
