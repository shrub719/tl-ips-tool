#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 0x100

void view(char *filename) {
    FILE *fptr = fopen(filename, "rb");

    char patch[6];
    fread(patch, 1, 5, fptr);
    patch[5] = '\0';
    printf("%s\n", patch);

    uint32_t offset;
    uint16_t length;
    char buffer[BUFFER_SIZE];

    while (1) {
        fread(&offset, 1, 3, fptr);
        offset = offset >> 8;
        printf("offset: 0x%X\n", offset);

        fread(&length, 1, 2, fptr);
        printf("length: 0x%X\n", length);

        /*
        if (length == 0) {
            printf("rle hunk found (not implemented) - aborting\n");
            break;
        } if (length > BUFFER_SIZE - 1) {
            printf("hunk too large - aborting\n");
            break;
        }
        

        fread(buffer, 1, length, fptr);
        printf("buffer: 0x%x\n", buffer);
        */

        break;
    }

    fclose(fptr);
}

int main(int argc, char **argv) {
    char *command = argv[1];

    if (strlen(command) >= 4 && strncmp("view", command, 4) == 0) {
        char *filename = argv[2];
        view(filename);
    }

    return 0;
}
