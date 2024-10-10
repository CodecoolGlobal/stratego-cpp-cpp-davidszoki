cmake_minimum_required(VERSION 3.28)
project(stratego_cpp_cpp_davidszoki)

set(CMAKE_CXX_STANDARD 17)

# Find SDL2 and SDL2_image
find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_image CONFIG REQUIRED)

add_executable(stratego_cpp_cpp_davidszoki main.cpp
        UI/UI.h
        UI/UI.cpp
        UI/Texture.cpp
        Game/Game.h
        Game/Game.cpp
        Game/Field.h
        Game/Field.cpp
        Game/Units/ArmyUnit.h
        Game/Units/Enum.h
        Game/Units/NonSpecialUnit.h
        Game/Units/SpecialUnit/Bomb.h
        Game/Units/SpecialUnit/Flag.h
        Game/Units/SpecialUnit/Marshal.h
        Game/Units/SpecialUnit/Miner.h
        Game/Units/SpecialUnit/Scout.h
        Game/Units/SpecialUnit/Spy.h
        Game/Units/Obstacle.h)

include_directories(
        Game/
        Game/Units
        Game/Units/SpecialUnit
        UI/
)

# Link SDL2 and SDL2_image libraries
target_link_libraries(stratego_cpp_cpp_davidszoki
        PRIVATE
        SDL2::SDL2main   # SDL2 main function library
        SDL2::SDL2       # SDL2 library
        SDL2_image::SDL2_image  # SDL2_image library for image handling
)