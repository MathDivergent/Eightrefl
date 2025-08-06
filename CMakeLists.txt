# [[Root]]
cmake_minimum_required(VERSION 3.16)

project(Eightrefl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_SHARED_LIBRARY_PREFIX "")


# [[Options]]
option(EIGHTREFL_BUILD_FAST_LIBS "Build with -O3 by Default" OFF)
option(EIGHTREFL_BUILD_SHARED_LIBS "Build shared libraies by Default" ON)
option(EIGHTREFL_FULLY_ENABLE "Build fully by Default" OFF)
option(EIGHTREFL_RTTI_ENABLE "Build with RTTI by Default" OFF)
option(EIGHTREFL_STANDARD_ENABLE "Build with Standard by Default" OFF)
option(EIGHTREFL_DEV_ENABLE "Build with Dev by Default" OFF)
option(EIGHTREFL_BUILD_TEST_LIBS "Build testing libraies by Default" OFF)


# [[Defaults]]
if(PROJECT_IS_TOP_LEVEL)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Binaries")
    if(APPLE)
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Binaries/EightestLauncher.app/Contents/Frameworks")
    else()
        set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/Binaries")
    endif()
endif()

if(LINUX)
    set(EIGHTREFL_RPATH "$ORIGIN")
elseif(APPLE)
    set(EIGHTREFL_RPATH "@loader_path/../Frameworks")
endif()

if(WIN32)
    set(EIGHTREFL_MODULE_EXPORT "__declspec(dllexport)")
    set(EIGHTREFL_MODULE_IMPORT "__declspec(dllimport)")
else()
    set(EIGHTREFL_MODULE_EXPORT "__attribute__((visibility(\"default\")))")
    set(EIGHTREFL_MODULE_IMPORT "")
endif()


# [[Binaries]]
if(EIGHTREFL_BUILD_SHARED_LIBS)
    set(PROJECT_LIBS_TYPE SHARED)
else()
    set(PROJECT_LIBS_TYPE STATIC)
    message(WARNING "Eightrefl: build static library not recommended, registration may be lost, use export all symbols to be sure")
endif()


file(GLOB_RECURSE PROJECT_SOURCES_FILES "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
add_library(Eightrefl ${PROJECT_LIBS_TYPE} ${PROJECT_SOURCES_FILES})
target_include_directories(Eightrefl PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")

if(EIGHTREFL_BUILD_FAST_LIBS)
    target_compile_options(Eightrefl PRIVATE -O3)
else()
    target_compile_options(Eightrefl PRIVATE -O2)
endif()

if(EIGHTREFL_BUILD_SHARED_LIBS)
    target_compile_definitions(Eightrefl PRIVATE "EIGHTREFL_API=${EIGHTREFL_MODULE_EXPORT}" INTERFACE "EIGHTREFL_API=${EIGHTREFL_MODULE_IMPORT}")
else()
    target_compile_definitions(Eightrefl PUBLIC "EIGHTREFL_API=")
endif()

if(EIGHTREFL_FULLY_ENABLE)
    target_compile_definitions(Eightrefl PUBLIC "EIGHTREFL_FULLY_ENABLE")
endif()

if(EIGHTREFL_RTTI_ENABLE)
    target_compile_options(Eightrefl PUBLIC -frtti)
    target_compile_definitions(Eightrefl PUBLIC "EIGHTREFL_RTTI_ENABLE")
else()
    target_compile_options(Eightrefl PUBLIC -fno-rtti)
endif()

if(EIGHTREFL_STANDARD_ENABLE)
    target_compile_definitions(Eightrefl PUBLIC "EIGHTREFL_STANDARD_ENABLE")
endif()

if(EIGHTREFL_DEV_ENABLE)
    # we recomend in Release builds only
    target_compile_definitions(Eightrefl PUBLIC "EIGHTREFL_DEV_ENABLE")
endif()


# [[Tests]]
if(EIGHTREFL_BUILD_TEST_LIBS)
    file(GLOB_RECURSE PROJECT_TEST_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/test/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/test/*.hpp")
    add_library(EightreflTests ${PROJECT_LIBS_TYPE} ${PROJECT_TEST_SOURCES})

    if(PROJECT_IS_TOP_LEVEL)
        # you should manually download Eightest if not
        set(EIGHTEST_RUN_MODULE "EightreflTests")
        add_subdirectory("Eightest")
    endif()

    if(EIGHTREFL_BUILD_FAST_LIBS)
        target_compile_options(EightreflTests PRIVATE -O3)
    else()
        target_compile_options(EightreflTests PRIVATE -O2)
    endif()

    target_link_libraries(EightreflTests PUBLIC Eightrefl Eightest)
    target_include_directories(EightreflTests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/test")
    set_target_properties(EightreflTests PROPERTIES BUILD_WITH_INSTALL_RPATH TRUE INSTALL_RPATH "${EIGHTREFL_RPATH}")
endif()
