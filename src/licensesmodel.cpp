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
        {Roles::ImplemenationRole, QByteArrayLiteral("implementation")},
        {Roles::PermissionsRole, QByteArrayLiteral("permissions")},
        {Roles::ConditionsRole, QByteArrayLiteral("conditions")},
        {Roles::LimitationsRole, QByteArrayLiteral("limitations")},
        {Roles::UsingRole, QByteArrayLiteral("using")},
        {Roles::BodyRole, QByteArrayLiteral("body")}
    };
}

QVariant LicensesModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() < 0 || index.row() >= m_licenses.count()) {
        return {};
    }

    auto license = m_licenses.at(index.row());

    switch (role) {
    case Roles::KeyRole:
        return license.key();
    case Roles::NameRole:
        return license.name();
    case Roles::SpdxRole:
        return license.spdx();
    case Roles::DescriptionRole:
        return license.description();
    case Roles::ImplemenationRole:
        return license.implementation();
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
    Q_UNUSED(parent)
    return m_licenses.size();
}

bool LicensesModel::loadLicenses()
{
    beginResetModel();

    QFile inputFile(":/licenses.json");
    if (!inputFile.exists()) {
        return false;
    }

    if (!inputFile.open(QIODevice::ReadOnly)) {
        qDebug() << "Failed to load licenses from disk";
    }

    const auto licensesStorage = QJsonDocument::fromJson(inputFile.readAll()).object();
    m_licenses.clear();

    const auto licenses = licensesStorage.value("licenses").toArray();

    std::transform(licenses.cbegin(), licenses.cend(), std::back_inserter(m_licenses), [](const QJsonValue &license) {
        return License::fromJson(license.toObject());
    });

    endResetModel();

    return true;
}
