cmake_minimum_required(VERSION 3.1)
project(Game)
set(CMAKE_CXX_STANDARD 17)

include_directories(${PROJECT_SOURCE_DIR}/2.5.1-SFML/include)
link_directories(${PROJECT_SOURCE_DIR}/2.5.1-SFML/lib)

#find_package(SFML 2.5 COMPONENTS graphics audio system window REQUIRED)

add_executable(Game
        source/main.cpp
        source/Game/Game.cpp
        source/Game/Game.hpp
        source/Game/BackgroundBoard/BackgroundBoard.cpp
        source/Game/BackgroundBoard/BackgroundBoard.hpp
        source/Game/Player/Player.cpp
        source/Game/Player/Player.hpp
        source/Game/World/World.cpp
        source/Game/World/World.hpp
        source/Game/World/Fragment/Fragment.cpp
        source/Game/World/Fragment/Fragment.hpp
        source/Game/World/Components/BasicComponent.cpp
        source/Game/World/Components/BasicComponent.hpp
        source/Game/World/Chunk/Chunk.cpp
        source/Game/World/Chunk/Chunk.hpp
        source/Game/World/Components/Component.hpp
        source/Game/World/Components/Inverter/Inverter.cpp
        source/Game/World/Components/Inverter/Inverter.hpp
        source/Game/World/Components/Blotter/Blotter.cpp
        source/Game/World/Components/Blotter/Blotter.hpp
        source/Game/World/Components/Peg/Peg.cpp
        source/Game/World/Components/Peg/Peg.hpp
        source/Game/World/Components/sfLine/sfLine.cpp
        source/Game/World/Components/sfLine/sfLine.hpp
        source/Game/Rotation.hpp
        source/Game/PlayerState.hpp
        source/Game/Collision/Collision.cpp
        source/Game/Collision/Collision.hpp
        source/Game/Interaction/Interaction.cpp
        source/Game/Interaction/Interaction.hpp)

target_link_libraries(Game sfml-graphics sfml-audio sfml-system sfml-window)

#set_target_properties(Game PROPERTIES COMPILE_FLAGS "-m32" LINK_FLAGS "-m32")