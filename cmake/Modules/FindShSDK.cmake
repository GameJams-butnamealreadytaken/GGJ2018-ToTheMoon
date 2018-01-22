# - Try to find ShSDK
# Once done this will define
#  SHSDK_FOUND - System has ShSDK
#  SHSDK_INCLUDE_DIRS - The ShSDK include directories
#  SHSDK_LIBRARIES - The libraries needed to use ShSDK

set(CMAKE_PREFIX_PATH $ENV{SHINE_BASE_DIR}) # needed for android !!!

find_path(SHSDK_INCLUDE_DIR "ShSDK/ShSDK.h" HINTS ENV SHINE_BASE_DIR PATH_SUFFIXES "include" NO_CMAKE_FIND_ROOT_PATH)

macro(FIND_SHSDK_LIBRARY _var)
	find_library(${_var} NAMES ${ARGN} HINTS ENV SHINE_BASE_DIR PATH_SUFFIXES "lib" NO_CMAKE_FIND_ROOT_PATH)
	mark_as_advanced(${_var})
endmacro()

# ------------------------------------------------------------------------------------------------

if (MSVC)
	set(SHSDK_COMPILE_FLAGS "/EHs-c- /GR-") # disable exceptions / disable RTTI
else (MSVC)
	set(SHSDK_COMPILE_FLAGS "-fno-exceptions -fno-rtti")
endif (MSVC)

set(SHSDK_COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")

if (MSVC)
	list(APPEND SHSDK_COMPILE_DEFINITIONS "_ITERATOR_DEBUG_LEVEL=0")
endif (MSVC)

# ------------------------------------------------------------------------------------------------

set(SHSDK_LIBRARIES )

FIND_SHSDK_LIBRARY(SHCORE_LIBRARY ShCore)

list(FIND ShSDK_FIND_COMPONENTS "ShEntryPoint" ShEntryPoint_INDEX)
if (${ShEntryPoint_INDEX} GREATER -1)
	FIND_SHSDK_LIBRARY(SHENTRYPOINT_LIBRARY ShEntryPoint)
	set(SHSDK_LIBRARIES ${SHSDK_LIBRARIES} "${SHENTRYPOINT_LIBRARY}")
endif()

list(FIND ShSDK_FIND_COMPONENTS "StubUserSystem" ShEntryPoint_INDEX)
if (${ShEntryPoint_INDEX} GREATER -1)
	FIND_SHSDK_LIBRARY(STUBUSERSYSTEM_LIBRARY StubUserSystem)
	set(SHSDK_LIBRARIES ${SHSDK_LIBRARIES} "${STUBUSERSYSTEM_LIBRARY}")
endif()

FIND_SHSDK_LIBRARY(SHSDK_LIBRARY ShSDK)

set(SHSDK_LIBRARIES "${SHSDK_LIBRARY}" "${SHCORE_LIBRARY}")

set(SHSDK_INCLUDE_DIRS "${SHSDK_INCLUDE_DIR}")

if (${CMAKE_SYSTEM_NAME} MATCHES "Android")

	#find_package(Threads) # automatic
	set(LIB_ANDROID android)
	set(LIB_LOG log)
	set(OPENSLES_LIBRARIES OpenSLES)
	set(OPENGLES2_LIBRARIES GLESv2)
	set(EGL_LIBRARIES EGL)
	
	list(APPEND SHSDK_LIBRARIES "${OPENGLES2_LIBRARIES}" "${EGL_LIBRARIES}" "${OPENSLES_LIBRARIES}" "${LIB_ANDROID}" "${LIB_LOG}")

elseif (APPLE)

	# TODO

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Linux") # Not Android and not Apple ... must be Linux or BSD

	find_package(Threads QUIET)
	find_package(OpenGL QUIET)
	find_package(OpenAL QUIET)
	find_package(X11 QUIET)

	list(APPEND SHSDK_LIBRARIES "${OPENGL_LIBRARIES}" "${X11_LIBRARIES}" "${OPENAL_LIBRARY}" "${CMAKE_THREAD_LIBS_INIT}")

elseif (${CMAKE_SYSTEM_NAME} MATCHES "Windows")

	find_package(DirectX9 QUIET)
	find_package(XAudio QUIET)
	find_package(XInput QUIET)

	list(APPEND SHSDK_INCLUDE_DIRS "${DirectX9_INCLUDE_DIR}")
	list(APPEND SHSDK_LIBRARIES "${DirectX9_LIBRARIES}" "${XInput_LIBRARIES}" "${XAudio_LIBRARY}")

else ()

	# TODO

	message("Platform not supported")

endif()

include(FindPackageHandleStandardArgs)

FIND_PACKAGE_HANDLE_STANDARD_ARGS(ShSDK DEFAULT_MSG SHSDK_LIBRARIES SHSDK_INCLUDE_DIRS)
