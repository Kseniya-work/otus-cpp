#include "editor_view.h"
#include <iostream>

void EditorView::display() const
{
    /*
    auto data = model_->getData();
    std::cout << data << std::endl;
    */
}

void EditorView::update(std::string operation)
{
    std::cout << "view: update after " + operation << std::endl;
    display();
}