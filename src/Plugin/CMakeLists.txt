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

# AnimatedSpriteManager files
set(SOURCES_AnimatedSpriteManager Animation/AnimatedSpriteManager.cpp Animation/AnimatedSpriteManager.h)
source_group("Animation" FILES ${SOURCES_AnimatedSpriteManager})

# SoundManager files
set(SOURCES_SoundManager Sound/SoundManager.cpp Sound/SoundManager.h)
source_group("Sound\\SoundManager" FILES ${SOURCES_SoundManager})

# World files
set(SOURCES_World World/World.cpp World/World.h)
source_group("World" FILES ${SOURCES_World})

# MiniMap files
set(SOURCES_MiniMap World/MiniMap/MiniMap.cpp World/MiniMap/MiniMap.h)
source_group("World\\MiniMap" FILES ${SOURCES_MiniMap}) 

# Inputs files
set(SOURCES_Inputs World/Inputs/InputManager.cpp World/Inputs/InputManager.h)
source_group("World\\Inputs" FILES ${SOURCES_Inputs}) 

# GameObject files
set(SOURCES_GameObject World/GameObjects/GameObject.cpp World/GameObjects/GameObject.h)
source_group("World\\GameObject" FILES ${SOURCES_GameObject})

# Planet files
set(SOURCES_Planet World/GameObjects/Planet/Planet.cpp World/GameObjects/Planet/Planet.h)
source_group("World\\GameObject\\Planet" FILES ${SOURCES_Planet})

# Explosion files
set(SOURCES_Explosion World/GameObjects/Explosion/Explosion.cpp World/GameObjects/Explosion/Explosion.h)
source_group("World\\GameObject\\Explosion" FILES ${SOURCES_Explosion})

# ExplosionManager files
set(SOURCES_ExplosionManager World/GameObjects/Explosion/ExplosionManager.cpp World/GameObjects/Explosion/ExplosionManager.h)
source_group("World\\GameObject\\Explosion\\Manager" FILES ${SOURCES_ExplosionManager})

# Projectile files
set(SOURCES_Projectile World/GameObjects/Projectile/Projectile.cpp World/GameObjects/Projectile/Projectile.h)
source_group("World\\GameObject\\Projectile" FILES ${SOURCES_Projectile})

# ProjectileManager files
set(SOURCES_ProjectileManager World/GameObjects/Projectile/ProjectileManager.cpp World/GameObjects/Projectile/ProjectileManager.h)
source_group("World\\GameObject\\Projectile\\Manager" FILES ${SOURCES_ProjectileManager})

# Bullet files
set(SOURCES_Bullet World/GameObjects/Projectile/Bullet/Bullet.cpp World/GameObjects/Projectile/Bullet/Bullet.h)
source_group("World\\GameObject\\Projectile\\Bullet" FILES ${SOURCES_Bullet})

# Ship files
set(SOURCES_Ship World/GameObjects/Ship/Ship.cpp World/GameObjects/Ship/Ship.h)
source_group("World\\GameObject\\Ship" FILES ${SOURCES_Ship})

# Transmitter files
set(SOURCES_Transmitter World/GameObjects/Transmitter/Transmitter.cpp World/GameObjects/Transmitter/Transmitter.h)
source_group("World\\GameObject\\Transmitter" FILES ${SOURCES_Transmitter})

# Team files
set(SOURCES_Team World/Team/Team.cpp World/Team/Team.h)
source_group("World\\Team" FILES ${SOURCES_Team})

# Put everything together before adding platform-specific files
set(SOURCES 
${SOURCES_Plugin} 
${SOURCES_Factory} 
${SOURCES_AnimatedSpriteManager}
${SOURCES_SoundManager}
${SOURCES_World}
${SOURCES_MiniMap}
${SOURCES_GameObject}
${SOURCES_Planet}
${SOURCES_Explosion}
${SOURCES_ExplosionManager}
${SOURCES_Projectile}
${SOURCES_ProjectileManager}
${SOURCES_Bullet}
${SOURCES_Ship}
${SOURCES_Transmitter}
${SOURCES_Team}
${SOURCES_Inputs}
)

# Compile to use it on Runtime
add_library(Plugin STATIC ${SOURCES})
set_property(TARGET Plugin PROPERTY FOLDER "Runtime")
set_property(TARGET Plugin APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS} -fno-exceptions -fno-rtti")
set_property(TARGET Plugin APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS}")

target_link_libraries(Plugin INTERFACE ${SHSDK_LIBRARIES} Network)
target_include_directories(Plugin PUBLIC "${SHSDK_INCLUDE_DIR}")
target_include_directories(Plugin INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")

# Compile to use it in the Shine Editor
add_library(Plugin_Editor SHARED ${SOURCES_main} ${SOURCES})
set_property(TARGET Plugin_Editor PROPERTY FOLDER "Editor")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_DEFINITIONS "${SHSDK_COMPILE_DEFINITIONS}")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_FLAGS "${SHSDK_COMPILE_FLAGS} -fPIC")
set_property(TARGET Plugin_Editor APPEND PROPERTY COMPILE_DEFINITIONS "SH_EDITOR=1" "_INTERNAL_DLL") # FIXME
set_property(TARGET Plugin_Editor APPEND PROPERTY POSITION_INDEPENDENT_CODE True)

target_link_libraries(Plugin_Editor PRIVATE ${SHSDK_EDITOR_LIBRARIES} Network)
target_include_directories(Plugin_Editor PUBLIC "${SHSDK_INCLUDE_DIR}")
target_include_directories(Plugin_Editor INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}")
