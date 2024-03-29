// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStandardPaths>

#include "licensesmodel.h"

LicensesModel::LicensesModel(QObject *parent)
    : QAbstractListModel(parent)
{
    loadLicenses();
}

QHash<int, QByteArray> LicensesModel::roleNames() const
{
    return {
        {Roles::KeyRole, QByteArrayLiteral("key")},
        {Roles::NameRole, QByteArrayLiteral("name")},
        {Roles::SpdxRole, QByteArrayLiteral("spdx")},
        {Roles::DescriptionRole, QByteArrayLiteral("description")},
        {Roles::FileImplemenationRole, QByteArrayLiteral("fileImplementation")},
        {Roles::SpdxImplemenationRole, QByteArrayLiteral("spdxImplementation")},
        {Roles::PermissionsRole, QByteArrayLiteral("permissions")},
        {Roles::ConditionsRole, QByteArrayLiteral("conditions")},
        {Roles::LimitationsRole, QByteArrayLiteral("limitations")},
        {Roles::UsingRole, QByteArrayLiteral("using")},
        {Roles::BodyRole, QByteArrayLiteral("body")}
    };
}

QVariant LicensesModel::data(const QModelIndex &index, int role) const
{
    Q_ASSERT(checkIndex(index, QAbstractItemModel::CheckIndexOption::IndexIsValid));

    const auto &license = m_licenses.at(index.row());

    switch (role) {
    case Roles::KeyRole:
        return license.key();
    case Roles::NameRole:
        return license.name();
    case Roles::SpdxRole:
        return license.spdx();
    case Roles::DescriptionRole:
        return license.description();
    case Roles::FileImplemenationRole:
        return license.fileImplementation();
    case Roles::SpdxImplemenationRole:
        return license.spdxImplementation();
    case Roles::PermissionsRole:
        return license.permissions();
    case Roles::ConditionsRole:
        return license.conditions();
    case Roles::LimitationsRole:
        return license.limitations();
    case Roles::UsingRole:
        return license.projectsUsing();
    case Roles::BodyRole:
        return license.body();
    }

    return {};
}

int LicensesModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : m_licenses.size();
}

bool LicensesModel::loadLicenses()
{
    beginResetModel();

    QFile inputFile(QStringLiteral(":/licenses.json"));
    if (!inputFile.exists()) {
        return false;
    }

    if (!inputFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to load licenses from disk";
    }

    const auto licensesStorage = QJsonDocument::fromJson(inputFile.readAll()).object();
    m_licenses.clear();

    const auto licenses = licensesStorage.value(QStringLiteral("licenses")).toArray();

    std::transform(licenses.cbegin(), licenses.cend(), std::back_inserter(m_licenses), [](const QJsonValue &license) {
        return License::fromJson(license.toObject());
    });

    endResetModel();

    return true;
}
