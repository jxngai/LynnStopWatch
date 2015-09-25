#include "znModel.h"

znModel::znModel()
{
    wxLogDebug(wxT("<<< znModel::znModel() >>>"));

    Initialize();
}

znModel::~znModel()
{
    wxLogDebug(wxT("<<< znModel::~znModel() >>>"));
}

void znModel::Initialize()
{
    m_time_start = wxDefaultDateTime;
    m_time_end = wxDefaultDateTime;

    m_time_lap_offset = 0;
    m_time_span_offset = 0;

    m_lap_count = 0;
}

void znModel::SetStartTime(wxDateTime date)
{
    if (date.IsValid() == false)
    {
        m_time_start = wxDateTime::UNow();
    }
    else
    {
        m_time_start = date;
    }
}

void znModel::SetEndTime()
{
    m_time_end = wxDateTime::UNow();
}

wxDateTime znModel::GetEndTime()
{
    return m_time_end;
}

void znModel::SetOffsetTime()
{
    wxTimeSpan time_diff = (m_time_end - m_time_start + m_time_span_offset);

    m_time_span_offset = time_diff;
}

void znModel::SetOffsetTimeLap()
{
    m_time_lap_offset = wxDateTime::UNow() - m_time_start;
}

void znModel::ClearOffsetTimeLap()
{
    m_time_lap_offset = 0;
}

void znModel::ClearLapCounter()
{
    m_lap_count = 0;
}

void znModel::IncrementLapCounter()
{
    m_lap_count++;
}

int znModel::GetLapCounter()
{
    return m_lap_count;
}

wxTimeSpan znModel::GetTimeDifferenceCurrentLap()
{
    wxTimeSpan time_diff = (m_time_end - m_time_start + m_time_lap_offset);

    return time_diff;
}

wxTimeSpan znModel::GetTimeDifference()
{
    wxTimeSpan time_diff = (m_time_end - m_time_start + m_time_span_offset);

    return time_diff;
}

int znModel::GetTimeDifferenceInSeconds()
{
    wxTimeSpan time_diff = (m_time_end - m_time_start + m_time_span_offset);

    return time_diff.GetSeconds().ToLong();
}

int znModel::GetTimeDifferenceInMilliseconds()
{
    wxTimeSpan time_diff = (m_time_end - m_time_start + m_time_span_offset);

    return time_diff.GetMilliseconds().ToLong();
}