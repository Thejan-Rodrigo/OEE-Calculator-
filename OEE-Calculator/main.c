#include <stdio.h>
#include <stdlib.h>

#define USERDATA "userData.txt"
#define PRODUCTIONDATA "production_data.txt"
#define PRODUCTIONTIME 480

// Function to compare two strings manually
int are_strings_equal(const char *str1, const char *str2) {
    // Compare each character one by one
    while (*str1 != '\0' && *str2 != '\0') {
        if (*str1 != *str2) {
            return 0;  // Strings are not equal
        }
        str1++;
        str2++;
    }

    // Check if both strings ended at the same time (same length)
    return *str1 == *str2;
}

// Function to check if username already exists
int username_exists(const char *username) {
    FILE *file = fopen(USERDATA, "r");
    if (file == NULL) {
        return 2; // File doesn't exist, no usernames yet
    }

    char stored_username[100];
    char stored_password[100];
    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF) {
        if (are_strings_equal(stored_username ,username) == 1) {
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

int authenticate(const char *username, const char *password) {
    FILE *file = fopen(USERDATA, "r");
    if (file == NULL) {
        return 2;
    }

    char stored_username[100];
    char stored_password[100];
    while (fscanf(file, "%s %s", stored_username, stored_password) != EOF) {
        if (are_strings_equal(stored_username, username) == 1 && are_strings_equal(stored_password, password) == 1) {
            fclose(file);
            return 1; // Authentication successful
        }
    }

    fclose(file);
    return 0; // Authentication failed
}

// Function to calculate availability
float calculate_availability(float operating_time, float planned_production_time) {
    return operating_time / planned_production_time;
}

// Function to calculate performance
float calculate_performance(float pieces_produced, float ideal_speed, float operating_time) {
    return (pieces_produced / (ideal_speed * operating_time)) * 100;
}

// Function to calculate quality
float calculate_quality(float acceptable_pieces, float total_pieces) {
    return (acceptable_pieces / total_pieces) * 100;
}

// Function to calculate OEE
float calculate_oee(float availability, float performance, float quality) {
    return (availability * performance * quality) / 10000;  // OEE is percentage, so divided by 10000
}

int main()
{
    while(1){
        int choice;
        char username[100];
        char password[100];
        FILE *production_file;
        FILE *summery_file;
        float planned_break_time;
        float unplanned_downtime;
        float ideal_speed;
        float total_panels_produced;
        float scrap_panels;
        float planned_production_time;
        float operating_time;
        float pieces_produced;
        float acceptable_pieces;
        float availability;
        float performance;
        float quality;
        float oee;

        printf("Overall Equipment Effectiveness Calculator\n");
        printf("--------------------------------------------\n");
        printf(" \n");
        printf("1. Login\n");
        printf("2. Create Account\n");
        printf("3. Exit\n");
        printf(" \n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        printf(" \n");

        switch(choice){
         case 1:
            printf("Login Page\n");
            printf("------------------\n");
            printf("Enter username: ");
            scanf("%s", &username);
            printf("Enter password: ");
            scanf("%s", &password);
            int isUser = authenticate(username, password);
            switch(isUser){
                case 0:
                    printf(" \n");
                    printf("Authentication failed! Please try again! \n");
                    printf(" \n");
                    break;
                case 1:

                    production_file = fopen(PRODUCTIONDATA, "r");
                    if (production_file == NULL) {
                        printf(" \n");
                        printf("Error: Could not open production file.\n");
                        printf(" \n");
                    }

                    // Read data from the file (assuming one value per line)
                    if (fscanf(production_file, "%f", &planned_break_time) != 1 ||
                        fscanf(production_file, "%f", &unplanned_downtime) != 1 ||
                        fscanf(production_file, "%f", &ideal_speed) != 1 ||
                        fscanf(production_file, "%f", &total_panels_produced) != 1 ||
                        fscanf(production_file, "%f", &scrap_panels) != 1) {
                            printf(" \n");
                            printf("Error: Invalid or incomplete data in the input file.\n");
                            printf(" \n");
                            fclose(production_file);
                    }

                    fclose(production_file);

                    // Calculate the planned production time
                    planned_production_time = PRODUCTIONTIME - planned_break_time;

                    // Calculate operating time (planned production time - unplanned downtime)
                    operating_time = planned_production_time - unplanned_downtime;

                    // Calculate total pieces produced (acceptable pieces + scrap pieces)
                    pieces_produced = total_panels_produced;
                    acceptable_pieces = total_panels_produced - scrap_panels;

                    availability = calculate_availability(operating_time, planned_production_time);
                    performance = calculate_performance(pieces_produced, ideal_speed, operating_time);
                    quality = calculate_quality(acceptable_pieces, total_panels_produced);
                    oee = calculate_oee(availability, performance, quality);

                    printf(" \n");
                    printf("Production Data Summary Report\n");
                    printf("------------------------------------\n");
                    printf("Planned Break Time: %.2f minutes\n", planned_break_time);
                    printf("Unplanned Downtime: %.2f minutes\n", unplanned_downtime);
                    printf("Ideal Machine Rate: %.2f panels per minute\n", ideal_speed);
                    printf("Total Panels Produced: %.2f\n", total_panels_produced);
                    printf("Scrap Panels: %.2f\n", scrap_panels);
                    printf("------------------------------------\n");

                    // Display results on the console
                    printf(" \n");
                    printf("Availability: %.2f%%\n", availability * 100);
                    printf("Performance: %.2f%%\n", performance);
                    printf("Quality: %.2f%%\n", quality);
                    printf("OEE: %.2f%%\n", oee * 100);
                    printf(" \n");

                    // Open the output file to write the report
                    summery_file = fopen("oee_report.txt", "w");
                    if (summery_file == NULL) {
                        printf(" \n");
                        printf("Error: Could not open production file.\n");
                        printf(" \n");
                    }

                    // Write the results to the output file
                    fprintf(production_file, "Production Data Summary Report\n");
                    fprintf(production_file, "------------------------------------\n");
                    fprintf(production_file, "Planned Break Time: %.2f minutes\n", planned_break_time);
                    fprintf(production_file, "Unplanned Downtime: %.2f minutes\n", unplanned_downtime);
                    fprintf(production_file, "Ideal Machine Rate: %.2f panels per minute\n", ideal_speed);
                    fprintf(production_file, "Total Panels Produced: %.2f\n", total_panels_produced);
                    fprintf(production_file, "Scrap Panels: %.2f\n", scrap_panels);
                    fprintf(production_file, "------------------------------------\n");

                    fprintf(production_file, "OEE Calculation Components:\n");
                    fprintf(production_file, "------------------------------------\n");
                    fprintf(production_file, "Availability: %.2f%%\n", availability * 100);
                    fprintf(production_file, "Performance: %.2f%%\n", performance);
                    fprintf(production_file, "Quality: %.2f%%\n", quality);
                    fprintf(production_file, "OEE: %.2f%%\n", oee * 100);

                    // Check if OEE is above or below 80%
                    if (oee >= 0.80) {
                        printf("The production line is performing well, with an OEE of 80 or higher, meeting the target standards..\n");
                        printf(" \n");
                        fprintf(production_file, "The production line is performing well, with an OEE of 80 or higher, meeting the target standards..\n");
                    } else {
                        printf("The production line is falling short of the target, with an OEE below 80. Improvement is needed to meet the required standards.\n");
                        printf(" \n");
                        fprintf(production_file, "The production line is falling short of the target, with an OEE below 80%. Improvement is needed to meet the required standards.\n");
                    }

                    // Close the output file
                    fprintf(production_file, "------------------------------------\n");
                    fclose(production_file);

                    continue;
                case 2:
                    printf(" \n");
                    printf("Error opening file that in path %s .\n", USERDATA);
                    printf(" \n");
                    break;
            }
            continue;

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

          case 3:
              printf(" \n");
              printf("Good Bye!\n");
              printf(" \n");
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
