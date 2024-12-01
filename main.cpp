#include "editor_controller.h"
#include "editor_model.h"
#include "editor_view.h"
#include "facade_of_model.h"

#include <iostream>

int main(int, char **) {
    std::shared_ptr<Model>                   model = std::make_shared<EditorModel>();
    std::shared_ptr<FacadeOfModel> facade_of_model = std::make_shared<FacadeOfModel>(model);
    std::shared_ptr<Controller>         controller = std::make_shared<EditorController>(facade_of_model);
    std::shared_ptr<Observer>                 view = std::make_shared<EditorView>(facade_of_model);
    facade_of_model->attach(view);

    controller->createNewDocument();
    controller->importDocument();
    controller->exportDocument();
    controller->createGraphicPrimitive();
    controller->removeGraphicPrimitive();

    return 0;
}
