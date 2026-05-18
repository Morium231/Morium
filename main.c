#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BLOOD_GROUPS 8
#define MAX_DONORS 100
#define MAX_REQUESTS 100

struct BloodGroup {
    char bloodType[10];
    int quantity;
};

struct Donor {
    char name[50];
    int age;
    char phone[20];
    char bloodType[10];
};

struct BloodRequest {
    char hospitalName[50];
    char bloodType[10];
    int quantity;
};

struct BloodGroup bloodGroups[MAX_BLOOD_GROUPS];
struct Donor donors[MAX_DONORS];
struct BloodRequest requests[MAX_REQUESTS];

int bloodCount = 0;
int donorCount = 0;
int requestCount = 0;

bool isValidBloodType(char bloodType[]) {
    char validTypes[8][10] = {"A+", "A-", "B+", "B-", "O+", "O-", "AB+", "AB-"};

    for (int i = 0; i < 8; i++) {
        if (strcmp(bloodType, validTypes[i]) == 0) {
            return true;
        }
    }
    return false;
}

int searchBloodGroup(char bloodType[]) {
    for (int i = 0; i < bloodCount; i++) {
        if (strcmp(bloodGroups[i].bloodType, bloodType) == 0) {
            return i;
        }
    }
    return -1;
}

void saveBloodStock() {
    FILE *file = fopen("blood_stock.txt", "w");

    if (file == NULL) {
        printf("Error saving blood stock!\n");
        return;
    }

    for (int i = 0; i < bloodCount; i++) {
        fprintf(file, "%s %d\n", bloodGroups[i].bloodType, bloodGroups[i].quantity);
    }

    fclose(file);
}

void loadBloodStock() {
    FILE *file = fopen("blood_stock.txt", "r");

    if (file == NULL) {
        return;
    }

    bloodCount = 0;

    while (fscanf(file, "%s %d", bloodGroups[bloodCount].bloodType, &bloodGroups[bloodCount].quantity) != EOF) {
        bloodCount++;
    }

    fclose(file);
}

void saveDonors() {
    FILE *file = fopen("donors.txt", "w");

    if (file == NULL) {
        printf("Error saving donors!\n");
        return;
    }

    for (int i = 0; i < donorCount; i++) {
        fprintf(file, "%s %d %s %s\n",
                donors[i].name,
                donors[i].age,
                donors[i].phone,
                donors[i].bloodType);
    }

    fclose(file);
}

void loadDonors() {
    FILE *file = fopen("donors.txt", "r");

    if (file == NULL) {
        return;
    }

    donorCount = 0;

    while (fscanf(file, "%s %d %s %s",
                  donors[donorCount].name,
                  &donors[donorCount].age,
                  donors[donorCount].phone,
                  donors[donorCount].bloodType) != EOF) {
        donorCount++;
    }

    fclose(file);
}

void saveRequests() {
    FILE *file = fopen("requests.txt", "w");

    if (file == NULL) {
        printf("Error saving requests!\n");
        return;
    }

    for (int i = 0; i < requestCount; i++) {
        fprintf(file, "%s %s %d\n",
                requests[i].hospitalName,
                requests[i].bloodType,
                requests[i].quantity);
    }

    fclose(file);
}

void loadRequests() {
    FILE *file = fopen("requests.txt", "r");

    if (file == NULL) {
        return;
    }

    requestCount = 0;

    while (fscanf(file, "%s %s %d",
                  requests[requestCount].hospitalName,
                  requests[requestCount].bloodType,
                  &requests[requestCount].quantity) != EOF) {
        requestCount++;
    }

    fclose(file);
}

void addBloodGroup() {
    char bloodType[10];
    int quantity;

    if (bloodCount >= MAX_BLOOD_GROUPS) {
        printf("Blood stock is full!\n");
        return;
    }

    printf("Enter blood type: ");
    scanf("%s", bloodType);

    if (!isValidBloodType(bloodType)) {
        printf("Invalid blood type!\n");
        return;
    }

    int index = searchBloodGroup(bloodType);

    if (index != -1) {
        printf("Blood group already exists. Use update option.\n");
        return;
    }

    printf("Enter quantity: ");
    scanf("%d", &quantity);

    if (quantity < 0) {
        printf("Quantity cannot be negative!\n");
        return;
    }

    strcpy(bloodGroups[bloodCount].bloodType, bloodType);
    bloodGroups[bloodCount].quantity = quantity;
    bloodCount++;

    saveBloodStock();

    printf("Blood group added successfully!\n");
}

void displayBloodStock() {
    if (bloodCount == 0) {
        printf("No blood stock available.\n");
        return;
    }

    printf("\n========== Blood Stock ==========\n");

    for (int i = 0; i < bloodCount; i++) {
        printf("%d. Blood Type: %s | Quantity: %d bags\n",
               i + 1,
               bloodGroups[i].bloodType,
               bloodGroups[i].quantity);
    }
}

void searchBlood() {
    char bloodType[10];

    printf("Enter blood type to search: ");
    scanf("%s", bloodType);

    if (!isValidBloodType(bloodType)) {
        printf("Invalid blood type!\n");
        return;
    }

    int index = searchBloodGroup(bloodType);

    if (index == -1) {
        printf("Blood group not found.\n");
    } else {
        printf("Blood Type: %s\n", bloodGroups[index].bloodType);
        printf("Available Quantity: %d bags\n", bloodGroups[index].quantity);
    }
}

