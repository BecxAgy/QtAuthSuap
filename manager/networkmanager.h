#ifndef NETWORKMANAGER_H
#define NETWORKMANAGER_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkCookieJar>

class NetworkManager : public QObject
{
    Q_OBJECT
public:
    explicit NetworkManager(QObject *parent = nullptr);

public slots:
    void login(const QString &username, const QString &password);

private:
    QNetworkAccessManager *manager;
    QNetworkCookieJar *cookieJar;
};

#endif // NETWORKMANAGER_H
