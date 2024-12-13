# SPDX-FileCopyrightText: 2022 Felipe Kinoshita <kinofhek@gmail.com>
# SPDX-License-Identifier: BSD-2-Clause

add_executable(${CMAKE_PROJECT_NAME}
    main.cpp
    license.cpp
    licensesmodel.cpp)

ecm_add_qml_module(${CMAKE_PROJECT_NAME} URI org.kde.licentia
    QML_FILES
    ui/GlobalMenu.qml
    ui/LicensePanel.qml
    ui/Main.qml
    ui/PageHeader.qml)

qt_add_resources(${CMAKE_PROJECT_NAME} resources
        PREFIX "/"
        FILES licenses.json)

target_link_libraries(${CMAKE_PROJECT_NAME}
PUBLIC
    Qt::Core
    Qt::Gui
    Qt::Qml
    Qt::Quick
    Qt::QuickControls2
    Qt::Svg
    Qt::Widgets
    KF6::I18n
    KF6::CoreAddons
    KF6::ConfigCore
    KF6::ConfigGui
)

if(TARGET KF6::DBusAddons)
    target_link_libraries(${CMAKE_PROJECT_NAME} PUBLIC KF6::DBusAddons)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC -DHAVE_KDBUSADDONS)
endif()

kconfig_target_kcfg_file(${CMAKE_PROJECT_NAME} FILE config.kcfg CLASS_NAME Config MUTATORS GENERATE_PROPERTIES GENERATE_MOC DEFAULT_VALUE_GETTERS PARENT_IN_CONSTRUCTOR QML_REGISTRATION SINGLETON)
install(TARGETS ${CMAKE_PROJECT_NAME} ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})
