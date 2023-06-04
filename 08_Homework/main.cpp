#include "Application.h"

int main(int argc, char* argv[]) {
    auto app = Application(argc, argv);
    return app.exec();
}
