#include "networkmanager.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QVariant>
#include <QDebug>
#include <QNetworkCookieJar>
#include <QEventLoop>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    //manager que faz as requisições
    manager = new QNetworkAccessManager(this);
    cookieJar = new QNetworkCookieJar(this);
    manager->setCookieJar(cookieJar);
}
void NetworkManager::login(const QString &username, const QString &password)
{
    QNetworkRequest request;
    QNetworkReply *reply;

    qDebug() << "Running GET request for handling csrftoken";
    QUrl url("https://suap.ifba.edu.br/accounts/login/");

    request.setUrl(url);

    reply = manager->get(request);

    QObject::connect(reply, &QNetworkReply::readyRead, [&](){
        //print
        qDebug() << reply->readAll();
    });

    QObject::connect(reply, &QNetworkReply::finished, [&](){
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Request finished successfully";
        } else {
            qDebug() << "Error during request:" << reply->errorString();
        }
        reply->deleteLater(); // Clean up memory
    });

    QObject::connect(reply, QOverload<QNetworkReply::NetworkError>::of(&QNetworkReply::errorOccurred), [&](QNetworkReply::NetworkError code) {
        qDebug() << "Network error occurred:" << code;
        reply->deleteLater(); // Clean up memory
    });
}

