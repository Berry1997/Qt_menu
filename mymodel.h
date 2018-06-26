#ifndef MYMODEL_H
#define MYMODEL_H

#include <QAbstractListModel>
#include "data.h"

class Data;
class MyModel : public QAbstractListModel//Type needs to be defined in upper letter
{
    Q_OBJECT
    Q_PROPERTY(Data *list READ list WRITE setList)

public:
    explicit MyModel(QObject *parent = nullptr);
    enum {
        NameRole = Qt::UserRole,
        LevelRole,
        ParentRole,
        SublevelRole
    };
    // Basic functionality:
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    // Editable:
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole) override;

    Qt::ItemFlags flags(const QModelIndex& index) const override;
    virtual QHash <int ,QByteArray>roleNames()const override;

    Data *list() const;
    void setList(Data *list);

private:
    Data* mList;
};

#endif // MyModel_H
