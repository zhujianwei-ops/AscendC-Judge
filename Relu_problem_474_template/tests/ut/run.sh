#!/bin/bash
# relu 算子 UT 测试执行脚本

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="${SCRIPT_DIR}/build"
CLEAN_BUILD=true

echo "========================================"
echo "relu 算子 UT 测试"
echo "========================================"

if [ -z "$ASCEND_HOME_PATH" ]; then
    export ASCEND_HOME_PATH=/home/developer/Ascend/cann
fi

export LD_LIBRARY_PATH=${ASCEND_HOME_PATH}/lib64:${LD_LIBRARY_PATH}

if [ "$CLEAN_BUILD" = true ]; then
    rm -rf "${BUILD_DIR}"
fi

mkdir -p "${BUILD_DIR}"
cd "${BUILD_DIR}"
cmake ..
make -j$(nproc)

echo "========================================"
echo "执行 UT 测试"
echo "========================================"

FAILED_TESTS=()
PASSED_TESTS=()

cd "${BUILD_DIR}/op_host"
if ./relu_op_host_ut; then
    PASSED_TESTS+=("op_host")
else
    FAILED_TESTS+=("op_host")
fi

# 生成测试数据
echo "========================================"
echo "生成 Kernel UT 测试数据"
echo "========================================"
DATA_DIR="${SCRIPT_DIR}/op_kernel/relu_data"
cd "${DATA_DIR}"
python3 gen_data.py

# 运行 Kernel UT
cd "${BUILD_DIR}/op_kernel"
if ./relu_op_kernel_ut; then
    PASSED_TESTS+=("op_kernel")
else
    FAILED_TESTS+=("op_kernel")
fi

# 拷贝输出 bin 文件到 DATA_DIR 供 compare_data.py 比对
cp "${BUILD_DIR}/op_kernel/"*.bin "${DATA_DIR}/" 2>/dev/null || true

# 精度比对
echo "========================================"
echo "精度比对"
echo "========================================"
cd "${DATA_DIR}"
if python3 compare_data.py; then
    echo "精度比对通过"
else
    # precision_check 在 stub 阶段预期失败（kernel 为空实现），kernel 正确实现后应通过
    FAILED_TESTS+=("precision_check")
fi

if [ -d "${BUILD_DIR}/../../../op_api" ]; then
    cd "${BUILD_DIR}/op_api"
    if ./relu_op_api_ut; then
        PASSED_TESTS+=("op_api")
    else
        FAILED_TESTS+=("op_api")
    fi
fi

echo "========================================"
echo "测试结果汇总"
echo "========================================"

if [ ${#FAILED_TESTS[@]} -gt 0 ]; then
    echo "失败的测试: ${FAILED_TESTS[@]}"
    exit 1
else
    echo "所有测试通过"
    exit 0
fi
