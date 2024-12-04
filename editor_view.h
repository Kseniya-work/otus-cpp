/*! \file
    \brief Editor view.

*/

#pragma once

#include "facade_of_model.h"
#include "observer.h"
#include "view.h"

#include <memory>

/*! \class EditorView.
    \brief Editor view.
*/
class EditorView : public Observer, View
{
private:
    std::shared_ptr<FacadeOfModel> model_; /*!< model being viewed */

public:
    EditorView(std::shared_ptr<FacadeOfModel> model) : model_(model) {}
    virtual ~EditorView() {}

    virtual void display() const override;
    virtual void update(std::string) override;
};