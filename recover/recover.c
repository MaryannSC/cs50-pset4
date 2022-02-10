#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

typedef uint8_t  BYTE;

int main(int argc, char *argv[])
{
    // check for 1 command line argument - Usage: ./ recover image
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Get filename
    char *infile = argv[1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 1;
    }

    char outfile[8];
    BYTE *buffer = malloc(512 * sizeof(BYTE));
    bool writing_file = false;
    int file_count = 0;
    int num_bytes = 0;
    FILE *outptr;

    num_bytes = fread(buffer, sizeof(BYTE), 512, inptr);

    while (num_bytes == 512)
    {
        // check if start of JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            printf("Found JPEG header\n");
            // get new filename
            sprintf(outfile, "%03i.jpg", file_count);
            printf("filename: %s\n", outfile);
            file_count++;
            printf("filecount: %i\n", file_count);

            if (writing_file)
            {
                fclose(outptr);
            }

            // open new file

            outptr = fopen(outfile, "w");
            if (outptr == NULL)
            {
                fprintf(stderr, "Could not create %s.\n", outfile);
                return 1;
            }

            writing_file = true;

        }

        // ready for writing file
        if (writing_file)
        {
            fwrite(buffer, sizeof(BYTE), 512, outptr);
        }

        // else not already writing file, continue searching, read next 512 bytes
        num_bytes = fread(buffer, sizeof(BYTE), 512, inptr);
    }

    free(buffer);
    fclose(inptr);
    fclose(outptr);

    return 0;
}
