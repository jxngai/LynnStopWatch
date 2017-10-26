#include "znTimeThread.h"
#include "znConstants.h"
#include "znControllerUi.h"

#include <wx/log.h>

// This is a timer that keeps ticking.

znTimeThread::znTimeThread()
	: wxThread(wxTHREAD_JOINABLE), m_flag_abort(false)
{
    Run();
}

znTimeThread::~znTimeThread()
{
	wxLogDebug(wxT("<<< znTimeThread::~znTimeThread() >>>"));

    // Set the abort flag.
    {
        wxCriticalSectionLocker locker(m_flag_abort_cs);
        m_flag_abort = true;
    }

    // The Wait() function is like a join() in other framework.
    // wxThread::Wait() for the thread will wait for the return
    //  from both OnEntry() and OnExit().
    Wait();
}

wxThread::ExitCode znTimeThread::Entry()
{
    wxLogDebug(wxT("<<< znTimeThread::Entry() >>>"));

	while (TestDestroy() == false)
    {
        Sleep(50);

		if (TestDestroy() == true)
		{
			break;
		}

        // Post a event to the frame for every clock tick.

        znSingleton::GetInstance<znControllerUi>().QueueEvent(new wxThreadEvent(wxEVT_THREAD, ID_ZN_EVENT_TIME_THREAD_TICK));
    }

    wxLogDebug(wxT("<<< znTimeThread::Entry() >>> ... Done"));

    return (wxThread::ExitCode)0;                 // success
}

void znTimeThread::OnExit()
{
    wxLogDebug(wxT("<<< znTimeThread::OnExit() >>>"));
    // Post a thread completion event.

    znSingleton::GetInstance<znControllerUi>().QueueEvent(new wxThreadEvent(wxEVT_THREAD, ID_ZN_EVENT_TIME_THREAD_COMPLETED));
}

bool znTimeThread::TestDestroy()
{
    if (wxThread::TestDestroy() == true) return true;

    wxCriticalSectionLocker locker(m_flag_abort_cs);
    return m_flag_abort;
}

