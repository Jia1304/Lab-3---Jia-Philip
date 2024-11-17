#include <stdio.h>

void process_transactions(int transactions[], int num_transactions) {
    int balance = 1000;  //initial balance
    int tobeprocessed[100];  //array to store unprocessed transactions
    int tobeprocessed_count = 0;  //counter for unprocessed transactions

    //Process each transaction
    for (int i = 0; i < num_transactions; i++) {
        int transaction = transactions[i];

        if (transaction < 0) {  //withdrawal
            if (-transaction > balance) {
                printf("Invalid transaction: Withdrawal of %d exceeds available balance of %d.\n", -transaction, balance);
                tobeprocessed[tobeprocessed_count++] = transaction;  // Store unprocessed withdrawal
            } else {
                balance += transaction;  //deduct the withdrawal
                printf("Processed withdrawal of %d. New balance: %d AED.\n", -transaction, balance);
            }
        } else {  //deposit
            balance += transaction;  //add the deposit
            printf("Processed deposit of %d. New balance: %d AED.\n", transaction, balance);
        }

        //stop processing if balance reaches 0 or below
        if (balance <= 0) {
            printf("Balance has reached 0 AED. No further transactions will be processed.\n");
            tobeprocessed[tobeprocessed_count++] = transaction;  //store the last transaction
            break;
        }
    }

    //after processing all transactions
    printf("Final balance: %d AED.\n", balance);
    printf("Unprocessed transactions: ");
    for (int i = 0; i < tobeprocessed_count; i++) {
        printf("%d ", tobeprocessed[i]);
    }
    printf("\n");
}

int main() {
    //test with the provided transactions
    int transactions[] = {200, -150, -500, -400, -50, -200, 300};
    int num_transactions = sizeof(transactions) / sizeof(transactions[0]);

    process_transactions(transactions, num_transactions);
    return 0;
}

