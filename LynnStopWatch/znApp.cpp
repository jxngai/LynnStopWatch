#include "znConstants.h"

#include "znApp.h"
#include "znFrame.h"
#include "znControllerUi.h"
#include "znSingleton.h"

#include <wx/clipbrd.h>
#include <wx/textctrl.h>
#include <wx/stattext.h>

#if defined _MSC_VER

#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#endif

bool znApp::OnInit()
{
#if defined _MSC_VER

    _CrtSetDbgFlag ( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );

#endif

    // Frame will delete itself upon application exit.
    znFrame * const frame = new znFrame();
    frame->Center();
    frame->Show(TRUE);
    SetTopWindow(frame);

    return true;
}

void znApp::OnKeyDown(wxKeyEvent& event)
{
    if (wxGetApp().GetTopWindow() == NULL)
    {
        // Top window is no longer valid.
        return;
    }

    if (event.GetKeyCode() == WXK_PAGEUP || event.GetKeyCode() == WXK_LEFT)
    {
        znSingleton::GetInstance<znControllerUi>().OnStartStopTimer(wxCommandEvent());

        return;
    }

    if (event.GetKeyCode() == WXK_PAGEDOWN || event.GetKeyCode() == WXK_RIGHT)
    {
        znSingleton::GetInstance<znControllerUi>().OnResetLapTimer(wxCommandEvent());

        return;
    }

    if (event.ControlDown() == true && event.GetKeyCode() == 'A')
    {
        // Ctrl + A
        // Select all text in the output window.
		wxTextCtrl *text_control = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_TXT_OUTPUT_TEXT), wxTextCtrl);

        if (text_control != NULL)
        {
            text_control->SelectAll();
            text_control->SetFocus();
        }
    }

    if (event.ControlDown() == true && event.GetKeyCode() == 'C')
    {
        // Ctrl + C
        // Copy text to the clipboard

        if (wxTheClipboard->Open())
        {
            // This data objects are held by the clipboard,
            // so do not delete them in the app.

            wxString str;
			wxTextCtrl *text_control = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_TXT_OUTPUT_TEXT), wxTextCtrl);

            if (text_control != NULL)
            {
                str = text_control->GetStringSelection();
            }

            if (str == wxEmptyString)
            {
				wxStaticText *static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_M1), wxStaticText);
                str += static_text->GetLabel();

				static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_M2), wxStaticText);
                str += static_text->GetLabel();

                str += wxT(":");

				static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_S1), wxStaticText);
                str += static_text->GetLabel();

				static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_S2), wxStaticText);
                str += static_text->GetLabel();

                str += wxT(".");

				static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_U1), wxStaticText);
                str += static_text->GetLabel();
            }

            wxTheClipboard->SetData(new wxTextDataObject(str));
            wxTheClipboard->Close();
        }

        return;
    }

    // Skip() will let other event handler to process this event.
    // Without this statement, the event will disappear after that.
    event.Skip();
}

wxIMPLEMENT_APP(znApp);

wxBEGIN_EVENT_TABLE(znApp, wxApp)
    EVT_KEY_DOWN(znApp::OnKeyDown)
wxEND_EVENT_TABLE()


