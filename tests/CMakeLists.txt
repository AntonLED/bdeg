cmake_minimum_required(VERSION 3.20)

project(test_modeling)

include_directories(
    "../potentials/"
    "../utils/" 
    "../integration_engines" 
    "/home/anton/Downloads/eigen/Eigen"
)

set (
    SOURCES ./test_main.cpp
)

add_executable(test ${SOURCES})