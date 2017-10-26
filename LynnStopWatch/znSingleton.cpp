#include "znSingleton.h"
#include "znApp.h"

znSingleton::znSingleton()
{
    wxGetApp().AddSingletonChild(this);
}

znSingleton::~znSingleton()
{
}