cmake_minimum_required(VERSION 3.1.0)

project(ls_cjson)

add_library(${PROJECT_NAME} STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/ls_cjson.c
    ${CMAKE_CURRENT_SOURCE_DIR}/cJSON/cJSON.c
)

target_include_directories(
    ${PROJECT_NAME} PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/cJSON
)