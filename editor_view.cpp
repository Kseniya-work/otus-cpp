#include "editor_view.h"
#include <iostream>

void EditorView::display() const
{
    /*
    model_->getData();
    */
}

void EditorView::update(std::string operation)
{
    std::cout << "view: update after " + operation << std::endl;
    display();
}