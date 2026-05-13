cmake_minimum_required(VERSION 4.2.2)
project(hi)

set(CMAKE_CXX_STANDARD 23)

set(SDL2_PATH "C:/Users/brand/Documents/SDL2-2.32.10/x86_64-w64-mingw32")

set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")
set(SDL2_LIBRARY "${SDL2_PATH}/lib/libSDL2.dll.a")
set(SDL2_MAIN_LIBRARY "${SDL2_PATH}/lib/libSDL2main.a")

add_executable(hi hi.cpp
        square.cpp
        square.h)

target_include_directories(hi PRIVATE ${SDL2_INCLUDE_DIR})
target_link_libraries(hi PRIVATE -lmingw32 ${SDL2_MAIN_LIBRARY} ${SDL2_LIBRARY})

add_custom_command(TARGET hi POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${SDL2_PATH}/bin/SDL2.dll"
        $<TARGET_FILE_DIR:hi>)