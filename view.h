/*! \file
    \brief View interface.

*/

#pragma once

#include <string>

/*! \class View.
    \brief Interface of abstract view.
*/
class View
{
private:
    /* data */

public:
    View() {}
    virtual ~View() {}

    virtual void display() const = 0;
};