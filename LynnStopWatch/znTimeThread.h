#ifndef ZNTIMETHREAD_H
#define ZNTIMETHREAD_H

#include <wx/thread.h>

class znTimeThread : private wxThread
{
public:
    znTimeThread();
	~znTimeThread();

private:
    wxThread::ExitCode Entry();
    void OnExit();

	bool TestDestroy();

private:
	bool					    m_flag_abort;
	wxCriticalSection		m_flag_abort_cs;
};

#endif