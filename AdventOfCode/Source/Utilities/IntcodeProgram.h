#pragma once
#include "../CommonDefinitions.h"
#include <queue>

class CIntcodeProgram
{
public:
    ~CIntcodeProgram();

    void ResetProgram();

    int GetMemoryAt(size_t const memoryIdx) const;
    void SetMemoryAt(size_t const memoryIdx, int const memory);
    void SetInitialMemory(int const* memory, size_t const memorySize);

    bool HasInput() const { return !m_inputQueue.empty(); }
    void PushInput(int const inputValue) { return m_inputQueue.push(inputValue); }

    bool HasOutput() const { return !m_outputQueue.empty(); }
    int PopOutput() { int const outputValue = m_outputQueue.front(); m_outputQueue.pop(); return outputValue; }

    bool HasTerminated() const { return m_terminated; }

    EErrorCode RunNextOperation();

private:
    int GetParameterMode(int const parameterModes, int const positionIdx) const;

    void Add(int const paramModes);
    void Multiply(int const paramModes);
    void ReadInput();
    void WriteOutput(int const paramModes);
    void JumpIfNotZero(int const paramModes);
    void JumpIfZero(int const paramModes);
    void CompareIsLesser(int const paramModes);
    void CompareIsEqual(int const paramModes);

    int* m_initialMemory = nullptr;
    int* m_memory = nullptr;
    size_t m_memorySize = 0;

    size_t m_operationIdx = 0;
    bool m_terminated = false;

    std::queue<int> m_inputQueue;
    std::queue<int> m_outputQueue;
};
