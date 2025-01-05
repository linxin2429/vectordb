cmake_minimum_required(VERSION 3.15)
project(vectordb VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 添加faiss编译选项
option(BUILD_TESTING "Build tests" OFF)
option(FAISS_ENABLE_GPU "Build GPU version" OFF)
option(FAISS_ENABLE_PYTHON "Build Python interface" OFF)
option(FAISS_ENABLE_GPU "Build GPU version" ON)
enable_language(CUDA)
find_package(CUDAToolkit REQUIRED)


# 添加第三方库
add_subdirectory(third_party/faiss)
add_subdirectory(third_party/spdlog)
add_subdirectory(third_party/hnswlib)
add_subdirectory(third_party/googletest)

# RapidJSON是头文件库，只需要包含头文件
include_directories(third_party/rapidjson/include)
include_directories(third_party/cpp_httplib)
# 添加项目源文件
file(GLOB_RECURSE SOURCES "src/*.cpp")

# 创建可执行文件
add_executable(${PROJECT_NAME} ${SOURCES})

find_package(OpenMP REQUIRED)
if(OpenMP_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE OpenMP::OpenMP_CXX)
endif()

# 查找BLAS
find_package(BLAS REQUIRED)
if(BLAS_FOUND)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${BLAS_LIBRARIES})
endif()

# 链接第三方库
target_link_libraries(${PROJECT_NAME}
    PRIVATE
    faiss
    spdlog::spdlog
    hnswlib
)

# 包含头文件目录
target_include_directories(${PROJECT_NAME}
    PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# 启用测试
enable_testing()
add_subdirectory(tests)
