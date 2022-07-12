// SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
// SPDX-License-Identifier: LGPL-2.1-or-later

#include <QJsonArray>

#include <KLocalizedString>

#include "license.h"

License::License(QString key, QString name, QString spdx, QString description, QString fileImplementation, QString spdxImplementation, QJsonArray permissions, QJsonArray conditions, QJsonArray limitations, QJsonArray projectsUsing, QString body)
{
    m_key = key;
    m_name = name;
    m_spdx = spdx;
    m_description = description;
    m_fileImplementation = fileImplementation;
    m_spdxImplementation = spdxImplementation;
    m_permissions = permissions;
    m_conditions = conditions;
    m_limitations = limitations;
    m_projectsUsing = projectsUsing;
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

QString License::fileImplementation()
{
    return m_fileImplementation;
}

QString License::spdxImplementation()
{
    return m_spdxImplementation;
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

QJsonArray License::projectsUsing()
{
    return m_projectsUsing;
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
        } else if (i == "none") {
            limitation = {
                {QStringLiteral("name"), i18n("None")},
                {QStringLiteral("description"), i18n("There's no limitations.")}
            };
        }
        limitations.push_back(limitation);
    }

    QString key = obj.value(QStringLiteral("key")).toString();
    QString spdx = obj.value(QStringLiteral("spdx_id")).toString();
    QString description;
    QString fileImplementation;
    QString spdxImplementation = i18n("For REUSE compliance, copy the text of the license into a file named %1.txt, it must be placed in the LICENSES/ directory in the root of your source code.", spdx);

    if (key == "afl-3.0") {
        description = i18n("The Academic Free License is a variant of the Open Software License that does not require that the source code of derivative works be disclosed. It contains explicit copyright and patent grants and reserves trademark rights in the author.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file. Files licensed under AFL 3.0 must also include the notice \"Licensed under the Academic Free License version 3.0\" adjacent to the copyright notice.");
    } else if (key == "apache-2.0") {
        description = i18n("A permissive license whose main conditions require preservation of copyright and license notices. Contributors provide an express grant of patent rights. Licensed works, modifications, and larger works may be distributed under different terms and without source code.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file.");
    } else if (key == "0bsd") {
        description = i18n("The BSD Zero Clause license goes further than the BSD 2-Clause license to allow you unlimited freedom with the software without requirements to include the copyright notice, license text, or disclaimer in either source or binary forms.");
        fileImplementation = i18nc("do not translate the placeholders e.g [year], [fullname] as they refer to the untranslated original license", "Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file.  Replace [year] with the current year and [fullname] with the name (or names) of the copyright holders. You may take the additional step of removing the copyright notice.");
    } else if (key == "bsd-2-clause") {
        description = i18n("A permissive license that comes in two variants, the BSD 2-Clause and BSD 3-Clause. Both have very minute differences to the MIT license.");
        fileImplementation = i18nc("do not translate the placeholders e.g [year], [fullname] as they refer to the untranslated original license", "Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file. Replace [year] with the current year and [fullname] with the name (or names) of the copyright holders.");
    } else if (key == "bsd-3-clause") {
        description = i18n("A permissive license similar to the BSD 2-Clause License, but with a 3rd clause that prohibits others from using the name of the project or its contributors to promote derived products without written consent.");
        fileImplementation = i18nc("do not translate the placeholders e.g [year], [fullname] as they refer to the untranslated original license", "Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file. Replace [year] with the current year and [fullname] with the name (or names) of the copyright holders.");
    } else if (key == "bsd-3-clause-clear") {
        description = i18n("A variant of the BSD 3-Clause License that explicitly does not grant any patent rights.");
        fileImplementation = i18nc("do not translate the placeholders e.g [year], [fullname] as they refer to the untranslated original license", "Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file. Replace [year] with the current year and [fullname] with the name (or names) of the copyright holders.");
    } else if (key == "bsd-4-clause") {
        description = i18n("A permissive license similar to the BSD 3-Clause License, but with an \"advertising clause\" that requires an acknowledgment of the original source in all advertising material.");
        fileImplementation = i18nc("do not translate the placeholders e.g [year], [fullname] as they refer to the untranslated original license", "Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file. Replace [year] with the current year and [fullname] with the name (or names) of the copyright holders. Replace [project] with the project organization, if any, that sponsors this work.");
    } else if (key == "bsl-1.0") {
        description = i18n("A simple permissive license only requiring preservation of copyright and license notices for source (and not binary) distribution. Licensed works, modifications, and larger works may be distributed under different terms and without source code.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file.");
    } else if (key == "cc0-1.0") {
        description = i18n("The Creative Commons CC0 Public Domain Dedication waives copyright interest in a work you've created and dedicates it to the world-wide public domain. Use CC0 to opt out of copyright entirely and ensure your work has the widest reach. As with the Unlicense and typical software licenses, CC0 disclaims warranties. CC0 is very similar to the Unlicense.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file.");
    } else if (key == "cc-by-4.0") {
        description = i18n("Permits almost any use subject to providing credit and license notice. Frequently used for media assets and educational materials. The most common license for Open Access scientific publications. Not recommended for software.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file. It is also acceptable to solely supply a link to a copy of the license, usually to the canonical URL for the license.");
    } else if (key == "cc-by-sa-4.0") {
        description = i18n("Similar to CC-BY-4.0 but requires derivatives be distributed under the same or a similar, compatible license. Frequently used for media assets and educational materials. A previous version is the default license for Wikipedia and other Wikimedia projects. Not recommended for software.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file. It is also acceptable to solely supply a link to a copy of the license, usually to the canonical URL for the license.");
    } else if (key == "epl-2.0") {
        description = i18n("This commercially-friendly copyleft license provides the ability to commercially license binaries; a modern royalty-free patent license grant; and the ability for linked works to use other licenses, including commercial ones.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file.");
    } else if (key == "gpl-2.0") {
        description = i18n("The GNU GPL is the most widely used free software license and has a strong copyleft requirement. When distributing derived works, the source code of the work must be made available under the same license. There are multiple variants of the GNU GPL, each with different requirements.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file.");
    } else if (key == "gpl-3.0") {
        description = i18n("Permissions of this strong copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights.");
        fileImplementation = i18n("Create a text file (typically named COPYING, as per GNU conventions) in the root of your source code and copy the text of the license into the file.");
    } else if (key == "lgpl-2.1") {
        description = i18n("Primarily used for software libraries, the GNU LGPL requires that derived works be licensed under the same license, but works that only link to it do not fall under this restriction. There are two commonly used versions of the GNU LGPL.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file.");
    } else if (key == "lgpl-3.0") {
        description = i18n("Permissions of this copyleft license are conditioned on making available complete source code of licensed works and modifications under the same license or the GNU GPLv3. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights. However, a larger work using the licensed work through interfaces provided by the licensed work may be distributed under different terms and without source code for the larger work.");
        fileImplementation = i18n("This license is an additional set of permissions to the GNU GPLv3 license. Follow the instructions to apply the GNU GPLv3, in the root of your source code. Then add another file named COPYING.LESSER and copy the text.");
    } else if (key == "agpl-3.0") {
        description = i18n("Permissions of this strongest copyleft license are conditioned on making available complete source code of licensed works and modifications, which include larger works using a licensed work, under the same license. Copyright and license notices must be preserved. Contributors provide an express grant of patent rights. When a modified version is used to provide a service over a network, the complete source code of the modified version must be made available.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file.");
    } else if (key == "mit") {
        description = i18n("A short and simple permissive license with conditions only requiring preservation of copyright and license notices. Licensed works, modifications, and larger works may be distributed under different terms and without source code.");
        fileImplementation = i18nc("do not translate the placeholders e.g [year], [fullname] as they refer to the untranslated original license", "Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file. Replace [year] with the current year and [fullname] with the name (or names) of the copyright holders.");
    } else if (key == "mpl-2.0") {
        description = i18n("Permissions of this weak copyleft license are conditioned on making available source code of licensed files and modifications of those files under the same license (or in certain cases, one of the GNU licenses). Copyright and license notices must be preserved. Contributors provide an express grant of patent rights. However, a larger work using the licensed work may be distributed under different terms and without source code for files added in the larger work.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file.");
    } else if (key == "wtfpl") {
        description = i18n("The easiest license out there. It gives the user permissions to do whatever they want with your code.");
        fileImplementation = i18n("Create a text file (typically named LICENSE or LICENSE.txt) in the root of your source code and copy the text of the license into the file.");
    } else if (key == "unlicense") {
        description = i18n("A license with no conditions whatsoever which dedicates works to the public domain. Unlicensed works, modifications, and larger works may be distributed under different terms and without source code.");
        fileImplementation = i18n("Create a text file (typically named UNLICENSE or UNLICENSE.txt) in the root of your source code and copy the text of the license disclaimer into the file.");
    }

    License l(
        key,
        obj.value(QStringLiteral("name")).toString(),
        spdx,
        description,
        fileImplementation,
        spdxImplementation,
        permissions,
        conditions,
        limitations,
        obj.value(QStringLiteral("using")).toArray(),
        obj.value(QStringLiteral("body")).toString()
    );

    return l;
}
