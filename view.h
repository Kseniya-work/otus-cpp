/*!
\file
\brief View interface.

*/

#pragma once

#include <string>

class View
{
private:
    /* data */

public:
    View() {}
    virtual ~View() {}

    virtual void display() const = 0;
};