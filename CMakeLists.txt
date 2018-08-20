cmake_minimum_required(VERSION 3.10)
set(PROJECT_NAME network_learning)

set(CMAKE_BUILD_TYPE DEBUG)

project(${PROJECT_NAME} CXX)

set(CMAKE_CXX_COMPILER "/usr/local/opt/llvm/bin/clang++" CACHE string "clang++ compiler" FORCE)

include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++14" COMPILER_SUPPORTS_CXX14)

if(COMPILER_SUPPORTS_CXX14)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")
else()
    message(STATUS "The compiler ${CMAKE_CXX_COMPILER} has no C++14 support. Please use a different C++ compiler.")
endif()

set(CMAKE_CXX_FLAGS "-std=c++1z -Wall -Wextra -pedantic -Wcast-align -Wcast-qual -Wconversion -Wdisabled-optimization -Wendif-labels -Wfloat-equal -Winit-self -Winline -Wmissing-include-dirs -Wnon-virtual-dtor -Wold-style-cast -Woverloaded-virtual -Wpacked -Wpointer-arith -Wredundant-decls -Wshadow -Wsign-promo -Wswitch-default -Wswitch-enum -Wvariadic-macros -Wwrite-strings -Wunused-private-field")

set(CMAKE_CXX_FLAGS_DEBUG "-g3 -O0 -pg -fsanitize=address -fno-omit-frame-pointer")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -s -DNDEBUG -march=native")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-g3 -Og -pg")
set(CMAKE_CXX_FLAGS_MINSIZEREL "-Os -s -DNDEBUG -march=native")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ./build)


include_directories(./include)


find_package(PkgConfig)
pkg_check_modules(lib_allegro REQUIRED
    allegro-5
    allegro_acodec-5
    allegro_audio-5
    allegro_color-5
    allegro_dialog-5
    allegro_font-5
    allegro_image-5
    allegro_main-5
    allegro_memfile-5
    allegro_physfs-5
    allegro_primitives-5
    allegro_ttf-5
    )

set(lib_boost boost_system-mt boost_filesystem-mt)

set(libs ${lib_allegro_LIBRARIES} ${lib_boost} m c)

set(sources_dir src)
set(headers_dir include)
file(GLOB sources RELATIVE ${PROJECT_SOURCE_DIR} ${sources_dir}/*.cc)
file(GLOB headers RELATIVE ${PROJECT_SOURCE_DIR} ${headers_dir}/*.hh)

# get_cmake_property(_variableNames VARIABLES):w
# foreach(_variableNames ${_variableNames})
#     message(STATUS "${_variableNames}=${${_variableNames}}")
# endforeach(_variableNames)


add_executable(${PROJECT_NAME} ${sources})
target_include_directories(${PROJECT_NAME} PRIVATE ./include)
target_link_libraries(${PROJECT_NAME} ${libs})
