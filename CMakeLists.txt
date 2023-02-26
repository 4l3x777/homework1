cmake_minimum_required(VERSION 3.25)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(helloworld VERSION ${PROJECT_VESRION})

include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.13.0
)

FetchContent_GetProperties(googletest)
if(NOT googletest_POPULATED)
  FetchContent_Populate(googletest)
  add_subdirectory(${googletest_SOURCE_DIR} ${googletest_BINARY_DIR})
endif()

set(BOOST_INCLUDE_LIBRARIES test)
set(BOOST_ENABLE_CMAKE ON)
#set(Boost_DEBUG ON)
FetchContent_Declare(
    Boost
    GIT_REPOSITORY https://github.com/boostorg/boost.git
    GIT_TAG boost-1.81.0
)

FetchContent_GetProperties(Boost)
if (NOT Boost_POPULATED)
    FetchContent_Populate(Boost)
    add_subdirectory(${Boost_SOURCE_DIR} ${Boost_BINARY_DIR})
endif ()

configure_file(
    version.h.in 
    version.h    
)

add_executable(
    helloworld_cli 
    main.cpp
)

add_library(
    helloworld 
    lib.cpp
)

add_executable(
    test_version_boost 
    test_version_boost.cpp
)

add_executable(
    test_version_gtest 
    test_version_gtest.cpp
)

set_target_properties(
    helloworld_cli 
    helloworld 
    test_version_boost 
    test_version_gtest 
    PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(
    helloworld
    PRIVATE 
    "${CMAKE_BINARY_DIR}"
)

set_target_properties(
    test_version_gtest 
    PROPERTIES 
    COMPILE_DEFINITIONS 
    STATIC_LINK
)

set_target_properties(
    test_version_boost 
    PROPERTIES 
    COMPILE_DEFINITIONS 
    STATIC_LINK
)


target_link_libraries(
    test_version_gtest 
    gtest 
    gtest_main 
    helloworld
)

target_link_libraries(
    helloworld_cli 
    PRIVATE 
    helloworld
)

target_link_libraries(
    test_version_boost 
    Boost::unit_test_framework 
    helloworld
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE /W4)
    target_compile_options(helloworld PRIVATE /W4)
    target_compile_options(test_version_boost PRIVATE /W4)
else ()
    target_compile_options(
        helloworld_cli 
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
    target_compile_options(
        helloworld 
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
    target_compile_options(
        test_version_boost 
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
    target_compile_options(
        test_version_gtest 
        PRIVATE
        -Wall 
        -Wextra 
        -pedantic 
        -Werror
    )
endif()

install (
    TARGETS 
    helloworld_cli 
    RUNTIME 
    DESTINATION 
    bin
)


# CPack area
if (WIN32)
    set(CPACK_GENERATOR "ZIP")
else ()
    set(CPACK_GENERATOR "DEB")
endif()
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT https://github.com/4l3x777/homework1)
include(CPack)

# Tests area
enable_testing()

add_test(
    NAME 
    unit_tests_test_version_boost 
    COMMAND 
    test_version_boost
)

add_test(
    NAME 
    unit_tests_test_version_gtest 
    COMMAND 
    test_version_gtest
)
