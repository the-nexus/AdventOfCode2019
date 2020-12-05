#include "Challenge_09.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_09::sm_inputFilePath = "Inputs/Input_Challenge_09.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_09::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_09::Run_FirstPart()
{
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_09::CleanUp_FirstPart()
{
    return EErrorCode::NotImplemented;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_09::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }
    
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_09::Run_SecondPart()
{
    return EErrorCode::NotImplemented;
}

EErrorCode CChallenge_09::CleanUp_SecondPart()
{
    return EErrorCode::NotImplemented;
}
