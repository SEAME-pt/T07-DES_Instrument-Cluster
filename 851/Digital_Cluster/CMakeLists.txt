cmake_minimum_required(VERSION 3.16)

project(Digital_Cluster VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Quick)

qt_standard_project_setup(REQUIRES 6.5)

qt_add_executable(appDigital_Cluster
    main.cpp
)

qt_add_qml_module(appDigital_Cluster
    URI Digital_Cluster
    VERSION 1.0
    QML_FILES
        Main.qml
        ui/LeftPanel/LeftPanel.qml
        ui/CenterPanel/CenterPanel.qml
        ui/LeftPanel/Leftcolumn/Gear.qml
        ui/CenterPanel/Menu.qml
        ui/CenterPanel/Navigation.qml
        ui/LeftPanel/Leftcolumn/LeftColumn.qml
        ui/LeftPanel/Centercolumn/CenterColumn.qml
        ui/LeftPanel/Rightcolumn/RightColumn.qml
        ui/LeftPanel/Leftcolumn/Info.qml
        ui/LeftPanel/Leftcolumn/Service.qml
        ui/LeftPanel/Rightcolumn/Media.qml
        ui/LeftPanel/Rightcolumn/List.qml
        ui/LeftPanel/Centercolumn/Signs.qml
        ui/LeftPanel/Rightcolumn/Navigation_right.qml
        ui/LeftPanel/Rightcolumn/Navigation_right_Mapview.qml
        ui/CenterPanel/Bottombar.qml
        ui/LeftPanel/Centercolumn/Left.qml
        ui/LeftPanel/Centercolumn/Route.qml
        ui/LeftPanel/Centercolumn/Right.qml
        ui/LeftPanel/Centercolumn/Signsright.qml
    RESOURCES
        ui/assets/carRender.jpg
        ui/assets/modes.svg
        ui/assets/navigation.svg
        ui/assets/settings.svg
        ui/assets/nirvana.jpg
        ui/assets/icon00.png
        ui/assets/icon03.png
        ui/assets/icon13.png
        ui/assets/icon16.png
        ui/assets/red_marker.png
        ui/assets/battery.png
        ui/assets/odometer.png
        ui/assets/trip.png
        ui/assets/brake.png
        ui/assets/hold.png
        ui/assets/light.png
        ui/assets/lightauto.png
        ui/assets/minlight.png
        ui/assets/car.png
        ui/assets/HeadLights.png
        ui/assets/Tirepressure.png
        ui/assets/Tractioncontrol.png
        ui/assets/Turnsignal.png
        ui/assets/turn_light_01.png
        ui/assets/turn_light_02.png
    SOURCES
        System.h
        System.cpp
        zmqreader.h
        zmqreader.cpp
)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
set_target_properties(appDigital_Cluster PROPERTIES
#    MACOSX_BUNDLE_GUI_IDENTIFIER com.example.appDigital_Cluster
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

target_link_libraries(appDigital_Cluster
    PRIVATE Qt6::Quick
)

target_link_libraries(appDigital_Cluster PRIVATE zmq)


include(GNUInstallDirs)
install(TARGETS appDigital_Cluster
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
