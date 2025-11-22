#include <stdio.h>
#include <stdlib.h>

#define USERDATA "userData.txt"

// Function to check if username already exists
int username_exists(const char *username) {
    FILE *file = fopen(USERDATA, "r");
    if (file == NULL) {
        return 2; // File doesn't exist, no usernames yet
    }

    char stored_username[100], stored_password[100];
    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF) {
        if (strcmp(stored_username, username) == 0) {
            fclose(file);
            return 1; // Username exists
        }
    }

    fclose(file);
    return 0; // Username does not exist
}

// Function to create a new user
void create_account(const char *username, const char *password) {
    FILE *file = fopen(USERDATA, "a");
    if (file == NULL) {
        printf(" \n");
        printf("Error opening file that in path %s .\n", USERDATA);
        printf(" \n");
        return;
    }

    fprintf(file, "%s %s\n", username, password);
    fclose(file);
    printf(" \n");
    printf("Account created successfully.\n");
    printf(" \n");
}

int main()
{
    while(1){
        int choice;
        char username[100];
        char password[100];

        printf("Overall Equipment Effectiveness Calculator\n");
        printf("--------------------------------------------\n");
        printf(" \n");
        printf("1. Login\n");
        printf("2. Create Account\n");
        printf(" \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf(" \n");

        switch(choice){
         case 1:
            printf("Login Page!");
            break;
         case 2:
            while(1){
                printf("Create Account\n");
                printf("------------------\n");
                printf("Enter username: ");
                scanf("%s", &username);
                int isExists = username_exists(username);
                switch(isExists){
                  case 0:
                      printf("Enter password: ");
                      scanf("%s", &password);
                      create_account(username, password);
                      break;
                  case 1:
                      printf(" \n");
                      printf("User Name Exists! Please Use another Username\n");
                      printf(" \n");
                      continue;
                  case 2:
                      printf(" \n");
                      printf("Can not find the for the path %s . \n", USERDATA);
                      printf(" \n");
                      break;
                }
                break;
            }
            continue;
         default:
            printf(" \n");
            printf("Invalid choice selected!\n");
            printf(" \n");
            continue;
        }
        break;
    }
    return 0;
}
