#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>
#include <QQmlEngine>

class NetworkManager : public QObject
{
    Q_OBJECT
    QML_ELEMENT
    QML_SINGLETON

public:
    explicit NetworkManager(QObject *parent = nullptr);

public slots:
    void login(const QString &username, const QString &password);

private:
    QNetworkAccessManager *manager;
    QNetworkCookieJar *cookieJar;
};

#endif // NETWORKMANAGER_H
