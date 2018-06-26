#ifndef DATA_H
#define DATA_H
#include <QtQuick>
#include <iostream>
#include <QtXml>
#include <QUrl>
#include <QFileDialog>
#include <QDebug>
struct unit{
    QString name;
    QString parent;
    QString level;
    QVariantList subNodes;
};
class Data:public QObject
{
    Q_OBJECT
public:
    explicit Data(QObject *parent = nullptr);
    QVector<unit> items() const{
       QVector<unit> menu;
        return menu;
    }
    bool setItemAt(int index, const unit &item)
    {
        if (index < 0 || index >= menu.size())
            return false;

        const unit &oldItem = menu.at(index);
        if (item.name == oldItem.name && item.level == oldItem.level&&item.parent==oldItem.parent&&item.subNodes==oldItem.subNodes)
            return false;

        menu[index] = item;
        return true;
    }
    void appendItem()
    {
        emit preItemAppended();
        unit item;
        menu.append(item);
        emit postItemAppended();
    }
    void removeItem(const QString props)
    {
        for (int i = 0; i < menu.size(); ) {
            if (menu.at(i).name==props) {
                emit preItemRemoved(i);

                menu.removeAt(i);

                emit postItemRemoved();
                return;
            } else {
                ++i;
            }
        }
    }
    /*Q_INVOKABLE void export_xml(){
        //create root tag
        QDomDocument document;
        QDomElement root = document.createElement("File");
        document.appendChild(root);

        for(int i=0;i<menu.length();i++){
            //create second level tag -- Title
            QDomElement doc = document.createElement(menu[i].first);
            doc.setAttribute("Title",menu[i].first);
            root.appendChild(doc);

            //create third level tag -- Prop
            if(menu[i].second.length()!=0){
                for(int j=0;j<menu[i].second.length();j++){
                    QDomElement doc_child = document.createElement(menu[i].second[j]);
                    doc_child.setAttribute("prop",menu[i].second[j]);
                    doc.appendChild(doc_child);
                }
            }
        }

        //Open file to write
        QFile file("/Users/shichanglin/Desktop/myXml.xml");
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
            qDebug()<<"fail";
        }else{
            QTextStream stream(&file);
            stream<<document.toString();
            file.close();
        }
    }
    Q_INVOKABLE void import_xml(){
        QDomDocument document;
        //openFile();
        //qDebug()<<cur_path;
        QFile file("/Users/shichanglin/Desktop/myXml.xml");

        //Check if file exists
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text)||!document.setContent(&file)){
            qDebug()<<"fail to read";
        }else{
            qDebug()<<"success to read";
            //close file first
            file.close();

            //Find root element
            QDomElement root = document.firstChildElement();//file
            //Find all value tags and push into Vector --> Title
            QDomNodeList items = root.childNodes();
            menu.clear();
            for(int i=0;i<items.count();i++){
                QDomNode itemnode = items.at(i);//Find the properties of each title and push to vector
                if(itemnode.isElement())
                {
                    QDomElement itemelement = itemnode.toElement();
                    QPair<QString,QVector<QString>> tmp;
                    menu.push_back(tmp);
                    menu[i].first = itemelement.nodeName();
                    qDebug()<<"found tag name"<<itemelement.nodeName();
                    QDomNodeList items2 = itemelement.childNodes();
                    for(int j=0;j<items2.count();j++){
                        QDomNode item2node = items2.at(i);
                        if(itemnode.isElement()){
                            QDomElement item2element = item2node.toElement();
                            menu[i].second.push_back(item2element.nodeName());
                        }
                    }
                }
            }
        }
    }*/

signals:
    void preItemAppended();
    void postItemAppended();

    void preItemRemoved(int index);
    void postItemRemoved();

private:
    QVector<unit> menu;
};

#endif // Data_H
