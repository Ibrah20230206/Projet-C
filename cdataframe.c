//
// Created by Ibrahima Sory Diallo on 18/04/2024.
//

#include "column.h"
#include "cdataframe.h"
// Function to create a column (4.1.1)
Column *create_column(const char *title) {
    Column *col = malloc(sizeof(Column));
    if (col == NULL) return NULL;

    col->title = strdup(title);
    col->size = 0;
    col->max_size = 10; // Start with an initial capacity of 10
    col->data = malloc(col->max_size * sizeof(int));
    if (col->data == NULL) {
        free(col->title);
        free(col);
        return NULL;
    }
    return col;
}

// Function to insert a value into a column (4.1.2)
void insert_value(Column *column, int value) {
    if (column->size == column->max_size) {
        int *new_data = realloc(column->data, (column->max_size + 10) * sizeof(int));
        if (new_data == NULL) return;
        column->data = new_data;
        column->max_size += 10;
    }
    column->data[column->size++] = value;
}

// Function to print the content of a column (4.1.4)
void print_col(const Column *column) {
    printf("Column: %s\n", column->title);
    for (unsigned int i = 0; i < column->size; i++) {
        printf("[%u] %d\n", i, column->data[i]);
    }
}

// Function to free a column from memory (4.1.3)
void delete_column(Column **column) {
    if (column == NULL || *column == NULL) return;
    free((*column)->data);
    free((*column)->title);
    free(*column);
    *column = NULL;
}

// Function to count occurrences of a specific value (4.1.5)
int count_value(const Column *column, int value) {
    int count = 0;
    for (unsigned int i = 0; i < column->size; i++) {
        if (column->data[i] == value) {
            count++;
        }
    }
    return count;
}

// Function to check value at a specific index (4.1.5)
int value_at_index(const Column *column, unsigned int index) {
    if (index < column->size) {
        return column->data[index];
    } else {
        printf("Index out of bounds.\n");
        return -1; // Indicative error value
    }
}

// Function to find the maximum value in the column (4.1.5)
int find_max(const Column *column) {
    if (column->size == 0) return -1; // Indicative error if column is empty

    int max = column->data[0];
    for (unsigned int i = 1; i < column->size; i++) {
        if (column->data[i] > max) {
            max = column->data[i];
        }
    }
    return max;
}
// Function to count values less than a specified value 'x' (4.1.5)
int count_less_than(const Column *column, int x) {
    int count = 0;
    for (unsigned int i = 0; i < column->size; i++) {
        if (column->data[i] < x) {
            count++;
        }
    }
    return count;
}

// Function to count the number of values equal to 'x' (4.1.5)
int count_equals_x(const Column *column, int x) {
    int count = 0;
    for (unsigned int i = 0; i < column->size; i++) {
        if (column->data[i] == x) {
            count++;
        }
    }
    return count;
}

// Implementations for Column functions
// Implementations for CDataframe functions
CDataframe* create_cdataframe() {
    CDataframe *df = malloc(sizeof(CDataframe));
    if (!df) return NULL;
    df->columns = NULL;
    df->num_columns = 0;
    df->capacity = 0;
    return df;
}
// Function to create a new column


int insert_cdataframe_value(COLUMN *col, void *value) {
    // Check if the column is valid
    if (col == NULL) {
        printf("Invalid column.\n");
        return -1;
    }

    // Check if the value is valid
    if (value == NULL) {
        printf("Invalid value.\n");
        return -1;
    }

    // Check memory space
    if (col->size >= col->max_size) {
        printf("No memory space available.\n");
        return -1;
    }

    // Allocate memory for the new value
    col->data[col->size] = malloc(sizeof(int));
    if (col->data[col->size] == NULL) {
        printf("Memory allocation failed.\n");
        return -1;
    }

    // Copy the value (INT type)
    *((int *)col->data[col->size]) = *((int *)value);

    // Increment the size of the column
    col->size++;

    return 0; // Successful insertion
}

