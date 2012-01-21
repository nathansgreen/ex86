#include "interpreter.h"
#include "config.h"

#include <stdio.h>

int main(int argc, char *argv[]) {
    ex86_config config = {
        .memory_size = 1024
    };

    ex86_interpreter *interp = ex86_interpreter_new(&config);
    ex86_interpreter_destroy(interp);
    return 0;
}
