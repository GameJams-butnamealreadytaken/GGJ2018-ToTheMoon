cmake_minimum_required(VERSION 3.1)

# Network files
set(SOURCES_Network )
source_group("Network" FILES ${SOURCES_Network})

# World files
set(SOURCES_World World.cpp World.h WorldListener.h)
source_group("World" FILES ${SOURCES_World})

# Ship files
set(SOURCES_Ship Ship.cpp Ship.h)
source_group("Ship" FILES ${SOURCES_Ship})

# NetworkHelper files
set(SOURCES_NetworkHelper NetworkHelper.h NetworkHelper.cpp)
source_group("Helpers" FILES ${SOURCES_NetworkHelper})

# Transmitter files
set(SOURCES_Transmitter Transmitter.cpp Transmitter.h)
source_group("Transmitter" FILES ${SOURCES_Transmitter})

# Put everything together before adding platform-specific files
set(SOURCES 
			${SOURCES_Network} 
			${SOURCES_World} 
			${SOURCES_Ship}
			${SOURCES_Transmitter}
			${SOURCES_NetworkHelper} 
			)

add_library(Network STATIC ${SOURCES} utils.h)

if(CMAKE_SYSTEM_NAME MATCHES "Windows")
	target_link_libraries(Network INTERFACE ws2_32.lib) # Sockets
	target_link_libraries(Network INTERFACE Iphlpapi.lib) # ip retrieval
endif(CMAKE_SYSTEM_NAME MATCHES "Windows")

set_property(TARGET Network APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS} -fno-exceptions -fno-rtti")
set_property(TARGET Network APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS} -fPIC")

add_executable(NetworkTest test.cpp)
target_link_libraries(NetworkTest PRIVATE Network)
