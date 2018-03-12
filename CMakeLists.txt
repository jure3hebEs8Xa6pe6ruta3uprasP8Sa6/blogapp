cmake_minimum_required(VERSION 3.9)

set(PROJECT blogapp)
project(${PROJECT})
#        VERSION "1.0.0")
set(PROJECT_VERSION "1.0.0")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

find_package(Qt5 COMPONENTS Sql Xml Qml Core Widgets REQUIRED)
find_package(qtcsv REQUIRED)
include_directories(/usr/include/treefrog)
include_directories(/usr/local/include/qtcsv)
include_directories(models)
include_directories(models/sqlobjects)
include_directories(helpers)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_executable(hello test.cpp)

#   helper
add_library(
        helper SHARED
        helpers/applicationhelper.cpp
        helpers/applicationhelper.h)

set_target_properties(helper PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1 SOVERSION 1.0)
target_link_libraries(helper pthread treefrog rt Qt5::Core Qt5::Network Qt5::Sql Qt5::Qml Qt5::Xml)

#	model
add_library(model SHARED
        models/sqlobjects/blogappobject.h
        models/blogapp.cpp
        models/blogapp.h)

set_target_properties(model PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1 SOVERSION 1.0)
target_link_libraries(model pthread treefrog rt helper qtcsv Qt5::Core Qt5::Network Qt5::Sql Qt5::Qml Qt5::Xml)

#	controller
add_library(controller SHARED
        controllers/applicationcontroller.cpp
        controllers/applicationcontroller.h
        controllers/blogappcontroller.cpp
        controllers/blogappcontroller.h)

set_target_properties(controller PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1 SOVERSION 1.0)
target_link_libraries(controller pthread treefrog rt helper model Qt5::Core Qt5::Network Qt5::Sql Qt5::Qml Qt5::Xml)

#  view
add_library(view SHARED
        views/_src/blogapp_createView.cpp
        views/_src/blogapp_indexView.cpp
        views/_src/blogapp_saveView.cpp
        views/_src/blogapp_loadView.cpp
        views/_src/blogapp_showView.cpp)

set_target_properties(view PROPERTIES VERSION ${PROJECT_VERSION} SOVERSION 1 SOVERSION 1.0)
target_link_libraries(view pthread treefrog rt helper model Qt5::Core Qt5::Network Qt5::Sql Qt5::Qml Qt5::Xml)

add_custom_command(
        TARGET controller
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
)

add_custom_command(
        TARGET model
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
)

add_custom_command(
        TARGET view
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
)

add_custom_command(
        TARGET helper
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} --build ${CMAKE_BINARY_DIR} --target install
)
#add_custom_command(TARGET controller
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:controller> ${PROJECT_SOURCE_DIR}/lib
#        COMMENT "Copying controller to lib directory")
#
#add_custom_command(TARGET model
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:model> ${PROJECT_SOURCE_DIR}/lib)
#
#add_custom_command(TARGET view
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:view> ${PROJECT_SOURCE_DIR}/lib)
#
#add_custom_command(TARGET helper
#        POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:helper> ${PROJECT_SOURCE_DIR}/lib)

#install(TARGETS controller LIBRARY DESTINATION ${PROJECT_LIBRARY_DIR}/lib)
install(TARGETS controller DESTINATION ${PROJECT_SOURCE_DIR}/lib)
install(TARGETS model DESTINATION ${PROJECT_SOURCE_DIR}/lib)
install(TARGETS view DESTINATION ${PROJECT_SOURCE_DIR}/lib)
install(TARGETS helper DESTINATION ${PROJECT_SOURCE_DIR}/lib)

