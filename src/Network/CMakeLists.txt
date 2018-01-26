cmake_minimum_required(VERSION 3.1)

# World files
set(SOURCES_World World.cpp World.h)
source_group("World" FILES ${SOURCES_World})

# Ship files
set(SOURCES_Ship Ship.cpp Ship.h)
source_group("Ship" FILES ${SOURCES_Ship})

# Put everything together before adding platform-specific files
set(SOURCES ${SOURCES_Plugin} ${SOURCES_World} ${SOURCES_Ship})

add_library(Network STATIC ${SOURCES})

