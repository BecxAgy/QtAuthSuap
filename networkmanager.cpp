#include "networkmanager.h"
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QVariant>
#include <QDebug>
#include <QNetworkCookieJar>

NetworkManager::NetworkManager(QObject *parent) : QObject(parent)
{
    //manager que faz as requisições
    manager = new QNetworkAccessManager(this);
    cookieJar = new QNetworkCookieJar(this);
    manager->setCookieJar(cookieJar);
}

void NetworkManager::login(const QString &username, const QString &password)
{
    qDebug() << "Running with credentials:" << username << password;
    QUrl url("https://suap.ifba.edu.br/accounts/login/");

        // POST com o token CSRF e os dados de login
        QUrlQuery postData;
        postData.addQueryItem("csrfmiddlewaretoken", "D4S48S4ZjoIglSjriyMDgz6pP1TRjATV3PJ5fLKEPuhwL2iFwURdCJr073ahRaqp");
        postData.addQueryItem("username", username);
        postData.addQueryItem("password", password);
        postData.addQueryItem("this_is_the_login_form", "1");
        postData.addQueryItem("next", "");

        QNetworkRequest postRequest(url);
        postRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/x-www-form-urlencoded");

        QNetworkReply *postReply = manager->post(postRequest, postData.toString(QUrl::FullyEncoded).toUtf8());
        connect(postReply, &QNetworkReply::finished, this, [this, postReply]() {
            postReply->deleteLater();

            if (postReply->error() == QNetworkReply::NoError) {
                // Login bem-sucedido, podemos acessar uma página privada, por exemplo
                QUrl privateUrl("https://suap.ifrn.edu.br/minhas-informacoes/");
                QNetworkRequest privateRequest(privateUrl);
                QNetworkReply *privateReply = manager->get(privateRequest);
                connect(privateReply, &QNetworkReply::finished, this, [privateReply]() {
                    qDebug() << "Página privada:" << privateReply->readAll();
                    privateReply->deleteLater();
                });
            } else {
                qDebug() << "Erro ao fazer login:" << postReply->errorString();
            }
        });

}
