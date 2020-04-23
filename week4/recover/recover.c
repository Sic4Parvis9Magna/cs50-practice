#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define PAGE_SIZE 512

typedef uint8_t  BYTE;
typedef struct
{ 
    BYTE data[PAGE_SIZE];
} __attribute__((__packed__))
PAGE;

void write_picture(char *file_name, long start_page, long end_page, PAGE *pages);
char* get_new_image_name(int number);

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }
    
    char *file_name  = argv[1];

    // Open input file
    FILE *inptr = fopen(file_name, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", file_name);
        return 1;
    }

    //Get file length
	fseek(inptr, 0, SEEK_END);
	long fileLen = ftell(inptr);
    long num_pages = fileLen / PAGE_SIZE;
    printf("bytes in total = %lu\n", fileLen);
    printf("pages in total = %lu\n", num_pages);
	fseek(inptr, 0, SEEK_SET);
    PAGE *pages = malloc(num_pages * sizeof(PAGE));
    
    fread(pages, sizeof(PAGE), num_pages, inptr);
    fclose(inptr);

    long start_page = 0;
    long end_page = 0;
    bool first_picture = true;
    int image_number = 0;

    char *outfile = get_new_image_name(image_number);

    for (long i = 0; i < num_pages; i++)
    {
        PAGE next_page = pages[i];
        BYTE first = next_page.data[0];
        BYTE second = next_page.data[1];
        BYTE third = next_page.data[2];
        BYTE fourth = next_page.data[3];

        bool is_next_file = first == 0xff &&
                            second == 0xd8 &&
                            third == 0xff &&
                            (fourth >= 0xe0 && fourth <= 0xef);
        
        if (i == 0) {
            printf("is true: %i\n", true);
            printf("is first pic: %i\n", is_next_file);
        }

        bool is_last_page = i == num_pages-1;
        end_page = i;

        //here we suggest that each pic larger than PAGE
        if(is_next_file && first_picture)
        {
            printf("first page: %lu\n", i);
            start_page = i;
            first_picture = false;
            continue;
        }

        //0xff 0xd8 0xff
        if (is_next_file || is_last_page)
        {
            if (is_next_file)
            {
                end_page = i -1;
            }

            printf("start page = %lu, end page = %lu\n", start_page, end_page);
            write_picture(outfile, start_page, end_page, pages);
            image_number++;
            char *tmp = get_new_image_name(image_number);
            free(outfile);
            outfile = tmp;
            start_page = i;
        }
    }
}


void write_picture(char *file_name, long start_page, long end_page, PAGE *pages)
{
    FILE *outptr = fopen(file_name, "w");
    printf("filename %s : ", file_name);
    printf("start page %lu : ", start_page);
    printf("last page %lu\n", end_page);
    for (long i = start_page; i < end_page; i++)
    {
        // Write row to outfile
        fwrite(&pages[i], sizeof(PAGE), 1, outptr);
    }

    int last_worth_byte = -1;
    PAGE last_page = pages[end_page];
    for (int i = PAGE_SIZE - 1; i > -1; i--)
    {
        if (last_page.data[i] != 0)
        {
            last_worth_byte = i;
            break;
        }
    }
    printf("last page data ends %i\n", last_worth_byte);
    if (last_worth_byte != -1)
    {
        fwrite(&pages[end_page], sizeof(BYTE), last_worth_byte + 1, outptr);
    }
    
    fclose(outptr);
}

char* get_new_image_name(int number)
{
    char *name = malloc(sizeof(char) * 7);
    char *suffix = ".jpg";
    char *prefix;
    if (number < 10)
    {
        prefix = "00";
    }
    else if (number < 100)
    {
        prefix = "0";
    } else
    {
        prefix = "";
    }
    
    sprintf(name,"%s%i%s", prefix, number, suffix);
    return name;
}
