cmake_minimum_required(VERSION 3.10.0)
project(stg_game VERSION 0.1.0 LANGUAGES C CXX)

#设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

#设置编译选项
add_compile_options(-Wall -Wextra -Wpedantic)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)
find_package(SDL2_ttf REQUIRED)

add_executable(stg_game main.cpp game_base.cpp BattleField.cpp self.cpp menu.cpp selectRole.cpp selectLevel.cpp storySelect1.cpp enermy.cpp enemyBehaviour.cpp)

target_link_libraries(stg_game 
    SDL2::SDL2
    SDL2::SDL2main 
    SDL2_image::SDL2_image 
    SDL2_mixer::SDL2_mixer
    SDL2_ttf::SDL2_ttf
    "-framework Cocoa"
    "-framework OpenGL")