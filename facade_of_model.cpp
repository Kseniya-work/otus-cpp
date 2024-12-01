#include "facade_of_model.h"

void FacadeOfModel::attach(std::shared_ptr<Observer> observer)
{
    observer_ = observer;
}

void FacadeOfModel::notify(std::string operation)
{
    observer_->update(operation);
}

void FacadeOfModel::createNewDocument()
{
    model_->createNewDocument();
    if (observer_ != nullptr) notify("createNewDocument");
}

void FacadeOfModel::importDocument()
{
    model_->importDocument();
    if (observer_ != nullptr) notify("importDocument");
}

void FacadeOfModel::exportDocument()
{
    model_->exportDocument();
    if (observer_ != nullptr) notify("exportDocument");
}

void FacadeOfModel::createGraphicPrimitive()
{
    model_->createGraphicPrimitive();
    if (observer_ != nullptr) notify("createGraphicPrimitive");
}

void FacadeOfModel::removeGraphicPrimitive()
{
    model_->removeGraphicPrimitive();
    if (observer_ != nullptr) notify("removeGraphicPrimitive");
}
