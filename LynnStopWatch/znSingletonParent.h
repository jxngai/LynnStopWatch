#ifndef ZNSINGLETONPARENT_H
#define ZNSINGLETONPARENT_H

#include <wx/any.h>
#include <wx/log.h>

class znSingletonParent
{
public:
    void AddChild(wxAny);

protected:
    ~znSingletonParent();

private:
    wxVector<wxAny> m_children_list;
};

#endif