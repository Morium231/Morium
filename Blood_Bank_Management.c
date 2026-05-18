#include<stdio.h>
#include<string.h>
#include <stdbool.h>
#include <stdlib.h>

struct BloodGroup {
    char bloodType[10];
    int quantity;
} ;
struct BloodGroupPackage {
    int N;
    struct BloodGroup bloodPackage[10] ;
} Packages[10];
int package_count=0;


bool isValidBloodType(const char *bloodType) {
    const char *validBloodTypes[] = {"A+", "A-", "B+", "B-", "O+", "O-", "AB+", "AB-"};
    for (int i = 0; i < 8; i++) {
        if (strcmp(bloodType, validBloodTypes[i]) == 0) {
            return true;
        }
    }
    return false;
}


int searchBloodGroup(struct BloodGroup * bloodGroups, int count,
    const char * bloodType) {
    for (int i = 0; i < count; i++) {
        if (strcmp(bloodGroups[i].bloodType, bloodType) == 0) {
            return i;
        }
    }
    return -1;
}


void addBloodGroup(struct BloodGroup * bloodGroups, int * count ) {
    int maxCount = 8;

    if (*count >= maxCount) {
        printf("Blood group array is full.\n");
        return;
    }

    char bloodType[10];
    int quantity;

    printf("\n\t\tEnter blood type: ");
    scanf("%s", bloodType);

    int index = searchBloodGroup(bloodGroups, * count, bloodType);
    if (index != -1) {
        printf("\nThis blood group already added!\nIf you want to update this blood group, then enter your choice 5.\n");
        return;
    }

    printf("\n\t\tEnter quantity: ");
    scanf("%d", & quantity);

    strcpy(bloodGroups[ * count].bloodType, bloodType);
    bloodGroups[ * count].quantity = quantity;
    ( * count) += 1;
}

void updateBloodPackageAfterDelete(const char *bloodType) {
    for (int i = 0; i < package_count; i++) {
     for (int j = 0; j < Packages[i].N; j++) {
      if (strcmp(Packages[i].bloodPackage[j].bloodType, bloodType) == 0) {
       for (int k = j; k < Packages[i].N - 1; k++) {
                    strcpy(Packages[i].bloodPackage[k].bloodType, Packages[i].bloodPackage[k + 1].bloodType);
                    Packages[i].bloodPackage[k].quantity = Packages[i].bloodPackage[k + 1].quantity;
             }
             Packages[i].N--;

             printf("\nAfter deleting all Packages:\n");

     for (int j = 0; j < package_count; j++) {
        printf("Blood Package no.%d:\n", j + 1);
        for (int i = 0; i < Packages[j].N; i++) {
            printf("%d. Blood Type: %s, Quantity: %d\n", i + 1, Packages[j].bloodPackage[i].bloodType, Packages[j].bloodPackage[i].quantity);
          }
        }
         return;
      }
     }
   }
}



void deleteBloodGroup(struct BloodGroup * bloodGroups, int * count,
    const char * bloodType) {
    int index = searchBloodGroup(bloodGroups, * count, bloodType);

    if (index == -1) {
        printf("Blood group not found.\n");
        return;
    }

    for (int i = index; i < * count - 1; i++) {
        bloodGroups[i] = bloodGroups[i + 1];
    }
    ( * count) --;
    updateBloodPackageAfterDelete(bloodType);
}



void displayBloodGroups(struct BloodGroup * bloodGroups, int count) {
    if (count == 0) {
        printf("Blood group not found.\n");
        return;
    }

    printf("Available blood groups:\n");

    for (int i = 0; i < count; i++) {
        printf("Blood Type: %s  quantity: %d\n", bloodGroups[i].bloodType, bloodGroups[i].quantity);
    }
}

void updateBloodPackageAfterUpdate(struct BloodGroup *bloodGroups, int count, const char *bloodType) {
    for (int i = 0; i < package_count; i++) {
     for (int j = 0; j < Packages[i].N; j++) {
      if (strcmp(Packages[i].bloodPackage[j].bloodType, bloodType) == 0) {
        printf("Enter new quantity of blood %s for blood package no.%d:",bloodType,i);
           scanf("%d",&Packages[i].bloodPackage[j].quantity );

           printf("\n After updating all  Packages:\n");

    for (int j = 0; j < package_count; j++) {
        printf("Blood Package no.%d:\n", j + 1);
        for (int i = 0; i < Packages[j].N; i++) {
            printf("%d. Blood Type: %s, Quantity: %d\n", i + 1, Packages[j].bloodPackage[i].bloodType, Packages[j].bloodPackage[i].quantity);
        }
      }
              return;
    }
  }
 }
}


