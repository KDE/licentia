// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "license.h"
#include <qjsonarray.h>

License::License(QString key, QString name, QString spdx, QString description, QString implementation, QJsonArray permissions, QJsonArray conditions, QJsonArray limitations, QString body)
{
    m_key = key;
    m_name = name;
    m_spdx = spdx;
    m_description = description;
    m_implementation = implementation;
    m_permissions = permissions;
    m_conditions = conditions;
    m_limitations = limitations;
    m_body = body;
}

QString License::key()
{
    return m_key;
}

QString License::name()
{
    return m_name;
}

QString License::spdx()
{
    return m_spdx;
}

QString License::description()
{
    return m_description;
}

QString License::implementation()
{
    return m_implementation;
}

QJsonArray License::permissions()
{
    return m_permissions;
}

QJsonArray License::conditions()
{
    return m_conditions;
}

QJsonArray License::limitations()
{
    return m_limitations;
}

QString License::body()
{
    return m_body;
}

License License::fromJson(const QJsonObject &obj)
{
    License l(
        obj.value(QStringLiteral("key")).toString(),
        obj.value(QStringLiteral("name")).toString(),
        obj.value(QStringLiteral("spdx_id")).toString(),
        obj.value(QStringLiteral("description")).toString(),
        obj.value(QStringLiteral("implementation")).toString(),
        obj.value(QStringLiteral("permissions")).toArray(),
        obj.value(QStringLiteral("conditions")).toArray(),
        obj.value(QStringLiteral("limitations")).toArray(),
        obj.value(QStringLiteral("body")).toString()
    );

    return l;
}
