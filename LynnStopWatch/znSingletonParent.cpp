#include "znSingletonParent.h"
#include "znSingleton.h"

void znSingletonParent::AddChild(wxAny any)
{
    wxLogDebug(wxT("<<< znSingletonParent::AddChild() >>>"));

    // This function is for objects to add znApp as parent. So that
    // znApp will destroy the object when znApp's destructor is called.

    for (unsigned int ix = 0; ix < m_children_list.size(); ix++)
    {
        if (any.As<znSingleton*>() == m_children_list[ix].As<znSingleton*>())
        {
            // The object is already in the list.
            return;
        }
    }

    m_children_list.push_back(any);
}

znSingletonParent::~znSingletonParent()
{
    wxLogDebug(wxT("<<< znSingletonParent::~znSingletonParent() >>>"));

    // Destroy all the children.

    // That is to destroy all the singletons explicitly.
    // This is so that all singletons are destroyed before wxWidgets is un-initialized.
    // Creating the singletons as global stack variables and leaving them for the application to
    // destroy them automatically during application exit may cause undesirable behaviours
    // because the singletons may call wxWidgets functions after the wxWidgets has been uninitialized.

    // One down side about this is, the class type must be known before hand.

    while (m_children_list.size() > 0)
    {
        wxAny any = m_children_list[m_children_list.size() - 1];
        m_children_list.pop_back();

        delete any.As<znSingleton*>();
    }
}
