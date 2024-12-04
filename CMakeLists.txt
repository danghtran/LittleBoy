cmake_minimum_required(VERSION 3.10)
project(LittleBoy)

set(SOURCES 
    ${CMAKE_SOURCE_DIR}/src/LittleBoyGame.cpp
    ${CMAKE_SOURCE_DIR}/src/ViewRenderer.cpp
    ${CMAKE_SOURCE_DIR}/src/TileFactory.cpp
    ${CMAKE_SOURCE_DIR}/src/GameMap.cpp
    ${CMAKE_SOURCE_DIR}/src/handler/EventHandler.cpp
    ${CMAKE_SOURCE_DIR}/src/handler/InputEventHandler.cpp

)

add_executable(LittleBoyGame ${SOURCES})

target_include_directories(LittleBoyGame PRIVATE 
    src 
    include
)

# Add SDL2 dependency
set(SDL2_FOLDER ${CMAKE_SOURCE_DIR}/libs/sdl2)
set(SDL2_DIR ${SDL2_FOLDER}/SDL2-devel-2.30.2-VC/SDL2-2.30.2/cmake)

find_package(SDL2 REQUIRED CONFIG REQUIRED COMPONENTS SDL2)
find_package(SDL2 REQUIRED CONFIG COMPONENTS SDL2main)

if(TARGET SDL2::SDL2main)
    target_link_libraries(LittleBoyGame PRIVATE SDL2::SDL2main)
endif()
target_link_libraries(LittleBoyGame PRIVATE SDL2::SDL2)

# Add SDL2_image dependency
set(SDL2_image_DIR ${SDL2_FOLDER}/SDL2_image-devel-2.8.2-VC/SDL2_image-2.8.2/cmake)

find_package(SDL2_image REQUIRED CONFIG REQUIRED COMPONENTS SDL2_image)
target_link_libraries(LittleBoyGame PRIVATE SDL2_image::SDL2_image)

# Copy DLL and resource files
add_custom_command(TARGET LittleBoyGame POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:LittleBoyGame> $<TARGET_FILE_DIR:LittleBoyGame>
  COMMAND_EXPAND_LISTS
  )

add_custom_command(TARGET LittleBoyGame POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory 
    ${CMAKE_SOURCE_DIR}/res/ $<TARGET_FILE_DIR:LittleBoyGame>/res)