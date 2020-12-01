#include "IntcodeProgram.h"


CIntcodeProgram::~CIntcodeProgram()
{
    if (m_memory != nullptr)
    {
        delete[] m_memory;
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

void CIntcodeProgram::SetMemory(int const* memory, size_t const memorySize)
{
    if (m_memory != nullptr)
    {
        delete[] m_memory;
        m_memorySize = 0;
    }

    if (memory != nullptr && memorySize > 0)
    {
        m_memorySize = memorySize;
        m_memory = new int[memorySize];
        for (size_t memoryIdx = 0; memoryIdx < memorySize; ++memoryIdx)
        {
            m_memory[memoryIdx] = memory[memoryIdx];
        }
    }
}

EErrorCode CIntcodeProgram::Run()
{
    if (!m_memory || m_memorySize == 0)
    {
        return EErrorCode::Undefined;
    }

    size_t memoryIdx = 0;
    bool exitProgram = false;

    while (!exitProgram && memoryIdx < m_memorySize)
    {
        int const paramModes = m_memory[memoryIdx] / 100;
        int const opcode = m_memory[memoryIdx] % 100;

        switch (m_memory[memoryIdx])
        {
        case 01: Add(paramModes, memoryIdx); break;
        case 02: Multiply(paramModes, memoryIdx); break;
        case 99: exitProgram = true; break;

        default: return EErrorCode::Undefined;
        }
    }

    return EErrorCode::Success;
}

int CIntcodeProgram::GetParameterMode(int const parameterModes, int const positionIdx) const
{
    return (parameterModes / static_cast<int>(pow(10, positionIdx))) % 10;
}

void CIntcodeProgram::Add(int const paramModes, size_t& memoryIdx)
{
    size_t readMemoryIdxA = GetParameterMode(paramModes, 0) > 0 ? memoryIdx + 1 : m_memory[memoryIdx + 1];
    size_t readMemoryIdxB = GetParameterMode(paramModes, 1) > 0 ? memoryIdx + 2 : m_memory[memoryIdx + 2];
    size_t writeMemoryIdx = m_memory[memoryIdx + 3];

    m_memory[writeMemoryIdx] = m_memory[readMemoryIdxA] + m_memory[readMemoryIdxB];
    memoryIdx += 4;
}

void CIntcodeProgram::Multiply(int const paramModes, size_t& memoryIdx)
{
    size_t readMemoryIdxA = m_memory[memoryIdx + 1];
    size_t readMemoryIdxB = m_memory[memoryIdx + 2];
    size_t writeMemoryIdx = m_memory[memoryIdx + 3];

    m_memory[writeMemoryIdx] = m_memory[readMemoryIdxA] * m_memory[readMemoryIdxB];
    memoryIdx += 4;
}
