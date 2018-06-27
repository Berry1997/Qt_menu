#include "mymodel.h"
#include <iostream>
#include "data.h"

MyModel::MyModel(QObject *parent)
    : QAbstractListModel(parent)
    , mDatas(nullptr)
{
    std::cout<<"inside Model constructed"<<std::endl;
}

int MyModel::rowCount(const QModelIndex &parent) const
{
    // For list models only the root node (an invalid parent) should return the list's size. For all
    // other (valid) parents, rowCount() should return 0 so that it does not become a tree model.
    if (parent.isValid())
        return 0;

    // FIXME: Implement me!

    return mDatas->items().size();
}

QVariant MyModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();
    const unit item = mDatas->items().at(index.row());

    // FIXME: Implement me!
    switch (role) {
    case NameRole:
        return QVariant(item.name);
    case LevelRole:
        return QVariant(item.level);
    case ParentRole:
        return QVariant(item.parent);
    }
    return QVariant();
}

bool MyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (!mDatas)
            return false;
        unit item = mDatas->items().at(index.row());
        switch (role) {
        case NameRole:
            item.name = value.toString();
            break;
        case LevelRole:
            item.level = value.toString();
            break;
        case ParentRole:
            item.parent = value.toString();
            break;

        }
    if (mDatas->setItemAt(index.row(), item)) {
        // FIXME: Implement me!
        emit dataChanged(index, index, QVector<int>{role});
        return true;
    }
    return false;
}

Qt::ItemFlags MyModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::NoItemFlags;

    return Qt::ItemIsEditable; // FIXME: Implement me!
}

QHash<int, QByteArray> MyModel::roleNames() const
{
    QHash<int ,QByteArray>names;
    names[NameRole] = "name";
    names[LevelRole] = "level";
    names[ParentRole] = "parent";
    return names;
}

Data *MyModel::datas() const
{
    return mDatas;
}

void MyModel::setDatas(Data *data)
{
    beginResetModel();
    if (mDatas)
        mDatas->disconnect(this);
    delete mDatas;
    mDatas = data;
    if (mDatas) {
        connect(mDatas, &Data::preItemAppended, this, [=](int number) {
            const int index = mDatas->items().size();
            beginInsertRows(QModelIndex(), number, number);
        });
        connect(mDatas, &Data::postItemAppended, this, [=]() {
            endInsertRows();
        });

        connect(mDatas, &Data::preItemRemoved, this, [=](int index) {
            beginRemoveRows(QModelIndex(), index, index);
        });

        connect(mDatas, &Data::postItemRemoved, this, [=]() {
            endRemoveRows();
        });
    }

    endResetModel();
}
