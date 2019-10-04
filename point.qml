import QtQuick 2.4
import QtLocation 5.6

 MapQuickItem {
        coordinate:  QtPositioning.coordinate(51.5, 0.1275)

        anchorPoint.x: image.width * 0.5
        anchorPoint.y: image.height

        sourceItem: Column {
            Image { id: image; source: "marker.png" }
            Text { text: title; font.bold: true }
        }
    }

