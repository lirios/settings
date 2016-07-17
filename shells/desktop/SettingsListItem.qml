import QtQuick 2.2
import Fluid.Controls 1.0

ListItem {
    text: title
    iconName: model.iconName

    highlighted: selectedModule ? model.mainScriptUrl == selectedModule.mainScriptUrl : false

    onClicked: {
        if (!model.mainScriptUrl)
            return;

        moduleLoader.sourceComponent = Qt.createComponent(model.mainScriptUrl);
    }
}
