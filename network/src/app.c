
#include <stdio.h>

#include <string.h>
#include <libgen.h>

#include <errno.h>
#include "message.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_native_dialog.h>

#include "global.h"
#include "graphics.h"
#include "resource.h"

int errno;

char *init_filepath(char *command, char *resource_path) {

    char exec_filepath[MAX_STRLEN];
    char *exec_filename;

    realpath(command, exec_filepath);

    exec_filename = basename(exec_filepath);

    unsigned int exec_filename_len, exec_filepath_len;

    exec_filepath_len = strlen(exec_filepath);
    exec_filename_len = strlen(exec_filename);

    strncpy(
        resource_path, exec_filepath, exec_filepath_len - exec_filename_len);

    unsigned int resource_path_len;
    resource_path_len = strlen(resource_path);

    for (int i = 1; i <= 5; i++) {
        resource_path[resource_path_len - i] = '\0';
    }

    if (snprintf(
            resource_path, MAX_STRLEN, "%s/%s", resource_path, "resource/") <
        0) {
        return NULL;
    }

    return resource_path;
}

int main(int argc, char **argv) {

    char resource_path[MAX_STRLEN];
    memset(resource_path, '\0', MAX_STRLEN);

    if (!init_filepath(argv[0], resource_path)) {
        fprintf(stderr, "Failed to initialize init_filepath\n");
        return EXIT_FAILURE;
    }

    init(resource_path);
    loop();
    shutdown();

    return EXIT_SUCCESS;
}
