#ifndef STRING_OPERATIONS_H
#define STRING_OPERATIONS_H

#include <stdio.h>

// webkit --- codestyle
enum errors
{
    NULL_POINTER = 1,
    NAN_INPUT = 2,
    NOT_EQUAL_SIZE = 3
};

enum return_val
{
    ERROR = -1,
    NO_ERRORS = 0
};


struct line_poz
{
    char* start;
    int length;
};

extern line_poz* lines_my;
extern int der; 

/*!
\brief �������� ������ ����� � ���� � ������� ������� �����
\param f ��������� �� ����(�� fopen)
\param lines ������ �����
\param str_ID ������ �����
\param num_of_lines ���������� �����
\return ��������� ����������(��������� ������ ��� ���)
*/
int print_lines(FILE* f, line_poz* lines, int str_ID[], int num_of_lines);

/*!
\brief ������� ��� �����
\param val_1, val_2 �����
\return ��������� ����������(��������� ������ ��� ���)
*/
int my_swap(void* val_1, void* val_2, int size_of_elem);

/*!
\brief ��������� ������ ������� �� 0 �� num_of_elem
\param str_ID[]
\param num_of_elem ���������� ��������� � ������
\return ��������� ����������(��������� ������ ��� ���)
*/
int int_array_init(int* str_ID, int num_of_elem);

/*!
\brief ���������� �������
\param str1, str2 ������
\param der ����������� ����������
\return ��������� ���������
*/
int line_cmp(const void* str_1, const void* str_2);

/*!
\brief ������ ������ �����
\param file �������� �����
\return ������ �����
*/
int get_file_size(char* file, int* size_of_file);

/*!
\brief �������������� ����� �� ���������
\param file �����
\param lines ������ ������������ ��������
\param size_of_file ������ ������
\param num_of_lines ������������ ���������� �������
\return ��������� ����������(��������� ������ ��� ���)
*/
int liner_text(char* file, int size_of_file, int* num_of_lines, line_poz** lines);

/*!
\brief ��������� ������� � ����������������� �������
\param str_ID ������ ������� �����
\param lines ������ ������� ������
\param high_elem ������� ������ ����������
\param low_elem ������ ������ ����������
\param der ����������� ����������
\return ��������� ����������(��������� ������ ��� ���)
*/
int qsort_string(int str_ID[], size_t low_elem, size_t high_elem);

/*!
\brief ������ ���� � ������
\param file_name ��� �����
\param str ������ ��� ������
\param size_of_file ������ �����
\return ��������� ����������(��������� ������ ��� ���)
*/
int read_file(char* file_name, char** str_ptr, int* size_of_file);

#endif // STRING_OPERATIONS_H
