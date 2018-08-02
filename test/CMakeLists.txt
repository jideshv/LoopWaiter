set(testsources
    tests.cpp
    main.cpp
)

include(FetchContent)
FetchContent_Declare(
  fff
  GIT_REPOSITORY https://github.com/jideshv/fff.git
)

FetchContent_GetProperties(fff)
if(NOT fff_POPULATED)
  FetchContent_Populate(fff)
  add_subdirectory(${fff_SOURCE_DIR} ${fff_BINARY_DIR})
endif()

add_executable(LoopWaiterTest ${testsources})

target_link_libraries(LoopWaiterTest LoopWaiter gtest_main gmock_main fff)

include(GoogleTest)

gtest_add_tests(TARGET LoopWaiterTest)