void updateBloodQuantity() {
    char bloodType[10];
    int quantity;

    printf("Enter blood type to update: ");
    scanf("%s", bloodType);

    int index = searchBloodGroup(bloodType);

    if (index == -1) {
        printf("Blood group not found.\n");
        return;
    }

    printf("Enter new quantity: ");
    scanf("%d", &quantity);

    if (quantity < 0) {
        printf("Quantity cannot be negative!\n");
        return;
    }

    bloodGroups[index].quantity = quantity;

    saveBloodStock();

    printf("Blood quantity updated successfully!\n");
}

void deleteBloodGroup() {
    char bloodType[10];

    printf("Enter blood type to delete: ");
    scanf("%s", bloodType);

    int index = searchBloodGroup(bloodType);

    if (index == -1) {
        printf("Blood group not found.\n");
        return;
    }

    for (int i = index; i < bloodCount - 1; i++) {
        bloodGroups[i] = bloodGroups[i + 1];
    }

    bloodCount--;

    saveBloodStock();

    printf("Blood group deleted successfully!\n");
}

void addDonor() {
    if (donorCount >= MAX_DONORS) {
        printf("Donor list is full!\n");
        return;
    }

    printf("Enter donor name without space: ");
    scanf("%s", donors[donorCount].name);

    printf("Enter age: ");
    scanf("%d", &donors[donorCount].age);

    if (donors[donorCount].age < 18) {
        printf("Donor must be at least 18 years old.\n");
        return;
    }

    printf("Enter phone: ");
    scanf("%s", donors[donorCount].phone);

    printf("Enter blood type: ");
    scanf("%s", donors[donorCount].bloodType);

    if (!isValidBloodType(donors[donorCount].bloodType)) {
        printf("Invalid blood type!\n");
        return;
    }

    donorCount++;

    saveDonors();

    printf("Donor added successfully!\n");
}

void displayDonors() {
    if (donorCount == 0) {
        printf("No donors found.\n");
        return;
    }

    printf("\n========== Donor List ==========\n");

    for (int i = 0; i < donorCount; i++) {
        printf("%d. Name: %s | Age: %d | Phone: %s | Blood Type: %s\n",
               i + 1,
               donors[i].name,
               donors[i].age,
               donors[i].phone,
               donors[i].bloodType);
    }
}

void createBloodRequest() {
    char bloodType[10];
    int quantity;

    if (requestCount >= MAX_REQUESTS) {
        printf("Request list is full!\n");
        return;
    }

    printf("Enter hospital name without space: ");
    scanf("%s", requests[requestCount].hospitalName);

    printf("Enter required blood type: ");
    scanf("%s", bloodType);

    if (!isValidBloodType(bloodType)) {
        printf("Invalid blood type!\n");
        return;
    }

    printf("Enter required quantity: ");
    scanf("%d", &quantity);

    if (quantity <= 0) {
        printf("Quantity must be positive!\n");
        return;
    }

    int index = searchBloodGroup(bloodType);

    if (index == -1 || bloodGroups[index].quantity < quantity) {
        printf("Not enough blood stock available!\n");
        return;
    }

    bloodGroups[index].quantity -= quantity;

    strcpy(requests[requestCount].bloodType, bloodType);
    requests[requestCount].quantity = quantity;
    requestCount++;

    saveBloodStock();
    saveRequests();

    printf("Blood request completed successfully!\n");
}

void displayRequests() {
    if (requestCount == 0) {
        printf("No blood requests found.\n");
        return;
    }

    printf("\n========== Blood Request History ==========\n");

    for (int i = 0; i < requestCount; i++) {
        printf("%d. Hospital: %s | Blood Type: %s | Quantity: %d bags\n",
               i + 1,
               requests[i].hospitalName,
               requests[i].bloodType,
               requests[i].quantity);
    }
}

int login() {
    char username[20];
    char password[20];

    printf("\n========== Admin Login ==========\n");
    printf("Username: ");
    scanf("%s", username);

    printf("Password: ");
    scanf("%s", password);

    if (strcmp(username, "admin") == 0 && strcmp(password, "1234") == 0) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Invalid username or password!\n");
        return 0;
    }
}

void menu() {
    printf("\n====================================\n");
    printf("     BLOOD BANK MANAGEMENT SYSTEM\n");
    printf("====================================\n");
    printf("1. Add Blood Group\n");
    printf("2. Display Blood Stock\n");
    printf("3. Search Blood Group\n");
    printf("4. Update Blood Quantity\n");
    printf("5. Delete Blood Group\n");
    printf("6. Add Donor\n");
    printf("7. Display Donors\n");
    printf("8. Create Blood Request\n");
    printf("9. Display Blood Requests\n");
    printf("10. Exit\n");
    printf("====================================\n");
    printf("Enter your choice: ");
}

int main() {
    int choice;

    loadBloodStock();
    loadDonors();
    loadRequests();

    if (!login()) {
        return 0;
    }

    while (1) {
        menu();
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addBloodGroup();
                break;

            case 2:
                displayBloodStock();
                break;

            case 3:
                searchBlood();
                break;

            case 4:
                updateBloodQuantity();
                break;

            case 5:
                deleteBloodGroup();
                break;

            case 6:
                addDonor();
                break;

            case 7:
                displayDonors();
                break;

            case 8:
                createBloodRequest();
                break;

            case 9:
                displayRequests();
                break;

            case 10:
                printf("Thank you for using Blood Bank Management System.\n");
                exit(0);

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}