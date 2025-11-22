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

int main()
{
    while(1){
        int choice;
        char username[100];

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
                      break;
                  case 1:
                      printf(" \n");
                      printf("User Name Exists! Please User another User name\n");
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


            break;
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
