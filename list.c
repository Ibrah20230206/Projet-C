//
// Created by Ibrahima Sory Diallo on 07/05/2024.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

CDataframe* load_from_csv(char *file_name, ENUM_TYPE *dftype, int size) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error: Failed to open file for reading.\n");
        return NULL;
    }

    // Create a new CDataframe
    CDataframe *cdf = create_cdataframe();
    if (cdf == NULL) {
        fclose(file);
        printf("Error: Failed to create CDataframe.\n");
        return NULL;
    }

    // Read data from the CSV file
    char line[1024];
    while (fgets(line, sizeof(line), file)) {
        char *token = strtok(line, ",");
        int col_index = 0;
        while (token != NULL && col_index < size) {
            // Insert value into the dataframe based on the specified column type
            switch (dftype[col_index]) {
                case INT: {
                    int int_value = atoi(token);
                    insert_cdataframe_value(cdf->columns[col_index], &int_value);
                    break;
                }
                case FLOAT: {
                    float float_value = atof(token);
                    insert_cdataframe_value(cdf->columns[col_index], &float_value);
                    break;
                }
                case STRING:
                    insert_cdataframe_value(cdf->columns[col_index], token);
                break;
                // Add cases for other column types as needed
            }
            token = strtok(NULL, ",");
            col_index++;
        }
    }

    fclose(file);
    return cdf;
}

// Function to export a CDataframe to a CSV file
void save_into_csv(CDataframe *cdf, char *file_name) {
    FILE *file = fopen(file_name, "w");
    if (file == NULL) {
        printf("Error: Failed to open file for writing.\n");
        return;
    }

    // Write data from the dataframe to the CSV file
    for (int row = 0; row < num_rows(cdf); row++) {
        for (int col = 0; col < cdf->num_columns; col++) {
            switch (cdf->columns[col]->column_type) {
                case INT:
                    fprintf(file, "%d", *((int*)cdf->columns[col]->data[row]));
                    break;
                case FLOAT:
                    fprintf(file, "%.2f", *((float*)cdf->columns[col]->data[row]));
                    break;
                case STRING:
                    fprintf(file, "%s", (char*)cdf->columns[col]->data[row]);
                    break;
                // Add cases for other column types as needed
            }
            if (col < cdf->num_columns - 1) {
                fprintf(file, ",");
            }
        }
        fprintf(file, "\n");
    }

    fclose(file);
}

lnode *lst_create_lnode(void *dat) {
    lnode *ptmp = (lnode *) malloc(sizeof(lnode));
    ptmp->data = dat;
    ptmp->next = NULL;
    ptmp->prev = NULL;
    return ptmp;
}
list *lst_create_list() {
    list *lst = (list *) malloc(sizeof(list));
    lst->head = NULL;
    lst->tail = NULL;
    return lst;
}
void lst_delete_list(list * lst) {
    lst_erase(lst);
    free(lst);
}
void lst_insert_head(list * lst, lnode * pnew) {
    if (lst->head == NULL) {
        lst->head = pnew;
        lst->tail = pnew;
        return;
    }
    pnew->next = lst->head;
    pnew->prev = NULL;
    lst->head = pnew;
    pnew->next->prev = pnew;
}
void lst_insert_tail(list * lst, lnode * pnew) {
    if (lst->head == NULL) {
        lst->head = pnew;
        lst->tail = pnew;
        return;
    }
    pnew->next = NULL;
    pnew->prev = lst->tail;
    lst->tail = pnew;
    pnew->prev->next = pnew;
}
void lst_insert_after(list * lst, lnode * pnew, lnode * ptr) {
    if (lst->head == NULL) {
        lst->head = pnew;
        lst->tail = pnew;
    } else if (ptr == NULL) {
        return;
    } else if (lst->tail == ptr) {
        lst_insert_tail(lst, pnew);
    } else {
        pnew->next = ptr->next;
        pnew->prev = ptr;
        pnew->next->prev = pnew;
        pnew->prev->next = pnew;
    }
}
void lst_delete_head(list * lst) {
    if (lst->head->next == NULL) {free(lst->head);
        lst->head = NULL;
        lst->tail = NULL;
        return;
    }
    lst->head = lst->head->next;
    free(lst->head->prev);
    lst->head->prev = NULL;
}
void lst_delete_tail(list * lst) {
    if (lst->tail->prev == NULL) {
        free(lst->tail);
        lst->head = NULL;
        lst->tail = NULL;
        return;
    }
    lst->tail = lst->tail->prev;
    free(lst->tail->next);
    lst->tail->next = NULL;
}
void lst_delete_lnode(list * lst, lnode * ptr) {
    if (ptr == NULL)
        return;
    if (ptr == lst->head) {
        lst_delete_head(lst);
        return;
    }
    if (ptr == lst->tail) {
        lst_delete_tail(lst);
        return;
    }
    ptr->next->prev = ptr->prev;
    ptr->prev->next = ptr->next;
    free(ptr);
}
void lst_erase(list * lst) {
    if (lst->head == NULL)
        return;
    while (lst->head != lst->tail) {
        lst->head = lst->head->next;
        free(lst->head->prev);
    }
    free(lst->head);
    lst->head = NULL;
    lst->tail = NULL;
}
lnode *get_first_node(list * lst) {
    if (lst->head == NULL)
        return NULL;
    return lst->head;
}
lnode *get_last_node(list * lst) {
    if (lst->tail == NULL)
        return NULL;
    return lst->tail;
}
lnode *get_next_node(list * lst, lnode * lnode) {
    if (lnode == NULL)
        return NULL;
    return lnode->next;
}
void *get_previous_elem(list * lst, lnode * lnode) {
    if (lnode == NULL)
        return NULL;
    return lnode->prev;
}