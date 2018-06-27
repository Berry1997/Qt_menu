#include "data.h"
#include <iostream>


Data::Data(QObject *parent) : QObject(parent)
{
}

QVector<unit> Data::items() const{
    return menu;
}

bool Data::setItemAt(int index, const unit &item)
{
    if (index < 0 || index >= menu.size())
        return false;

    const unit &oldItem = menu.at(index);

    if (item == oldItem)
        return false;

    menu[index] = item;
    return true;
}

void Data::appendItem(const QString name, const QString &level, const QString &parent)
{
    unit item{name, parent, level};
    //CHECK IF ALREADY EXISTS
    for(int i=0;i<menu.length();i++){
        if(menu[i].name==name && menu[i].level==level&& menu[i].parent==parent)
            return;
    }
    //level 0 insert
    if(level=="0"){
        //std::cout<<"inside level 0"<<std::endl;
        int i = menu.length();
        emit preItemAppended(i);
        menu.append(item);
        emit postItemAppended();
    }else{
        //level 1 insert
        bool found = false;
        //std::cout<<"size is: "<<menu.size()<<std::endl;
        int k = 0;
        for(int i=0;i<menu.size();i++){
            if(parent==menu.at(i).name && menu.at(i).level=="0"){
                found = true;
                k = i;
                break;
            }
            k = i;
        }
        //std::cout<<"k is: "<<k<<" menu size is: "<<menu.size()<<std::endl;
        if(!found)
            return;
        while(1){//try to get to the end of the child in level 1
            if(k+1 ==menu.size()) break;
            if(menu.at(k+1).level=="0")
                break;
            k++;
        }
        emit preItemAppended(k+1);
        menu.insert(k+1,item);
        emit postItemAppended();

    }
}

void Data::removeItem(const QString props , const QString level)
{
    if(level=="0"){
        for(int i=0;i<menu.size();i++){
            if (menu.at(i).name==props&&menu.at(i).level==level){
                emit preItemRemoved(i);
                menu.removeAt(i);
                emit postItemRemoved();
                break;
            }
        }
        int i=0;

        //delete Title property
        while(1){
            if(i>=menu.size())
                break;
            else if (menu.at(i).parent==props){
                //std::cout<<"Removed at: "<<i<<" name is: "<<menu.at(i).name.toStdString()<<std::endl;
                emit preItemRemoved(i);
                menu.removeAt(i);
                emit postItemRemoved();
                i=0;
            }
            else
                i++;
        }
    }else{
        for (int i = 0; i < menu.size(); ) {
            if (menu.at(i).name==props&& menu.at(i).level == level) {
                emit preItemRemoved(i);
                menu.removeAt(i);
                emit postItemRemoved();
                return;
            } else {
                ++i;
            }
        }
    }
}

void Data::export_xml(const QString path){
    qDebug()<<"in export xml function ";
    //create root tag
    QDomDocument document;
    QDomElement root = document.createElement("File");
    document.appendChild(root);

    for(int i=0;i<menu.length();i++){
        //create second level tag -- Title
        if(menu[i].level=="0"){
            qDebug()<<menu[i].name;
            QDomElement doc = document.createElement(menu[i].name);
            doc.setAttribute("Title",menu[i].name);
            root.appendChild(doc);
            int k;
            for(k=i+1;k<menu.length();k++){
                if(menu[k].level=="0")
                    break;
                else{
                    QDomElement doc_child = document.createElement(menu[k].name);
                    doc_child.setAttribute("prop",menu[k].name);
                    doc.appendChild(doc_child);
                }
            }
            if(k>=menu.length())
                break;
            else
                i = k-1;
        }
    }

    //Open file to write
    QFile file(path);
    if(!file.open(QIODevice::WriteOnly|QIODevice::Text)){
        qDebug()<<"fail";
    }else{
        QTextStream stream(&file);
        stream<<document.toString();
        file.close();
    }

}
void Data::import_xml(const QString path){
    //clear first

    while(menu.size()!=0){
        emit preItemRemoved(0);
        menu.removeAt(0);
        emit postItemRemoved();
    }
    QDomDocument document;
    //openFile();
    //qDebug()<<cur_path;
    QFile file(path);

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
        //use a varable to store the amount of second level node
        int level2_node = 0;
        for(int i=0;i<items.count();i++){
            QDomNode itemnode = items.at(i);//Find the properties of each title and push to vector
            if(itemnode.isElement())
            {
                QDomElement itemelement = itemnode.toElement();
                unit tmp;
                QString pt;
                pt = tmp.name = itemelement.nodeName();
                tmp.level = "0";
                tmp.parent = "null";
                //insert into menu
                emit preItemAppended(i+level2_node);
                menu.insert(i+level2_node,tmp);
                emit postItemAppended();
                //qDebug()<<"found tag name"<<itemelement.nodeName();
                //parse second level child node
                QDomNodeList items2 = itemelement.childNodes();
                for(int j=0;j<items2.count();j++){
                    level2_node++;
                    QDomNode item2node = items2.at(j);
                    if(itemnode.isElement()){
                        QDomElement item2element = item2node.toElement();
                        unit tmp;
                        tmp.name = item2element.nodeName();
                        tmp.level = "1";
                        tmp.parent = pt;
                        //insert into menu
                        //qDebug()<<"index is: "<<i+level2_node;
                        emit preItemAppended(i+level2_node);
                        menu.insert(i+level2_node,tmp);
                        emit postItemAppended();
                    }
                }
            }
        }
    }
}
