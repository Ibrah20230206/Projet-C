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
    printf("\nTesting dataframe operations:\n");
    CDataframe *df = create_cdataframe();

    printf("Filling dataframe with user input:\n");
    fill_cdataframe_with_input(df);
    display_cdataframe(df);

    // Free and recreate the dataframe to not mix user input with hardcoded data
    free_cdataframe(df);
    df = create_cdataframe();

    printf("\nFilling dataframe with hardcoded data:\n");
    hard_fill_cdataframe(df);
    display_cdataframe(df);

    free_cdataframe(df);
    return 0;
}


