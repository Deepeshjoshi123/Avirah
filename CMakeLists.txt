cmake_minimum_required(VERSION 3.28)

project(avirah VERSION 0.1.0 LANGUAGES CXX)

option(AVIRAH_BUILD_TESTS "Build native tests" ON)
option(AVIRAH_ENABLE_WT_PROTOTYPE "Build the optional Wt feasibility prototype" OFF)
option(AVIRAH_ENABLE_SANITIZERS "Enable address and undefined-behaviour sanitizers" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(compiler_options)
include(architecture_checks)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(avirah_build_options INTERFACE)
avirah_configure_compiler_options(avirah_build_options)
if(AVIRAH_ENABLE_SANITIZERS)
  include(sanitizer_options)
  avirah_enable_sanitizers(avirah_build_options)
endif()

add_library(avirah_foundation INTERFACE)
target_include_directories(avirah_foundation INTERFACE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/modules/foundation/include>")
target_link_libraries(avirah_foundation INTERFACE avirah_build_options)

function(avirah_add_identity_executable target source)
  add_executable(${target} ${source})
  target_link_libraries(${target} PRIVATE avirah_foundation)
  target_compile_definitions(${target} PRIVATE
    AVIRAH_VERSION_MAJOR=${PROJECT_VERSION_MAJOR}
    AVIRAH_VERSION_MINOR=${PROJECT_VERSION_MINOR}
    AVIRAH_VERSION_PATCH=${PROJECT_VERSION_PATCH})
endfunction()

avirah_add_identity_executable(avirah-server apps/server/main.cpp)
avirah_add_identity_executable(avirah-agent apps/agent/main.cpp)
avirah_add_identity_executable(avirah apps/cli/main.cpp)
avirah_add_identity_executable(avirah-test-driver tooling/test_driver/main.cpp)
avirah_add_identity_executable(avirah-browser-tests tooling/browser_tests/main.cpp)

if(AVIRAH_ENABLE_WT_PROTOTYPE)
  find_package(Wt CONFIG REQUIRED COMPONENTS Wt HTTP)
  add_executable(avirah-wt-prototype apps/server/wt_prototype.cpp)
  target_link_libraries(avirah-wt-prototype PRIVATE Wt::Wt Wt::HTTP avirah_build_options)
  target_include_directories(avirah-wt-prototype PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/modules/foundation/include")
endif()

if(AVIRAH_BUILD_TESTS)
  enable_testing()
  add_executable(architecture-check tooling/architecture_check/main.cpp)
  target_link_libraries(architecture-check PRIVATE avirah_build_options)
  add_test(NAME architecture-dependency-rules COMMAND architecture-check
    "${CMAKE_CURRENT_SOURCE_DIR}")

  add_executable(foundation-smoke-tests tests/unit/foundation_smoke.cpp)
  target_link_libraries(foundation-smoke-tests PRIVATE avirah_foundation)
  add_test(NAME foundation-smoke-tests COMMAND foundation-smoke-tests)
endif()

include(CTest)
if(BUILD_TESTING)
  set_tests_properties(architecture-dependency-rules foundation-smoke-tests
    PROPERTIES LABELS "p01;native")
endif()

message(STATUS "Avirah ${PROJECT_VERSION} | C++${CMAKE_CXX_STANDARD} | ${CMAKE_SYSTEM_NAME}")
