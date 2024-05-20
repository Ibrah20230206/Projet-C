#include "column.h"
#include "cdataframe.h"


int main() {
    // Testing individual column operations
    printf("Testing individual column operations:\n");
    Column *my_col = create_column("My column");
    insert_value(my_col, 10);
    insert_value(my_col, 20);
    insert_value(my_col, 10);
    insert_value(my_col, 30);
    print_col(my_col);

    // Display various statistics and counts
    printf("Occurrences of 10: %d\n", count_value(my_col, 10));
    printf("Value at index 1: %d\n", value_at_index(my_col, 1));
    printf("Maximum value: %d\n", find_max(my_col));
    printf("Number of values less than 15: %d\n", count_less_than(my_col, 20));
    printf("Number of values equal to 10: %d\n", count_equals_x(my_col, 30));

    // Clean up memory for column
    delete_column(&my_col);

    // Testing dataframe operations
   // Create a dataframe
    CDataframe *df = create_cdataframe();

    // Fill the dataframe with user input
    printf("Filling dataframe with user input:\n");
    fill_cdataframe_with_input(df);
    display_cdataframe(df);

    // Hard fill the dataframe
    printf("\nFilling dataframe with hardcoded data:\n");
    hard_fill_cdataframe(df);
    display_cdataframe(df);

    // Display rows
    printf("\nDisplaying first 3 rows:\n");
    display_rows(df, 3);

    // Display columns
    printf("\nDisplaying first 2 columns:\n");
    display_columns(df, 2);

    // Add a row
    int new_row_values[] = {99, 88, 77};
    add_row(df, new_row_values, 3);
    printf("\nAdding a new row:\n");
    display_cdataframe(df);

    // Delete a row
    printf("\nDeleting row at index 1:\n");
    delete_row(df, 1);
    display_cdataframe(df);

    // Rename a column
    printf("\nRenaming column 'Column 1' to 'New Column 1':\n");
    rename_column(df, "Column 1", "New Column 1");
    display_cdataframe(df);

    // Search for a value
    printf("\nSearching for value 42 in the dataframe: %s\n", search_value(df, 42) ? "Found" : "Not found");

    // Get a value
    printf("\nValue at row 0, column 1: %d\n", get_value(df, 0, 1));

    // Replace a value
    printf("\nReplacing value at row 0, column 1 with 99:\n");
    replace_value(df, 0, 1, 99);
    display_cdataframe(df);

    // Display column names
    printf("\nDisplaying column names:\n");
    display_column_names(df);

    // Get number of rows and columns
    printf("\nNumber of rows: %d\n", num_rows(df));
    printf("Number of columns: %d\n", num_columns(df));

    // Count cells equal to, greater than, and less than a value
    printf("\nCount cells equal to 42: %d\n", count_cells_equal_to(df, 42));
    printf("Count cells greater than 50: %d\n", count_cells_greater_than(df, 50));
    printf("Count cells less than 30: %d\n", count_cells_less_than(df, 30));

    // Free dataframe memory
    free_cdataframe(df);

    return 0;
}