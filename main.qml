import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.12
import QtQuick.Controls.Styles 1.4
import QtQuick.Extras 1.4
import QtQuick.Layouts 1.12
import PlayerManager 1.0
import Player 1.0

Window {
    visible: true
    title: qsTr("TSDV lucky draw")
    //flags: Qt.FramelessWindowHint
    x: 0
    y: - 1
    width: Screen.width
    height: Screen.height + 1
    property Player picking_player: null
    Image {
        id: background_image
        anchors.fill: parent
        source: "qrc:/image/background.png"
    }
    Text {
        id: title
        anchors.top: parent.top
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: textSingleton.font.pixelSize * 4
        font.family: openSans.name
        font.bold: true
        color: "white"
        text: "TSDV YEAR END LUCKY DRAW"
    }

    Text {
        id: textSingleton
    }

    FontLoader {
        id: openSans
        source: "qrc:/fonts/OpenSans-Regular.ttf"
    }


    Tumbler {
        id: tumbler
        anchors.top: title.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter

        // TODO: Use FontMetrics with 5.4
        Label {
            id: characterMetrics
            font.bold: true
            font.pixelSize: textSingleton.font.pixelSize * 4
            font.family: openSans.name
            visible: false
            text: "M"
        }

        Component {
            id: tumbler_delegate
            Label {
                text: styleData.value
                opacity: 0.4 + Math.max(0, 1 - Math.abs(styleData.displacement)) * 0.6
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
                font.pixelSize: textSingleton.font.pixelSize * 3
            }
        }
        ListModel {
            id: tumbler_model
            Component.onCompleted: {
                for (var i = 0; i < 10; ++i) {
                    append({value: i.toString()});
                }
            }
        }

        readonly property real delegateTextMargins: characterMetrics.width * 1.5
        TumblerColumn {
            id: thousan_column
            width: characterMetrics.width + tumbler.delegateTextMargins *2
            model: tumbler_model
            delegate: tumbler_delegate
        }
        TumblerColumn {
            id: hundred_column
            width: characterMetrics.width + tumbler.delegateTextMargins *2
            model: tumbler_model
            delegate: tumbler_delegate
        }

        TumblerColumn {
            id: ten_column
            width: characterMetrics.width + tumbler.delegateTextMargins *2
            model: tumbler_model
            delegate: tumbler_delegate
        }
    }

    Button {
        id: btn_pick
        checkable: true
        text: checked? "STOP" : "Pick a lucky member"
        anchors.top: tumbler.bottom
        anchors.margins: 30
        anchors.horizontalCenter: parent.horizontalCenter
        font.pixelSize: textSingleton.font.pixelSize * 4
        background: Rectangle {
            implicitHeight: 100
            implicitWidth: 500
            color: btn_pick.checked ? "#FF857D" : "#84f75e"
            border.width: 0
            radius: 20
        }
        onToggled: {
            if(checked) {
                picking_player = playerManager.randomPrize(0)

                timer_ten.start()
                timer_hundred.start()
                timer_thousand.start()

                timer_stop_ten.target_index = picking_player.code % 10
                timer_stop_ten.restart()

                timer_stop_hundred.target_index = (picking_player.code/10)%10
                timer_stop_hundred.restart()

                timer_stop_thousand.target_index =  (picking_player.code/100)%10
                timer_stop_thousand.restart()
            } else {
                btn_pick.enabled = false
                timer_ten.stop()
                timer_hundred.stop()
                timer_thousand.stop()

                timer_stop_ten.stop()
                tumbler.setCurrentIndexAt(2, 0, 0)
                tumbler.setCurrentIndexAt(2, timer_stop_ten.target_index, 2500)

                timer_stop_hundred.stop()
                timer_stop_hundred.repeat_count = 0
                timer_stop_hundred.interval = 5000
                tumbler.setCurrentIndexAt(1, 0, 0)
                tumbler.setCurrentIndexAt(1, timer_stop_hundred.target_index, 2500)

                timer_stop_thousand.stop()
                timer_stop_thousand.repeat_count = 0
                timer_stop_thousand.interval = 6000
                tumbler.setCurrentIndexAt(0, 0, 0)
                tumbler.setCurrentIndexAt(0, timer_stop_thousand.target_index, 2500)

                timer_stop_all.start();
            }
        }
    }

    TableView {
        id: result_table
        columnSpacing: 20
        rowSpacing: 20
        clip: true
        anchors.top: btn_pick.bottom
        anchors.bottom: parent.bottom
        anchors.left: background_image.left
        anchors.right: background_image.right
        anchors.topMargin: 20
        anchors.leftMargin: 140
        anchors.rightMargin: 140
        model: lastPrizeItemModel

        delegate:
            Label  {
            font.pixelSize: textSingleton.font.pixelSize *(4.5 - lastPrizeItemModel.columnCount() )
            font.family: openSans.name
            color: "white"
            horizontalAlignment: Text.AlignHCenter
            text:  code? "   " + code + ". " + name + "   " : "";
            visible: code? true : false
            background: Rectangle {
                color: "#808080"
                radius: 4
                opacity: 0.5
            }
        }
        columnWidthProvider: function (column) {
            var column_count = lastPrizeItemModel.columnCount()
            var column_width = result_table.width/column_count
            return column_width
        }
    }

    Timer{
        id: timer_thousand
        interval: 100
        running: true
        repeat: true
        onTriggered: {
            scrollTumblerint(0, interval);
        }
    }
    Timer{
        id: timer_hundred
        interval: 80
        running: true
        repeat: true
        onTriggered: {
            scrollTumblerint(1, interval);
        }
    }
    Timer{
        id: timer_ten
        interval: 60
        running: true
        repeat: true
        onTriggered: {
            scrollTumblerint(2, interval);
        }
    }

    function scrollTumblerint(index, timer_interval) {
        var a = tumbler.currentIndexAt(index) >= 9? 0 : tumbler.currentIndexAt(index) +  1
        tumbler.setCurrentIndexAt(index, a, timer_interval)
    }

    Timer{
        id: timer_stop_ten
        interval: 3000
        running: false
        repeat: false
        property int target_index: 1
        onTriggered: {
            timer_ten.stop()
            tumbler.setCurrentIndexAt(2, 0, 0)
            tumbler.setCurrentIndexAt(2, target_index, 3000)
        }
    }

    Timer{
        id: timer_stop_hundred
        interval: 5000
        running: false
        repeat: true
        property int repeat_count: 0
        property int target_index: 2
        onTriggered: {
            if(repeat_count === 0) {
                timer_hundred.stop()
                tumbler.setCurrentIndexAt(1, 0, 0)
                interval = timer_hundred.interval
                btn_pick.enabled = false
            }
            interval += 200
            if(tumbler.currentIndexAt(1) === target_index){
                stop()
                repeat_count = 0
                interval = 5000
                if(!timer_stop_thousand.running && picking_player !== null){
                    display_text.text = picking_player.code + ". "+ picking_player.name
                    happy_screen.visible = true
                    happy_screen_animation.restart()
                    lastPrizeItemModel.addPrize(picking_player)
                    btn_pick.checked = false
                    btn_pick.enabled = true
                }
            } else {
                scrollTumblerint(1, interval)
                repeat_count++
            }
        }
    }

    Timer{
        id: timer_stop_thousand
        interval: 6000
        running: false
        repeat: true

        property int repeat_count: 0
        property int target_index: 3
        onTriggered: {
            if(repeat_count === 0) {
                timer_thousand.stop()
                tumbler.setCurrentIndexAt(0, 0, 0)
                interval = timer_thousand.interval
            }
            interval += 300
            if(tumbler.currentIndexAt(0) === target_index){
                stop()
                repeat_count = 0
                interval = 6000
                if(!timer_stop_hundred.running && picking_player !== null){
                    display_text.text = picking_player.code + ". "+ picking_player.name
                    happy_screen.visible = true
                    happy_screen_animation.restart()
                    lastPrizeItemModel.addPrize(picking_player)
                    btn_pick.checked = false
                    btn_pick.enabled = true

                }
            } else {
                scrollTumblerint(0, interval)
                repeat_count++
            }
        }
    }

    Timer{
        id: timer_stop_all
        interval: 3000
        running: false
        repeat: false

        onTriggered: {
            if(picking_player !== null){
                lastPrizeItemModel.addPrize(picking_player)
                btn_pick.enabled = true
            }
        }
    }

    Button {
        id: btn_ignore
        text: "Ignore this turn"
        anchors.right: parent.right
        anchors.bottom: btn_next.top
        anchors.rightMargin: 20
        anchors.bottomMargin: 10
        background: Rectangle {
            color: btn_ignore.down ? "#FF5E5E" : "#FFB7B7"
            radius: 4
            opacity: 0.5
        }
        font.pixelSize: textSingleton.font.pixelSize * 1.5
        onClicked: {
            lastPrizeItemModel.removeLastPrize()
        }
    }
    Button {
        id: btn_next
        text: "Next round"
        width: btn_ignore.width
        anchors.right: parent.right
        anchors.bottom: parent.bottom
        anchors.rightMargin: 20
        anchors.bottomMargin: 20
        background: Rectangle {
            color: btn_next.down ? "#FF5E5E" : "#FFB7B7"
            radius: 4
            opacity: 0.5
        }
        font.pixelSize: textSingleton.font.pixelSize * 1.5
        onClicked: {
            lastPrizeItemModel.resetPrize()
        }
    }
    Rectangle {
        id: happy_screen
        anchors.fill: parent
        color: "black"
        visible: false
        Item {
            id: container
            x: screen.width / 2; y: screen.height / 2

            Text {
                id: display_text
                anchors.centerIn: parent
                color: "white"
                text: "display_text"
                font.pixelSize: 64

                SequentialAnimation on font.letterSpacing {
                    id: happy_screen_animation
                    loops: 1;
                    NumberAnimation { from: 0; to: 50; easing.type: Easing.InQuad; duration: 4000 }
                    ScriptAction {
                        script: {
                            container.y = happy_screen.height / 2
                            container.x = happy_screen.width / 2
                        }
                    }
                    onFinished: {
                        happy_screen.visible = false
                    }

                }

            }
        }
    }
}