void updateBloodQuantity(struct BloodGroup * bloodGroups, int count,
    const char * bloodType, int quantity) {
    int index = searchBloodGroup(bloodGroups, count, bloodType);

    if (index == -1) {
        printf("Blood group not found.\n");
        return;
    }
    printf("\n\t\tEnter quantity: ");

    bloodGroups[index].quantity = quantity;
    updateBloodPackageAfterUpdate(bloodGroups,count, bloodType);
}



void createBloodGroupPackage(struct BloodGroup * bloodGroups, int count, const char * packageDetails) {
    char bloodType[10];
    int quantity;
    printf("Creating blood group package...\n");
    printf("Enter the number of blood group to creat a package:");
    scanf("%d",&Packages[package_count].N);
     for (int i = 0; i <Packages[package_count].N; i++)
     {
       printf("\n\t\tEnter blood type: ");
       scanf("%s",&bloodType);
       int index = searchBloodGroup(bloodGroups, count, bloodType);
       if (index == -1)  {
        printf("Blood group not found.\n");
        return;
       }
       printf("\n\t\tEnter quantity: ");
       scanf("%d", & quantity);
       if (bloodGroups[index].quantity<quantity)  {
        printf("You have not enough amount of %s blood to creat this package!\n",bloodType);
        return;
       }
       strcpy(Packages[package_count].bloodPackage[i].bloodType, bloodType);
      Packages[package_count].bloodPackage[i].quantity = quantity;
     }

     printf("New package details:\n");
     printf("Blood Package no.%d:\n", package_count + 1);
     for (int i = 0; i < Packages[package_count].N; i++) {
        printf("%d. Blood Type: %s, Quantity: %d\n", i + 1, Packages[package_count].bloodPackage[i].bloodType, Packages[package_count].bloodPackage[i].quantity);
    }
    package_count++;

    printf("\nAll Created Packages:\n");


    for (int j = 0; j < package_count; j++) {
        printf("Blood Package no.%d:\n", j + 1);
        for (int i = 0; i < Packages[j].N; i++) {
            printf("%d. Blood Type: %s, Quantity: %d\n", i + 1, Packages[j].bloodPackage[i].bloodType, Packages[j].bloodPackage[i].quantity);
        }
    }
}

int main() {
    struct BloodGroup bloodGroups[8];
    int count = 0;
    int choice;
    char bloodType[10];
    int quantity;

    while (1) {
        printf("\nBlood Bank Management System\n");
        printf("1. Add Blood Group\n");
        printf("2. Delete Blood Group\n");
        printf("3. Search Blood Group\n");
        printf("4. Display Blood Groups\n");
        printf("5. Update Blood Quantity\n");
        printf("6. Create Blood Group Package\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", & choice);
        switch (choice) {
        case 1:
            addBloodGroup(bloodGroups, & count);
            break;
        case 2:
            printf("Enter blood type to delete: ");
            scanf("%s", bloodType);
            deleteBloodGroup(bloodGroups, & count, bloodType);
            break;
        case 3:
            printf("Enter blood type to search: ");
            scanf("%s", bloodType);
            if(isValidBloodType(bloodType)) {
                if (searchBloodGroup(bloodGroups, count, bloodType) != -1) {
                    printf("Blood group found.\n");
                } else {
                    printf("Blood group not found.\n");
                }
            } else {

                printf("Entered Blood Group Does not Exist.\n");
            }
            break;
        case 4:
            displayBloodGroups(bloodGroups, count);
            break;
        case 5:
            printf("Enter blood type to update: ");
            scanf("%s", bloodType);
            printf("Enter new quantity: ");
            scanf("%d", & quantity);
            updateBloodQuantity(bloodGroups, count, bloodType, quantity);
            break;
        case 6:
            createBloodGroupPackage(bloodGroups, count, "PackageDetails");
            break;
        case 7:
            exit(0);
        default:
            printf("Invalid choice!\n");
        }
    }
    return 0;
}
