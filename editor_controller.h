/*! \file
    \brief Editor controller.

*/

#pragma once

#include "controller.h"
#include "facade_of_model.h"

#include <memory>

/*! \class EditorController.
    \brief Editor controller.
*/
class EditorController : public Controller
{
private:
    std::shared_ptr<FacadeOfModel> model_; /*!< controlled model */

public:
    EditorController(std::shared_ptr<FacadeOfModel> model) : model_(model) {}
    virtual ~EditorController() {}

    virtual void createNewDocument() const override;
    virtual void importDocument() const override;
    virtual void exportDocument() const override;
    virtual void createGraphicPrimitive() const override;
    virtual void removeGraphicPrimitive() const override;
};