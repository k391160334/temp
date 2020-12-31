#ifndef QTH_H
#define QTH_H

#include <QThread>

class qTh : public QThread
{
    Q_OBJECT

public:
    explicit qTh(QObject* parent = 0);
    ~qTh();
private:
    void run();
signals:
    void setAngle(float a);
};

#endif // QTH_H
