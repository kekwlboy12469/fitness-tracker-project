#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLKHB "\033[0;100m"
#define REDHB "\033[0;101m"
#define GRNHB "\033[0;102m"
#define YELHB "\033[0;103m"
#define BLUHB "\033[0;104m"
#define MAGHB "\033[0;105m"
#define CYNHB "\033[0;106m"
#define WHTHB "\033[0;107m"

#define HBLK "\033[0;90m"
#define HRED "\033[0;91m"
#define HGRN "\033[0;92m"
#define HYEL "\033[0;93m"
#define HBLU "\033[0;94m"
#define HMAG "\033[0;95m"
#define HCYN "\033[0;96m"
#define HWHT "\033[0;97m"
#define RESET "\033[0m"

// Structures to store user data and workout log
struct WorkoutLog {
    char userName[50];
    char exercise[50];
    int sets;
    int *reps;
    int *weight;
    char date[20];
};

typedef struct {
    char name[50];
    char type[20]; 
    int duration;  
    char equipment[50];
} Workout;

typedef struct {
    Workout workouts[10];
    int workoutCount;
} WorkoutPlan;


struct UserData {
    char userName[50];
    float userWeight;
    char userHeight[10];
    int userAge;
    int maxBench;
    int maxSquat;
    int maxDeadlift;
};

// Struct to handle Fitness Tracker
struct FitnessTracker {
    struct UserData *users;
    int userCount;
    char fileName[50];
};

// Struct to handle Log Workout
struct LogWorkout {
    struct WorkoutLog *logs;
    int logCount;
    char logName[50];
};

struct Workout {
    char date[20];
    char type[50];
    int duration;
};

typedef struct {
    char name[100]; 
    float calories; 
    float protein;  
    float carbs;    
    float fats;     
} FoodItem;

typedef struct {
    float dailyCaloriesGoal;
    float dailyProteinGoal;
    float dailyCarbsGoal;
    float dailyFatsGoal;
} FitnessGoals;

typedef struct {
    FoodItem food[100]; 
    int foodCount;      
    char mealTime[20];  
} Meal;

//function for menu
void displayMenu(){
    printf("\n%s======================%s\n", BLUHB, RESET);

    printf("%s  FITNESS TRACKER MENU  %s\n", CYNHB, RESET);

    printf("%s======================%s\n", BLUHB, RESET);

    printf("%s1.%s Add or Update User Data\n", HGRN, RESET);
    printf("%s2.%s View User Data\n", HYEL, RESET);
    printf("%s3.%s Remove User\n", HRED, RESET);
    printf("%s4.%s Set Fitness Goals\n", HBLU, RESET);
    printf("%s5.%s View Fitness Goal\n", HCYN, RESET);
    printf("%s6.%s View Progress\n", HWHT, RESET);
    printf("%s7.%s Print User Data\n",HGRN,RESET);
    printf("%s8.%s Add Workout Log\n",HYEL,RESET);
    printf("%s9.%s Display Workout Logs\n",HGRN,RESET);
    printf("%s10.%s. Show Progress Summary\n",HCYN, RESET);
     printf("%s11.%sRemove Goal for a user \n",HRED, RESET);
    printf("%s12.%s Log a Meal\n", HBLU, RESET);
    printf("%s13.%s Display Logged Meals\n", HCYN, RESET);
    printf("%s14.%s Calculate Nutritional Intake\n", HWHT, RESET); 
    printf("%s15.%s Check Fitness Goals\n", HYEL, RESET);
    
    printf("%s16.%s Workout Program Generator\n", HBLU, RESET);
   


    printf("%s17.%s Exit Program\n", HMAG, RESET);

    printf("%s======================%s\n", BLUHB, RESET);

    printf("%sChoose an option:%s ", HWHT, RESET);


    
}
// Function to load users from a file
void loadUsers(struct FitnessTracker *tracker) {
    FILE *file = fopen(tracker->fileName, "r");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    while (!feof(file)) {
        struct UserData newUser;
        fscanf(file, "%s %f %s %d %d %d %d",
               newUser.userName,
               &newUser.userWeight,
               newUser.userHeight,
               &newUser.userAge,
               &newUser.maxBench,
               &newUser.maxSquat,
               &newUser.maxDeadlift);

        tracker->userCount++;
        tracker->users = realloc(tracker->users, tracker->userCount * sizeof(struct UserData));
        tracker->users[tracker->userCount - 1] = newUser;
    }

    fclose(file);
}


