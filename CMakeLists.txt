cmake_minimum_required(VERSION 3.2)

project(allocator VERSION 0.0.$ENV{TRAVIS_BUILD_NUMBER})
#project(allocator VERSION 0.0.1)

configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

add_executable(allocator main.cpp lib.cpp lib.h)

set_target_properties(allocator PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-Wpedantic;-Wall;-Wextra"
        )

install(TARGETS allocator RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT olpotkin@gmail.com)

include(CPack)
