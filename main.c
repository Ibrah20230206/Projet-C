#include <stdio.h>
#include "cdataframe.h"
#include "list.h"

int main() {
    // Test create_column and insert_value functions
    Column *col1 = create_column("Column 1");
    insert_value(col1, 10);
    insert_value(col1, 20);
    insert_value(col1, 30);

    // Test print_col function
    printf("Column :\n");
    print_col(col1);

    // Test delete_column function
    delete_column(&col1);

    // Test count_value function
    Column *col2 = create_column("My column");
    insert_value(col2, 10);
    insert_value(col2, 20);
    insert_value(col2, 30);
    insert_value(col2, 10);
    printf("Count of value 10 in my column: %d\n", count_value(col2, 10));

    // Test value_at_index function
    printf("Value at index 2 in my column: %d\n", value_at_index(col2, 2));

    // Test find_max function
    printf("Max value in my column: %d\n", find_max(col2));

    // Test count_less_than function
    printf("Count of values less than 20 in my column: %d\n", count_less_than(col2, 20));

    // Test count_equals_x function
    printf("Count of values equal to 10 in my column: %d\n", count_equals_x(col2, 10));


    // Test create_cdataframe and fill_cdataframe_with_input functions
    printf("\nCreating and filling a CDataframe from user input...\n");
    CDataframe *df1 = create_cdataframe();
    fill_cdataframe_with_input(df1);
    display_cdataframe(df1);

    // Test sort function
 printf("\nSorting the first column in ascending order...\n");
    sort(df1->columns[0], ASC);
    display_cdataframe(df1);

    // Allocate memory space here
    // For example:
    // Let's allocate memory for an array of 100 integers
    int *dynamic_array = (int *)malloc(100 * sizeof(int));
    if (dynamic_array == NULL) {
        printf("Memory allocation failed.\n");
        return 1; // Or handle the failure in some appropriate way
    }

    // Now you can use dynamic_array like a regular array

    // Test add_row function
    printf("\nAdding a row to the CDataframe...\n");
    int new_row[] = {130, 140, 150, 160};
    add_row(df1, new_row, 4);
    display_cdataframe(df1);

    // Don't forget to free the allocated memory when you're done using it
    free(dynamic_array);

    // Test delete_row function
    printf("\nDeleting a row from the CDataframe...\n");
    delete_row(df1, 1);
    display_cdataframe(df1);

    // Test rename_column function
    printf("\nRenaming a column in the CDataframe...\n");
    rename_column(df1, "Column2", "Renamed Column");
    display_cdataframe(df1);

    // Test search_value function
    printf("\nSearching for a value in the CDataframe...\n");
    printf("Value 100 exists in the CDataframe: %s\n", search_value(df1, 100) ? "true" : "false");

    // Test get_value function
    printf("\nAccessing a value in the CDataframe...\n");
    printf("Value at row 1, column 2: %d\n", get_value(df1, 0, 1));

    // Test replace_value function
    printf("\nReplacing a value in the CDataframe...\n");
    replace_value(df1, 0, 1, 200);
    display_cdataframe(df1);

    // Test display_column_names function
    printf("\nDisplaying column names of the CDataframe...\n");
    display_column_names(df1);

    // Test num_rows function
    printf("\nNumber of rows in the CDataframe: %d\n", num_rows(df1));

    // Test num_columns function
    printf("Number of columns in the CDataframe: %d\n", num_columns(df1));

    // Test count_cells_equal_to function
    printf("Number of cells equal to 150 in the CDataframe: %d\n", count_cells_equal_to(df1, 150));

    // Test count_cells_greater_than function
    printf("Number of cells greater than 100 in the CDataframe: %d\n", count_cells_greater_than(df1, 100));

    // Test count_cells_less_than function
    printf("Number of cells less than 150 in the CDataframe: %d\n", count_cells_less_than(df1, 150));

    // Test load_from_csv function
    printf("\nLoading data from CSV file...\n");
    ENUM_TYPE dftype[] = {INT, INT, INT, INT};
    CDataframe *csv_df = load_from_csv("data.csv", dftype, 4);
    if (csv_df != NULL) {
        display_cdataframe(csv_df);
    }

    // Test save_into_csv function
    printf("\nSaving dataframe into CSV file...\n");
    save_into_csv(df1, "saved_data.csv");

    delete_cdataframe(&df1);

}

