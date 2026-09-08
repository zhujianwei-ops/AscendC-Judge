#include <iostream>
#include <gtest/gtest.h>
#include "tiling_context_faker.h"
#include "tiling_case_executor.h"
#include "relu_tiling_data.h"

namespace ReluUT {
using namespace std;
using namespace ge;
using namespace gert;
static const std::string OP_NAME = "Relu";

struct ReluTestParam {
    std::string caseName;
    std::initializer_list<int64_t> xShape;
    ge::DataType xDtype;
    ge::Format xFormat;
    std::initializer_list<int64_t> yShape;
    ge::DataType yDtype;
    ge::Format yFormat;
    std::string socVersion;
    ge::graphStatus status;
    uint64_t expectTilingKey;
    std::string expectTilingData;
    std::vector<size_t> expectWorkspaces;
    uint64_t maxAIVNum;
    uint64_t ubSize;
    uint64_t tilingDataMaxSize;
};

// TODO: 以下期望值基于初始模板实现，修改 tiling 逻辑后请更新：
//   expectTilingKey:  参考 op_kernel/relu_tiling_key.h 和 op_host/relu_tiling.cpp 中 tilingKey 的逻辑
//   expectTilingData: 参考 op_host/relu_tiling.cpp 中 TilingData 各字段的赋值
//   expectWorkspaces: 参考 op_host/relu_tiling.cpp 中 GetWorkspaceSize 的逻辑
static ReluTestParam testCases[] = {
    {"relu_0", {45, 2048}, ge::DT_FLOAT, ge::FORMAT_ND, {45, 2048}, ge::DT_FLOAT, ge::FORMAT_ND, "Ascend910B", ge::GRAPH_SUCCESS, 1UL, "0 1 0 ", {0}, 64, 262144, 4096},
};

class ReluTilingTest : public testing::TestWithParam<ReluTestParam> {
protected:
    static void SetUpTestCase() {
        std::cout << "ReluTilingTest SetUp." << std::endl;
    }
    static void TearDownTestCase() {
        std::cout << "ReluTilingTest TearDown." << std::endl;
    }
};

struct ReluCompileInfo {} compileInfo;

static void TestOneParamCase(const ReluTestParam &param)
{
    gert::StorageShape xShape = {param.xShape, param.xShape};
    gert::StorageShape yShape = {param.yShape, param.yShape};
    std::vector<gert::TilingContextPara::TensorDescription> inputTensorDesc_(
        {{xShape, param.xDtype, param.xFormat}});
    std::vector<gert::TilingContextPara::TensorDescription> outputTensorDesc_(
        {{yShape, param.yDtype, param.yFormat}});
    std::vector<gert::TilingContextPara::OpAttr> attrs_;

    gert::TilingContextPara tilingContextPara(
        OP_NAME,
        inputTensorDesc_,
        outputTensorDesc_,
        attrs_,
        &compileInfo,
        param.maxAIVNum,
        param.ubSize,
        param.tilingDataMaxSize);
    ExecuteTestCase(tilingContextPara, param.status, param.expectTilingKey,
                    param.expectTilingData, param.expectWorkspaces);
}

TEST_P(ReluTilingTest, tiling_test)
{
    const ReluTestParam &param = GetParam();
    TestOneParamCase(param);
}

INSTANTIATE_TEST_SUITE_P(
    ReluTilingTests,
    ReluTilingTest,
    testing::ValuesIn(testCases));

}
