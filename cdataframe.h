//
// Created by Ibrahima Sory Diallo on 19/04/2024.
//

#ifndef CDATAFRAME_H
#define CDATAFRAME_H

#include "column.h"
#include <stdbool.h>



union column_type{
    unsigned int uint_value;
    signed int int_value;
    char char_value;
    float float_value;
    double double_value;
    char* string_value;
    void* struct_value;
};
typedef union column_type COL_TYPE ;

struct column {
    char *title;
    unsigned int i;
    unsigned int size; //logical size
    unsigned int max_size; //physical size
    int **data; // array of pointers to stored int data
    unsigned long long int *index; // array of integers
    int valid_index; // 0: no index, -1: invalid index, 1: valid index
    int sort_dir; // 0: ASC, 1: DESC
    int column_type; // Type of data stored in the column (1 for INT)
};
#define ASC 0
#define DESC 1
typedef struct column COLUMN;

typedef struct {
    Column **columns;    // Array of pointers to Columns
    int num_columns;     // Number of columns
    int capacity;        // Capacity of the dataframe (for dynamic resizing)
} CDataframe;

// Function prototypes for CDataframe
CDataframe* create_cdataframe(void);
int insert_cdataframe_value(COLUMN *col, void *value) ;
void print_cdataframe_col(const Column *col);
void fill_cdataframe_with_input(CDataframe *df);
void hard_fill_cdataframe(CDataframe *df);
void display_cdataframe(const CDataframe *df);
void display_rows(const CDataframe *df, int limit);
void display_columns(const CDataframe *df, int limit);
void add_row(CDataframe *df, int *values, int num_values);
void delete_row(CDataframe *df, int row_index);
void rename_column(CDataframe *df, const char *old_title, const char *new_title);
bool search_value(const CDataframe *df, int value);
int get_value(const CDataframe *df, int row, int column);
void replace_value(CDataframe *df, int row, int column, int new_value);
void display_column_names(const CDataframe *df);
int num_rows(const CDataframe *df);
int num_columns(const CDataframe *df);
int count_cells_equal_to(const CDataframe *df, int value);
int count_cells_greater_than(const CDataframe *df, int value);
int count_cells_less_than(const CDataframe *df, int value);
void free_cdataframe(CDataframe *df);
void convert_value(Column *col, unsigned long long int i, char *str, int size);

// Functionalies (6.0)

void sort(COLUMN* col, int sort_dir);
void print_col_by_index(Column *col);
void erase_index(COLUMN *col);
int check_index(COLUMN *col);
void update_index(COLUMN *col);
int search_value_in_column(COLUMN *col, void *val);
void delete_cdataframe(CDataframe **cdf);
#endif
