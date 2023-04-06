#include "string_operations.h"

#include <errno.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

extern line_poz* lines_my;
extern int der; 

int main()
{

    setlocale(LC_ALL, "Russian");
    errno = 0;
    char* text_input = "gamlet.txt";
    char* str_read = NULL;
    int num_of_lines = 0;
    int size_of_file = 0;

    FILE* out = fopen("out.txt", "w");

    if(get_file_size(text_input, &size_of_file) == ERROR)
        printf("ERROR: %d", errno);

    if(read_file(text_input, &str_read, &size_of_file) == ERROR)
        printf("ERROR: %d", errno);

    str_read[size_of_file] = 0;

    line_poz* lines = (line_poz*)calloc(size_of_file, sizeof(line_poz));

    
    if(liner_text(str_read, strlen(str_read), &num_of_lines, &lines) == ERROR)
        printf("ERROR: %d", errno);

    lines_my = lines;

    int* str_ID = (int*)calloc(sizeof(int), num_of_lines);

    int_array_init(str_ID, num_of_lines);

    print_lines(out, lines_my, str_ID, num_of_lines);

    der = 1;

    qsort(str_ID, num_of_lines, sizeof(int), line_cmp);

    print_lines(out, lines, str_ID, num_of_lines);

    der = -1;

    qsort(str_ID, num_of_lines, sizeof(int), line_cmp);

    print_lines(out, lines, str_ID, num_of_lines);

    free(lines);
    free(str_read);
    free(str_ID);
    fclose(out);
    return 0;
}
