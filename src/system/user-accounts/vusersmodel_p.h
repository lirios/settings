
#ifndef VUSERSMODEL_P_H
#define VUSERSMODEL_P_H

class VUserItem
{
public:
    uid_t uid;
    gid_t gid;
    QString name;
    QString realName;
    QString homeDirectory;
    QString shell;
    QString image;
    bool isLoggedIn;

    QString displayName() const;
};

class VUsersModelPrivate
{
    Q_DECLARE_PUBLIC(VUsers)
public:
    VUsersModelPrivate(VUsersModel *parent);
    virtual ~VUsersModelPrivate();

    void populate();

    QList<VUserItem> users;

    VUsersModel *const q_ptr;
};

#endif // VUSERSMODEL_P_H
