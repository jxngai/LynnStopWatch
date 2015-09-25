#include "znControllerUi.h"
#include "znTimeThread.h"
#include "znDialogAbout.h"
#include "znConstants.h"
#include "znModel.h"

#include <wx/frame.h>
#include <wx/button.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
#include <wx/log.h>

znControllerUi::znControllerUi() : m_time_thread(NULL)
{
}

znControllerUi::~znControllerUi()
{
    wxLogDebug(wxT("<<< znControllerUi::~znControllerUi() >>>"));
}

void znControllerUi::OnClose(wxCloseEvent& event)
{
	wxLogDebug(wxT("znControllerUi::OnClose()"));

	// Kill a thread whether it is running or not.
	// Note that after returning from the call,
	// m_time_thread object is deleted and
	// m_time_thread will be set to NULL.

	znTimeThread::TerminateThread(m_time_thread);

	// Need to Skip() so that the event can continue to be processed.
	event.Skip();
}

void znControllerUi::OnAbout(wxCommandEvent& event)
{
	wxLogDebug(wxT("znControllerUi::OnAbout()"));

	if (znDialogAbout().ShowModal() == wxID_OK)
	{
	}
}

void znControllerUi::OnResetLapTimer(wxCommandEvent& event)
{
	wxButton *button = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_BTN_RESET_LAP_TIMER), wxButton);

	if (button != NULL)
	{
		if (button->GetLabel() == wxT("Reset"))
		{
            znSingleton::GetInstance<znModel>().Initialize();

			wxStaticText *static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_M1), wxStaticText);
			if (static_text != NULL) static_text->SetLabel(wxT("0"));

			static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_M2), wxStaticText);
			if (static_text != NULL) static_text->SetLabel(wxT("0"));

			static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_S1), wxStaticText);
			if (static_text != NULL) static_text->SetLabel(wxT("0"));

			static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_S2), wxStaticText);
			if (static_text != NULL) static_text->SetLabel(wxT("0"));

			static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_U1), wxStaticText);
			if (static_text != NULL) static_text->SetLabel(wxT("0"));

			wxTextCtrl *text_control = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_TXT_OUTPUT_TEXT), wxTextCtrl);
			if (text_control != NULL) text_control->Clear();
		}
		else
		{
			// Lap.
			znSingleton::GetInstance<znModel>().SetEndTime();
			znSingleton::GetInstance<znModel>().IncrementLapCounter();

			wxTimeSpan time_diff = znSingleton::GetInstance<znModel>().GetTimeDifference();
			wxTimeSpan time_diff_lap = znSingleton::GetInstance<znModel>().GetTimeDifferenceCurrentLap();

			znSingleton::GetInstance<znModel>().SetOffsetTime();
			znSingleton::GetInstance<znModel>().SetStartTime(znSingleton::GetInstance<znModel>().GetEndTime());  // Need to make sure the end time and start time are atomic.
			znSingleton::GetInstance<znModel>().ClearOffsetTimeLap();

			wxString str = wxString::Format(wxT("Lap %d :"), znSingleton::GetInstance<znModel>().GetLapCounter()) + time_diff.Format(wxT("%M:%S.%l"));
			str.RemoveLast();
			str.RemoveLast();
			str += wxT(" ... ") + time_diff_lap.Format(wxT("%M:%S.%l"));
			str.RemoveLast();
			str.RemoveLast();
			str += wxT("\n");

			wxTextCtrl *text_control = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_TXT_OUTPUT_TEXT), wxTextCtrl);
			if (text_control != NULL) text_control->SetValue(str + text_control->GetValue());
			// text_control->SetInsertionPointEnd();
		}
	}
}

