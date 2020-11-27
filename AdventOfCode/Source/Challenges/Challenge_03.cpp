#include "Challenge_03.h"
#include "../Helpers/FileHelpers.h"



////////////////////////////////////////////////////////////////////////////////////////////////////
std::string const CChallenge_03::sm_inputFilePath = "Inputs/Input_Challenge_03.txt";



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_03::SetUp_FirstPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_firstWire = MakeWireFromString(lines[0], m_firstWireSize);
    m_secondWire = MakeWireFromString(lines[1], m_secondWireSize);
    return EErrorCode::Success;
}

EErrorCode CChallenge_03::Run_FirstPart()
{
    SPoint centerPoint;
    unsigned int shortestIntersectionDistance = -1; // max unsigned int

    for (size_t firstSegmentIdx = 0; firstSegmentIdx < m_firstWireSize; ++firstSegmentIdx)
    {
        SSegment const& firstSegment = m_firstWire[firstSegmentIdx];

        for (size_t secondSegmentIdx = 0; secondSegmentIdx < m_secondWireSize; ++secondSegmentIdx)
        {
            SSegment const& secondSegment = m_secondWire[secondSegmentIdx];

            SPoint intersection;
            if (secondSegment.Intersects(firstSegment, intersection))
            {
                unsigned int const intersectionDistance = intersection.GetManhattanDistance(centerPoint);
                if (intersectionDistance < shortestIntersectionDistance)
                {
                    shortestIntersectionDistance = intersectionDistance;
                }
            }
        }
    }

    std::cout << "Shortest intersection distance = " << shortestIntersectionDistance << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_03::CleanUp_FirstPart()
{
    delete[] m_firstWire;
    delete[] m_secondWire;
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
EErrorCode CChallenge_03::SetUp_SecondPart()
{
    std::vector<std::string> lines;
    EErrorCode const readErrorCode = FileHelper::ReadLines(sm_inputFilePath, lines);
    if (readErrorCode != EErrorCode::Success)
    {
        return readErrorCode;
    }

    m_firstWire = MakeWireFromString(lines[0], m_firstWireSize);
    m_secondWire = MakeWireFromString(lines[1], m_secondWireSize);
    return EErrorCode::Success;
}

EErrorCode CChallenge_03::Run_SecondPart()
{
    SPoint centerPoint;
    unsigned int shortestIntersectionTravelDistance = -1; // max unsigned int

    unsigned int firstTravelDistance = 0;
    for (size_t firstSegmentIdx = 0; firstSegmentIdx < m_firstWireSize; ++firstSegmentIdx)
    {
        SSegment const& firstSegment = m_firstWire[firstSegmentIdx];

        unsigned int secondTravelDistance = 0;
        for (size_t secondSegmentIdx = 0; secondSegmentIdx < m_secondWireSize; ++secondSegmentIdx)
        {
            SSegment const& secondSegment = m_secondWire[secondSegmentIdx];

            SPoint intersection;
            if (secondSegment.Intersects(firstSegment, intersection))
            {
                unsigned int const adjustedFirstTravelDistance = firstTravelDistance + firstSegment.m_pointA.GetManhattanDistance(intersection);
                unsigned int const adjustedSecondTravelDistance = secondTravelDistance + secondSegment.m_pointA.GetManhattanDistance(intersection);
                unsigned int const totalTravelDistance = adjustedFirstTravelDistance + adjustedSecondTravelDistance;

                if (totalTravelDistance < shortestIntersectionTravelDistance)
                {
                    shortestIntersectionTravelDistance = totalTravelDistance;
                }
            }

            secondTravelDistance += secondSegment.m_length;
        }

        firstTravelDistance += firstSegment.m_length;
    }

    std::cout << "Shortest intersection travel distance = " << shortestIntersectionTravelDistance << std::endl;
    return EErrorCode::Success;
}

EErrorCode CChallenge_03::CleanUp_SecondPart()
{
    delete[] m_firstWire;
    delete[] m_secondWire;
    return EErrorCode::Success;
}



////////////////////////////////////////////////////////////////////////////////////////////////////
int CChallenge_03::SPoint::GetManhattanDistance(SPoint const& otherPoint) const
{
    return abs(m_x - otherPoint.m_x) + abs(m_y - otherPoint.m_y);
}

bool CChallenge_03::SSegment::Intersects(SSegment const& otherLine, SPoint& outIntersectionPoint) const
{
    if (m_isVertical != otherLine.m_isVertical)
    {
        if (m_isVertical)
        {
            if ((otherLine.m_pointA.m_x < m_axisAlignedCoordinate && m_axisAlignedCoordinate < otherLine.m_pointB.m_x) ||
                (otherLine.m_pointB.m_x < m_axisAlignedCoordinate && m_axisAlignedCoordinate < otherLine.m_pointA.m_x))
            {
                if ((m_pointA.m_y < otherLine.m_axisAlignedCoordinate && otherLine.m_axisAlignedCoordinate < m_pointB.m_y) ||
                    (m_pointB.m_y < otherLine.m_axisAlignedCoordinate && otherLine.m_axisAlignedCoordinate < m_pointA.m_y))
                {
                    outIntersectionPoint.m_x = m_axisAlignedCoordinate;
                    outIntersectionPoint.m_y = otherLine.m_axisAlignedCoordinate;
                    return true;
                }
            }
        }
        else
        {
            if ((otherLine.m_pointA.m_y < m_axisAlignedCoordinate && m_axisAlignedCoordinate < otherLine.m_pointB.m_y) ||
                (otherLine.m_pointB.m_y < m_axisAlignedCoordinate && m_axisAlignedCoordinate < otherLine.m_pointA.m_y))
            {
                if ((m_pointA.m_x < otherLine.m_axisAlignedCoordinate && otherLine.m_axisAlignedCoordinate < m_pointB.m_x) ||
                    (m_pointB.m_x < otherLine.m_axisAlignedCoordinate && otherLine.m_axisAlignedCoordinate < m_pointA.m_x))
                {
                    outIntersectionPoint.m_x = otherLine.m_axisAlignedCoordinate;
                    outIntersectionPoint.m_y = m_axisAlignedCoordinate;
                    return true;
                }
            }
        }
    }

    return false;
}

CChallenge_03::SSegment* CChallenge_03::MakeWireFromString(std::string const& wireString, size_t& outWireSize)
{
    std::vector<std::string> segmentStrings;
    FileHelper::SplitLine(wireString, ",", segmentStrings);

    size_t const segmentCount = segmentStrings.size();
    SSegment* wire = new SSegment[segmentCount];
    outWireSize = segmentCount;

    SPoint currentPoint;
    for (size_t segmentIdx = 0; segmentIdx < segmentCount; ++segmentIdx)
    {
        std::string const& segmentString = segmentStrings[segmentIdx];
        SSegment& segment = wire[segmentIdx];

        char const segmentDirection = segmentString[0];
        int const segmentLength = atoi(segmentString.substr(1).c_str());

        segment.m_pointA = currentPoint;

        // Positive axis : Up, Right
        switch (segmentDirection)
        {
        case 'L':
            segment.m_isVertical = false;
            currentPoint.m_x -= segmentLength;
            break;

        case 'R':
            segment.m_isVertical = false;
            currentPoint.m_x += segmentLength;
            break;

        case 'D':
            segment.m_isVertical = true;
            currentPoint.m_y -= segmentLength;
            break;

        case 'U':
            segment.m_isVertical = true;
            currentPoint.m_y += segmentLength;
            break;
        }

        segment.m_axisAlignedCoordinate = segment.m_isVertical ? currentPoint.m_x : currentPoint.m_y;
        segment.m_pointB = currentPoint;
        segment.m_length = segmentLength;
    }

    return wire;
}
