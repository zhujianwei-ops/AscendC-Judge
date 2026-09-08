#include "infershape_context_faker.h"

namespace gert {

InferShapeContextFaker& InferShapeContextFaker::SetOpType(const std::string opType)
{
    OpInferShapeContextBuilder::OpType(opType.c_str()).OpName(opType.c_str());
    return *this;
}

InferShapeContextFaker& InferShapeContextFaker::NodeIoNum(size_t inputNum, size_t outputNum)
{
    OpInferShapeContextBuilder::IONum(inputNum, outputNum);
    return *this;
}

InferShapeContextFaker& InferShapeContextFaker::IrInstanceNum(const std::vector<uint32_t>& inputInstanceNum,
                                                              const std::vector<uint32_t>& outputInstanceNum)
{
    OpInferShapeContextBuilder::IOInstanceNum(inputInstanceNum, outputInstanceNum);
    return *this;
}

InferShapeContextFaker& InferShapeContextFaker::NodeOutputTd(int32_t index, ge::DataType dtype, ge::Format originFormat,
                                                             ge::Format storageFormat)
{
    OpInferShapeContextBuilder::OutputTensorDesc(index, dtype, originFormat, storageFormat);
    return *this;
}

InferShapeContextFaker& InferShapeContextFaker::InputTensors(const std::vector<Tensor *>& inputTensors)
{
    OpInferShapeContextBuilder::InputTensors(inputTensors);
    return *this;
}

ContextHolder<InferShapeContext> InferShapeContextFaker::Build()
{
    return OpInferShapeContextBuilder::Build();
}

} // namespace gert
