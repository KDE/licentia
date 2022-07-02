// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QAbstractListModel>
#include <QJsonObject>

#include "license.h"

class LicensesModel : public QAbstractListModel
{
    Q_OBJECT

public:
    enum Roles {
        KeyRole = Qt::UserRole + 1,
        NameRole,
        SpdxRole,
        DescriptionRole,
        ImplemenationRole,
        PermissionsRole,
        ConditionsRole,
        LimitationsRole,
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
