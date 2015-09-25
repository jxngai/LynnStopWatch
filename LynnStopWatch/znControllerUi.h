#ifndef ZNCONTROLLERUI_H
#define ZNCONTROLLERUI_H

#include "znSingleton.h"
#include "znTimeThread.h"

#include <wx/event.h>
#include <wx/window.h>
#include <wx/control.h>

class znControllerUi : public wxEvtHandler, public znSingleton
{
private:
    friend znSingleton;

	znControllerUi();
	wxDECLARE_NO_COPY_CLASS(znControllerUi);
	~znControllerUi();

private:
	void OnClose(wxCloseEvent& event);
	void OnAbout(wxCommandEvent& event);

	void OnUpdateTimer(wxThreadEvent& event);
	void OnTimerThreadCompletion(wxThreadEvent& event);

public:

	void OnResetLapTimer(wxCommandEvent& event);
	void OnStartStopTimer(wxCommandEvent& event);

protected:
	znTimeThread        *m_time_thread;

private:
	wxDECLARE_EVENT_TABLE();
};

#endif