#include "interpreter.h"

int main(int argc, char *argv[]) {
    ex86_interpreter *interp = ex86_interpreter_new();
    ex86_interpreter_destroy(interp);
    return 0;
}
