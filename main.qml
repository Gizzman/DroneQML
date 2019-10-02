import QtQuick 2.4
import QtQuick.Controls 2.9
import QtQuick.Window 2.4
import QtPositioning 5.5
import QtLocation 5.6

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

    Row
    {
        id: row2
        x: 0
        y: 0
        width: aplication.width
        height: aplication.height


        Column {

        id: column
        width: aplication.width/2
        height: aplication.height
        spacing: 6
        transformOrigin: Item.Center
            Row
            {
            id: row
            width: 382
            height: 33
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
                        width: 150
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
                        width: 150
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
                    text: "50.190133, 27.063131"
                    font.family: "Arial"
                    font.pointSize: 9
                }

                RadioButton {
                    id: radioBase
                    height: 23
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
                    text: "50.189676, 27.063756"
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
                    text: "50.186699, 27.069989"
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
            id: mapOfEurope

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
                    myPlane.showMessage(xPos+" "+yPos);


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
                    myPlane.arrived();
                    //myPlaneAnimation.start();
                }

                function arrived()
                {
//                            var point = [london,berlin,oslo, shepetivka,kyiv];

//                    myPlaneControl.position = point[i];
//                        myPlaneControl.from = point[i];  // start position
//                        myPlaneControl.to = point[i+1];
                      myPlaneControl.pos();
                      myPlaneAnimation.rotationDirection = myPlaneControl.position.azimuthTo(myPlaneControl.to)
                      myPlaneAnimation.start()
                      myPlane.showMessage(qsTr(i.toString()))

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

                // when qml is loaded
                Component.onCompleted:
                {
                    myPlaneControl.position = london;  // default position before moving
                    myPlaneControl.from = point1;  // start position
                    myPlaneControl.to = point2;  // end position
                    myPlaneControl.arrived.connect(arrived)
                }


                function departed()
                {
                    if (myPlaneControl.from === point2)
                        myPlane.showMessage(qsTr("See you bro!"))
                    else if (myPlaneControl.from === point1)
                        myPlane.showMessage(qsTr("Bye, see you soon!"))
                }

                function delay(delayTime)
                {
                    timer = new Timer();
                    timer.interval = delayTime;
                    timer.repeat = false;
                    timer.start();
                }
            }

            visibleRegion: viewOfEurope
        }
    }
}
/*##^##
Designer {
    D{i:4;anchors_height:23;anchors_width:150}D{i:3;anchors_height:23;anchors_width:194}
D{i:1;anchors_height:584;anchors_width:381;anchors_x:48;anchors_y:57}
}
##^##*/

