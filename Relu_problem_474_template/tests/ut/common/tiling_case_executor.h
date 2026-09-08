#ifndef OPS_MATH_DEV_TESTS_UT_COMMON_TILING_CASE_EXECUTOR_H
#define OPS_MATH_DEV_TESTS_UT_COMMON_TILING_CASE_EXECUTOR_H

#include "tiling_context_faker.h"

using namespace std;

const string EMPTY_EXPECT_TILING_DATA = "EMPTY_EXPECT_TILING_DATA";

struct TilingInfo {
    int64_t tilingKey = -1;
    std::vector<int64_t> workspaceSizes;
    std::unique_ptr<uint8_t[]> tilingData;
    size_t tilingDataSize = 0;
    size_t blockNum = 0;
};

void ExecuteTestCase(const gert::TilingContextPara& tilingContextPara, 
                     ge::graphStatus                expectResult = ge::GRAPH_FAILED,
                     uint64_t                       expectTilingKey = 0, 
                     const string&                  expectTilingData = "",
                     const std::vector<size_t>&     expectWorkspaces = {});

void ExecuteTestCase(const gert::TilingContextPara& tilingContextPara,
                     ge::graphStatus                expectResult,
                     uint64_t                       expectTilingKey,
                     const std::vector<size_t>&     expectWorkspaces);

bool ExecuteTiling(const gert::TilingContextPara& tilingContextPara, TilingInfo& tilingInfo);

#endif // OPS_MATH_DEV_TESTS_UT_COMMON_TILING_CASE_EXECUTOR_H