void print_cdataframe_col(const Column *col) {
    printf("%s: ", col->title);
    for (int i = 0; i < col->size; i++) {
        printf("%d ", col->data[i]);
    }
    printf("\n");
}



void fill_cdataframe_with_input(CDataframe *df) {
    if (df == NULL) {
        printf("Error: Null pointer to dataframe.\n");
        return;
    }

    // Get the number of rows and columns
    int num_rows, num_columns;
    printf("Enter the number of rows: ");
    scanf("%d", &num_rows);
    printf("Enter the number of columns: ");
    scanf("%d", &num_columns);

    // Set the dimensions of the dataframe
    df->num_columns = num_columns;
    df->capacity = num_rows;

    // Allocate memory for columns array
    df->columns = malloc(num_columns * sizeof(Column *));
    if (df->columns == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Prompt user to enter column titles
    for (int i = 0; i < num_columns; ++i)
        {
        char title[100];
        printf("Enter title for column %d: ", i + 1);
        scanf("%s", title);
        // Allocate memory for column structure
        df->columns[i] = malloc(sizeof(Column));
        if (df->columns[i] == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }

        // Set column title
        df->columns[i]->title = strdup(title);
        // Allocate memory for column data
        df->columns[i]->data = malloc(num_rows * sizeof(int));
        if (df->columns[i]->data == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        // Prompt user to input data for each column
        printf("Enter values for column %d:\n", i + 1);
        for (int j = 0; j < num_rows; ++j) {
            printf("Row %d: ", j + 1);
            scanf("%d", &df->columns[i]->data[j]);
        }
        // Set column size
        df->columns[i]->size = num_rows;
    }
}

void hard_fill_cdataframe(CDataframe *df) {
    if (df == NULL) {
        printf("Error: Null pointer to dataframe.\n");
        return;
    }

    // Predefined values to fill the dataframe
    int data[3][4] = {
        {10, 20, 30, 40},
        {50, 60, 70, 80},
        {90, 100, 110, 120}
    };

    // Set the dimensions of the dataframe
    int num_rows = 3;
    int num_columns = 4;
    df->num_columns = num_columns;
    df->capacity = num_rows; // Capacity for dynamic resizing if needed

    // Allocate memory for columns array
    df->columns = malloc(num_columns * sizeof(Column *));
    if (df->columns == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Create columns and insert predefined values
    for (int i = 0; i < num_columns; ++i) {
        char title[100];
        sprintf(title, "Column %d", i + 1);
        df->columns[i] = create_cdataframe();
        if (df->columns[i] == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        // Insert predefined values into the column
        for (int j = 0; j < num_rows; ++j) {
            insert_cdataframe_value(df->columns[i], data[j][i]);
        }
    }
}


void display_cdataframe(const CDataframe *df) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return;
    }

    // Display column titles
    for (int i = 0; i < df->num_columns; ++i) {
        printf("%s\t", df->columns[i]->title);
    }
    printf("\n");

    // Display data row by row
    for (int i = 0; i < df->capacity; ++i) {
        for (int j = 0; j < df->num_columns; ++j) {
            // Print data if it exists for the current row and column
            if (i < df->columns[j]->size) {
                printf("%d\t", df->columns[j]->data[i]);
            } else {
                printf("-\t"); // Placeholder for missing data
            }
        }
        printf("\n");
    }
}

void display_rows(const CDataframe *df, int limit) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return;
    }

    // Determine the number of rows to display
    int num_rows = df->capacity < limit ? df->capacity : limit;

    // Display column titles
    for (int i = 0; i < df->num_columns; ++i) {
        printf("%s\t", df->columns[i]->title);
    }
    printf("\n");

    // Display data row by row up to the limit
    for (int i = 0; i < num_rows; ++i) {
        for (int j = 0; j < df->num_columns; ++j) {
            // Print data if it exists for the current row and column
            if (i < df->columns[j]->size) {
                printf("%d\t", df->columns[j]->data[i]);
            } else {
                printf("-\t"); // Placeholder for missing data
            }
        }
        printf("\n");
    }
}


