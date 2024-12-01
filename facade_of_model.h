/*!
\file
\brief Facade of model.

*/

#pragma once

#include "model.h"
#include "observer.h"

#include <memory>
#include <string>

class FacadeOfModel
{
private:
    std::shared_ptr<Model> model_;
    std::shared_ptr<Observer> observer_;

public:
    FacadeOfModel(std::shared_ptr<Model> model)
    : model_(model)
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