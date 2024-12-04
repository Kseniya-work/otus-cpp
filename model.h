/*! \file
    \brief Model interface.

*/

#pragma once

/*! \class Model.
    \brief Interface of abstract model.
*/
class Model
{
private:
    /* data */

public:
    Model() {}
    virtual ~Model() {}

    virtual void createNewDocument() = 0;
    virtual void importDocument() = 0;
    virtual void exportDocument() = 0;
    virtual void createGraphicPrimitive() = 0;
    virtual void removeGraphicPrimitive() = 0;
};