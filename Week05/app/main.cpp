#include "core.h"
#include "utils.h"

int main() {
    std::string name = get_app_name();
    print_message("Hello from main!");
    print_message("App name: " + name);
    return 0;
}
