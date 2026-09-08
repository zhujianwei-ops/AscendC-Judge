#include "tiling_context_faker.h"

namespace gert {

TilingContextFaker& TilingContextFaker::SetOpType(const std::string opType)
{
    OpTilingContextBuilder::OpType(opType.c_str()).OpName(opType.c_str());
    return *this;
}

TilingContextFaker& TilingContextFaker::NodeIoNum(size_t inputNum, size_t outputNum)
{
    OpTilingContextBuilder::IONum(inputNum, outputNum);
    return *this;
}

TilingContextFaker& TilingContextFaker::IrInstanceNum(const std::vector<uint32_t>& inputInstanceNum,
                                                      const std::vector<uint32_t>& outputInstanceNum)
{
    OpTilingContextBuilder::IOInstanceNum(inputInstanceNum, outputInstanceNum);
    return *this;
}

TilingContextFaker& TilingContextFaker::InputTensors(const std::vector<Tensor *>& inputTensors)
{
    OpTilingContextBuilder::InputTensors(inputTensors);
    return *this;
}

TilingContextFaker& TilingContextFaker::OutputTensors(const std::vector<Tensor *>& outputTensors)
{
    OpTilingContextBuilder::OutputTensors(outputTensors);
    return *this;
}

TilingContextFaker& TilingContextFaker::CompileInfo(const void* compileInfo)
{
    OpTilingContextBuilder::CompileInfo(compileInfo);
    return *this;
}

TilingContextFaker& TilingContextFaker::PlatformInfo(const void* platformInfo)
{
    OpTilingContextBuilder::PlatformInfo(platformInfo);
    return *this;
}

TilingContextFaker& TilingContextFaker::DeterministicInfo(int32_t* deterministicInfo)
{
    OpTilingContextBuilder::Deterministic(*deterministicInfo);
    return *this;
}

TilingContextFaker& TilingContextFaker::TilingData(const void* tilingData)
{
    OpTilingContextBuilder::TilingData(static_cast<const gert::TilingData *>(tilingData));
    return *this;
}

TilingContextFaker& TilingContextFaker::Workspace(const ContinuousVector* workspace)
{
    OpTilingContextBuilder::Workspace(workspace);
    return *this;
}

ContextHolder<TilingContext> TilingContextFaker::Build()
{
    return OpTilingContextBuilder::Build();
}

} // namespace gert
