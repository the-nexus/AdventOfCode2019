#include "IntcodeProgram.h"


CIntcodeProgram::~CIntcodeProgram()
{
    if (m_memory != nullptr)
    {
        delete[] m_memory;
    }
}

void CIntcodeProgram::ResetProgram()
{
    m_operationIdx = 0;
    m_terminated = false;

    while (!m_inputQueue.empty())
    {
        m_inputQueue.pop();
    }

    while (!m_outputQueue.empty())
    {
        m_outputQueue.pop();
    }

    if (m_initialMemory && m_memory)
    {
        for (size_t memoryIdx = 0; memoryIdx < m_memorySize; ++memoryIdx)
        {
            m_memory[memoryIdx] = m_initialMemory[memoryIdx];
        }
    }
}

int CIntcodeProgram::GetMemoryAt(size_t const memoryIdx) const
{
    if (m_memory && memoryIdx < m_memorySize)
    {
        return m_memory[memoryIdx];
    }
    return 0;
}

void CIntcodeProgram::SetMemoryAt(size_t const memoryIdx, int const memory)
{
    if (m_memory && memoryIdx < m_memorySize)
    {
        m_memory[memoryIdx] = memory;
    }
}

void CIntcodeProgram::SetInitialMemory(int const* memory, size_t const memorySize)
{
    if (m_initialMemory != nullptr)
    {
        delete[] m_initialMemory;
        delete[] m_memory;
        m_memorySize = 0;
    }

    if (memory != nullptr && memorySize > 0)
    {
        m_memorySize = memorySize;
        m_initialMemory = new int[memorySize];
        m_memory = new int[memorySize];

        for (size_t memoryIdx = 0; memoryIdx < memorySize; ++memoryIdx)
        {
            m_initialMemory[memoryIdx] = memory[memoryIdx];
            m_memory[memoryIdx] = memory[memoryIdx];
        }
    }
}

EErrorCode CIntcodeProgram::RunNextOperation()
{
    if (!m_terminated && m_memory && m_memorySize > 0)
    {
        int const paramModes = m_memory[m_operationIdx] / 100;
        int const opcode = m_memory[m_operationIdx] % 100;

        switch (opcode)
        {
        case 1:
            Add(paramModes);
            break;

        case 2:
            Multiply(paramModes);
            break;

        case 3:
            ReadInput();
            break;

        case 4:
            WriteOutput(paramModes);
            break;

        case 5:
            JumpIfNotZero(paramModes);
            break;

        case 6:
            JumpIfZero(paramModes);
            break;

        case 7:
            CompareIsLesser(paramModes);
            break;

        case 8:
            CompareIsEqual(paramModes);
            break;

        case 99:
            m_terminated = true;
            break;

        default:
            return EErrorCode::Undefined;
        }
    }

    return EErrorCode::Success;
}

int CIntcodeProgram::GetParameterMode(int const parameterModes, int const positionIdx) const
{
    return (parameterModes / static_cast<int>(pow(10, positionIdx))) % 10;
}

void CIntcodeProgram::Add(int const paramModes)
{
    size_t const readMemoryIdxA = GetParameterMode(paramModes, 0) > 0 ? m_operationIdx + 1 : m_memory[m_operationIdx + 1];
    size_t const readMemoryIdxB = GetParameterMode(paramModes, 1) > 0 ? m_operationIdx + 2 : m_memory[m_operationIdx + 2];
    size_t const writeMemoryIdx = m_memory[m_operationIdx + 3];

    m_memory[writeMemoryIdx] = m_memory[readMemoryIdxA] + m_memory[readMemoryIdxB];
    m_operationIdx += 4;
}

void CIntcodeProgram::Multiply(int const paramModes)
{
    size_t const readMemoryIdxA = GetParameterMode(paramModes, 0) > 0 ? m_operationIdx + 1 : m_memory[m_operationIdx + 1];
    size_t const readMemoryIdxB = GetParameterMode(paramModes, 1) > 0 ? m_operationIdx + 2 : m_memory[m_operationIdx + 2];
    size_t const writeMemoryIdx = m_memory[m_operationIdx + 3];

    m_memory[writeMemoryIdx] = m_memory[readMemoryIdxA] * m_memory[readMemoryIdxB];
    m_operationIdx += 4;
}

void CIntcodeProgram::ReadInput()
{
    size_t const writeMemoryIdx = m_memory[m_operationIdx + 1];

    if (m_inputQueue.size() > 0)
    {
        m_memory[writeMemoryIdx] = m_inputQueue.front();
        m_inputQueue.pop();
        m_operationIdx += 2;
    }
}

void CIntcodeProgram::WriteOutput(int const paramModes)
{
    size_t const readMemoryIdx = GetParameterMode(paramModes, 0) > 0 ? m_operationIdx + 1 : m_memory[m_operationIdx + 1];

    m_outputQueue.push(m_memory[readMemoryIdx]);
    m_operationIdx += 2;
}

void CIntcodeProgram::JumpIfNotZero(int const paramModes)
{
    size_t const readMemoryIdxA = GetParameterMode(paramModes, 0) > 0 ? m_operationIdx + 1 : m_memory[m_operationIdx + 1];
    size_t const readMemoryIdxB = GetParameterMode(paramModes, 1) > 0 ? m_operationIdx + 2 : m_memory[m_operationIdx + 2];

    if (m_memory[readMemoryIdxA] != 0)
    {
        m_operationIdx = m_memory[readMemoryIdxB];
    }
    else
    {
        m_operationIdx += 3;
    }
}

void CIntcodeProgram::JumpIfZero(int const paramModes)
{
    size_t const readMemoryIdxA = GetParameterMode(paramModes, 0) > 0 ? m_operationIdx + 1 : m_memory[m_operationIdx + 1];
    size_t const readMemoryIdxB = GetParameterMode(paramModes, 1) > 0 ? m_operationIdx + 2 : m_memory[m_operationIdx + 2];

    if (m_memory[readMemoryIdxA] == 0)
    {
        m_operationIdx = m_memory[readMemoryIdxB];
    }
    else
    {
        m_operationIdx += 3;
    }
}

void CIntcodeProgram::CompareIsLesser(int const paramModes)
{
    size_t const readMemoryIdxA = GetParameterMode(paramModes, 0) > 0 ? m_operationIdx + 1 : m_memory[m_operationIdx + 1];
    size_t const readMemoryIdxB = GetParameterMode(paramModes, 1) > 0 ? m_operationIdx + 2 : m_memory[m_operationIdx + 2];
    size_t const writeMemoryIdx = m_memory[m_operationIdx + 3];

    m_memory[writeMemoryIdx] = m_memory[readMemoryIdxA] < m_memory[readMemoryIdxB] ? 1 : 0;
    m_operationIdx += 4;
}

void CIntcodeProgram::CompareIsEqual(int const paramModes)
{
    size_t const readMemoryIdxA = GetParameterMode(paramModes, 0) > 0 ? m_operationIdx + 1 : m_memory[m_operationIdx + 1];
    size_t const readMemoryIdxB = GetParameterMode(paramModes, 1) > 0 ? m_operationIdx + 2 : m_memory[m_operationIdx + 2];
    size_t const writeMemoryIdx = m_memory[m_operationIdx + 3];

    m_memory[writeMemoryIdx] = m_memory[readMemoryIdxA] == m_memory[readMemoryIdxB] ? 1 : 0;
    m_operationIdx += 4;
}
