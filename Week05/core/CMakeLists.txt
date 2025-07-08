file(GLOB CORE_SOURCES *.cpp)

add_library(core STATIC ${CORE_SOURCES})

target_include_directories(core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
