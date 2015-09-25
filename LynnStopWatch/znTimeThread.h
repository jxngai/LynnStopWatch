#ifndef ZNTIMETHREAD_H
#define ZNTIMETHREAD_H

#include <wx/thread.h>

class znTimeThread : private wxThread
{
    znTimeThread();
	~znTimeThread();

    wxThread::ExitCode Entry();
    void OnExit();

	bool TestDestroy();
	void DestroyThread();

public:
    static void StartThread(znTimeThread *&);
    static void TerminateThread(znTimeThread *&);

private:
	bool					m_flag_abort;
	wxCriticalSection		m_cs_flag_abort;
};

#endif