#include <stdio.h>
#include <string.h>  //for string manipulation functions
#include <ctype.h>   //for character classification functions
#include <time.h> //for retrieving the current year

#define NUM_TEAMS 5      //maximum number of teams allowed
#define SQUAD_SIZE 20    //maximum number of players per team

//structure to represent a player's age (birthdate)
typedef struct {
    int day, month, year;
} age_t;

//structure to represent a player with various attributes
typedef struct {
    char name[26];      //player's name (max 25 characters + null terminator)
    int kit_number;     //jersey number of the player
    char club[50];      //player's club name
    age_t age;          //player's birthdate
    char position[30];  //player's position on the team
} player_t;

//structure to represent a team with its players
typedef struct {
    char name[21];          //team name (max 20 characters + null terminator)
    player_t players[SQUAD_SIZE]; //array of players in the team
    int active_size;        //current number of players in the team
} team_t;

team_t teams[NUM_TEAMS];  //array to store teams
int team_count = 0;       //current number of enrolled teams

//Function prototypes
void display_menu();
void enroll_club();
void add_player();
void search_update();
void display_club_statistics();
void handle_error(const char msg[]);
int get_valid_int(const char prompt[], int min, int max);

int main() {
    //Main program loop
    while (1) {
        display_menu();  //display the menu to the user
        int choice = get_valid_int("Enter your choice: ", 1, 4); //get a valid menu choice

        //Handle user's choice
        switch (choice) {
            case 1: enroll_club(); break;  //option to enroll a new club
            case 2: add_player(); break;  //option to add a new player to a club
            case 3: search_update(); break;  //option to search/update player info
            case 4: display_club_statistics(); break;  //option to display club statistics
            default:
                printf("Goodbye!\n");  //exit the program
                return 0;
        }
    }
}

//displays the menu options
void display_menu() {
    printf("\n--- League Team Management ---\n");
    printf("1. Enroll Club\n");
    printf("2. Add Player\n");
    printf("3. Search/Update Player\n");
    printf("4. Display Statistics\n");
    printf("Any other number to exit\n");
}

//enrolls a new club
void enroll_club() {
    if (team_count >= NUM_TEAMS) {  //check if the maximum number of teams is reached
        handle_error("Max teams reached.");
        return;
    }

    printf("Enter club name (max 20 characters): ");
    scanf(" %[^\n]", teams[team_count].name);  //read the club name

    if (strlen(teams[team_count].name) > 20) {  //validate the length of the club name
        handle_error("Club name too long.");
        return;
    }

    teams[team_count].active_size = 0;  //initialize the number of players in the team
    team_count++;  //increment the count of enrolled teams
    printf("Club '%s' enrolled.\n", teams[team_count - 1].name);
}

//adds a player to an existing club
void add_player() {
    if (team_count == 0) {  //ensure at least one club is enrolled
        handle_error("No clubs enrolled.");
        return;
    }

    //display a list of enrolled clubs
    printf("Select club:\n");
    for (int i = 0; i < team_count; i++) {
        printf("%d. %s\n", i + 1, teams[i].name);
    }
    int club_index = get_valid_int("Enter club number: ", 1, team_count) - 1;  //select a club

    if (teams[club_index].active_size >= SQUAD_SIZE) {  //check if the club's squad is full
        handle_error("Squad full.");
        return;
    }

    player_t new_player;  //create a new player
    printf("Enter player name (max 25 characters): ");
    scanf(" %[^\n]", new_player.name);  //read the player's name

    if (strlen(new_player.name) > 25) {  //validate the length of the player's name
        handle_error("Player name too long.");
        return;
    }

    //read and validate other player details
    new_player.kit_number = get_valid_int("Enter kit number (1-99): ", 1, 99);
    printf("Enter position (max 29 characters): ");
    scanf(" %[^\n]", new_player.position);

    if (strlen(new_player.position) > 29) {  //validate the position length
        handle_error("Position too long.");
        return;
    }

    printf("Enter birthdate (day month year): ");
    int day, month, year;
    if (scanf("%d %d %d", &day, &month, &year) != 3 || day < 1 || day > 31 || month < 1 || month > 12 || year < 1900 || year > 2024) {
        handle_error("Invalid birthdate.");
        return;
    }
    new_player.age.day = day;
    new_player.age.month = month;
    new_player.age.year = year;

    //add the new player to the club's squad
    teams[club_index].players[teams[club_index].active_size] = new_player;
    teams[club_index].active_size++;
    printf("Player '%s' added.\n", new_player.name);
}

//searches for a player by name or kit number and allows updating their position
void search_update() {
    int option = get_valid_int("Search by:\n1. Name\n2. Kit Number\nEnter choice: ", 1, 2);

    char search_name[26];
    int kit_number = 0;
    if (option == 1) {  //search by name
        printf("Enter player name: ");
        scanf(" %[^\n]", search_name);
    } else {  //search by kit number
        kit_number = get_valid_int("Enter kit number: ", 1, 99);
    }

    //search for the player in all clubs
    for (int i = 0; i < team_count; i++) {
        for (int j = 0; j < teams[i].active_size; j++) {
            if ((option == 1 && strcasecmp(teams[i].players[j].name, search_name) == 0) ||
                (option == 2 && teams[i].players[j].kit_number == kit_number)) {
                //player found, display their details
                printf("Player found: %s, Kit: %d, Position: %s, Birthdate: %d-%d-%d\n",
                       teams[i].players[j].name, teams[i].players[j].kit_number,
                       teams[i].players[j].position, teams[i].players[j].age.day,
                       teams[i].players[j].age.month, teams[i].players[j].age.year);

                //update the player's position
                printf("Enter new position: ");
                scanf(" %[^\n]", teams[i].players[j].position);
                printf("Position updated.\n");
                return;
            }
        }
    }
    handle_error("Player not found.");
}

//displays the statistics of all enrolled clubs
void display_club_statistics() {

    //calculate the current year manually
    time_t t = time(NULL);
    int seconds_in_a_year = 365 * 24 * 60 * 60;
    int current_year = 1970 + t / seconds_in_a_year;

    printf("\n--- Club Statistics ---\n");
    for (int i = 0; i < team_count; i++) {
        printf("Club: %s\n", teams[i].name);
        printf("Players: %d\n", teams[i].active_size);

        int total_age = 0;
        for (int j = 0; j < teams[i].active_size; j++) {
            int age = current_year - teams[i].players[j].age.year;
            total_age += age;

            printf("  %d. %s, Kit: %d, Position: %s, Age: %d\n",
                   j + 1, teams[i].players[j].name,
                   teams[i].players[j].kit_number, teams[i].players[j].position,
                   age);
        }

        if (teams[i].active_size > 0) {
            float average_age = (float)total_age / teams[i].active_size;
            printf("Average Age: %.2f\n", average_age);
        } else {
            printf("Average Age: N/A (No players)\n");
        }
        printf("\n");
    }
}

//prints an error message
void handle_error(const char msg[]) {
    printf("Error: %s\n", msg);
}

//reads a valid integer within a specified range
int get_valid_int(const char prompt[], int min, int max) {
    int value;
    while (1) {
        printf("%s", prompt);
        if (scanf("%d", &value) == 1 && value >= min && value <= max) {
            return value;
        } else {
            printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
            while (getchar() != '\n');  //clear input buffer
        }
    }
}


