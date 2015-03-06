#ifndef KEYBORDLAYOUTSMODEL_H
#define KEYBORDLAYOUTSMODEL_H

#include <QtCore/QAbstractListModel>

class KeybordLayoutsModel : public QAbstractListModel
{
public:
    KeybordLayoutsModel();
    ~KeybordLayoutsModel();

private:
    void loadData();
};

#endif // KEYBORDLAYOUTSMODEL_H
