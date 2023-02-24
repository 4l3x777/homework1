cmake_minimum_required(VERSION 3.2)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VESRION 0.0.${PATCH_VERSION})
project(helloworld VERSION ${PROJECT_VESRION})

message("Target system: ${CMAKE_HOST_SYSTEM_NAME}")
# Boost Add Windows area
if (WIN32)
    if("${BOOST_ROOT}" STREQUAL "")
        if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "4")
            set (X86 TRUE)
            message("Target build: x86")
        else()
            set (X86 FALSE)
            message("Target build: x64")
        endif ()

        message("Compiler Type: ${CMAKE_CXX_COMPILER_ID}")

        if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
            if (X86)
                set(BOOST_ROOT "C:/boost_mingw/boost32")
            else()
                set(BOOST_ROOT "C:/boost_mingw/boost64")
            endif()
        elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
            if (X86)
                set(BOOST_ROOT "C:/boost_msvc/boost32")
            else()
                set(BOOST_ROOT "C:/boost_msvc/boost64")
            endif()
        endif()

        message("Set boost library path is ${BOOST_ROOT}")
        #set(Boost_DEBUG 1)
        enable_language(CXX)
    endif()
endif ()

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

configure_file(version.h.in version.h)

add_executable(helloworld_cli main.cpp)
add_library(helloworld lib.cpp)
add_executable(test_version_boost test_version_boost.cpp)

set_target_properties(helloworld_cli helloworld test_version_boost PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED ON
)

target_include_directories(helloworld
    PRIVATE "${CMAKE_BINARY_DIR}"
)

if (WIN32)
    set_target_properties(test_version_boost 
        PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_STATIC_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )
else ()
    set_target_properties(test_version_boost 
        PROPERTIES
        COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
        INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIR}
    )
endif ()


target_link_libraries(helloworld_cli PRIVATE
    helloworld
)
target_link_libraries(
    test_version_boost
    ${Boost_LIBRARIES}
    helloworld
)

if (MSVC)
    target_compile_options(helloworld_cli PRIVATE
        /W4
    )
    target_compile_options(helloworld PRIVATE
        /W4
    )
    target_compile_options(test_version_boost PRIVATE
        /W4
    )
else ()
    target_compile_options(helloworld_cli PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(helloworld PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
    target_compile_options(test_version_boost PRIVATE
        -Wall -Wextra -pedantic -Werror
    )
endif()

install (TARGETS helloworld_cli RUNTIME DESTINATION bin)


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
add_test(NAME unit_tests_test_version_boost COMMAND test_version_boost)
