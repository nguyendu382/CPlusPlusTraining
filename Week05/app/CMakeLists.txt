file(GLOB APP_SOURCES *.cpp)

add_executable(app ${APP_SOURCES})

target_link_libraries(app PRIVATE core utils)

