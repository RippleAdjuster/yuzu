// Copyright 2016 Citra Emulator Project
// Licensed under GPLv2 or any later version
// Refer to the license.txt file included.

#pragma once

#include <memory>
#include <dynarmic/dynarmic.h>
#include "common/common_types.h"
#include "core/arm/arm_interface.h"
#include "core/arm/skyeye_common/armstate.h"

class ARM_Dynarmic final : public ARM_Interface {
public:
    ARM_Dynarmic(PrivilegeMode initial_mode);

    void SetPC(u64 pc) override;
    u64 GetPC() const override;
    u64 GetReg(int index) const override;
    void SetReg(int index, u64 value) override;
    u32 GetVFPReg(int index) const override;
    void SetVFPReg(int index, u32 value) override;
    u32 GetVFPSystemReg(VFPSystemRegister reg) const override;
    void SetVFPSystemReg(VFPSystemRegister reg, u32 value) override;
    u32 GetCPSR() const override;
    void SetCPSR(u32 cpsr) override;
    u32 GetCP15Register(CP15Register reg) override;
    void SetCP15Register(CP15Register reg, u32 value) override;
    VAddr GetTlsAddress() const override;
    void SetTlsAddress(VAddr address) override;

    void AddTicks(u64 ticks) override;

    void SaveContext(ThreadContext& ctx) override;
    void LoadContext(const ThreadContext& ctx) override;

    void PrepareReschedule() override;
    void ExecuteInstructions(int num_instructions) override;

    void ClearInstructionCache() override;

private:
    std::unique_ptr<Dynarmic::Jit> jit;
    std::shared_ptr<ARMul_State> interpreter_state;
};
