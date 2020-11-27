#pragma once

#include "Common/Challenge.h"

class CChallenge_03 : public CChallenge
{
private:
    struct SPoint
    {
        int m_x = 0;
        int m_y = 0;

        int GetManhattanDistance(SPoint const& otherPoint) const;
    };

    struct SSegment
    {
        SPoint m_pointA;
        SPoint m_pointB;

        int m_length = 0;
        int m_axisAlignedCoordinate = 0;
        bool m_isVertical = false;

        bool Intersects(SSegment const& otherLine, SPoint& outIntersectionPoint) const;
    };

    virtual EErrorCode SetUp_FirstPart() override;
    virtual EErrorCode Run_FirstPart() override;
    virtual EErrorCode CleanUp_FirstPart() override;

    virtual EErrorCode SetUp_SecondPart() override;
    virtual EErrorCode Run_SecondPart() override;
    virtual EErrorCode CleanUp_SecondPart() override;

    static SSegment* MakeWireFromString(std::string const& wireString, size_t& outWireSize);

    static std::string const sm_inputFilePath;

    SSegment* m_firstWire = nullptr;
    SSegment* m_secondWire = nullptr;

    size_t m_firstWireSize = 0;
    size_t m_secondWireSize = 0;
};
