cmake_minimum_required(VERSION 3.1)

set(SHINE_EDITOR_EXT_DIR "" CACHE PATH "Extension directory")
set(SHSDK_EDITOR_LIBRARIES "" CACHE PATH "ShSDK (editor) path") # FIXME

# main file
if (WIN32)
	set(SOURCES_main dllmain.cpp)
	source_group("" FILES ${SOURCES_main})
else(WIN32)
	set(SOURCES_main )
endif (WIN32)

# Plugin files
set(SOURCES_Plugin Plugin.cpp Plugin.h)
source_group("Plugin" FILES ${SOURCES_Plugin})

# Factory files
set(SOURCES_Factory PluginFactory.cpp PluginFactory.h)
source_group("Factory" FILES ${SOURCES_Factory})

# Put everything together before adding platform-specific files
set(SOURCES ${SOURCES_Plugin} ${SOURCES_Factory})

# Compile to use it on Runtime
add_library(Plugin STATIC ${SOURCES})
set_property(TARGET Plugin PROPERTY FOLDER "Runtime")
set_property(TARGET Plugin APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS} -fno-exceptions -fno-rtti")
set_property(TARGET Plugin APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")

target_link_libraries(Plugin INTERFACE ${SHSDK_LIBRARIES})
target_include_directories(Plugin PUBLIC "${SHSDK_INCLUDE_DIR}")

# Compile to use it in the Shine Editor
add_library(Plugin_Editor SHARED ${SOURCES_main} ${SOURCES})
set_property(TARGET Plugin_Editor PROPERTY FOLDER "Editor")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS} -fPIC")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1" "_INTERNAL_DLL") # FIXME
set_property(TARGET Plugin_Editor APPEND PROPERTY POSITION_INDEPENDENT_CODE True)

target_link_libraries(Plugin_Editor PRIVATE ${SHSDK_EDITOR_LIBRARIES})
target_include_directories(Plugin_Editor PUBLIC "${SHSDK_INCLUDE_DIR}")
