#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

char logged_in_user[1000];
char *cities[] = {"Karachi", "Lahore", "Islamabad", "Peshawar", "Quetta"};

int user_signup();
int user_login();
int user_menu();
void seats();
void selectCities(char *from, char *to);
void displayBusTypes(char *from, char *to);
void calculateFare(char *from, char *to, char *busType); // Declare this function

int main()
{
    char input[50];
    int choice;

    while (1)
    {
        printf("\n\t====Bus Reservation System====\n");
       
        printf("\n\t1. Sign-Up\n");
        printf("\n\t2. Login\n");
        printf("\n\t3. Exit\n");
        printf("\n\tEnter your choice: ");
        fgets(input, 50, stdin);

        if (sscanf(input, "%d", &choice) == 1)
        {

            if (choice == 1)
            {
                user_signup();
            }
            else if (choice == 2)
            {
                user_login();
            }
            else if (choice == 3)
            {
                printf("\n\tEXISTING.........\n");
                sleep(2);
                break;
            }
        }
        else
        {
            printf("\nInvalid Input, Please input options (1-3)\n");
        }
    }

    return 0;
}

int user_signup()
{
    FILE *fptr = fopen("login-details.txt", "a");
    printf("\n\t===Welcome To SIGN-UP From===\n\n");
    printf("\tPlease Sign-Up:\n");
    printf("\n\tEnter your username: ");
    scanf("%s", logged_in_user);
    printf("\n\tEnter your password: ");
    char org_pass[100];
    scanf("%s", org_pass);

    fprintf(fptr, "%s  %s\n", logged_in_user, org_pass);
    fflush(stdin);
    fclose(fptr);
    printf("\n\n\tSIGN-UP Succesfully..!\n");
    return 1;
}

int user_login()
{
    FILE *ptr = fopen("login-details.txt", "r");
    if (ptr != NULL)
    {
        char pass[1000];
        char file_user[1000];
        char file_pass[1000];

        printf("Please Login:\n");
        printf("Enter your username: ");
        scanf("%s", logged_in_user);
        printf("Enter your password: ");
        scanf("%s", pass);
        fflush(stdin);

        while (fscanf(ptr, "%s %s", file_user, file_pass) != EOF)
        {
            if (strcmp(logged_in_user, file_user) == 0 && strcmp(pass, file_pass) == 0)
            {
                user_menu();
                fclose(ptr);
                return 0;
            }
        }
        printf("\n\n\tInvalid Username and password\n");
        fclose(ptr);
    }
    return 1;
}

int user_menu()
{
    printf("\n\n\tWelcome to the user menu!\n");
    char from[20], to[20];
    seats();
   

    return 0;
}

void selectCities(char *from, char *to)
{
    int fromChoice, toChoice;

    do
    {
        printf("\n\tSelect your route:\n");
        for (int i = 0; i < 5; i++)
        {
            printf("\t%d. %s\n", i + 1, cities[i]);
        }

        printf("\n\n\tEnter your choice for 'From' city: ");
        scanf("%d", &fromChoice);

        if (fromChoice < 1 || fromChoice > 5)
        {
            printf("\n\tInvalid choice for 'From' city. Please enter a number between 1 and 5.\n");
            continue;
        }

        printf("\n\n\tEnter your choice for 'To' city: ");
        scanf("%d", &toChoice);

        if (toChoice < 1 || toChoice > 5)
        {
            printf("\n\tInvalid choice for 'To' city. Please enter a number between 1 and 5.\n");
            continue;
        }

        if (fromChoice == toChoice)
        {
            printf("You can't travel from the same city to the same city. Please choose different cities.\n");
            continue;
        }

        strcpy(from, cities[fromChoice - 1]);

        strcpy(to, cities[toChoice - 1]);
    } while (fromChoice == toChoice || fromChoice < 1 || fromChoice > 5 || toChoice < 1 || toChoice > 5);
}

void displayBusTypes(char *from, char *to)
{
    char busType[20];
    int validBusType = 0;

    while (!validBusType)
    {
        printf("\n\tAvailable Bus Types:\n");
        printf("\t1. VIP\n");
        printf("\t2. Economy\n");
        printf("\t3. Business\n");
        printf("\n\tEnter your bus type: ");
        scanf("%s", busType);

        if (strcmp(busType, "VIP") == 0 || strcmp(busType, "Economy") == 0 || strcmp(busType, "Business") == 0)
        {
            validBusType = 1;
            calculateFare(from, to, busType);
        }
        else
        {
            printf("Invalid BusType. Please enter a valid bus type.\n");
        }
    }
}