void addWorkoutLog(struct LogWorkout *workout) {
    struct WorkoutLog newWorkout;
    printf("Enter username: ");
    scanf("%s", newWorkout.userName);
    
    printf("Enter date (YYYY-MM-DD): ");
    scanf("%s", newWorkout.date);
    
    printf("Enter exercise name: ");
    scanf("%s", newWorkout.exercise);
    
    printf("Enter number of sets: ");
    scanf("%d", &newWorkout.sets);
   
    newWorkout.reps = malloc(newWorkout.sets * sizeof(int));
    newWorkout.weight = malloc(newWorkout.sets * sizeof(int));
    if (newWorkout.reps == NULL || newWorkout.weight == NULL) {
        printf("Memory allocation failed.\n");
        return;
    }
    
   
    for (int i = 0; i < newWorkout.sets; i++) {
        printf("Enter reps for set %d: ", i + 1);
        scanf("%d", &newWorkout.reps[i]);
        
        printf("Enter weight for set %d: ", i + 1);
        scanf("%d", &newWorkout.weight[i]);
    }
    workout->logCount++;
    workout->logs = realloc(workout->logs, workout->logCount * sizeof(struct WorkoutLog));
    if (workout->logs == NULL) {
        printf("Memory reallocation failed.\n");
        free(newWorkout.reps);
        free(newWorkout.weight);
        return;
    }
    workout->logs[workout->logCount - 1] = newWorkout;
    printf("Workout log added successfully!\n");
}
// Function to save users to a file
void saveUsers(struct FitnessTracker *tracker) {
    FILE *file = fopen(tracker->fileName, "w");
    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    for (int i = 0; i < tracker->userCount; i++) {
        struct UserData user = tracker->users[i];
        fprintf(file, "%s %.2f %s %d %d %d %d\n",
                user.userName,
                user.userWeight,
                user.userHeight,
                user.userAge,
                user.maxBench,
                user.maxSquat,
                user.maxDeadlift);
    }

    fclose(file);
}
void displayWorkoutLogs(struct LogWorkout *workout) {
    printf("-----------------------------------------------------------\n");
    printf("| %-10s | %-10s | %-10s | %-5s | %-5s |\n", "User", "Date", "Exercise", "Reps", "Weight");
    printf("-----------------------------------------------------------\n");

    for (int i = 0; i < workout->logCount; i++) {
        struct WorkoutLog *log = &workout->logs[i];
        
        printf("| %-10s | %-10s | %-10s | %-5d | %-5d |\n",
               log->userName, log->date, log->exercise, log->sets, log->sets);
        
        for (int j = 0; j < log->sets; j++) {
            printf("  Set %d: Reps: %-5d Weight: %-5d\n", j + 1, log->reps[j], log->weight[j]);
        }
        printf("-----------------------------------------------------------\n");
    }
}
//function to print user data
void printuserdata(struct FitnessTracker *tracker){
    printf("-----------------------------------------------------\n");
    printf("| %s%-15s%s | %s%-10s%s | %s%-6s%s | %s%-3s%s | %s%-5s%s | %s%-5s%s | %s%-5s%s |\n",
           HGRN, "User Name", RESET, HBLU, "Weight", RESET, HYEL, "Height", RESET,
           HMAG, "Age", RESET, HCYN, "Bench", RESET, HRED, "Squat", RESET, HWHT, "Deadlift", RESET);
    printf("-----------------------------------------------------\n");
    for(int i=0;i<tracker->userCount;i++){
        struct UserData user = tracker->users[i];
        printf("| %s%-15s%s | %s%-10.2f%s | %s%-6s%s | %s%-3d%s | %s%-5d%s | %s%-5d%s | %s%-5d%s |\n",
               HGRN, user.userName, RESET,
               HBLU, user.userWeight, RESET,
               HYEL, user.userHeight, RESET,
               HMAG, user.userAge, RESET,
               HCYN, user.maxBench, RESET,
               HRED, user.maxSquat, RESET,
               HWHT, user.maxDeadlift, RESET);

    }
    printf("-----------------------------------------------------\n");
    }
