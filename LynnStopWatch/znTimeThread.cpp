#include "znTimeThread.h"
#include "znConstants.h"
#include "znControllerUi.h"

#include <wx/log.h>

// This is a timer that keeps ticking.

znTimeThread::znTimeThread()
	: wxThread(wxTHREAD_JOINABLE), m_flag_abort(false)
{
}

znTimeThread::~znTimeThread()
{
	wxLogDebug(wxT("<<< znTimeThread::~znTimeThread() >>>"));
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

void znTimeThread::DestroyThread()
{
	wxCriticalSectionLocker locker(m_cs_flag_abort);
	m_flag_abort = true;
}

bool znTimeThread::TestDestroy()
{
	if (wxThread::TestDestroy() == true) return true;

	wxCriticalSectionLocker locker(m_cs_flag_abort);
	if (m_flag_abort == true) return true;

	return false;
}

void znTimeThread::StartThread(znTimeThread*& thread_ptr)
{
    // Only start the thread when thread_ptr is NULL.

    if (thread_ptr != NULL)
    {
        return;
    }

    thread_ptr = new znTimeThread();

    if (thread_ptr != NULL)
    {
        if (thread_ptr->Create() != wxTHREAD_NO_ERROR)
        {
            delete thread_ptr;
            thread_ptr = NULL;
        }
        else if (thread_ptr->Run() != wxTHREAD_NO_ERROR)
        {
            delete thread_ptr;
            thread_ptr = NULL;
        }
    }

    if (thread_ptr == NULL)
    {
        // For some reason, the thread fail to start.
        return;
    }
}


void znTimeThread::TerminateThread(znTimeThread *& thread_ptr)
{
	wxLogDebug(wxT("<<< znTimeThread::TerminateThread() >>>"));

    // User can call this static function to kill a running thread.
    // This routine will take care of the case whether the thread is running or not.
    // This is a blocking function.

    if (thread_ptr == NULL)
    {
        // Thread has already been terminated OR
        // in the process of being terminated.
        return;
    }

	// Keep a copy of the thread pointer.
	// Set the original thread_ptr to NULL.
	// So that the next time this routine is re-entered, it will
	// will return immediately.
	znTimeThread *cache_thread_ptr = thread_ptr;
	thread_ptr = NULL;

	// While waiting, thread completion event can come in.
	// With the cached copy of the pointer, we can take
	// our time to terminate the thread.

    // The wait function is like a join() in other framework.
	cache_thread_ptr->DestroyThread();
	cache_thread_ptr->Wait();
	delete cache_thread_ptr;
}