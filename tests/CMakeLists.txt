# 查找所有测试文件
file(GLOB TEST_SOURCES "*.cpp")

# 为每个测试文件创建一个测试可执行文件
foreach(TEST_SOURCE ${TEST_SOURCES})
    get_filename_component(TEST_NAME ${TEST_SOURCE} NAME_WE)
    add_executable(${TEST_NAME} ${TEST_SOURCE})
    target_link_libraries(${TEST_NAME}
        PRIVATE
        gtest
        gtest_main
        ${PROJECT_NAME}
    )
    add_test(NAME ${TEST_NAME} COMMAND ${TEST_NAME})
endforeach()