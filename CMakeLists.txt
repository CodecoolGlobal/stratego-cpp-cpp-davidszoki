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
        GameLogic/GameLogic.h
        GameLogic/GameLogic.cpp
        GameLogic/Field.h
        GameLogic/Field.cpp
        GameLogic/Units/ArmyUnit.h
        GameLogic/Units/Enum.h
        GameLogic/Units/ArmyUnit.cpp
        GameLogic/Units/NonSpecialUnit.h
        GameLogic/Units/SpecialUnit/Bomb.h
        GameLogic/Units/SpecialUnit/Flag.h
        GameLogic/Units/SpecialUnit/Marshal.h
        GameLogic/Units/SpecialUnit/Miner.h
        GameLogic/Units/SpecialUnit/Scout.h
        GameLogic/Units/SpecialUnit/Spy.h)

# Link SDL2 and SDL2_image libraries
target_link_libraries(stratego_cpp_cpp_davidszoki
        PRIVATE
        SDL2::SDL2main   # SDL2 main function library
        SDL2::SDL2       # SDL2 library
        SDL2_image::SDL2_image  # SDL2_image library for image handling
)