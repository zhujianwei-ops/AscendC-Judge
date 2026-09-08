#!/bin/bash
# Mul_problem_471_template 编译脚本
# 参照 op_01_sub_problem_469_template/run.sh 的流程骨架:
#   Set CANN env -> Build (cmake + make) -> 产物说明
# 本工程为标准 AscendC 算子包工程(op_host + op_kernel),
# 编译产物是 custom 算子包(host optiling.so / kernel .o), 而不是可执行文件。
set -euo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "${SCRIPT_DIR}"

if [ -z "${ASCEND_HOME_PATH:-}" ]; then
    echo "ERROR: ASCEND_HOME_PATH is not set. Please run:"
    echo "  source /usr/local/Ascend/ascend-toolkit/set_env.sh"
    echo "or set ASCEND_HOME_PATH to your CANN toolkit path."
    exit 1
fi

echo "=== [1/2] Set CANN env ==="
source "${ASCEND_HOME_PATH}/set_env.sh"

echo "=== [2/2] Build ==="
rm -rf build
mkdir -p build
cd build
cmake ..
make -j4
cd ..

echo ""
echo "=== Build OK ==="
echo "算子包产物见 build/ 目录:"
find build -maxdepth 3 -type d -name "*.so" 2>/dev/null || true
find build -name "*.so" 2>/dev/null | head -10 || true
echo "(若需安装算子包: 将 build 下生成目录配置为 ASCEND_CUSTOM_OPP_PATH 后使用)"
