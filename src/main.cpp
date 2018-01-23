#include "Application.h"

int main() {
    auto& app = Application::get();
    return app.run();
}