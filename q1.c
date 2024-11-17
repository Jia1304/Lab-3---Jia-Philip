#include <stdio.h>  //for input/output functions
#include <stdbool.h>  //for boolean data type

#define SIZE 24       //size of the main array
#define nRows 8       //number of rows for 2D reshaping
#define nCols 3       //number of columns for 2D reshaping

//Function Prototypes
void print_array(int array[], int length); //prints a 1D array
bool isValid(int length, int pos); //checks if a position is valid
void remove_element(int arr[], int *length, int pos); //removes an element from a 1D array
void insert_element(int arr[], int *length, int pos, int value); //inserts an element into a 1D array
void reshape(const int arr[], int length, int arr2d[nRows][nCols]); //reshapes a 1D array into a 2D array
void trans_matrix(const int mat[nRows][nCols], int mat_transp[nCols][nRows]); //transposes a 2D matrix
bool found_duplicate(int arr[], int length); //checks if there are duplicates in a 1D array

int main() {
    int arr[SIZE];  //main array to store elements
    int arr2d[nRows][nCols];  //2D array for reshaping
    int user_choice, position, new_elem, length = SIZE;  //user input variables

    //Initialize the array with sequential values (0 to SIZE-1)
    for (int i = 0; i < SIZE; i++) {
        arr[i] = i;
    }

    //Main program loop
    while (1) {
        //display the menu options
        printf("\nMain Menu\n");
        printf("1. Remove Element\n");
        printf("2. Insert Element\n");
        printf("3. Reshape Matrix\n");
        printf("4. Transpose Matrix\n");
        printf("5. Check for Duplicates\n");
        printf("0. Exit\n");
        printf("Please choose your preference: ");
        scanf("%d", &user_choice); //read user choice

        //Process user choice using a switch statement
        switch (user_choice) {
            case 1: //remove an element
                printf("Enter position to remove: ");
                scanf("%d", &position);
                if (isValid(length, position)) { //validate position
                    remove_element(arr, &length, position); //remove element
                    print_array(arr, length); //display the updated array
                } else {
                    printf("Position out of bounds!\n");
                }
                break;

            case 2: //insert an element
                printf("Enter position to insert: ");
                scanf("%d", &position);
                printf("Enter value to insert: ");
                scanf("%d", &new_elem);
                if (isValid(length, position)) { //validate position
                    insert_element(arr, &length, position, new_elem); //insert element
                    print_array(arr, length); //display the updated array
                } else {
                    printf("Invalid position!\n");
                }
                break;

            case 3: //reshape the array into a 2D matrix
                reshape(arr, length, arr2d);
                printf("Reshaped Matrix:\n");
                for (int i = 0; i < nRows; i++) { //print the 2D matrix
                    for (int j = 0; j < nCols; j++) {
                        printf("%d ", arr2d[i][j]);
                    }
                    printf("\n");
                }
                break;

            case 4: //transpose the 2D matrix
                reshape(arr, length, arr2d); //first reshape the array
                int mat_transpose[nCols][nRows]; //create a matrix to hold the transpose
                trans_matrix(arr2d, mat_transpose); //perform the transpose
                printf("Transposed Matrix:\n");
                for (int i = 0; i < nCols; i++) { //print the transposed matrix
                    for (int j = 0; j < nRows; j++) {
                        printf("%d ", mat_transpose[i][j]);
                    }
                    printf("\n");
                }
                break;

            case 5: //check for duplicates in the array
                if (found_duplicate(arr, length)) {
                    printf("Array has duplicates.\n");
                } else {
                    printf("No duplicates in the array.\n");
                }
                break;

            case 0: //exit the program
                return 0;

            default: //handle invalid input
                printf("Invalid input! Please try again.\n");
                break;
        }
    }
}

//prints a 1D array
void print_array(int array[], int length) {
    printf("Array: ");
    for (int i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

//checks if a position is valid in the array
bool isValid(int length, int pos) {
    return pos >= 0 && pos < length; // Valid if within array bounds
}

//removes an element at a specified position in the array
void remove_element(int arr[], int *length, int pos) {
    if (isValid(*length, pos)) {
        for (int i = pos; i < *length - 1; i++) {
            arr[i] = arr[i + 1]; //shift elements to the left
        }
        (*length)--; //decrease the size of the array
    } else {
        printf("Invalid position!\n");
    }
}

//inserts an element at a specified position in the array
void insert_element(int arr[], int *length, int pos, int value) {
    if (isValid(*length, pos)) {
        for (int i = *length; i > pos; i--) {
            arr[i] = arr[i - 1]; //shift elements to the right
        }
        arr[pos] = value; //insert the new value
        (*length)++; //increase the size of the array
    } else {
        printf("Invalid position!\n");
    }
}

//reshapes a 1D array into a 2D array of size nRows x nCols
void reshape(const int arr[], int length, int arr2d[nRows][nCols]) {
    int index = 0; //tracks the current element in the 1D array
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            arr2d[i][j] = arr[index++]; //fill the 2D array row by row
        }
    }
}

//transposes a 2D matrix (swaps rows and columns)
void trans_matrix(const int mat[nRows][nCols], int mat_transp[nCols][nRows]) {
    for (int i = 0; i < nRows; i++) {
        for (int j = 0; j < nCols; j++) {
            mat_transp[j][i] = mat[i][j]; //swap rows and columns
        }
    }
}

//checks if the array contains duplicate elements
bool found_duplicate(int arr[], int length) {
    for (int i = 0; i < length; i++) {
        for (int j = i + 1; j < length; j++) {
            if (arr[i] == arr[j]) { //check for matching elements
                return true; //duplicate found
            }
        }
    }
    return false; //no duplicates
}
