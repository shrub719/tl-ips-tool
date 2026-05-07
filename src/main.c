#include <stdio.h>
#include <string.h>
#include <stdint.h>

#define BUFFER_SIZE 256

uint32_t convertBytes(unsigned char *bytes, size_t len) {
    uint32_t result = 0;

    for (int i = 0; i < len; i++) {
        result += bytes[i] << (len - i - 1) * 8;
    }

    return result;
}

void displayBytes(unsigned char *bytes, size_t len) {
    for (int i = 0; i < len; i++) {
        printf("%02X ", (uint8_t)bytes[i]);
    }
    printf("\n");
}

void view(char *filename) {
    FILE *fptr = fopen(filename, "rb");

    unsigned char patch[6];
    fread(patch, 1, 5, fptr);
    patch[5] = '\0';
    printf("%s\n", patch);
    printf("\n");

    unsigned char buffer[BUFFER_SIZE];

    while (1) {
        fread(buffer, 1, 3, fptr);
        
        if (strncmp("EOF", buffer, 3) == 0) {
            printf("EOF\n");
            break;
        }

        uint32_t offset = convertBytes(buffer, 3);
        printf("offset: 0x%X\n", offset);

        fread(buffer, 1, 2, fptr);
        uint32_t length = convertBytes(buffer, 2);
        printf("length: 0x%X\n", length);

        if (length == 0) {
            printf("rle hunk found (not implemented) - aborting\n");
            break;
        } if (length > BUFFER_SIZE - 1) {
            printf("hunk too large - aborting\n");
            break;
        }

        fread(buffer, 1, length, fptr);
        displayBytes(buffer, length);
        printf("\n");
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
