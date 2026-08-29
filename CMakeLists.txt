cmake_minimum_required(VERSION 3.20)
project(My_PS3IOS C CXX OBJC OBJCXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_OSX_SYSROOT "iphoneos")
set(CMAKE_OSX_ARCHITECTURES "arm64")

add_compile_options(-O3 -ffast-math -march=armv8.5-a+fp16+simd)

include_directories(include)

file(GLOB SOURCES 
    "src/*.cpp" 
    "src/*.mm"
)

add_executable(My_PS3IOS ${SOURCES})

find_library(METAL_LIB Metal REQUIRED)
find_library(FOUNDATION_LIB Foundation REQUIRED)
find_library(UIKIT_LIB UIKit REQUIRED)
find_library(QUARTZ_LIB QuartzCore REQUIRED)

target_link_libraries(My_PS3IOS 
    ${METAL_LIB} 
    ${FOUNDATION_LIB} 
    ${UIKIT_LIB} 
    ${QUARTZ_LIB}
)

set_target_properties(My_PS3IOS PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_CURRENT_SOURCE_DIR}/Info.plist
)