// function to display progress bar
void displayprogressbar(int current, int goal){
    int width=50;
    if (goal <= 0) {
        printf("[Error: Goal must be greater than zero]\n");
        return;
    }
    int pos=(current*width)/goal;
    int percentage = (current * 100) / goal;
    printf("[");
    for(int i=0;i<width;i++){
        if(i<pos)printf("=");
        else printf(" ");
    }
    printf("] %d/%d\n",current,goal);

    }



// Function to add or update users from input
void addOrUpdateUsersFromInput(struct FitnessTracker *tracker) {
    char name[50], height[10];
    char username[50];
    float weight;
    int age, bench, squat, deadlift;
    int found = 0;

    printf("Enter user name: ");
    scanf("%s", name);

    for (int i = 0; i < tracker->userCount; i++) {
        if (strcmp(tracker->users[i].userName, name) == 0) {
            found = 1;
            printf("User found. Updating information.\n");

            printf("Enter new weight: ");
            scanf("%f", &weight);

            printf("Enter new height: ");
            scanf("%s", height);

            printf("Enter new age: ");
            scanf("%d", &age);

            printf("Enter new bench PR: ");
            scanf("%d", &bench);

            printf("Enter new squat PR: ");
            scanf("%d", &squat);

            printf("Enter new deadlift PR: ");
            scanf("%d", &deadlift);

            tracker->users[i].userWeight = weight;
            strcpy(tracker->users[i].userHeight, height);
            tracker->users[i].userAge = age;
            tracker->users[i].maxBench = bench;
            tracker->users[i].maxSquat = squat;
            tracker->users[i].maxDeadlift = deadlift;

            printf("User updated successfully.\n");
            saveUsers(tracker);
            break;
        }
    }

    if (!found) {
        printf("User not found. Adding new user.\n");

        printf("Enter weight: ");
        scanf("%f", &weight);

        printf("Enter height: ");
        scanf("%s", height);

        printf("Enter age: ");
        scanf("%d", &age);

        printf("Enter bench PR: ");
        scanf("%d", &bench);

        printf("Enter squat PR: ");
        scanf("%d", &squat);

        printf("Enter deadlift PR: ");
        scanf("%d", &deadlift);

        tracker->userCount++;
        tracker->users = realloc(tracker->users, tracker->userCount * sizeof(struct UserData));

        struct UserData newUser;
        strcpy(newUser.userName, name);
        newUser.userWeight = weight;
        strcpy(newUser.userHeight, height);
        newUser.userAge = age;
        newUser.maxBench = bench;
        newUser.maxSquat = squat;
        newUser.maxDeadlift = deadlift;

        tracker->users[tracker->userCount - 1] = newUser;
        saveUsers(tracker);
    }
}

// Function to remove a user
void removeUser(struct FitnessTracker *tracker) {
    char name[50];
    printf("Enter name of user to be removed: ");
    scanf("%s", name);

    int found = -1;
    for (int i = 0; i < tracker->userCount; i++) {
        if (strcmp(tracker->users[i].userName, name) == 0) {
            found = i;
            break;
        }
    }

    if (found != -1) {
        for (int i = found; i < tracker->userCount - 1; i++) {
            tracker->users[i] = tracker->users[i + 1];
        }
        tracker->userCount--;
        tracker->users = realloc(tracker->users, tracker->userCount * sizeof(struct UserData));
        printf("User %s removed successfully.\n", name);
        saveUsers(tracker);
    } else {
        printf("User %s was not found.\n", name);
    }
}

