#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "accounts.dat"

typedef struct {
    int accountNumber;
    char name[100];
    double balance;
} Account;

void createAccount();
void balanceInquiry();
void depositMoney();
void withdrawMoney();
void accountManagement();
int getAccountIndex(int accountNumber, Account *accounts, int totalAccounts);

int main() {
    int choice;

    while (1) {
        printf("\nBank Management System\n");
        printf("1. Create Account\n");
        printf("2. Balance Inquiry\n");
        printf("3. Deposit Money\n");
        printf("4. Withdraw Money\n");
        printf("5. Account Management\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                balanceInquiry();
                break;
            case 3:
                depositMoney();
                break;
            case 4:
                withdrawMoney();
                break;
            case 5:
                accountManagement();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}

void createAccount() {
    Account account;
    FILE *file = fopen(FILENAME, "ab");

    printf("Enter account number: ");
    scanf("%d", &account.accountNumber);
    printf("Enter name: ");
    scanf("%s", account.name);
    account.balance = 0.0;

    fwrite(&account, sizeof(Account), 1, file);
    fclose(file);

    printf("Account created successfully.\n");
}

void balanceInquiry() {
    int accountNumber;
    Account account;
    FILE *file = fopen(FILENAME, "rb");

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    while (fread(&account, sizeof(Account), 1, file)) {
        if (account.accountNumber == accountNumber) {
            printf("Account Number: %d\n", account.accountNumber);
            printf("Name: %s\n", account.name);
            printf("Balance: %.2f\n", account.balance);
            fclose(file);
            return;
        }
    }

    printf("Account not found!\n");
    fclose(file);
}

void depositMoney() {
    int accountNumber;
    double amount;
    Account account;
    FILE *file = fopen(FILENAME, "rb+");
    int found = 0;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);

    while (fread(&account, sizeof(Account), 1, file)) {
        if (account.accountNumber == accountNumber) {
            account.balance += amount;
            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&account, sizeof(Account), 1, file);
            found = 1;
            break;
        }
    }

    if (found) {
        printf("Amount deposited successfully.\n");
    } else {
        printf("Account not found!\n");
    }

    fclose(file);
}

void withdrawMoney() {
    int accountNumber;
    double amount;
    Account account;
    FILE *file = fopen(FILENAME, "rb+");
    int found = 0;
    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);

    while (fread(&account, sizeof(Account), 1, file)) {
        if (account.accountNumber == accountNumber) {
            if (account.balance >= amount) {
                account.balance -= amount;
                fseek(file, -sizeof(Account), SEEK_CUR);
                fwrite(&account, sizeof(Account), 1, file);
                found = 1;
                printf("Amount withdrawn successfully.\n");
            } else {
                printf("Insufficient balance!\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}

void accountManagement() {
    int accountNumber;
    Account account;
    FILE *file = fopen(FILENAME, "rb+");
    int found = 0;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    while (fread(&account, sizeof(Account), 1, file)) {
        if (account.accountNumber == accountNumber) {
            printf("Enter new name: ");
            scanf("%s", account.name);
            fseek(file, -sizeof(Account), SEEK_CUR);
            fwrite(&account, sizeof(Account), 1, file);
            found = 1;
            printf("Account details updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }

    fclose(file);
}