// Function to display a part of the columns according to a user-provided limit
void display_columns(const CDataframe *df, int limit) {
    if (df == NULL || df->columns == NULL) {
        // Handle null pointer case or empty dataframe
        printf("Error: Null pointer to dataframe or empty dataframe.\n");
        return;
    }

    // Determine the number of columns to display
    int num_columns = df->num_columns < limit ? df->num_columns : limit;

    // Display column titles
    for (int i = 0; i < num_columns; ++i) {
        printf("%s\t", df->columns[i]->title);
    }
    printf("\n");

    // Display data of each column
    for (int i = 0; i < num_columns; ++i) {
        printf("Column %d:\t", i + 1);
        for (int j = 0; j < df->columns[i]->size; ++j) {
            printf("%d\t", df->columns[i]->data[j]);
        }
        printf("\n");
    }
}


// Function to add a row of values to the CDataframe
void add_row(CDataframe *df, int *values, int num_values) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return;
    }

    if (num_values != df->num_columns) {
        printf("Error: Number of values does not match the number of columns.\n");
        return;
    }

    // Allocate memory for the new row
    for (int i = 0; i < df->num_columns; ++i) {
        insert_cdataframe_value(df->columns[i], values[i]);
    }

    // Update the dataframe's capacity if needed
    if (df->capacity <= df->columns[0]->size) {
        df->capacity *= 2;
        for (int i = 0; i < df->num_columns; ++i) {
            df->columns[i]->data = realloc(df->columns[i]->data, df->capacity * sizeof(int));
            if (df->columns[i]->data == NULL) {
                printf("Error: Memory allocation failed.\n");
                return;
            }
        }
    }
}

// Function to delete a row from the CDataframe
void delete_row(CDataframe *df, int row_index) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return;
    }

    // Check if row_index is valid
    if (row_index < 0 || row_index >= df->columns[0]->size) {
        printf("Error: Invalid row index.\n");
        return;
    }

    // Delete row data from each column
    for (int i = 0; i < df->num_columns; ++i) {
        for (int j = row_index; j < df->columns[i]->size - 1; ++j) {
            df->columns[i]->data[j] = df->columns[i]->data[j + 1];
        }
        // Decrease column size
        df->columns[i]->size--;
    }
}

// Function to rename a column in the CDataframe
void rename_column(CDataframe *df, const char *old_title, const char *new_title) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return;
    }

    // Find the column index with the old title
    int column_index = -1;
    for (int i = 0; i < df->num_columns; ++i) {
        if (strcmp(df->columns[i]->title, old_title) == 0) {
            column_index = i;
            break;
        }
    }

    if (column_index == -1) {
        printf("Error: Column with title '%s' not found.\n", old_title);
        return;
    }

    // Update the column's title to the new title
    free(df->columns[column_index]->title);
    df->columns[column_index]->title = strdup(new_title);
    if (df->columns[column_index]->title == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }
}


// Function to check the existence of a value in the CDataframe
#include <stdbool.h> // Include for boolean type

// Function to check if a value exists in the dataframe
bool search_value(const CDataframe *df, int value) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return false;
    }

    // Iterate over each column to search for the value
    for (int i = 0; i < df->num_columns; ++i) {
        Column *col = df->columns[i];
        for (int j = 0; j < col->size; ++j) {
            if (col->data[j] == value) {
                return true; // Value found
            }
        }
    }

    return false; // Value not found
}


