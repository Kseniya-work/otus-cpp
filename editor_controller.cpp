#include "editor_controller.h"
#include <iostream>

void EditorController::createNewDocument() const
{
    std::cout << "controller: create new document" << std::endl;
    model_->createNewDocument();
}

void EditorController::importDocument() const
{
    std::cout << "controller: import document" << std::endl;
    model_->importDocument();
}

void EditorController::exportDocument() const
{
    std::cout << "controller: export document" << std::endl;
    model_->exportDocument();
}

void EditorController::createGraphicPrimitive() const
{
    std::cout << "controller: create graphic primitive" << std::endl;
    model_->createGraphicPrimitive();
}

void EditorController::removeGraphicPrimitive() const
{
    std::cout << "controller: remove graphic primitive" << std::endl;
    model_->removeGraphicPrimitive();
}
