#include "editor_controller.h"
#include "editor_model.h"
#include "editor_view.h"
#include "facade_of_model.h"

#include <iostream>

int main(int, char **) {
    std::unique_ptr<Model>                   model = std::make_unique<EditorModel>();
    std::shared_ptr<FacadeOfModel> facade_of_model = std::make_shared<FacadeOfModel>(std::move(model));
    std::unique_ptr<Controller>         controller = std::make_unique<EditorController>(facade_of_model);
    std::unique_ptr<Observer>                 view = std::make_unique<EditorView>(facade_of_model);
    facade_of_model->attach(std::move(view));

    controller->createNewDocument();
    controller->importDocument();
    controller->exportDocument();
    controller->createGraphicPrimitive();
    controller->removeGraphicPrimitive();

    return 0;
}
