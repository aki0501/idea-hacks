#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    // Current user's preferences
    FILE *prefsFile;
    char preferences[] = "preferences.txt";
    prefsFile = fopen(preferences, "r");
    if (prefsFile == NULL) {
        fprintf(stderr, "Unable to open file: %s\n", preferences);
        return 1;
    }

    // Person's profile for comparison
    FILE *personFile;
    char person[] = "person.txt";
    personFile = fopen(person, "r");
    if (personFile == NULL) {
        fprintf(stderr, "Unable to open file: %s\n", person);
        return 1;
    }

    // Keep score of similarities/matches between files
    int score = 0;
    char buffer[1024];

    // Check age
    char* ageRange = fgets(buffer, sizeof(buffer), prefsFile);
    const char delimiter[] = "-+";
    int realAge = atoi(fgets(buffer, sizeof(buffer), personFile));
    char *ageMin = strtok(ageRange, delimiter);
    char *ageMax = strtok(NULL, delimiter);
    if (atoi(ageMin) <= realAge && ((ageMax != NULL && atoi(ageMax) >= realAge) || ageMax == NULL)) {
        score++;
    }

    // Check gender
    char* prefGender = fgets(buffer, sizeof(buffer), prefsFile);
    char* realGender = fgets(buffer, sizeof(buffer), personFile);
    if (strcmp(prefGender, realGender) == 0) {
        score++;
    }

    // Increment score for each matching hobby
    char prefHobbies[5][20];
    for (int i = 0; i < 5; i++) {
        strcpy(prefHobbies[i], fgets(buffer, sizeof(buffer), prefsFile));
    }

    char personHobbies[5][20];
    for (int i = 0; i < 5; i++) {
        strcpy(personHobbies[i], fgets(buffer, sizeof(buffer), personFile));
    }

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (strcmp(prefHobbies[i], personHobbies[j]) == 0) {
                // Code here to tell user which hobbies match/save matching hobbies somewhere
                score++;
            }
        }
    }

    // If at least one hobby matches, vibrate
    if (score >= 3) {
        printf("~~~vibration~~~~ found a friend\n");
    } else {
        printf("incompatible :((\n");
    }

    fclose(prefsFile);
    fclose(personFile);

    return 0;
}
