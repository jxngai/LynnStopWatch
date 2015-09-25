#ifndef ZNAPP_H
#define ZNAPP_H

#include "znSingletonParent.h"

#include <wx/app.h>

class znApp : public wxApp, public znSingletonParent
{
private:
    virtual bool OnInit();

    void OnKeyDown(wxKeyEvent& event);

public:
    void Test() { wxLogDebug(wxT("<<< znApp::Test() >>>")); }

private:
    wxDECLARE_EVENT_TABLE();
};

wxDECLARE_APP(znApp);

#endif