// Function to print user information
void printUserInfo(struct FitnessTracker *tracker) {
    char name[50];
    printf("Enter your name to see your stats: ");
    scanf("%s", name);

    int found = 0;
    for (int i = 0; i < tracker->userCount; i++) {
        if (strcmp(tracker->users[i].userName, name) == 0) {
            printf("Name: %s\n", tracker->users[i].userName);
            printf("Weight: %.2f\n", tracker->users[i].userWeight);
            printf("Height: %s\n", tracker->users[i].userHeight);
            printf("Age: %d\n", tracker->users[i].userAge);
            printf("Bench PR: %d\n", tracker->users[i].maxBench);
            printf("Squat PR: %d\n", tracker->users[i].maxSquat);
            printf("Deadlift PR: %d\n", tracker->users[i].maxDeadlift);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("User %s was not found.\n", name);
    }
     printf("Press Enter to return to the main menu...");
    getchar();  // To consume the newline left over by scanf
    getchar();
}
void setGoal(const char *username) {
    FILE *file;
    char goal[100];
    char filename[50];
    
    // Create unique filename for each user
    snprintf(filename, sizeof(filename), "%s_goal.txt", username);

    printf("Enter your fitness goal (e.g., target weight, max bench): ");
    scanf(" %[^\n]s", goal);

    // Save goal to a file
    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "Goal: %s\n", goal);
    fclose(file);

    printf("Goal saved for %s.\n", username);
}

void loadGoal(const char *username) {
    FILE *file;
    char goal[100];
    char filename[50];

    // Open the user's goal file
    snprintf(filename, sizeof(filename), "%s_goal.txt", username);
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("No goal found for %s.\n", username);
        return;
    }
    printf("Opened goal file for %s.\n", username);

    // Read and display the goal
    if (fgets(goal, sizeof(goal), file) != NULL) {
        printf("Current Goal for %s: %s\n", username, goal);
    } else {
        printf("Goal file is empty or could not be read.\n");
    }

    fclose(file);
     printf("Goal file closed.\n");
}

void removeGoal(const char *username) {
    char filename[50];
    snprintf(filename, sizeof(filename), "%s_goal.txt", username);

    // Delete the goal file if it exists
    if (remove(filename) == 0) {
        printf("Goal removed for %s.\n", username);
    } else {
        printf("No goal found for %s to remove.\n", username);
    }
}
// Function to load workout logs from a file
void loadLog(struct LogWorkout *workout) {
    FILE *file = fopen("C:\\c lang\\Workout data.txt", "r");
    if (file == NULL) {
        perror("Error opening file...\n");
        return;
    }

    while (1) {
        struct WorkoutLog newWorkout;
        if(fscanf(file, "%s %s %s %d",
               newWorkout.userName,
               newWorkout.date,
               newWorkout.exercise,
               &newWorkout.sets)!=4){
                break;
               };

        newWorkout.reps = malloc(newWorkout.sets * sizeof(int));
        newWorkout.weight = malloc(newWorkout.sets * sizeof(int));
        if(newWorkout.reps==NULL || newWorkout.weight==NULL){
            printf("memory allocation failed.\n");
            free(newWorkout.reps);
            free(newWorkout.weight);
            fclose(file);
            return;
        }
        for (int i = 0; i < newWorkout.sets; i++) {
            if(fscanf(file, "%d", &newWorkout.reps[i])!=1)break;
        }
        for (int i = 0; i < newWorkout.sets; i++) {
            if(fscanf(file, "%d", &newWorkout.weight[i])!=1)break;
        }

        workout->logCount++;
        workout->logs = realloc(workout->logs, workout->logCount * sizeof(struct WorkoutLog));
        if (workout->logs == NULL) {
            printf("Memory reallocation failed.\n");
            free(newWorkout.reps);
            free(newWorkout.weight);
            fclose(file);
            return;
        }
        workout->logs[workout->logCount - 1] = newWorkout;
    }

    fclose(file);
}

