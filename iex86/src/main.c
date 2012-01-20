#include "interpreter.h"
#include "config.h"

int main(int argc, char *argv[]) {
    ex86_context_config config = {
        .memory_size = 1024
    };

    ex86_interpreter *interp = ex86_interpreter_new(&config);
    ex86_interpreter_destroy(interp);
    return 0;
}
