cmake_minimum_required(VERSION 3.5)

project(TeamProject VERSION 0.1 LANGUAGES CXX)

INCLUDE_DIRECTORIES(
    ${PROJECT_SOURCE_DIR}
)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(Qt6 COMPONENTS Sql REQUIRED)
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED Network COMPONENTS Core)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        roundimg.h roundimg.cpp
        res.qrc
        loginwindow.h loginwindow.cpp loginwindow.ui
        signsucess.h signsucess.cpp signsucess.ui
        gamehall.h gamehall.cpp gamehall.ui
        ico.rc
        hallbtn.h hallbtn.cpp
        gif_label.h gif_label.cpp
        ranklbabel.h ranklbabel.cpp
        search_results.h search_results.cpp search_results.ui
        smtp.h smtp.cpp
        download.h download.cpp download.ui
        removey.h removey.cpp removey.ui
        downloadtool.h downloadtool.cpp


)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(TeamProject
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET TeamProject APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(TeamProject SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(TeamProject
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(TeamProject PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(TeamProject PRIVATE Qt6::Sql)
target_link_libraries(TeamProject PRIVATE Qt${QT_VERSION_MAJOR}::Core)
target_link_libraries(TeamProject PRIVATE Qt6::Network)


set_target_properties(TeamProject PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)


install(TARGETS TeamProject
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(TeamProject)
endif()
