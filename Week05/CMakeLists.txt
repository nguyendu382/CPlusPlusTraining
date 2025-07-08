cmake_minimum_required(VERSION 3.10)
project(Week5Project)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(core)
add_subdirectory(utils)
add_subdirectory(app)

install(TARGETS core utils app
       RUNTIME DESTINATION bin
       LIBRARY DESTINATION lib
       ARCHIVE DESTINATION lib)
install(DIRECTORY core/ DESTINATION include FILES_MATCHING PATTERN "*.h")
install(DIRECTORY utils/ DESTINATION include FILES_MATCHING PATTERN "*.h")