// Function to access the value in a CDataframe cell using its row and column number
int get_value(const CDataframe *df, int row, int column) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return -1; // Return a sentinel value to indicate an error
    }

    // Check if the row index is valid
    if (row < 0 || row >= df->capacity) {
        printf("Error: Invalid row index.\n");
        return -1; // Return a sentinel value to indicate an error
    }

    // Check if the column index is valid
    if (column < 0 || column >= df->num_columns) {
        printf("Error: Invalid column index.\n");
        return -1; // Return a sentinel value to indicate an error
    }

    // Retrieve the value from the specified row and column
    if (row >= df->columns[0]->size) {
        printf("Error: Row index exceeds the number of rows with data.\n");
        return -1; // Return a sentinel value to indicate an error
    }

    return df->columns[column]->data[row];
}


// Function to replace the value in a CDataframe cell using its row and column number
void replace_value(CDataframe *df, int row, int column, int new_value) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return;
    }

    // Check if the row index is valid
    if (row < 0 || row >= df->capacity) {
        printf("Error: Invalid row index.\n");
        return;
    }

    // Check if the column index is valid
    if (column < 0 || column >= df->num_columns) {
        printf("Error: Invalid column index.\n");
        return;
    }

    // Check if the row index exceeds the number of rows with data
    if (row >= df->columns[0]->size) {
        printf("Error: Row index exceeds the number of rows with data.\n");
        return;
    }

    // Replace the value at the specified row and column
    df->columns[column]->data[row] = new_value;
}


// Function to display the column names of the CDataframe
void display_column_names(const CDataframe *df) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return;
    }

    // Display column names
    for (int i = 0; i < df->num_columns; ++i) {
        printf("%s\n", df->columns[i]->title);
    }
}

// Function to display the number of rows in the CDataframe
int num_rows(const CDataframe *df) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return 0;
    }

    // Get the number of rows by checking the size of any column
    // Assuming all columns have the same number of rows
    if (df->num_columns > 0) {
        return df->columns[0]->size;
    } else {
        return 0;
    }
}

// Function to display the number of columns in the CDataframe
int num_columns(const CDataframe *df) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return 0;
    }

    // Get the number of columns from the dataframe
    return df->num_columns;
}

// Function to display the number of cells equal to a given value in the CDataframe
int count_cells_equal_to(const CDataframe *df, int value) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return 0;
    }

    int count = 0;

    // Iterate over each column to count cells equal to the value
    for (int i = 0; i < df->num_columns; ++i) {
        for (int j = 0; j < df->columns[i]->size; ++j) {
            if (df->columns[i]->data[j] == value) {
                count++;
            }
        }
    }

    return count;
}

// Function to display the number of cells greater than a given value in the CDataframe
int count_cells_greater_than(const CDataframe *df, int value) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return 0;
    }

    int count = 0;

    // Iterate over each column to count cells greater than the value
    for (int i = 0; i < df->num_columns; ++i) {
        for (int j = 0; j < df->columns[i]->size; ++j) {
            if (df->columns[i]->data[j] > value) {
                count++;
            }
        }
    }

    return count;
}

// Function to display the number of cells less than a given value in the CDataframe
int count_cells_less_than(const CDataframe *df, int value) {
    if (df == NULL || df->columns == NULL) {
        printf("Error: Null pointer or empty dataframe.\n");
        return 0;
    }

    int count = 0;

    // Iterate over each column to count cells less than the value
    for (int i = 0; i < df->num_columns; ++i) {
        for (int j = 0; j < df->columns[i]->size; ++j) {
            if (df->columns[i]->data[j] < value) {
                count++;
            }
        }
    }

    return count;
}

void free_cdataframe(CDataframe *df) {
    if (df == NULL) {
        return; // Nothing to free if dataframe pointer is NULL
    }

    // Free memory for each column and its data
    for (int i = 0; i < df->num_columns; ++i) {
        Column *col = df->columns[i];
        free(col->title); // Free memory for the column title
        free(col->data);  // Free memory for the column data
        free(col);        // Free memory for the column structure itself
    }

    // Free memory for the columns array in the dataframe
    free(df->columns);

    // Free memory for the dataframe structure itself
    free(df);
}

