cmake_minimum_required(VERSION 3.1)

# Network files
set(SOURCES_Network Network.h)
source_group("Network" FILES ${SOURCES_Network})

# World files
set(SOURCES_World World.cpp World.h)
source_group("World" FILES ${SOURCES_World})

# Ship files
set(SOURCES_Ship Ship.cpp Ship.h)
source_group("Ship" FILES ${SOURCES_Ship})

# Put everything together before adding platform-specific files
set(SOURCES ${SOURCES_Network} ${SOURCES_World} ${SOURCES_Ship})

add_library(Network STATIC ${SOURCES})

set_property(TARGET Network APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS} -fno-exceptions -fno-rtti")
set_property(TARGET Network APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS} -fPIC")
