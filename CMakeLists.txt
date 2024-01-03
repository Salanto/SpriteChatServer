cmake_minimum_required(VERSION 3.14)

project(HVAC-Server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core WebSockets Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core WebSockets Network)

add_executable(HVAC-Server
  src/main.cpp
  src/hvacserverapplication.h src/hvacserverapplication.cpp
  src/hvacconnectionhandler.h src/hvacconnectionhandler.cpp
  src/options.h src/options.cpp
  src/hvacserverinformation.h
  src/hvacpacketbuilder.h src/hvacpacketbuilder.cpp
  src/hvacclientmanager.h src/hvacclientmanager.cpp
  src/client.h src/client.cpp
  src/packetrelay.h src/packetrelay.cpp
  src/hvaccoordinatorclient.h src/hvaccoordinatorclient.cpp
  src/packet/abstractpacket.h
  src/packet/packetfactory.h src/packet/packetfactory.cpp
  src/areadata.h src/areadata.cpp
  src/areamanager.h src/areamanager.cpp
  src/packet/packet_hello.h
  src/packet/packet_generic.h
)
target_link_libraries(HVAC-Server
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::WebSockets
    Qt${QT_VERSION_MAJOR}::Network
)

include(GNUInstallDirs)
install(TARGETS HVAC-Server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
