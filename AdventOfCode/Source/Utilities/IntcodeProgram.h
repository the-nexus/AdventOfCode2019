#pragma once
#include "../CommonDefinitions.h"

class CIntcodeProgram
{
public:
    ~CIntcodeProgram();

    int GetMemoryAt(size_t const memoryIdx) const;
    void SetMemoryAt(size_t const memoryIdx, int const memory);
    void SetMemory(int const* memory, size_t const memorySize);
    EErrorCode Run();

private:
    int GetParameterMode(int const parameterModes, int const positionIdx) const;

    void Add(int const paramModes, size_t& memoryIdx);
    void Multiply(int const paramModes, size_t& memoryIdx);

    int* m_memory = nullptr;
    size_t m_memorySize = 0;
};
