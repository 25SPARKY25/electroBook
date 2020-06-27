#ifndef NET_TEST_H
#define NET_TEST_H

#include <QObject>

class net_test : public QObject
{
    Q_OBJECT
public:
    explicit net_test(QObject *parent = nullptr);

signals:

public slots:
};

#endif // NET_TEST_H
