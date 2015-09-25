#ifndef ZNSINGLETON_H
#define ZNSINGLETON_H

#include "znSingletonParent.h"

#include <wx/defs.h>

// This is an abstract Singleton class.
// It assumes the defined default constructor is always called so that it can
// all any child singleton object can be added to a parent.

class znSingleton
{
    friend znSingletonParent;

public:
    znSingleton();

private:
    wxDECLARE_NO_COPY_CLASS(znSingleton);

protected:
    virtual ~znSingleton() = 0 {};

public:
    template <class T>
    static T& GetInstance()
    {
        // Create a static object. Since this is static, it is only 1 instance
        // of this object no matter how many times GetInstance() is called.

        static T *instance = new T;

        return *instance;
    };
};

#endif