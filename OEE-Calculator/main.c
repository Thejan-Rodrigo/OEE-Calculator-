#include <stdio.h>
#include <stdlib.h>

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
            printf("Create Account\n");
            printf("------------------\n");
            printf("Enter username: ");
            scanf("%s", &username);
            printf("user name is %s \n", username);
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
