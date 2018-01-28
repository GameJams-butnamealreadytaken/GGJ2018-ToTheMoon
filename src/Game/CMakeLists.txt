cmake_minimum_required(VERSION 3.1)

# main files
set(SOURCES_main main.cpp)
source_group("" FILES ${SOURCES_main})

# Inputs files
set(SOURCES_Inputs inputs.cpp inputs.h)
source_group("" FILES ${SOURCES_Inputs})

# Application files
set(SOURCES_Application application.cpp application.h)
source_group("" FILES ${SOURCES_Application})

# Game files
set(SOURCES_Game Game.cpp Game.h Game.inl)
source_group("Game" FILES ${SOURCES_Game})

# InputManager files
set(SOURCES_InputManager InputManager.cpp InputManager.h)
source_group("Game" FILES ${SOURCES_InputManager})

# Persistent Data
set(SOURCES_PersistentData PersistentData.cpp PersistentData.h)
source_group("Game" FILES ${SOURCES_PersistentData})

# State files
set(SOURCES_GameState GameStates/GameState.cpp GameStates/GameState.h)
source_group("State" FILES ${SOURCES_GameState})

# Main menu
set(SOURCES_GameStateMainMenu GameStates/GameStateMainMenu.cpp GameStates/GameStateMainMenu.h)
source_group("State\\MainMenu" FILES ${SOURCES_GameStateMainMenu})

# Ship selectino
set(SOURCES_GameStateShipSelection GameStates/GameStateShipSelection.cpp GameStates/GameStateShipSelection.h)
source_group("State\\ShipSelection" FILES ${SOURCES_GameStateShipSelection})

# Game
set(SOURCES_GameStateGame GameStates/GameStateGame.cpp GameStates/GameStateGame.h)
source_group("State\\Game" FILES ${SOURCES_GameStateGame})

# Put everything together before adding platform-specific files
set(SOURCES ${SOURCES_main} 
			${SOURCES_Game} 
			${SOURCES_Inputs} 
			${SOURCES_Application} 
			${SOURCES_InputManager} 
			${SOURCES_PersistentData} 
			${SOURCES_GameState} 
			${SOURCES_GameStateMainMenu} 
			${SOURCES_GameStateShipSelection} 
			${SOURCES_GameStateGame}
			)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
	add_executable(Game WIN32 ${SOURCES})
ELSE()
	add_executable(Game ${SOURCES})
ENDIF()

if (MSVC)
	SET(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /FORCE:MULTIPLE")
endif (MSVC)

set_property(TARGET Game PROPERTY FOLDER "Runtime")

set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")
set_property(TARGET Game APPEND PROPERTY COMPILE_DEFINITIONS "SH_$<UPPER_CASE:$<CONFIG>>=1")

target_link_libraries(Game PRIVATE ${SHSDK_LIBRARIES})
target_link_libraries(Game PRIVATE Plugin)
target_include_directories(Game PRIVATE "${SHSDK_INCLUDE_DIR}" "$<TARGET_PROPERTY:Plugin,INCLUDE_DIRECTORIES>")
