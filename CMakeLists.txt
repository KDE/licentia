# SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
# SPDX-License-Identifier: BSD-2-Clause

cmake_minimum_required(VERSION 3.16)

project(licentia VERSION 0.1)
string(TOUPPER ${CMAKE_PROJECT_NAME} CMAKE_PROJECT_NAME_UPPERCASE)

include(FeatureSummary)

set(QT_MIN_VERSION 5.15)
set(KF_MIN_VERSION 5.100)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(ECM ${KF_MIN_VERSION} REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})
set(KDE_COMPILERSETTINGS_LEVEL 5.100)

include(KDEInstallDirs)
include(KDECMakeSettings)
include(KDECompilerSettings NO_POLICY_SCOPE)
include(ECMSetupVersion)
include(ECMGenerateHeaders)
include(ECMPoQmTools)

ecm_setup_version(${PROJECT_VERSION}
    VARIABLE_PREFIX ${CMAKE_PROJECT_NAME_UPPERCASE}
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/src/version-${CMAKE_PROJECT_NAME}.h"
)

find_package(Qt${QT_MAJOR_VERSION} ${QT_MIN_VERSION} REQUIRED COMPONENTS Core Gui Qml QuickControls2 Svg)

if (NOT ANDROID AND NOT WIN32 AND NOT APPLE)
    find_package(KF${QT_MAJOR_VERSION}DBusAddons ${KF_MIN_VERSION} REQUIRED)
endif()

if (NOT ANDROID)
    find_package(Qt${QT_MAJOR_VERSION}Widgets ${QT_MIN_VERSION} REQUIRED)
endif()

find_package(KF5 ${KF5_MIN_VERSION} REQUIRED COMPONENTS Kirigami2 CoreAddons Config I18n DBusAddons ItemModels)

add_subdirectory(src)

install(PROGRAMS org.kde.${CMAKE_PROJECT_NAME}.desktop DESTINATION ${KDE_INSTALL_APPDIR})
install(FILES org.kde.${CMAKE_PROJECT_NAME}.metainfo.xml DESTINATION ${KDE_INSTALL_METAINFODIR})
install(FILES org.kde.${CMAKE_PROJECT_NAME}.svg DESTINATION ${KDE_INSTALL_FULL_ICONDIR}/hicolor/scalable/apps)

ki18n_install(po)

feature_summary(WHAT ALL INCLUDE_QUIET_PACKAGES FATAL_ON_MISSING_REQUIRED_PACKAGES)
