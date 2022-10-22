cmake_minimum_required(VERSION 3.12)

# Set your project name here
set(PROJECT_NAME PiMon)

# Set your project sources here
set(PROJECT_SOURCES
    main.cpp
    engine/Map.cpp
    engine/Player.cpp
    engine/Npc.cpp
    engine/Message.cpp
    engine/Battle.cpp
    engine/TitleScreen.cpp
    engine/Teleporter.cpp
    engine/LoadGame.cpp
    engine/NewGame.cpp
    engine/StarterPicker.cpp
    engine/menu/BaseMenu.cpp
    engine/menu/Menu.cpp
    engine/menu/Dex.cpp
    engine/menu/TownMap.cpp
    engine/menu/Bag.cpp
    engine/menu/Party.cpp
    engine/menu/Settings.cpp
    engine/menu/Stats.cpp
    globals.cpp
)

# --- Here Be Boilerplate ---

if(NOT PICO_SDK_PATH)
    message(WARNING "PICO_SDK_PATH not specified. Forcing fetch from git!")
    set(PICO_SDK_FETCH_FROM_GIT true)
endif()

# Pull in PICO SDK
include(pico_sdk_import.cmake)

# set up proejct
project(${PROJECT_NAME} C CXX ASM)
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Initialize the SDK
pico_sdk_init()

# Find the PicoSystem library
include(picosystem_sdk_import.cmake)

# Create the output target
picosystem_executable(
  ${PROJECT_NAME}
  ${PROJECT_SOURCES}
)

# --- End Of Boilerplate ---
target_include_directories(picosystem INTERFACE ${CMAKE_CURRENT_LIST_DIR})

# Set your build options here
pixel_double(${PROJECT_NAME})          # 120x120 resolution game, pixel-doubled to 240x240
disable_startup_logo(${PROJECT_NAME})  # Skip the PicoSystem splash
#no_font(${PROJECT_NAME})              # Omit the default font
no_spritesheet(${PROJECT_NAME})       # Omit the default spritesheet
#no_overclock(${PROJECT_NAME})         # Don't overclock

target_link_libraries(
    PiMon
    pico_multicore
)