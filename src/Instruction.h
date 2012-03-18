#ifndef INSTRUCTION_H
#define INSTRUCTION_H

#include "types/Value.h"
#include "types/String.h"
#include <vector>

namespace lua
{
    enum OpCode
    {
        OpCode_Assign,
        OpCode_CleanStack,
        OpCode_GetTable,
        OpCode_Push,
        OpCode_Call,
    };

    enum InstructionParamType
    {
        InstructionParamType_Value,
        InstructionParamType_Name,
        InstructionParamType_Number,
        InstructionParamType_Bool,
        InstructionParamType_Nil,
        InstructionParamType_Counter,
    };

    struct InstructionParam
    {
        InstructionParamType type;
        union
        {
            Value *value;
            String *name;
            double number;
            bool b;
            int counter;
        } param;
    };

    struct Instruction
    {
        OpCode op_code;
        InstructionParam param_a;
        InstructionParam param_b;
    };

    class InstructionSet
    {
    public:
        // New one instruction and return it.
        Instruction * NewInstruction()
        {
            instructions_.resize(instructions_.size() + 1);
            return &instructions_.back();
        }

        // Get instructions array base pointer.
        Instruction * GetInstructions()
        {
            if (instructions_.empty())
                return 0;
            return &instructions_[0];
        }

        // Get total instructions count.
        std::size_t GetInstructionCount() const
        {
            return instructions_.size();
        }

    private:
        std::vector<Instruction> instructions_;
    };
} // namespace lua

#endif // INSTRUCTION_H