void znControllerUi::OnStartStopTimer(wxCommandEvent& event)
{
	wxLogDebug(wxT("znControllerUi::OnStartStopTimer()"));

	wxButton *button = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_BTN_START_STOP_TIMER), wxButton);

	if (button != NULL)
	{
		if (button->GetLabel() == wxT("Start"))
		{
			// Start the timer
			znTimeThread::StartThread(m_time_thread);

			if (m_time_thread != NULL)
			{
                // The timer has been started successfully.

                znSingleton::GetInstance<znModel>().SetStartTime();

				button->SetLabel(wxT("Stop"));

				button = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_BTN_RESET_LAP_TIMER), wxButton);
				if (button != NULL) button->SetLabel(wxT("Lap"));
			}
		}
		else
		{
			// Stop the timer.
			znTimeThread::TerminateThread(m_time_thread);

			button->SetLabel(wxT("Start"));

			button = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_BTN_RESET_LAP_TIMER), wxButton);
			if (button != NULL) button->SetLabel(wxT("Reset"));
		}
	}
}

void znControllerUi::OnUpdateTimer(wxThreadEvent& event)
{
	wxLogDebug(wxT("<<< znControllerUi::OnUpdateTimer() >>>"));

	znSingleton::GetInstance<znModel>().SetEndTime();

	int miliseconds = (znSingleton::GetInstance<znModel>().GetTimeDifferenceInMilliseconds()) % 1000;

	int ms2 = miliseconds % 100;
	int ms1 = (miliseconds - ms2) / 100;

	wxStaticText *static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_U1), wxStaticText);
	if (static_text != NULL &&
		wxString::Format(wxT("%1d"), ms1) != static_text->GetLabel())
		static_text->SetLabel(wxString::Format(wxT("%1d"), ms1));

	int seconds = (znSingleton::GetInstance<znModel>().GetTimeDifferenceInSeconds()) % 60;

	int s2 = seconds % 10;
	int s1 = (seconds / 10) % 10;

	static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_S2), wxStaticText);
	if (static_text != NULL &&
		wxString::Format(wxT("%1d"), s2) != static_text->GetLabel())
		static_text->SetLabel(wxString::Format(wxT("%1d"), s2));

	static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_S1), wxStaticText);
	if (static_text != NULL &&
		wxString::Format(wxT("%1d"), s1) != static_text->GetLabel())
		static_text->SetLabel(wxString::Format(wxT("%1d"), s1));

	int minutes = (znSingleton::GetInstance<znModel>().GetTimeDifferenceInSeconds() / 60);

	int m2 = minutes % 10;
	int m1 = (minutes / 10) % 10;

	static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_M2), wxStaticText);
	if (static_text != NULL &&
		wxString::Format(wxT("%1d"), m2) != static_text->GetLabel())
		static_text->SetLabel(wxString::Format(wxT("%1d"), m2));

	static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_M1), wxStaticText);
	if (static_text != NULL &&
		wxString::Format(wxT("%1d"), m1) != static_text->GetLabel())
		static_text->SetLabel(wxString::Format(wxT("%1d"), m1));
}

void znControllerUi::OnTimerThreadCompletion(wxThreadEvent& event)
{
	wxLogDebug(wxT("<<< znControllerUi::OnTimerThreadCompletion() >>>"));

	znSingleton::GetInstance<znModel>().SetEndTime();
	znSingleton::GetInstance<znModel>().SetOffsetTime();
	znSingleton::GetInstance<znModel>().SetOffsetTimeLap();

	znTimeThread::TerminateThread(m_time_thread);

	wxLogDebug(wxT("<<< znControllerUi::OnTimerThreadCompletion() >>> .. Done"));
}

wxBEGIN_EVENT_TABLE(znControllerUi, wxEvtHandler)
	EVT_CLOSE(znControllerUi::OnClose)

	EVT_COMMAND(ID_ZN_BTN_ABOUT, wxEVT_COMMAND_BUTTON_CLICKED, znControllerUi::OnAbout)
    EVT_COMMAND(ID_ZN_BTN_RESET_LAP_TIMER, wxEVT_COMMAND_BUTTON_CLICKED, znControllerUi::OnResetLapTimer)
	EVT_COMMAND(ID_ZN_BTN_START_STOP_TIMER, wxEVT_COMMAND_BUTTON_CLICKED, znControllerUi::OnStartStopTimer)

	EVT_THREAD(ID_ZN_EVENT_TIME_THREAD_TICK, znControllerUi::OnUpdateTimer)
	EVT_THREAD(ID_ZN_EVENT_TIME_THREAD_COMPLETED, znControllerUi::OnTimerThreadCompletion)
wxEND_EVENT_TABLE()