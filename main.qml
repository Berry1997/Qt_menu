import QtQuick 2.9
import QtQuick.Window 2.2
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls.Styles 1.4
import QtQuick.Dialogs 1.3

import Model 1.0
Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")
    property int index;
    property string mode:"default"
    property string path
    property string old_path
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
                        width: level * 40
                    }
                    Text {
                        text: name
                    }
                    Button{
                        x:550
                        width:30
                        text: "-"
                        onClicked: {
                            info.removeItem(name,level);
                        }
                    }
                }
            }
        }
        //View
        ListView{
            anchors.fill: parent
            model:MyModel{
                datas: info //class data
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
            if(input2.text!="")
                info.appendItem(input2.text, "0", "null")
            input2.text="";
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
                if(input3.text!="" && input4.text!=""){
                    info.appendItem(input4.text,1,input3.text);
                    input3.text="";
                    input4.text="";
                }

            }
        }
    }


    Button{
        text:"save"
        y:400
        x:500
        onClicked: {
            mode = "save";
            if(path=="")
                filedialog.open();
            else
                info.export_xml(path);
        }
    }
    Button{
        text:"load"
        y:450
        x:500
        onClicked: {
            mode = "load";
            filedialog.open();
        }
    }
    Button{
        text:"save new"
        y:350
        x:500
        onClicked: {
            mode = "save_new";
            filedialog.open();
        }
    }
    FileDialog{
        id:filedialog
        nameFilters: "*.xml"

        selectExisting: {
            if(mode=="save_new")
                false
            else
                true
        }

        onAccepted: {
            path = fileUrl;

            //delete file://
            path = path.replace(/^(file:\/{2})/,"");
            // unescape html codes like '%23' for '#'
            if(path!="" && mode=="load"){
                old_path = path;
                info.import_xml(path);
            }else{
                info.export_xml(path);
            }
        }

    }

}




