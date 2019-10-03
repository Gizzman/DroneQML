import QtQuick 2.4
import QtQuick.Controls 2.9
import QtQuick.Window 2.4
import QtPositioning 5.5
import QtLocation 5.6
import QtQuick.Layouts 1.3

Window
{
    id: aplication
    width: 800
    height: 600
    visible: true
    title: "Dron"
    property variant startPositioLant: QtPositioning.coordinate( 50.161751, 27.078982 )
    property int comb

    property int i: 0
    property variant topLeftEurope: QtPositioning.coordinate(60.5, 0.0)
    property variant bottomRightEurope: QtPositioning.coordinate(51.0, 14.0)
    property variant viewOfEurope:
            QtPositioning.rectangle(topLeftEurope, bottomRightEurope)

    property variant berlin: QtPositioning.coordinate(52.5175, 13.384)
    property variant oslo: QtPositioning.coordinate(59.9154, 10.7425)
    property variant london: QtPositioning.coordinate(51.5, 0.1275)
    property variant point1: QtPositioning.coordinate(53.5175, 14.384)
    property variant point2: QtPositioning.coordinate(60.9154, 11.7425)
    property variant point3: QtPositioning.coordinate(50.358157, 26.697923)
    property variant shepetivka: QtPositioning.coordinate(50.181360, 27.053639)
    property variant kyiv: QtPositioning.coordinate(50.464055, 30.498494)
    property int xPos
    property int yPos
    property bool stop: false
    property string base:"50.190133, 27.063131"
    property string start:"50.189676, 27.063756"
    property string end: "50.186699, 27.069989"
    Row
    {
        id: row2
        width: aplication.width
        height: aplication.height
        anchors.top: parent.top
        anchors.topMargin: 0
        anchors.bottom: parent.bottom
        anchors.bottomMargin: 0
        anchors.left: parent.left
        anchors.leftMargin: 0
        anchors.right: parent.right
        anchors.rightMargin: 0


        Column {

            id: column
            width: aplication.width/2
        height: aplication.height
        Layout.maximumHeight: 600
        Layout.maximumWidth: 400
        Layout.fillHeight: true
        Layout.fillWidth: true
        anchors.verticalCenter: parent.verticalCenter
        spacing: 6.7
        transformOrigin: Item.Center
            Row
            {
                id: row
            width: 382
            height: 33
            Layout.fillHeight: true
            Layout.fillWidth: true

                Label {
                id:label1
                width: 194
                height: 23
                text: "Висота польоту"
                font.pointSize: 11
                verticalAlignment: Text.AlignTop
                font.family: "Arial"
                }
                TextField {
                id: he
                width: 150
                height: 23
                text: "150"
                font.family: "Arial"
                font.pointSize: 9
                }
            }
            Row {
                id: row1
                width: 382
                height: 33
                Layout.fillHeight: true
                Layout.fillWidth: true
                Label
                {
                    id:label2
                    width: 194
                    height: 23
                    text: "Фокусна відстань об'єктива"
                    font.pointSize: 11
                    verticalAlignment: Text.AlignTop
                    font.family: "Arial"
                }
                TextField
                {
                    id: focusdistance
                    width: 150
                    height: 23
                    text: "50"
                    Layout.fillWidth: false
                    font.family: "Arial"
                    font.pointSize: 9
                }
            }
            Label
            {
                id:label3
                width: 193
                height: 23
                text: "Геометрія фотосенсора"
                font.pointSize: 11
                verticalAlignment: Text.AlignTop
                font.family: "Arial"
            }
            Row {
                id: row13
                width: 334
            height: 32
            Layout.fillHeight: true
            Layout.fillWidth: true
                Row {
                    id: row10
                    width: 174
                height: 32
                    Label
                    {
                        id: label13
                        width: 20
                        height: 23
                        text: "V"
                        font.pointSize: 11
                        font.family: "Arial"
                        verticalAlignment: Text.AlignTop
                    }
                    TextField
                    {
                        id: v
                        width: 142
                        height: 23
                        text: "36"
                        font.family: "Arial"
                        font.pointSize: 9
                    }
                }
                Row
                {
                    id: row7
                width: 190
                height: 32
                    Label
                    {
                        id:label5
                        width: 20
                        height: 23
                        text: "H"
                        font.pointSize: 11
                        verticalAlignment: Text.AlignTop
                        font.family: "Arial"
                    }
                    TextField
                    {
                        id: h
                        width: 143
                        height: 23
                        text: "24"
                        font.family: "Arial"
                        font.pointSize: 9
                    }
                }
            }
            Row {
                id: row12
                width: 334
                height: 32
                Layout.fillHeight: true
                Layout.fillWidth: true
                Label
                {
                    id: label14
                    width: 194
                    height: 23
                    text: "Зарад батареї"
                    font.family: "Arial"
                    font.pointSize: 11
                    verticalAlignment: Text.AlignTop
                }
                TextField
                {
                    id: textbox11
                    width: 150
                    height: 23
                    text: "22222"
                    font.family: "Arial"
                    font.pointSize: 9
                }
            }
            Row {
                id: row11
                width: 334
                height: 32
                Layout.fillHeight: true
                Layout.fillWidth: true
                Label
                {
                    id: label12
                    width: 194
                    height: 23
                    text: "Витрати на фото"
                    font.family: "Arial"
                    font.pointSize: 11
                    verticalAlignment: Text.AlignTop
                }
                TextField
                {
                    id: costphoto
                    width: 150
                    height: 23
                    text: "2222"
                    font.family: "Arial"
                    font.pointSize: 9
                }
            }
            Row
            {
                id: row5
            width: 334
            height: 32
            Layout.fillHeight: true
            Layout.fillWidth: true
                Label
                {
                    id:label8
                    width: 194
                    height: 23
                    text: "Витрати на політ"
                    font.pointSize: 11
                    verticalAlignment: Text.AlignTop
                    font.family: "Arial"
                }
                TextField
                {
                    id: costfly
                    width: 150
                    height: 23
                    text: "222"
                    font.family: "Arial"
                    font.pointSize: 9
                }
            }
            Row
            {
                id: row4
                width: 334
                height: 32
                Layout.fillHeight: true
                Layout.fillWidth: true
                Label
                {
                    id: label9
                    width: 194
                    height: 23
                    text: "Координати бази"
                    font.pointSize: 11
                    font.family: "Arial"
                    verticalAlignment: Text.AlignTop
                }
                TextField
                {
                    id: pointbase
                    width: 150
                    height: 23
                    text:base
                    font.family: "Arial"
                    font.pointSize: 9
                }


                   RadioButton {
                    id: radioBase
                    height: 23
                    checkable: true
                    checked: false
                    onClicked:
                    {

                        radioStart.checkable=false;
                        radioEnd.checkable=false;
                    }
                }
            }
            Row
            {
                id: row9
            width: 334
            height: 32
            Layout.fillHeight: true
            Layout.fillWidth: true
                Label
                {
                    id: label11
                    width: 194
                    height: 23
                    text: "Початкові координати поля"
                    font.family: "Arial"
                    font.pointSize: 11
                    verticalAlignment: Text.AlignTop
                }
                TextField
                {
                    id: pointstart
                    width: 150
                    height: 23
                    text: start
                    font.family: "Arial"
                    font.pointSize: 9
                }

                RadioButton {
                    id: radioStart

                    height: 23
                    onClicked:
                    {

                        radioBase.checkable=false;
                        radioEnd.checkable=false;
                    }
                }
            }
            Row
            {
                id: row8
                width: 334
                height: 32
                Layout.fillHeight: true
                Layout.fillWidth: true
                Label
                {
                    id: label10
                    width: 194
                    height: 23
                    text: "Кінцеві координати поля"
                    font.family: "Arial"
                    font.pointSize: 11
                    verticalAlignment: Text.AlignTop
                }
                TextField
                {
                    id: pointend
                    width: 150
                    height: 23
                    text: end
                    font.family: "Arial"
                    font.pointSize: 9
                }

                RadioButton {
                    id: radioEnd
                    height: 23
                    onClicked:
                    {

                        radioBase.checkable=false;
                        radioStart.checkable=false;
                    }
                }
            }
            Button
            {
                id: button2
                width: 150
                height: 25
                text: "Вивести результат"
                visible: true
                onClicked:
                {
                    way.setCoordinates(pointbase.text,1);
                    way.setCoordinates(pointend.text,2);
                    way.setCoordinates(pointstart.text,3);
                    way.setAllParametrs(focusdistance.text,h.text,v.text,costphoto.text,costfly.text,he.text)
                    way.handleDate();
                }
            }
        }


        Map {
            id: map
            zoomLevel: 10
            width: aplication.width/2
            height: aplication.height
            plugin: Plugin {
                name: "esri" // "mapboxgl", "esri", ...
            }



            MouseArea
            {

                anchors.fill: parent
                hoverEnabled: true
                onPositionChanged: {
                //    xPos=mouse.x
                 //   yPos=mouse.y
                }

                onClicked:
                {

                        if(radioBase.checked)
                        {
                            base=map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude+','+ map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude;
                            radioBase.checkable=true
                            radioEnd.checkable=true;
                            radioStart.checkable=true;
                            radioBase.checked=false
                        }else if(radioEnd.checked)
                        {
                            end=map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude+','+ map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude;
                            radioBase.checkable=true
                            radioEnd.checkable=true;
                            radioStart.checkable=true
                            radioEnd.checked=false
                        } else if(radioStart.checked)
                        {
                            start=map.toCoordinate(Qt.point(mouse.x,mouse.y)).latitude+','+ map.toCoordinate(Qt.point(mouse.x,mouse.y)).longitude;
                            radioBase.checkable=true
                            radioEnd.checkable=true;
                            radioStart.checkable=true
                            radioStart.checked=false
                        }

                }
            }


            Plane
            {
                id: myPlane
                pilotName: "my own plane"
                coordinate: myPlaneControl.position


                MouseArea
                {
                    //for(var i; i<=1; i++){
                    anchors.fill: parent
                    onClicked:
                    {
                        if (myPlaneAnimation.running || myPlaneControl.isFlying())
                        {
                            console.log("Plane still in the air.");
                            return;
                        }

                        //set variable
                        myPlaneAnimation.rotationDirection = myPlaneControl.position.azimuthTo(myPlaneControl.to)

                        //it calls startFlight in the controller

                       // myPlane.departed(); // show messages
                        //myPlaneControl.onClicked();
                        myPlane.onPlaneClicked();

                            //sleep wait
                            /*myPlaneControl.from = berlin;  // start position
                            myPlaneControl.to = oslo;  // end position
                            myPlaneAnimation.start();
                            myPlaneControl.arrived.connect(arrived)
                            myPlaneAnimation.start();
                            myPlaneControllerOnClicked();*/


                    }
                }

                function onPlaneClicked()
                {
                    //myPlaneControl.arrived.connect(arrived);
                    stop=false;
                    myPlane.arrived();

                    //myPlaneAnimation.start();
                }

                function arrived()
                {
                    if(!stop)
                    {
                        myPlaneControl.pos();
                        myPlaneAnimation.rotationDirection = myPlaneControl.position.azimuthTo(myPlaneControl.to)
                        myPlaneAnimation.start()
                        myPlane.showMessage(qsTr("take Photo"))
                    }

                }



                SequentialAnimation
                {
                    id: myPlaneAnimation
                    property real rotationDirection : 0;

                    NumberAnimation
                    {
                        // Rotation to next point

                        target: myPlane; property: "bearing"; duration: 10
                        easing.type: Easing.InOutQuad
                        to: myPlaneAnimation.rotationDirection

                    }
                    // called when "myPlaneAnimation.start()"
                    ScriptAction { script: myPlaneControl.startFlight() }
                }
                //! [CppPlane3]
                function stoped()
                {
                    stop=true;
                }

                // when qml is loaded
                Component.onCompleted:
                {
                    myPlaneControl.position = london;  // default position before moving
                  //  myPlaneControl.from = point1;  // start position
                 //   myPlaneControl.to = point2;  // end position
                    myPlaneControl.stoped.connect(stoped)
                    myPlaneControl.arrived.connect(arrived)
                }



            }

            visibleRegion: viewOfEurope
        }
    }
}



/*##^##
Designer {
    D{i:1;anchors_x:0;anchors_y:0}
}
##^##*/