void calculateFare(char *from, char *to, char *busType)
{
    float fare = 0;
    char foodDrinkOption[20];

    // Set fare based on city route and bus type
    if (strcmp(from, "Lahore") == 0 && strcmp(to, "Karachi") == 0 || strcmp(from, "Karachi") == 0 && strcmp(to, "Lahore") == 0) // Lahore To Karachi
    {
        if (strcmp(busType, "VIP") == 0)
        {
            fare = 4500;
        }
        else if (strcmp(busType, "Economy") == 0)
        {
            fare = 3000;
        }
        else if (strcmp(busType, "Business") == 0)
        {
            fare = 4000;
        }
    }
    else if (strcmp(from, "Islamabad") == 0 && strcmp(to, "Karachi") == 0 || strcmp(from, "Karachi") == 0 && strcmp(to, "Islamabad") == 0) // Karachi To Islamabad
    {
        if (strcmp(busType, "VIP") == 0)
        {
            fare = 4000;
        }
        else if (strcmp(busType, "Economy") == 0)
        {
            fare = 2500;
        }
        else if (strcmp(busType, "Business") == 0)
        {
            fare = 3500;
        }
    }
    else if (strcmp(from, "Peshawar") == 0 && strcmp(to, "Karachi") == 0 || strcmp(from, "Karachi") == 0 && strcmp(to, "Peshawar") == 0) // Karachi To Peshawar
    {
        if (strcmp(busType, "VIP") == 0)
        {
            fare = 5200;
        }
        else if (strcmp(busType, "Economy") == 0)
        {
            fare = 3500;
        }
        else if (strcmp(busType, "Business") == 0)
        {
            fare = 4300;
        }
    }
    else if (strcmp(from, "Karachi") == 0 && strcmp(to, "Quetta") == 0 || strcmp(from, "Quetta") == 0 && strcmp(to, "Karachi") == 0) // Karachi To Quetta
    {
        if (strcmp(busType, "VIP") == 0)
        {
            fare = 6500;
        }
        else if (strcmp(busType, "Economy") == 0)
        {
            fare = 4500;
        }
        else if (strcmp(busType, "Business") == 0)
        {
            fare = 5400;
        }
    }

    else if (strcmp(from, "Lahore") == 0 && strcmp(to, "Islamabad") == 0 || strcmp(from, "Islamabad") == 0 && strcmp(to, "Lahore") == 0) // Karachi To Quetta
    {
        if (strcmp(busType, "VIP") == 0)
        {
            fare = 2300;
        }
        else if (strcmp(busType, "Economy") == 0)
        {
            fare = 1500;
        }
        else if (strcmp(busType, "Business") == 0)
        {
            fare = 1850;
        }
    }

    else if (strcmp(from, "Lahore") == 0 && strcmp(to, "Peshawar") == 0 || strcmp(from, "Peshawar") == 0 && strcmp(to, "Lahore") == 0) // Lahore to Peshawar
    {
        if (strcmp(busType, "VIP") == 0)
        {
            fare = 4500;
        }
        else if (strcmp(busType, "Economy") == 0)
        {
            fare = 2500;
        }
        else if (strcmp(busType, "Business") == 0)
        {
            fare = 3300;
        }
    }
    else if (strcmp(from, "Lahore") == 0 && strcmp(to, "Quetta") == 0 || strcmp(from, "Quetta") == 0 && strcmp(to, "Lahore") == 0) // Lahore to Quetta
    {
        if (strcmp(busType, "VIP") == 0)
        {
            fare = 6000;
        }
        else if (strcmp(busType, "Economy") == 0)
        {
            fare = 3400;
        }
        else if (strcmp(busType, "Business") == 0)
        {
            fare = 4300;
        }
    }

    else if (strcmp(from, "Islamabad") == 0 && strcmp(to, "Peshawar") == 0 || strcmp(from, "Peshawar") == 0 && strcmp(to, "Islamabad") == 0) // Islamabad to Peshawar
    {
        if (strcmp(busType, "VIP") == 0)
        {
            fare = 1300;
        }
        else if (strcmp(busType, "Economy") == 0)
        {
            fare = 700;
        }
        else if (strcmp(busType, "Business") == 0)
        {
            fare = 1000;
        }
    }

    else if (strcmp(from, "Islamabad") == 0 && strcmp(to, "Quetta") == 0 || strcmp(from, "Quetta") == 0 && strcmp(to, "Islamabad") == 0) // Islamabad to Quetta
    {
        if (strcmp(busType, "VIP") == 0)
        {
            fare = 3400;
        }
        else if (strcmp(busType, "Economy") == 0)
        {
            fare = 2000;
        }
        else if (strcmp(busType, "Business") == 0)
        {
            fare = 2400;
        }
    }

    else if (strcmp(from, "Peshawar") == 0 && strcmp(to, "Quetta") == 0 || strcmp(from, "Quetta") == 0 && strcmp(to, "Peshawar") == 0) // Peshawar to Quetta
    {
        if (strcmp(busType, "VIP") == 0)
        {
            fare = 1500;
        }
        else if (strcmp(busType, "Economy") == 0)
        {
            fare = 500;
        }
        else if (strcmp(busType, "Business") == 0)
        {
            fare = 1000;
        }
    }

    if (strcmp(busType, "VIP") == 0 || strcmp(busType, "Business") == 0)
    {
        printf("\nFood and Drink are available in this bus type.\n");
        printf("Do you want to add Food and Drink to your fare? (Yes/No): ");
        scanf("%s", foodDrinkOption);
        if (strcmp(foodDrinkOption, "Yes") == 0 || strcmp(foodDrinkOption, "yes") == 0)
        {
            fare += 200;
        }
    }
printf("\n\t==========================\n");
    printf("\n\tYour selected route: %s to %s\n", from, to);
    printf("\tSelected bus type: %s\n", busType);
    printf("\tFare: Rs. %.2f\n", fare);
}

