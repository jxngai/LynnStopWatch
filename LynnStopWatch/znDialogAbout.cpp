#include "znDialogAbout.h"
#include "znConstants.h"

#include <wx/panel.h>
#include <wx/sizer.h>
#include <wx/bmpbuttn.h>
#include <wx/stattext.h>
#include <wx/hyperlink.h>
#include <wx/statbmp.h>

znDialogAbout::znDialogAbout(wxWindow* parent)
: wxDialog(parent, ID_ZN_DLG_ABOUT, ZN_APP_TITLE wxT(" - About"))
{
    ////////////////////////////////////////////////////////
    // Panel
    ////////////////////////////////////////////////////////

    wxPanel *panel = new wxPanel(this);

	////////////////////////////////////////////////////////
	// Sizer
	////////////////////////////////////////////////////////
	wxBoxSizer *top_sizer = new wxBoxSizer(wxVERTICAL);
	panel->SetSizer(top_sizer);

    ////////////////////////////////////////////////////////
    // Image
    ////////////////////////////////////////////////////////

#ifdef __WINDOWS__
    wxStaticBitmap *bitmap_about = new wxStaticBitmap(panel, wxID_ANY, wxBitmap(wxT("BITMAP_ABOUT"), wxBITMAP_TYPE_BMP_RESOURCE));
#else
#   ifdef __WXMAC__
        static wxString done_flag;
        if (done_flag == wxEmptyString) wxImage::AddHandler(new wxJPEGHandler);
        done_flag = wxT("done");

        wxStaticBitmap *bitmap_about = new wxStaticBitmap(panel, wxID_ANY, wxBitmap(wxGetApp().GetAppName() + wxT(".app/Contents/Resources/portdickson.jpg"), wxBITMAP_TYPE_JPEG), wxDefaultPosition, wxSize(460, 86), wxBORDER_NONE);
#   else
        static wxString done_flag;
        if (done_flag == wxEmptyString) wxImage::AddHandler(new wxPNGHandler);
        done_flag = wxT("done");

        wxStaticBitmap *bitmap_about = new wxStaticBitmap(panel, wxID_ANY, wxBitmap(wxT("portdickson.png"), wxBITMAP_TYPE_PNG), wxDefaultPosition, wxSize(460, 86), wxBORDER_NONE);
#   endif
#endif

    wxBoxSizer *image_sizer = new wxBoxSizer(wxHORIZONTAL);
    image_sizer->Add(bitmap_about);

    ////////////////////////////////////////////////////////
    // Text
    ////////////////////////////////////////////////////////

    wxBoxSizer *info_sizer = new wxBoxSizer(wxVERTICAL);

    wxFont bold_font(20, wxFONTFAMILY_ROMAN, wxFONTSTYLE_NORMAL, wxFONTWEIGHT_BOLD);

    wxStaticText* static_text = new wxStaticText(panel, wxID_ANY, ZN_APP_TITLE);
    static_text->SetFont(bold_font);

    info_sizer->Add(static_text, 0, wxALIGN_CENTER | wxALL, 3);
    info_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Version : ")ZN_APP_VERSION), 0, wxALIGN_CENTER | wxALL, 3);
    info_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("by")), 0, wxALIGN_CENTER | wxALL, 3);
    info_sizer->Add(new wxStaticText(panel, wxID_ANY, wxT("Web Sailor Production")), 0, wxALIGN_CENTER | wxALL, 3);
    info_sizer->Add(new wxHyperlinkCtrl(panel, wxID_ANY, wxT("http://www.khngai.com/"), wxT("http://www.khngai.com/")), 0, wxALIGN_CENTER | wxALL, 3 );

    ////////////////////////////////////////////////////////
    // Buttons
    ////////////////////////////////////////////////////////

    wxBoxSizer *button_sizer = new wxBoxSizer(wxHORIZONTAL);

    button_sizer->Add(
        new wxButton(panel, wxID_OK, wxT("OK")),
        0,                  // Stretch factor
        wxALL,
        10 );               // Border width for wxALL or wxUP or wxDown or wxLEFT or wxRIGHT.

    ////////////////////////////////////////////////////////
    // The Top Container
    ////////////////////////////////////////////////////////

    top_sizer->Add(
        image_sizer,
        0,                  // Stretch factor
        wxALIGN_CENTER);

    top_sizer->Add(
        info_sizer,
        0,                  // Stretch factor
        wxALIGN_CENTER);

    top_sizer->Add(
        button_sizer,
        0,                  // Stretch factor
        wxALIGN_CENTER);

	// Tell the top level window "this" which is wxDialog that it should follow the size
	// of the "top_sizer". Initially the size will be set to the minimum.
	top_sizer->SetSizeHints(this);

    ////////////////////////////////////////////////////////
    // UI Control Initializations.
    ////////////////////////////////////////////////////////

	wxButton *button = wxDynamicCast(wxWindow::FindWindowById(wxID_OK), wxButton);
	if (button != NULL) button->SetFocus();

    Center();
}
