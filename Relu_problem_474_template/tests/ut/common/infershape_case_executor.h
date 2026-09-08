#ifndef OPS_MATH_DEV_TESTS_UT_COMMON_INFERSHAPE_CASE_EXECUTOR_H
#define OPS_MATH_DEV_TESTS_UT_COMMON_INFERSHAPE_CASE_EXECUTOR_H

#include "infershape_context_faker.h"

void ExecuteTestCase(gert::InfershapeContextPara&             infershapeContextPara, 
                     ge::graphStatus                          expectResult = ge::GRAPH_FAILED,
                     const std::vector<std::vector<int64_t>>& expectOutputShape = {});

#endif // OPS_MATH_DEV_TESTS_UT_COMMON_INFERSHAPE_CASE_EXECUTOR_H