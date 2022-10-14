
#include <errno.h>
#include <string.h>
#include "string_operations.h"
#include <stdio.h>
#define NDEBUG
#include <assert.h>
#include <math.h>
#include <sys/stat.h>
#include <ctype.h>
//#include <io.h>
#include <unistd.h>
#include <fcntl.h>

line_poz* lines_my;
int der; 


int my_swap(void* val_1, void* val_2, int size_of_elem)
{
    assert(val_1 != NULL);
    assert(val_2 != NULL);

    //if(val_1 == NULL || val_2 == NULL)
    //{
      //  errno = NULL_POINTER;
       // return ERROR;
   // }

    void* tmp_val = malloc(size_of_elem);
    memcpy(tmp_val, val_2, size_of_elem);
    memcpy(val_2, val_1, size_of_elem);
    memcpy(val_1, tmp_val, size_of_elem);

    free(tmp_val);
}

int print_lines(FILE* f, line_poz* lines, int str_ID[], int num_of_lines)
{
    assert(f != NULL);
    assert(lines != NULL);
    assert(str_ID != NULL);

    if(f == NULL && lines == NULL && str_ID == NULL)
    {
        errno = NULL_POINTER;
        return ERROR;
    }

    for(int i = 0; i < num_of_lines; i++)
    {
        fprintf(f, "%s\n", lines[str_ID[i]].start);
    }
}

int int_array_init(int* str_ID, int num_of_elem)
{

    assert(str_ID != NULL);

    if(str_ID == NULL)
    {
        errno = NULL_POINTER;
        return ERROR;
    }

    for(int i = 0; i < num_of_elem; i++)
        str_ID[i] = i;
}

int get_file_size(char* file, int* size_of_file)
{
    assert(file != NULL);

    if(file == NULL || size_of_file == NULL)
    {
        errno = NULL_POINTER;
        return ERROR;
    }
    else
    {
        struct stat st = {};;
        stat(file, &st);
        *size_of_file = st.st_size;
    }
    return NO_ERRORS;
}

int line_cmp(const void* str_1, const void* str_2)
{
    line_poz* str1 = &(lines_my[(*((int*)str_1))]);
    line_poz* str2 = &(lines_my[(*((int*)str_2))]);

    assert(str1 != 0);
    assert(str2 != 0);

    char* str1_ptr;
    char* str2_ptr;

    if(der > 0)
    {
        str1_ptr = str1 -> start;
        str2_ptr = str2 -> start;
    }
    else
    {
        str1_ptr = str1 -> start + str1 -> length - 1;
        str2_ptr = str2 -> start + str2 -> length - 1;
    }

    int i1 = 0;
    int i2 = 0;

    while(str1 -> length > i1 && str2 -> length > i2)
    {
        if(isalpha(*str2_ptr) && isalpha(*str1_ptr))
        {
            if(*str1_ptr != *str2_ptr)
                break;
            i1++;
            i2++;
            if(der > 0)
            {
                str1_ptr++;
                str2_ptr++;
            }
            else
            {
                str1_ptr--;
                str2_ptr--;
            }
        }
        else
        {
            if(der > 0)
            {
                if(!isalpha(*str2_ptr))
                {
                    str2_ptr++;
                    i2++;
                }
                if(!isalpha(*str1_ptr))
                {
                    str1_ptr++;
                    i1++;
                }
            }
            else
            {
                if(!isalpha(*str2_ptr))
                {
                    str2_ptr--;
                    i2++;
                }
                if(!isalpha(*str1_ptr))
                {
                    str1_ptr--;
                    i1++;
                }
            }
        }
    }

    if((str1 -> length == i1) || (str2 -> length == i2))
        return (i1 < i2) ? -1 : (i1 > i2) ? 1 : 0;

    return (*str1_ptr - *str2_ptr);
}

// !!! �������� ���� qsort (�������� ����� �� ��� � � stdlib.h) + ���� swap

int qsort_string(int str_ID[], size_t low_elem, size_t high_elem)
{
    assert(str_ID != 0);

    if(str_ID == NULL)
    {
        errno = NULL_POINTER;
        return ERROR;
    }

    int left_index = 0, right_index = 0;
    int central_index = 0;

    left_index = low_elem;
    right_index = high_elem - 1;

    central_index = (high_elem + low_elem)/2;
    do
    {
        while (line_cmp((void*)(&str_ID[left_index]), (void*)(&str_ID[central_index])) < 0)
            left_index++;

        while (line_cmp((void*)(&str_ID[right_index]), (void*)(&str_ID[central_index])) > 0) {
            right_index--;
        }

        if (left_index <= right_index)
        {
            if (line_cmp((void*)(&str_ID[left_index]), (void*)(&str_ID[right_index])) > 0)
                if(my_swap((void*)(&str_ID[left_index]), (void*)(&str_ID[right_index]), sizeof(int)) == ERROR)
                    return ERROR;

            left_index++;

            if (right_index > 0)
                right_index--;
        }
    }
    while (left_index <= right_index);

    if (left_index < high_elem)
        if(qsort_string(str_ID, left_index, high_elem) == ERROR)
            return ERROR;

    if (right_index > low_elem)
        if(qsort_string(str_ID, low_elem, right_index) == ERROR)
            return ERROR;

    return NO_ERRORS;
}



int read_file(char* file_name, char** str_ptr, int* size_of_file)
{
    assert(str_ptr != NULL);
    assert(*str_ptr != NULL);
    assert(size_of_file != NULL);
    assert(file_name != NULL);

    /*
    if(str_ptr == NULL || size_of_file == NULL || file_name == NULL)
    {
        errno = NULL_POINTER;
        return ERROR;
    }
    */

    int file_desc = open(file_name, O_RDONLY);

    //*str_ptr  = (char*)realloc(*str_ptr, *size_of_file);
    *str_ptr = (char*)calloc(*size_of_file + 2, sizeof(char));
    *size_of_file = read(file_desc, *str_ptr, *size_of_file);

    close(file_desc);

    return NO_ERRORS;
}

int liner_text(char* file, int size_of_file, int* num_of_lines, line_poz** lines)
{
    assert(file != NULL);
    assert(num_of_lines != NULL);
    assert(lines != NULL);

    if(num_of_lines == NULL || file == NULL || lines == NULL)
    {
        errno = NULL_POINTER;
        return ERROR;
    }

    *num_of_lines = 0;
    (*lines)[*num_of_lines].start = file;
    bool space_flag = true;

    for(int i = 0; i < size_of_file; i++)
    {
        if((file[i] == '\n' || file[i] == '\r') && !space_flag)
        {
            (*lines)[*num_of_lines].length = &file[i] - (*lines)[*num_of_lines].start + 1;
            file[i] = '\0';
            (*num_of_lines)++;
            space_flag = true;
        }

        if(!isspace(file[i]) && file[i] != '\0' && space_flag)
        {
            space_flag = false;
            (*lines)[*num_of_lines].start = file + i;
        }
    }
    (*num_of_lines)++;

    *lines = (line_poz*)realloc((*lines), (*num_of_lines) * sizeof(line_poz));
    return NO_ERRORS;
}

