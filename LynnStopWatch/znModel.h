#ifndef ZNMODEL_H
#define ZNMODEL_H

#include "znSingleton.h"

#include <wx/datetime.h>

class znModel : public znSingleton
{
private:
    friend znSingleton;

    znModel();
    wxDECLARE_NO_COPY_CLASS(znModel);
    ~znModel();

public:
    void Initialize();

    void SetStartTime(wxDateTime date = wxInvalidDateTime);
    void SetEndTime();
    wxDateTime GetEndTime();

    void SetOffsetTime();
    void SetOffsetTimeLap();
    void ClearOffsetTimeLap();

    void ClearLapCounter();
    void IncrementLapCounter();
    int  GetLapCounter();

    wxTimeSpan GetTimeDifference();
    int GetTimeDifferenceInSeconds();
    int GetTimeDifferenceInMilliseconds();

    wxTimeSpan GetTimeDifferenceCurrentLap();

private:
    int         m_lap_count;

    wxDateTime  m_time_start;
    wxDateTime  m_time_end;

    wxTimeSpan  m_time_lap_offset;
    wxTimeSpan  m_time_span_offset;
};

#endif