#include <stdlib.h>
#include "../include/wsh_input.h"

void clear_input(wsh_input *input) {

    free(input->text);

}
