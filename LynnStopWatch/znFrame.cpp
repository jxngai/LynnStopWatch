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
    ////////////////////////////////////////////////////////
    // Panel
    ////////////////////////////////////////////////////////

    wxPanel * const panel = new wxPanel(this, ID_ZN_PANEL);

	////////////////////////////////////////////////////////
	// Sizer
	////////////////////////////////////////////////////////
	wxBoxSizer * const top_sizer = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(top_sizer);

    ////////////////////////////////////////////////////////
    // Text Control Container
    ////////////////////////////////////////////////////////

    wxStaticBox *staticbox = new wxStaticBox(panel, wxID_ANY, wxT("Stop Watch"));
    wxStaticBoxSizer * static_box_sizer = new wxStaticBoxSizer(staticbox, wxHORIZONTAL);

    static_box_sizer->AddStretchSpacer();

    static_box_sizer->AddSpacer(6);

    static_box_sizer->Add(
        new wxStaticText(panel, ID_ZN_STATIC_TXT_DIGIT_M1, wxT("0")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(panel, ID_ZN_STATIC_TXT_DIGIT_M2, wxT("0")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(panel, ID_ZN_STATIC_TXT_DIGIT_COLON, wxT(":")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(panel, ID_ZN_STATIC_TXT_DIGIT_S1, wxT("0")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(panel, ID_ZN_STATIC_TXT_DIGIT_S2, wxT("0")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(panel, ID_ZN_STATIC_TXT_DIGIT_DOT, wxT(".")),
        0,           // Stretch factor
        wxALL,
        5            // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.
        );
    static_box_sizer->Add(
        new wxStaticText(panel, ID_ZN_STATIC_TXT_DIGIT_U1, wxT("0")),
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

    wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);

    button_sizer->Add(
        new wxButton(panel, ID_ZN_BTN_START_STOP_TIMER, wxT("Start") ),
        0,                  // Stretch factor
        wxALL,
        2 );

    button_sizer->AddSpacer(10);

    button_sizer->Add(
        new wxButton(panel, ID_ZN_BTN_RESET_LAP_TIMER, wxT("Reset") ),
        0,                  // Stretch factor
        wxALL,
        2 );

    ////////////////////////////////////////////////////////
    // Textbox Container
    ////////////////////////////////////////////////////////

    wxFont bold_font_2(12, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxTextCtrl *textbox = new wxTextCtrl(panel, ID_ZN_TXT_OUTPUT_TEXT, wxEmptyString, wxDefaultPosition, wxSize(20,200), wxTE_MULTILINE | wxTE_CENTRE);
    textbox->SetFont(bold_font_2);

    wxBoxSizer *textbox_sizer = new wxBoxSizer(wxHORIZONTAL);

    textbox_sizer->Add(textbox, 1, wxEXPAND | wxALL, 5);

    ////////////////////////////////////////////////////////
    // About Button Box Container
    ////////////////////////////////////////////////////////
    wxBoxSizer *about_button_sizer = new wxBoxSizer(wxHORIZONTAL);

    about_button_sizer->Add(
        new wxButton(panel, ID_ZN_BTN_ABOUT, wxT("About") ),
        0,                  // Stretch factor
        wxALL,
        2 );

    ////////////////////////////////////////////////////////
    // Top Container
    ////////////////////////////////////////////////////////

    top_sizer->Add(
        static_box_sizer,
        0,                                               // Stretch factor
        wxALIGN_CENTER_HORIZONTAL | wxEXPAND | wxALL,    // Expand the list control to fill the entire client area.
        8);
    top_sizer->Add(
        button_sizer,
        0,                                               // Stretch factor
        wxALIGN_CENTER_HORIZONTAL);
    top_sizer->Add(
        textbox_sizer,
        1,                                               // Stretch factor
        wxALIGN_CENTER_HORIZONTAL | wxEXPAND);
    top_sizer->Add(
        about_button_sizer,
        0,                                               // Stretch factor
        wxALIGN_CENTER_HORIZONTAL);

    top_sizer->AddSpacer(10);

	// Tell the top level window "this" which is znFrame that it should follow the size
	// of the "top_sizer". Initially the size will be set to the minimum.

	top_sizer->SetSizeHints(this);

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