cmake_minimum_required(VERSION 3.16)
project(TaskManagerAI VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Sql)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(TaskManagerAI WIN32 MACOSX_BUNDLE
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    task.h
    taskdb.cpp taskdb.h
    taskdialog.cpp taskdialog.h taskdialog.ui
    taskwidgetitem.cpp taskwidgetitem.h
)
target_link_libraries(TaskManagerAI PRIVATE
    Qt::Core
    Qt::Sql
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(TaskManagerAI PRIVATE
        Qt::Widgets
    )
endif()

install(TARGETS TaskManagerAI
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET TaskManagerAI
    OUTPUT_SCRIPT deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
