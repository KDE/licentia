// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QAbstractListModel>
#include <QJsonObject>
#include <QQmlEngine>

#include "license.h"

class LicensesModel : public QAbstractListModel
{
    Q_OBJECT
    QML_ELEMENT

public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        NameRole,
        SpdxRole,
        DescriptionRole,
        FileImplemenationRole,
        SpdxImplemenationRole,
        PermissionsRole,
        ConditionsRole,
        LimitationsRole,
        UsingRole,
        BodyRole
    };

    explicit LicensesModel(QObject *parent = nullptr);

    QHash<int, QByteArray> roleNames() const override;
    QVariant data(const QModelIndex &index, int role) const override;
    int rowCount(const QModelIndex &parent) const final;

protected:
    bool loadLicenses();

private:
    QList<License> m_licenses;
};
