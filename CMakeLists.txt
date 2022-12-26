cmake_minimum_required(VERSION 3.15)

project(Pong)

find_package(SDL2 CONFIG REQUIRED)
find_package(SDL2_mixer CONFIG REQUIRED)
find_package(SDL2_ttf CONFIG REQUIRED)

file(GLOB file_SRC
      CONFIGURE_DEPENDS
     "include/*.h"
     "src/*.cpp"
)

file(COPY Font Sound DESTINATION .)

add_executable(main ${file_SRC})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET main PROPERTY CXX_STANDARD 17)
endif()

   target_link_libraries(main
        PRIVATE
        $<TARGET_NAME_IF_EXISTS:SDL2::SDL2main>
        $<IF:$<TARGET_EXISTS:SDL2::SDL2>,SDL2::SDL2,SDL2::SDL2-static>)

 target_link_libraries(main 
	PRIVATE 
	$<IF:$<TARGET_EXISTS:SDL2_mixer::SDL2_mixer>,SDL2_mixer::SDL2_mixer,SDL2_mixer::SDL2_mixer-static>)

 target_link_libraries(main 
	PRIVATE 
	$<IF:$<TARGET_EXISTS:SDL2_ttf::SDL2_ttf>,SDL2_ttf::SDL2_ttf,SDL2_ttf::SDL2_ttf-static>)