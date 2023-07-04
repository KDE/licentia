# SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
# SPDX-License-Identifier: BSD-2-Clause

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    about.cpp
    app.cpp
    license.cpp
    licensesmodel.cpp
    resources.qrc)

target_link_libraries(${CMAKE_PROJECT_NAME}
PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::QuickControls2
    Qt::Svg
    Qt::Widgets
    KF${QT_MAJOR_VERSION}::I18n
    KF${QT_MAJOR_VERSION}::CoreAddons
    KF${QT_MAJOR_VERSION}::ConfigCore
    KF${QT_MAJOR_VERSION}::ConfigGui
)

if(TARGET KF${QT_MAJOR_VERSION}::DBusAddons)
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC KF${QT_MAJOR_VERSION}::DBusAddons)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -DHAVE_KDBUSADDONS)
endif()

kconfig_add_kcfg_files(${CMAKE_PROJECT_NAME} GENERATE_MOC config.kcfgc)
install(TARGETS ${CMAKE_PROJECT_NAME} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
