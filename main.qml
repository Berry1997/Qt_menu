import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4

import Model 1.0
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property int index;
    Item {
        id:item
        width: 600
        height: 600
        signal qmlSignal(string msg)

        //Delegate
        Component {
            id: objRecursiveDelegate
            Column {
                Row {
                    //indent
                    Item {
                        height: 1
                        width: model.level * 40
                    }
                    Text {
                        text:model.name
                    }
                    Button{
                        text:"-"
                        x:550
                        width:30
                        onClicked: {
                            //if(model.parent!=="null")
                            //  objModel.get(model.parent).subNode.remove(index);
                            //else
                            //  objModel.remove(index);
                        }
                    }
                }
                /*Repeater {
                    model: subNode
                    delegate: objRecursiveDelegate
                }*/
            }
        }
        //View
        ListView{
            anchors.fill: parent
            model:MyModel{
                list:data
            }
            delegate: objRecursiveDelegate
        }
    }
    TextField{
        id:input2
        x:450
        width:100
        anchors.verticalCenter: parent.verticalCenter
    }
    Button{
        text:"ADDTitle"
        anchors.verticalCenter: parent.verticalCenter
        x:550
        width:70
        onClicked: {
            //if(db.push_lv1(input2.text))
            //  objModel.append({"name":input2.text,"level":0,"parent":"null","subNode":[]})
            //input2.text="";
        }
    }
    Row{
        x:300
        Text{
            text:"add"
        }

        TextField{
            id:input3
            x:350
            width:100
        }
        Text{
            text:"property"
        }
        TextField{
            id:input4
            x:450
            width:100
        }
        Button{
            text:"OK"
            x:550
            width:70
            onClicked: {
                //if(db.get_prop_index(input3.text)!="null")
                //  objModel.get(db.get_prop_index(input3.text)).subNode.append({"name":input4.text,"level":1,"parent":db.get_prop_index(input3.text),"subNode":[]})
                input3.text="";
                input4.text="";
            }
        }
    }


    Button{
        text:"save"
        y:400
        x:500
        onClicked: {
            db.export_xml();
        }
    }
    Button{
        text:"load"
        y:450
        x:500
        onClicked: {
            db.import_xml();
            item.qmlSignal("Hello from QML")
        }
    }



}

