// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#pragma once

#include <QJsonArray>
#include <QJsonObject>
#include <QString>

class License
{
public:
    License(QString key, QString name, QString spdx, QString description, QString implementation, QJsonArray permissions, QJsonArray conditions, QJsonArray limitations, QString body);

    QString key();
    QString name();
    QString spdx();
    QString description();
    QString implementation();
    QJsonArray permissions();
    QJsonArray conditions();
    QJsonArray limitations();
    QString body();

    static License fromJson(const QJsonObject &obj);

private:
    QString m_key;
    QString m_name;
    QString m_spdx;
    QString m_description;
    QString m_implementation;
    QJsonArray m_permissions;
    QJsonArray m_conditions;
    QJsonArray m_limitations;
    QString m_body;
};
