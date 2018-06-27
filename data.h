#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <QtXml>
#include <QUrl>
#include <QFileDialog>
#include <QDebug>

struct unit{
    QString name;
    QString parent;
    QString level;
    bool operator==(unit o) const {
        return (name == o.name &&
                parent== o.parent &&
                level == o.level);
    }
};

class Data:public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);
    QVector<unit> items() const;
    bool setItemAt(int index, const unit &item);
    Q_INVOKABLE void appendItem(const QString name, const QString &level, const QString &parent);
    Q_INVOKABLE void removeItem(const QString props, const QString level);
    Q_INVOKABLE void export_xml(const QString path);
    Q_INVOKABLE void import_xml(const QString path);

signals:
    void preItemAppended(int number);
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

private:
    QVector<unit> menu;
};

#endif // Data_H