// Function to save workout logs to a file
void saveLog(struct LogWorkout *workout) {
    FILE *file = fopen(workout->logName, "w");
    if (file == NULL) {
        printf("Error opening file....\n");
        return;
    }

    for (int i = 0; i < workout->logCount; i++) {
        struct WorkoutLog log = workout->logs[i];
        fprintf(file, "%s %s %s %d ",
                log.userName,
                log.date,
                log.exercise,
                log.sets);

        for (int j = 0; j < log.sets; j++) {
            fprintf(file, "%d ", log.reps[j]);
        }
        for (int j = 0; j < log.sets; j++) {
            fprintf(file, "%d ", log.weight[j]);
        }
        fprintf(file, "\n");
    }

    fclose(file);
}
void displayExitMessage() {
    printf("\n%s======================%s\n", BLUHB, RESET);
    printf("%sThank you for using the Fitness Tracker!%s\n", HCYN, RESET);
    printf("%s======================%s\n", BLUHB, RESET);
}
void showProgressSummary() {
    FILE *file = fopen("workouts.txt", "a");  // Open in append mode to create file if it doesn't exist
if (file == NULL) {
    perror("Error opening file");
    return;
}

    int count = 0, td = 0;
    float ad = 0;
    int gd = 500; // Example: Total workout duration goal in minutes
    char line[100];

    printf("\n--- Progress Summary ---\n");

    while (fgets(line, sizeof(line), file)) {
        struct Workout w;
        sscanf(line, "%s %s %d", w.date, w.type, &w.duration);
        td += w.duration;
        count++;
    }

    fclose(file);

    if (count > 0) {
        ad = (float)td / count;
        printf("Total Workouts: %d\n", count);
        printf("Total Time Spent: %d minutes\n", td);
        printf("Average Workout Duration: %.2f minutes\n", ad);

        // Progress toward goal
        printf("\n--- Progress Toward Goal ---\n");
        if (gd > 0) {
            float progress = (float)td / gd * 100;
            printf("Workout Goal: %d minutes\n", gd);
            printf("Progress: %.2f%%\n", progress);

            if (progress >= 100) {
                printf("Congratulations! You've achieved your workout goal!\n");
            } else {
                printf("Keep going! You're %.2f%% away from your goal.\n", 100 - progress);
            }
        } else {
            printf("No goal set. Please set a goal to track your progress.\n");
        }
    } else {
        printf("No workouts logged yet.\n");
    }
}

void logMeal(Meal* meal) {
    int i;
    printf("Enter the meal time (e.g., breakfast, lunch, dinner): ");
    scanf("%s", meal->mealTime);

    printf("Enter the number of food items in your meal: ");
    scanf("%d", &meal->foodCount);

    for (i = 0; i < meal->foodCount; i++) {
        printf("Enter food name: ");
        scanf(" %[^\n]", meal->food[i].name);  

        printf("Enter calories for %s: ", meal->food[i].name);
        scanf("%f", &meal->food[i].calories);

        printf("Enter protein (grams) for %s: ", meal->food[i].name);
        scanf("%f", &meal->food[i].protein);

        printf("Enter carbs (grams) for %s: ", meal->food[i].name);
        scanf("%f", &meal->food[i].carbs);

        printf("Enter fats (grams) for %s: ", meal->food[i].name);
        scanf("%f", &meal->food[i].fats);
    }
}

void displayMeal(const Meal* meal) {
    if (meal->foodCount == 0) {
        printf("No meals logged yet.\n");
        return;
    }

    printf("\nMeal Time: %s\n", meal->mealTime);
    printf("----------------------------------------\n");
    printf("| %-20s | %-10s |\n", "Food Item", "Calories");
    printf("----------------------------------------\n");

    float totalCalories = 0;
    for (int i = 0; i < meal->foodCount; i++) {
        printf("| %-20s | %-10.2f |\n", meal->food[i].name, meal->food[i].calories);
        totalCalories += meal->food[i].calories;
    }
    printf("----------------------------------------\n");
    printf("Total Calories: %.2f\n", totalCalories);
}


void calculateNutritionalIntake(Meal* meal) {
     if (meal->foodCount == 0) {
        printf("No meals logged yet.\n");
        return;
    }

    float totalCalories = 0;
    printf("\nNutritional Intake:\n");
    for (int i = 0; i < meal->foodCount; i++) {
        totalCalories += meal->food[i].calories;
    }
    printf("Total Calories Consumed: %.2f kcal\n", totalCalories);
}



