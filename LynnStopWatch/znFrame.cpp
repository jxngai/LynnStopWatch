#include "znConstants.h"
#include "znFrame.h"
#include "znControllerUi.h"

#include <wx/panel.h>
#include <wx/statbox.h>
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/button.h>
#include <wx/textctrl.h>

znFrame::znFrame()
    : wxFrame(NULL, ID_ZN_FRAME, ZN_APP_TITLE)
{
    wxStaticBox *static_box;
    wxBoxSizer *box_sizer;

    ////////////////////////////////////////////////////////
    // Panel
    ////////////////////////////////////////////////////////

    wxPanel * const panel = new wxPanel(this, ID_ZN_PANEL);

	////////////////////////////////////////////////////////
	// Sizer
	////////////////////////////////////////////////////////
	wxBoxSizer * const panel_sizer = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(panel_sizer);

    ////////////////////////////////////////////////////////
    // Text Control Container
    ////////////////////////////////////////////////////////

    // wxStaticBox *static_box = new wxStaticBox(panel, wxID_ANY, wxT("Stop Watch"));
    wxStaticBoxSizer * static_box_sizer = new wxStaticBoxSizer(wxHORIZONTAL, panel);
    panel_sizer->Add(static_box_sizer, 0, wxEXPAND | wxALL, 8);

    static_box = static_box_sizer->GetStaticBox();

    static_box_sizer->AddStretchSpacer();

    static_box_sizer->AddSpacer(6);

    static_box_sizer->Add(
        new wxStaticText(static_box, ID_ZN_STATIC_TXT_DIGIT_M1, wxT("0")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(static_box, ID_ZN_STATIC_TXT_DIGIT_M2, wxT("0")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(static_box, ID_ZN_STATIC_TXT_DIGIT_COLON, wxT(":")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(static_box, ID_ZN_STATIC_TXT_DIGIT_S1, wxT("0")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(static_box, ID_ZN_STATIC_TXT_DIGIT_S2, wxT("0")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(static_box, ID_ZN_STATIC_TXT_DIGIT_DOT, wxT(".")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(static_box, ID_ZN_STATIC_TXT_DIGIT_U1, wxT("0")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );

    static_box_sizer->AddSpacer(6);

    static_box_sizer->AddStretchSpacer();

    wxFont bold_font(30, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

	wxStaticText *static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_M1), wxStaticText);
    static_text->SetFont(bold_font);

	static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_M2), wxStaticText);
    static_text->SetFont(bold_font);

	static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_COLON), wxStaticText);
    static_text->SetFont(bold_font);

	static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_S1), wxStaticText);
    static_text->SetFont(bold_font);

	static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_S2), wxStaticText);
    static_text->SetFont(bold_font);

	static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_DOT), wxStaticText);
    static_text->SetFont(bold_font);

	static_text = wxDynamicCast(wxWindow::FindWindowById(ID_ZN_STATIC_TXT_DIGIT_U1), wxStaticText);
    static_text->SetFont(bold_font);

    ////////////////////////////////////////////////////////
    // Button Container
    ////////////////////////////////////////////////////////

    box_sizer = new wxBoxSizer(wxHORIZONTAL);
    panel_sizer->Add(box_sizer, 0, wxALIGN_CENTER_HORIZONTAL);

    box_sizer->Add(new wxButton(panel, ID_ZN_BTN_START_STOP_TIMER, wxT("Start") ), 0, wxALL, 2);

    box_sizer->AddSpacer(10);

    box_sizer->Add(new wxButton(panel, ID_ZN_BTN_RESET_LAP_TIMER, wxT("Reset") ), 0, wxALL, 2);

    ////////////////////////////////////////////////////////
    // Textbox Container
    ////////////////////////////////////////////////////////

    wxFont bold_font_2(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxTextCtrl *textbox = new wxTextCtrl(panel, ID_ZN_TXT_OUTPUT_TEXT, wxEmptyString, wxDefaultPosition, wxSize(20,200), wxTE_MULTILINE | wxTE_CENTRE);
    textbox->SetFont(bold_font_2);

    box_sizer = new wxBoxSizer(wxHORIZONTAL);
    panel_sizer->Add(box_sizer, 1, wxEXPAND);

    box_sizer->Add(textbox, 1, wxEXPAND | wxALL, 5);

    ////////////////////////////////////////////////////////
    // About Button Box Container
    ////////////////////////////////////////////////////////
    box_sizer = new wxBoxSizer(wxHORIZONTAL);
    panel_sizer->Add(box_sizer, 0, wxALIGN_CENTER_HORIZONTAL);

    box_sizer->Add(
        new wxButton(panel, ID_ZN_BTN_ABOUT, wxT("About") ),
        0,                  // Stretch factor
        wxALL,
        2 );

    ////////////////////////////////////////////////////////
    // Top Container
    ////////////////////////////////////////////////////////

    // Tell the top level window "this" which is znFrame that it should follow the size
    // of the "panel_sizer". Initially the size will be set to the minimum.

    panel_sizer->SetSizeHints(this);

    panel_sizer->AddSpacer(10);

    // SetWindowStyle(GetWindowStyle() & ~wxRESIZE_BORDER & ~wxMAXIMIZE_BOX);

#ifdef __WINDOWS__

    SetIcon(wxIcon(wxT("ID_ZN_RC_ICON_01"), wxBITMAP_TYPE_ICO_RESOURCE));

#endif

	// Add znControllerUi to handle all UI events.
	// MVC separation.

	PushEventHandler(&znSingleton::GetInstance<znControllerUi>());
}

znFrame::~znFrame()
{
	PopEventHandler();
}