void seats()
{
    int numberOfseats[40] = {0};
    FILE *fptr = fopen("seats.txt", "r");
    if (fptr != NULL)
    {
        for (int i = 0; i < 40; i++)
        {
            fscanf(fptr, "%d", &numberOfseats[i]);
        }
        fclose(fptr);
    }
    char input[50];

    while (1)
    {
        printf("\n\n\t1. Booking of Ticket\n");
        printf("\n\t2. Cancellation of Tickets\n");
        printf("\n\t3. Show Seats\n");
        printf("\n\t4. Home\n");
        int choice;
        char from[20], to[20];
        fflush(stdin);
        printf("\n\tEnter your choice:");
        fgets(input, 50, stdin);
          
        if (sscanf(input, "%d", &choice) == 1)
        {

            if (choice == 1)
            {
                int seat = 0;

                printf("\n\n\tEnter the seat number(1-40):");
                scanf("%d", &seat);

                if (seat >= 1 && seat <= 40)
                {
                    if (numberOfseats[seat - 1] == 0)
                    {
                        selectCities(from, to);
                        displayBusTypes(from, to);

                        printf("\n\tSeat-%d is reserved\n", seat);
                        printf("\n\t....THANKS FOR USING OUR SERVICE....\n");
                        printf("\n\t============================\n");
                        numberOfseats[seat - 1] = 1;
                        fptr = fopen("user-details.txt", "a");
                        fprintf(fptr, "%s reserved seat number %d\n", logged_in_user, seat);
                        fclose(fptr);
                    }
                    else
                    {
                        printf("\n\n\tSeat-%d is already reserved....\n", seat);
                        
                    }
                }
                else
                {
                    printf("\n\n\tInvalid seat number\n");
                }
            }
            else if (choice == 2)
            {
                int seat = 0;

                printf("\n\n\tEnter the seat number you want to cancel(1-40):");
                scanf("%d", &seat);
                if (seat >= 1 && seat <= 40)
                {
                    if (numberOfseats[seat - 1] == 1)
                    {
                        printf("\n\n\tSeat-%d is cancelled\n", seat);
                        numberOfseats[seat - 1] = 0;
                        fptr = fopen("user-details.txt", "a");
                        fprintf(fptr, "%s cancelled seat number %d\n", logged_in_user, seat);
                        fclose(fptr);
                    }
                    else
                    {
                        printf("\n\n\tSeat-%d is not reserved\n", seat);
                    }
                }
                else
                {
                    printf("\n\tInvalid seat number\n");
                }
            }
            else if (choice == 3)
            {
                printf("\n\t\t\tSeats Status:\n");
                printf("============================================================\n");
                for (int i = 0; i < 40; i++)
                {

                    if (numberOfseats[i] == 0)
                    {
                        if (i % 4 == 0)
                            printf("\n");
                        printf("Seat-%d:Available\t", i + 1);
                    }
                    else
                    {
                        if (i % 4 == 0)
                            printf("\n");
                        printf("Seat-%d:Reserved\t", i + 1);
                    }
                }
            }
            else if (choice == 4)
            {

                fptr = fopen("seats.txt", "w");
                for (int i = 0; i < 40; i++)
                {
                    fprintf(fptr, "%d\n", numberOfseats[i]);
                }
                fclose(fptr);
                printf("\n\tGOING TO HOME WAIT!.......\n");
                sleep(2);
printf("\n\tWelcome To Home Again......!\n");
                break;
            }
        }
        else
        {
            printf("\n\tInvalid Input,Please input options(1-4)\n");
        }
    }
}