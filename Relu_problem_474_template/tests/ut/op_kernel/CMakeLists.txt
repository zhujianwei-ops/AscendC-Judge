set(OP_NAME relu)
set(UT_EXE ${OP_NAME}_op_kernel_ut)

message(STATUS "Building op_kernel UT for: ${OP_NAME}")

if(DEFINED ENV{ASCEND_HOME_PATH} AND EXISTS "$ENV{ASCEND_HOME_PATH}")
    set(CANN_HOME "$ENV{ASCEND_HOME_PATH}")
elseif(EXISTS "/usr/local/Ascend/cann-8.5.0")
    set(CANN_HOME "/usr/local/Ascend/cann-8.5.0")
else()
    message(FATAL_ERROR "Cannot find CANN installation")
endif()

message(STATUS "Using CANN_HOME: ${CANN_HOME}")

set(SOC_VERSION "Ascend910B1")

set(tikicpulib_DIR ${CANN_HOME}/tools/tikicpulib/lib/cmake)
find_package(tikicpulib REQUIRED)

set(OP_KERNEL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/../../../op_kernel)

set(UT_TEST_SRCS
    test_${OP_NAME}.cpp
)

set(UT_INCLUDE_DIRS
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${OP_KERNEL_DIR}
    ${UT_COMMON_INCLUDE_DIRS}
    ${CANN_HOME}/tools/tikicpulib/lib/include
    ${CANN_HOME}/compiler/ascendc/include/highlevel_api
    ${CANN_HOME}/compiler/ascendc/include/basic_api/impl
    ${CANN_HOME}/compiler/ascendc/include/basic_api
    ${CANN_HOME}/compiler/ascendc/include
    ${CANN_HOME}/compiler/ascendc/include/ascendc/host_api/tiling
    ${CANN_HOME}/compiler/ascendc/include/ascendc/host_api
    ${CANN_HOME}/compiler/ascendc/include/ascendc
    ${CANN_HOME}/aarch64-linux/include
    ${CANN_HOME}/aarch64-linux/asc/include/basic_api
    ${CANN_HOME}/aarch64-linux/asc/include
    ${CANN_HOME}/aarch64-linux/asc/include/interface
    ${CANN_HOME}/aarch64-linux/asc/impl/basic_api
    ${CANN_HOME}/aarch64-linux/asc
    ${CANN_HOME}/compiler/tikcpp/tikcfw
    ${CANN_HOME}/compiler/tikcpp/tikcfw/impl
    ${CANN_HOME}/compiler/tikcpp/tikcfw/interface
    ${CANN_HOME}/aarch64-linux/include/graph
    ${CANN_HOME}/aarch64-linux/ascendc/include/highlevel_api
    ${CANN_HOME}/aarch64-linux/asc/impl/basic_api/utils
)

add_executable(${UT_EXE}
    ${UT_TEST_SRCS}
)

target_include_directories(${UT_EXE} PRIVATE
    ${UT_INCLUDE_DIRS}
)

target_compile_definitions(${UT_EXE} PRIVATE
    _GLIBCXX_USE_CXX11_ABI=0
    __aicore__=
    __NPU_TILING__=1
)

target_compile_options(${UT_EXE} PRIVATE
    -Wall
    -Wno-deprecated-declarations
    -Wno-unused-variable
    -Wno-unknown-pragmas
    -fno-access-control
    -std=c++17
)

target_link_directories(${UT_EXE} PRIVATE
    ${UT_COMMON_LIB_DIRS}
    ${CANN_HOME}/lib64
)

target_link_libraries(${UT_EXE} PRIVATE
    gtest_main
    gtest
    ${CANN_HOME}/lib64/libmmpa.so
    tikicpulib::${SOC_VERSION}
    dl
    pthread
)

set_target_properties(${UT_EXE} PROPERTIES
    INSTALL_RPATH "$ORIGIN;${CANN_HOME}/lib64;${CANN_HOME}/tools/tikicpulib/lib;${CANN_HOME}/tools/tikicpulib/lib/Ascend910B1;${CANN_HOME}/aarch64-linux/simulator/Ascend910B1/lib"
    BUILD_WITH_INSTALL_RPATH TRUE
)

message(STATUS "  Kernel UT executable: ${UT_EXE}")
message(STATUS "  CANN Home: ${CANN_HOME}")
message(STATUS "  SOC Version: ${SOC_VERSION}")
