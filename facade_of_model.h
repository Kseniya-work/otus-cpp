/*! \file
    \brief Facade of model.

*/

#pragma once

#include "model.h"
#include "observer.h"

#include <memory>
#include <string>

/*! \class FacadeOfModel.
    \brief Facade of model.
*/
class FacadeOfModel
{
private:
    std::unique_ptr<Model> model_; /*!< masked model */
    std::shared_ptr<Observer> observer_; /*!< observer of model */

public:
    FacadeOfModel(std::unique_ptr<Model> model)
    : model_(std::move(model))
    , observer_(nullptr)
    {}

    ~FacadeOfModel() {}

    void attach(std::shared_ptr<Observer> observer);

    void createNewDocument();
    void importDocument();
    void exportDocument();
    void createGraphicPrimitive();
    void removeGraphicPrimitive();

private:
    void notify(std::string);
};