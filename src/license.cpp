// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include "license.h"
#include <qjsonarray.h>

#include <KLocalizedString>

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
    QJsonArray permissions;
    QJsonObject permission;

    for (auto i : obj.value(QStringLiteral("permissions")).toArray()) {
        if (i == "commercial-use") {
            permission = {
                {QStringLiteral("name"), i18n("Commercial use")},
                {QStringLiteral("description"), i18n("The licensed material and derivatives may be used for commercial purposes.")}
            };
        } else if (i == "modifications") {
            permission = {
                {QStringLiteral("name"), i18n("Modification")},
                {QStringLiteral("description"), i18n("The licensed material may be modified.")}
            };
        } else if (i == "distribution") {
            permission = {
                {QStringLiteral("name"), i18n("Distribution")},
                {QStringLiteral("description"), i18n("The licensed material may be distributed.")}
            };
        } else if (i == "private-use") {
            permission = {
                {QStringLiteral("name"), i18n("Private use")},
                {QStringLiteral("description"), i18n("The licensed material may be used and modified in private.")}
            };
        } else if (i == "patent-use") {
            permission = {
                {QStringLiteral("name"), i18n("Patent use")},
                {QStringLiteral("description"), i18n("The licensed provides and express grant of patent rights from contributors.")}
            };
        }
        permissions.push_back(permission);
    }

    QJsonArray conditions;
    QJsonObject condition;

    for (auto i : obj.value(QStringLiteral("conditions")).toArray()) {
        if (i == "include-copyright") {
            condition = {
                {QStringLiteral("name"), i18n("License and copyright notice")},
                {QStringLiteral("description"), i18n("The licensed material and derivatives may be used for commercial purposes.")}
            };
        } else if (i == "document-changes") {
            condition = {
                {QStringLiteral("name"), i18n("State changes")},
                {QStringLiteral("description"), i18n("Changes made to the licensed material must be documented.")}
            };
        } else if (i == "disclose-source") {
            condition = {
                {QStringLiteral("name"), i18n("Disclose source")},
                {QStringLiteral("description"), i18n("Source code must be made available when the licensed material is distributed.")}
            };
        } else if (i == "network-use-disclose") {
            condition = {
                {QStringLiteral("name"), i18n("Network use is distribution")},
                {QStringLiteral("description"), i18n("Users who interact with the licensed material via network are given the right to receive a copy of the source code.")}
            };
        } else if (i == "same-license") {
            condition = {
                {QStringLiteral("name"), i18n("Same license")},
                {QStringLiteral("description"), i18n("Modifications must be released under the same license when distributing the licensed material. In some cases a similar or related license may be used.")}
            };
        } else if (i == "same-license--library") {
            condition = {
                {QStringLiteral("name"), i18n("Same license (library)")},
                {QStringLiteral("description"), i18n("Modifications must be released under the same license when distributing the licensed material. In some cases a similar or related license may be used, or this condition may not apply to works that use the licensed material as a library.")}
            };
        } else if (i == "same-license--file") {
            condition = {
                {QStringLiteral("name"), i18n("Same license (file)")},
                {QStringLiteral("description"), i18n("Modifications of existing files must be released under the same license when distributing the licensed material. In some cases a similar or related license may be used.")}
            };
        } else if (i == "none") {
            condition = {
                {QStringLiteral("name"), i18n("None")},
                {QStringLiteral("description"), i18n("There's no conditions.")}
            };
        }
        conditions.push_back(condition);
    }

    QJsonArray limitations;
    QJsonObject limitation;

    for (auto i : obj.value(QStringLiteral("limitations")).toArray()) {
        if (i == "liability") {
            limitation = {
                {QStringLiteral("name"), i18n("Liability")},
                {QStringLiteral("description"), i18n("This license includes a limitation of liability.")}
            };
        } else if (i == "warranty") {
            limitation = {
                {QStringLiteral("name"), i18n("Warranty")},
                {QStringLiteral("description"), i18n("This license explicitly states that it does NOT provide any warranty.")}
            };
        } else if (i == "trademark-use") {
            limitation = {
                {QStringLiteral("name"), i18n("Trademark use")},
                {QStringLiteral("description"), i18n("This license explicitly states that it does NOT grant trademark rights, even though licenses without such a statement probably do not grant any implicit trademark rights.")}
            };
        } else if (i == "patent-use") {
            limitation = {
                {QStringLiteral("name"), i18n("Patent use")},
                {QStringLiteral("description"), i18n("This license explicitly states that it does NOT grant any rights in the patents of contributors.")}
            };
        }
        limitations.push_back(limitation);
    }

    License l(
        obj.value(QStringLiteral("key")).toString(),
        obj.value(QStringLiteral("name")).toString(),
        obj.value(QStringLiteral("spdx_id")).toString(),
        obj.value(QStringLiteral("description")).toString(),
        obj.value(QStringLiteral("implementation")).toString(),
        permissions,
        conditions,
        limitations,
        obj.value(QStringLiteral("body")).toString()
    );

    return l;
}
