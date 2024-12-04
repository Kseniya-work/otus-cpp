/*! \file
    \brief Observer interface.

*/

#pragma once

#include <string>

/*! \class Observer.
    \brief Interface of abstract observer.
*/
class Observer
{
public:
    virtual ~Observer() {}
    virtual void update(std::string) = 0;
};