void checkGoals(FitnessGoals goals, Meal* meal) {
    if (meal->foodCount == 0) {
        printf("No meals logged yet. Cannot check goals.\n");
        return;
    }

    float totalCalories = 0;
    for (int i = 0; i < meal->foodCount; i++) {
        totalCalories += meal->food[i].calories;
    }

    printf("\nChecking Goals:\n");
    printf("Daily Calorie Goal: %.2f kcal\n", goals.dailyCaloriesGoal);
    printf("Calories Consumed: %.2f kcal\n", totalCalories);

    if (totalCalories > goals.dailyCaloriesGoal) {
        printf("Warning: You have exceeded your daily calorie goal!\n");
    } else if (totalCalories < goals.dailyCaloriesGoal) {
        printf("You are under your daily calorie goal. Try to eat more nutritious meals.\n");
    } else {
        printf("Great job! You met your daily calorie goal exactly.\n");
    }
   
}

void generateWorkoutPlan(const char* goal, WorkoutPlan* plan) {
    plan->workoutCount = 0;

    if (strcmp(goal, "lose weight") == 0) {
        strcpy(plan->workouts[0].name, "Running");
        strcpy(plan->workouts[0].type, "Cardio");
        plan->workouts[0].duration = 30;
        strcpy(plan->workouts[0].equipment, "None");

        strcpy(plan->workouts[1].name, "Jump Rope");
        strcpy(plan->workouts[1].type, "Cardio");
        plan->workouts[1].duration = 20;
        strcpy(plan->workouts[1].equipment, "Jump rope");

        plan->workoutCount = 2;
    } else if (strcmp(goal, "build muscle") == 0) {
        strcpy(plan->workouts[0].name, "Push-ups");
        strcpy(plan->workouts[0].type, "Strength");
        plan->workouts[0].duration = 15;
        strcpy(plan->workouts[0].equipment, "None");

        strcpy(plan->workouts[1].name, "Dumbbell Rows");
        strcpy(plan->workouts[1].type, "Strength");
        plan->workouts[1].duration = 20;
        strcpy(plan->workouts[1].equipment, "Dumbbells");

        plan->workoutCount = 2;
    } else if (strcmp(goal, "increase strength") == 0) {
        strcpy(plan->workouts[0].name, "Deadlifts");
        strcpy(plan->workouts[0].type, "Strength");
        plan->workouts[0].duration = 30;
        strcpy(plan->workouts[0].equipment, "Barbell");

        strcpy(plan->workouts[1].name, "Pull-ups");
        strcpy(plan->workouts[1].type, "Strength");
        plan->workouts[1].duration = 20;
        strcpy(plan->workouts[1].equipment, "Pull-up bar");

        plan->workoutCount = 2;
    } else {
        printf("Invalid goal! Available goals: lose weight, build muscle, increase strength.\n");
    }
}

void customizeWorkoutPlan(WorkoutPlan* plan) {
    char workoutName[50];
    char workoutType[20];
    int duration;
    char equipment[50];

    printf("\nEnter a custom workout:\n");
    printf("Workout Name: ");
    scanf(" %[^\n]", workoutName);
    printf("Workout Type (e.g., Cardio, Strength): ");
    scanf(" %[^\n]", workoutType);
    printf("Duration (in minutes): ");
    scanf("%d", &duration);
    printf("Equipment: ");
    scanf(" %[^\n]", equipment);

    strcpy(plan->workouts[plan->workoutCount].name, workoutName);
    strcpy(plan->workouts[plan->workoutCount].type, workoutType);
    plan->workouts[plan->workoutCount].duration = duration;
    strcpy(plan->workouts[plan->workoutCount].equipment, equipment);

    plan->workoutCount++;
    printf("Custom workout added successfully!\n");
}

void displayWorkoutPlan(WorkoutPlan plan) {
    printf("\nWorkout Plan:\n");
    for (int i = 0; i < plan.workoutCount; i++) {
        printf("\nWorkout %d:\n", i + 1);
        printf("Name: %s\n", plan.workouts[i].name);
        printf("Type: %s\n", plan.workouts[i].type);
        printf("Duration: %d minutes\n", plan.workouts[i].duration);
        printf("Equipment: %s\n", plan.workouts[i].equipment);
    }
}

