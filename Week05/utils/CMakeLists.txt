file(GLOB UTILS_SOURCES *.cpp)

add_library(utils SHARED ${UTILS_SOURCES})

target_include_directories(utils PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(utils PRIVATE UTILS_DLL)
set_target_properties(utils PROPERTIES OUTPUT_NAME "utils")
