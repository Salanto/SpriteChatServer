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
  src/serverapplication.h src/serverapplication.cpp
  src/connectionhandler.h src/connectionhandler.cpp
  src/options.h src/options.cpp
  src/serverinformation.h
  src/packetbuilder.h src/packetbuilder.cpp
  src/clientmanager.h src/clientmanager.cpp
  src/client.h src/client.cpp
  src/packetrelay.h src/packetrelay.cpp
  src/coordinatorclient.h src/coordinatorclient.cpp
  src/packet/packet.h
  src/packet/packetfactory.h src/packet/packetfactory.cpp
  src/areas/areamanager.h src/areas/areamanager.cpp
  src/packet/packet_hello.h src/packet/packet_hello.cpp
  src/packet/packet_generic.h src/packet/packet_generic.cpp
  src/packet/packet_selectcharacter.h src/packet/packet_selectcharacter.cpp
  src/constants.h
  src/datatypes.h
  src/areas/location.h src/areas/location.cpp
  src/areas/area.h src/areas/area.cpp
  src/helper.h
)

target_include_directories(HVAC-Server
   PRIVATE src
   PRIVATE src/packet
   PRIVATE src/areas
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

set_target_properties(HVAC-Server PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_LIST_DIR}/bin>
        RUNTIME_OUTPUT_DIRECTORY $<1:${CMAKE_CURRENT_LIST_DIR}/bin>)
