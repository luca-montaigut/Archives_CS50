#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    FILE *raw_file = fopen(argv[1], "r");
    if (raw_file == NULL)
    {
        return 2;
    }

    int picture_count = 0;
    char new_filename[8];
    BYTE buffer[512];
    FILE *picture;


    while (fread(buffer, 512, 1, raw_file) == 1)
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if (picture_count == 0)
            {
                sprintf(new_filename, "%03i.jpg", picture_count);
                picture = fopen(new_filename, "w");
            }
            else
            {
                fclose(picture);
                sprintf(new_filename, "%03i.jpg", picture_count);
                picture = fopen(new_filename, "w");
            }
            fwrite(buffer, 512, 1, picture);
            picture_count++;
        }
        else
        {
            if (picture_count > 0)
            {
                fwrite(buffer, 512, 1, picture);
            }
        }
    };

    fclose(picture);
    fclose(raw_file);
}



