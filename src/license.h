// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QString>

class License
{
public:
    License(const QString &key, const QString &name, const QString &spdx, const QString &description, const QString &fileImplementation, const QString &spdxImplementation, const QJsonArray &permissions, const QJsonArray &conditions, const QJsonArray &limitations, const QJsonArray &projectsUsing, const QString &body);

    QString key() const;
    QString name() const;
    QString spdx() const;
    QString description() const;
    QString fileImplementation() const;
    QString spdxImplementation() const;
    QJsonArray permissions() const;
    QJsonArray conditions() const;
    QJsonArray limitations() const;
    QJsonArray projectsUsing() const;
    QString body() const;

    static License fromJson(const QJsonObject &obj);

private:
    QString m_key;
    QString m_name;
    QString m_spdx;
    QString m_description;
    QString m_fileImplementation;
    QString m_spdxImplementation;
    QJsonArray m_permissions;
    QJsonArray m_conditions;
    QJsonArray m_limitations;
    QJsonArray m_projectsUsing;
    QString m_body;
};
