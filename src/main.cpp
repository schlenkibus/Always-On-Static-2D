#include "Application.h"
#include "Tools/createNoiseImage.h"

int main() {
    auto& app = Application::get();
    return app.run();
}