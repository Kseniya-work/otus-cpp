/*!
\file
\brief Editor model.

*/

#pragma once

#include "model.h"

class EditorModel : public Model
{
private:
    /* data */

public:
    EditorModel() {}
    virtual ~EditorModel() {}

    virtual void createNewDocument() override;
    virtual void importDocument() override;
    virtual void exportDocument() override;
    virtual void createGraphicPrimitive() override;
    virtual void removeGraphicPrimitive() override;
};