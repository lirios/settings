import QtQuick 2.2
import Fluid.Controls 1.0

ListItem {
    text: title
    iconName: model.iconName

    onClicked: {
        if (!model.mainScriptUrl)
            return;

        var component = Qt.createComponent(model.mainScriptUrl);
        if (component.status !== Component.Ready) {
            console.error(component.errorString());
            return;
        }

        var item = component.createObject(null);

        if (item.minimumWidth != null)
            window.minimumWidth = item.minimumWidth;
        if (item.minimumHeight != null)
            window.minimumHeight = item.minimumHeight;

        prefletTitle.text = title;
        moduleStack.push(item);
    }
}
