/*! \file
    \brief Controller interface.

*/

#pragma once

/*! \class Controller.
    \brief Interface of abstract controller.
*/
class Controller
{
private:
    /* data */

public:
    Controller() {}
    virtual ~Controller() {}

    virtual void createNewDocument() const = 0;
    virtual void importDocument() const = 0;
    virtual void exportDocument() const = 0;
    virtual void createGraphicPrimitive() const = 0;
    virtual void removeGraphicPrimitive() const = 0;
};