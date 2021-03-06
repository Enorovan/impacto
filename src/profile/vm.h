#pragma once

#include "../impacto.h"
#include "../vm/vm.h"

namespace Impacto {
namespace Profile {
namespace Vm {

extern uint32_t StartScript;
extern uint32_t StartScriptBuffer;
extern Impacto::Vm::InstructionSet GameInstructionSet;
extern bool UseReturnIds;
extern int ScrWorkChaStructSize;
extern int ScrWorkBgStructSize;

void Configure();

}  // namespace Vm
}  // namespace Profile
}  // namespace Impacto