void workoutProgramMenu() {
    WorkoutPlan plan;
    char goal[50];
    int choice;

    printf("\n--- Workout Program Generator ---\n");
    printf("Enter your fitness goal (lose weight, build muscle, increase strength): ");
    scanf(" %[^\n]", goal);

    generateWorkoutPlan(goal, &plan);

    while (1) {
        printf("\n--- Workout Program Menu ---\n");
        printf("1. View Workout Plan\n");
        printf("2. Add Custom Workout\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                displayWorkoutPlan(plan);
                break;
            case 2:
                customizeWorkoutPlan(&plan);
                break;
            case 3:
                printf("Exiting Workout Program Menu.\n");
                return;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}



// Main function
int main(int meme, char *good[]) {
    
    struct FitnessTracker tracker;
    struct LogWorkout workout;
    tracker.users = NULL;
    tracker.userCount = 0;
    workout.logs = NULL;
    workout.logCount = 0;
    Meal meal = {{0}, 0, ""}; 
    FitnessGoals goals = {2000};
    

    strcpy(tracker.fileName, "user_data.txt");
    strcpy(workout.logName, "workout_log.txt");

    if(meme>1){
        if(meme>=2){
            strncpy(tracker.fileName,good[1],sizeof(tracker.fileName)-1);
        }
        if(meme>=3){
            strncpy(workout.logName,good[2],sizeof(workout.logName)-1);
        }
        if(meme>=4){
            printf("username '%s' provided, autoloadinh user details \n", good[3]);
        }
    }

    loadUsers(&tracker);
    loadLog(&workout);



    int choice;
     int current, goal;
    char username[50];
    if(meme>=4){
        strncpy(username,good[3],sizeof(username)-1);
    }




    do{
        displayMenu();
        scanf("%d",&choice);
        switch(choice){
        case 1:

        addOrUpdateUsersFromInput(&tracker);
        printf("\n%sAdd or Update User Data selected.%s\n", HGRN, RESET);
         break;

        case 2:
        if(meme>=4){
            printUserInfo(&tracker);
        }
        else{
        

         printf("\n%sView User Data selected.%s\n", HYEL, RESET);
         printUserInfo(&tracker);
          loadLog(&workout);}
         break;

        case 3:
        removeUser(&tracker);

        printf("\n%sRemove User selected.%s\n", HRED, RESET);
        break;

        case 4:
        if(meme>=4){
            setGoal(username);
        }
        else{
        printf("Enter username for setting goals: ");
        scanf("%s", username);
        setGoal(username);
        }

        break;

        case 5:
        if(meme>=4){
            loadGoal(username);
        }
        else{
            printf("Enter username to view goal: ");
            scanf("%s", username);
            loadGoal(username);}

            break;

        case 6: 
                printf("Enter current progress: ");
                scanf("%d", &current);
                printf("Enter goal: ");
                scanf("%d", &goal);
                displayprogressbar(current, goal);
                break;

        case 7:
         printuserdata(&tracker);  
                break;

         case 8:
                addWorkoutLog(&workout);
                break;

            case 9:
                displayWorkoutLogs(&workout);
                break;
            case 10:
                showProgressSummary();  
                break;
            case 11:
            printf("Enter username for removing goal : ");
        scanf("%s", username);
            removeGoal(username);
            break;
          case 12: 
                logMeal(&meal);
                break;
            case 13: 
                displayMeal(&meal);
                break;
            case 14: 
                calculateNutritionalIntake(&meal);
                break;
            case 15: 
                checkGoals(goals, &meal);
                break;
            case 16:
                workoutProgramMenu();
                break;



            

       
        case 17:
        displayExitMessage();
        saveUsers(&tracker);
        saveLog(&workout);
        break;
      
         default:
           printf("\n%sInvalid choice. Please try again.%s\n", REDHB, RESET);
        }
           if (choice != 17) {
            printf("Press Enter to return to the main menu...");
            getchar();  
            getchar();
        }
        }while (choice != 17);








    
 
    free(tracker.users);
    for (int i = 0; i < workout.logCount; i++) {
        free(workout.logs[i].reps);
        free(workout.logs[i].weight);
    }
    free(workout.logs);
    
 
    
  

    return 0;
}
