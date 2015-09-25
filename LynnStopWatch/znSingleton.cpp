#include "znSingleton.h"
#include "znApp.h"

znSingleton::znSingleton()
{
    wxGetApp().AddChild(this);
}

znSingleton::~znSingleton()
{
}