void convert_value(Column *col, unsigned long long int i, char *str, int size) {
    // Check if the column and string are valid
    if (col == NULL || str == NULL) {
        printf("Invalid column or string.\n");
        return;
    }

    // Check if the index is within bounds
    if (i >= col->size) {
        printf("Index out of bounds.\n");
        return;
    }

    // Initialize string to empty
    str[0] = '\0';

    // Convert the integer value to string
    snprintf(str, size, "%d", col->data[i]);
}


void sort(COLUMN* col, int sort_dir) {
    // Check if the column has a valid index
    if (col->valid_index != 1) {
        printf("Column not sorted or index invalid.\n");
        return;
    }

    // Implement sorting algorithm based on sort_dir
    if (sort_dir == ASC) {
        // Apply Quick sort algorithm
        // Implementation omitted for brevity
    } else if (sort_dir == DESC) {
        // Apply Quick sort algorithm in descending order
        // Implementation omitted for brevity
    } else {
        printf("Invalid sort direction.\n");
    }
}

void print_col_by_index(Column *col) {
    if (col == NULL) {
        printf("Invalid column.\n");
        return;
    }

    if (col->index == NULL) {
        printf("Column not sorted or index invalid.\n");
        return;
    }

    printf("Column Title: %s\n", col->title);
    printf("Column Size: %u\n", col->size);

    // Print each element of the column according to its index
    for (unsigned int i = 0; i < col->size; ++i) {
        unsigned long long idx = &col->index[i];
        int *value_ptr = (int *)col->data[idx]; // Cast the void* to int*
        int value = *value_ptr; // Dereference to get the actual value

        printf("[%llu] %d\n", idx, value);
    }
}
void erase_index(COLUMN *col) {
    if (col == NULL) {
        printf("Invalid column.\n");
        return;
    }

    if (col->index != NULL) {
        free(col->index);
        col->index = NULL;
        col->valid_index = 0;
        printf("Index deleted successfully.\n");
    } else {
        printf("No index associated with the column.\n");
    }
}

int check_index(COLUMN *col) {
    if (col == NULL) {
        printf("Invalid column.\n");
        return 0;
    }

    if (col->index != NULL) {
        if (col->valid_index == 1) {
            printf("Index exists and is correct.\n");
            return 1;
        } else {
            printf("Index exists but is invalid.\n");
            return -1;
        }
    } else {
        printf("No index associated with the column.\n");
        return 0;
    }
}

void update_index(COLUMN *col) {
    if (col == NULL) {
        printf("Invalid column.\n");
        return;
    }

    if (col->valid_index != 1) {
        printf("Index is not valid, sorting the column...\n");
        sort(col, col->sort_dir);
    } else {
        printf("Column is already sorted.\n");
    }
}

int search_value_in_column(COLUMN *col, void *val) {
    if (col == NULL || col->data == NULL) {
        printf("Invalid column.\n");
        return -1; // or any other suitable error code
    }
    int target_value = *((int *)val);
    // Iterate through the column's data array to find the target value
    for (unsigned int i = 0; i < col->size; ++i) {
        if (*((int *)col->data[i]) == target_value) {
            return i; // Return the index if value is found
        }
    }

    // If the value is not found, return -1 or any other suitable error code
    return -1;
}


void delete_cdataframe(CDataframe **cdf) {
    if (*cdf == NULL) {
        printf("Invalid CDataframe.\n");
        return;
    }

    // Free memory for each column
    for (int i = 0; i < (*cdf)->num_columns; ++i) {
        Column *col = (*cdf)->columns[i];
        if (col != NULL) {
            if (col->data != NULL) {
                // Free data pointers
                for (int j = 0; j < col->size; ++j) {
                    free(col->data[j]);
                }
                free(col->data);
            }
            if (col->index != NULL) {
                free(col->index);
            }
            free(col->title);
            free(col);
        }
    }

    // Free memory for columns array and CDataframe itself
    free((*cdf)->columns);
    free(*cdf);
    *cdf = NULL;

    printf("CDataframe deleted successfully.\n");
}