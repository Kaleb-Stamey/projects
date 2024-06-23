/*
* Name: Kaleb Stamey
* Class: CS2060 T/R 1:40 - 2:55 PM
* Windows OS
* Due: April 24th, 2024
* Description: This program is for the UCCS RideShare app, it
* takes in the user input for number of miles and calculates
* and displays the number of miles, minutes, and price for each ride
* Works for several Ride Shares
* 
* (NOTE: This program was written for a WINDOWS machine)
*/


#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>



//fare & str size
#define MAX_STRING_SIZE 80
#define MIN_RAND_MINUTES_FACTOR 1.2
#define MAX_RAND_MINUTES_FACTOR 1.5
#define MIN_MILES 1
#define MAX_MILES 100
//admin login
#define LOGIN_ATTEMPTS 4
#define CORRECT_LOGIN true 
#define INCORRECT_LOGIN false 
#define ID "id1"
#define PASSWORD "ABCD"
//survey
#define SURVEY_RIDERS 5
#define MAX_RATING 5
#define MIN_RATING 1
#define SURVEY_CATEGORIES 3
#define SAFETY 0
#define CLEANLINESS 1
#define COMFORT 2
//Values for admin Setup 
#define MIN_SETUP 0.1
#define MAX_SETUP 50
//admin
#define SENTINEL_VALUE -1
#define COUNT_FOR_ADMIN_SUMMARY 0





typedef struct rideShare {
	double baseFare;
	double costPerMin;
	double costPerMile;
	double minFlatRate;

	char orgName[MAX_STRING_SIZE];

	double totalFare;
	double totalMiles;
	double totalMinutes;
	unsigned int riderNum;
	unsigned int surveyCnt;

	unsigned int rideShareSurvey[SURVEY_RIDERS][SURVEY_CATEGORIES];
	double categoryAverages[SURVEY_CATEGORIES];
}RideShare;

typedef struct node {

	RideShare rideShare;
	struct node* next;

}Node;

//fare
double calculateFare(RideShare* rideShare, double miles, double minutes);
void printFare(int count, double miles, int minutes, double fare);
//admin
void insertNode(Node** headPtr, RideShare rideShare);
bool adminLogin();
void adminSetup(Node** headptr);
//miscellaneous
void initializeRideShare(RideShare* rideShare);
void removeNewLine(char* string);
//validation
double scanfDoubleSentinel(int sentinel);
bool scanfInt(int* myIntPtr);
double scanfDoubleAdmin();
bool yesNoBool();
double scanfDoubleSentinel(int sentinel);
//survey functions
void getRatings(const char* categories[], RideShare* rideShare);
void printSurveyResults(const char* categories[], RideShare rideShare);
void calculateCategoryAverages(RideShare* rideShare);
void printCategoryData(const char* categories[], RideShare* rideShare);

//Rider Mode
bool riderMode(RideShare* rideShare, const char* surveyCategories[SURVEY_CATEGORIES]);
void createFileName(char tempStr[MAX_STRING_SIZE], char myStr[MAX_STRING_SIZE], char orgName[MAX_STRING_SIZE]);
void replaceSpace(char* myStrPtr);
void printToFile(FILE* cFilePtr, RideShare rideShare, const char* surveyCategories[SURVEY_CATEGORIES]);

//main
int main(void) {

	bool correctLogin = false;
	bool userModeLoop = true;

	const char* surveyCategories[SURVEY_CATEGORIES] = { "Safety", "Cleanliness", "Comfort" };
	Node* headPtr = NULL;


	//admin login
	correctLogin = adminLogin();
	if (correctLogin == CORRECT_LOGIN) {
		adminSetup(&headPtr);
		correctLogin = false;


		Node* rideShareList = NULL;
		//stops if usermode returns false
		while (userModeLoop) {
			rideShareList = headPtr;
			//displays all ratings for each orginization
			while (rideShareList != NULL) {
				printf("\n%s RideShare Ratings: \n", rideShareList->rideShare.orgName);
				printSurveyResults(surveyCategories, rideShareList->rideShare);
				puts("");
				rideShareList = rideShareList->next;
			}
			char usersString[MAX_STRING_SIZE] = " ";
			bool found = false;
			//while user doesn't enter correct name
			while (!found) {
				printf("%s", "Enter the name of the rideShare that you want to take: ");
				fgets(&usersString, MAX_STRING_SIZE, stdin);
				removeNewLine(&usersString);
				rideShareList = headPtr;
				while (rideShareList != NULL && !found) {
					if (strcmp(usersString, rideShareList->rideShare.orgName) == 0) {
						found = true;
					}
					else {
						rideShareList = rideShareList->next;
					}
				}
				if (found == false) {
					puts("Error you did not enter a correct name.");
				}
			}
			userModeLoop = riderMode(&rideShareList->rideShare, surveyCategories);
		}

		//admin report
		correctLogin = adminLogin();
		if (correctLogin) {
			puts(" ");
			puts("Admin Summary");
			//writes to files
			Node* tempNode = headPtr;
			while (tempNode != NULL) {
				calculateCategoryAverages(&tempNode->rideShare);
				printCategoryData(surveyCategories, &tempNode->rideShare);
				puts(" ");
				puts("Totals: ");
				printFare(tempNode->rideShare.riderNum, tempNode->rideShare.totalMiles, tempNode->rideShare.totalMinutes, tempNode->rideShare.totalFare);
				tempNode = tempNode->next;
			}

			//printing the information to seperate files for each rideShare
			tempNode = headPtr;
		
			while (tempNode != NULL) {
				char filePath[MAX_STRING_SIZE] = "C:\\Users\\Orange\\RideShareTotals\\";
				char finalFilePath[MAX_STRING_SIZE] = " ";
				FILE* cFilePtr = NULL;
				char orgNameNoSpace[MAX_STRING_SIZE] = " ";
				for (size_t i = 0; i < MAX_STRING_SIZE; i++) {
					orgNameNoSpace[i] = tempNode->rideShare.orgName[i];
				}
				replaceSpace(&orgNameNoSpace);
				createFileName(finalFilePath, filePath, orgNameNoSpace);
				cFilePtr = fopen(finalFilePath, "w");
				printToFile(cFilePtr, tempNode->rideShare, surveyCategories);

				tempNode = tempNode->next;
			}

		}


	}//if correct login 

	else {
		puts("Exiting");
	}

	//free nodes
	Node* currentPtr = headPtr;
	Node* nextNodePtr = NULL;
	while (currentPtr != NULL) {
		nextNodePtr = currentPtr->next;
		free(currentPtr);
		currentPtr = nextNodePtr;
	}
	

}//main


/*
Returns: nothing
Parameters: file pointer, rideShare, survey categories
Description of Function: prints all information formatted to a file for rideShare.
*/
void printToFile(FILE* cFilePtr, RideShare rideShare, const char* surveyCategories[SURVEY_CATEGORIES]) {

	
	bool avgs = false;
	if (rideShare.categoryAverages[0] > 0) {
		avgs = true;
	}


	if (avgs) {
		//loop to display each category horizontally
		fprintf(cFilePtr, "\nCategory Rating Averages for %s\t\n", rideShare.orgName);
		for (size_t surveyCategory = 0; surveyCategory < SURVEY_CATEGORIES; ++surveyCategory) {
			fprintf(cFilePtr, "%zu.%s\t\t", surveyCategory + 1, surveyCategories[surveyCategory]);
		}
		fprintf(cFilePtr, "%s\n", " "); // start new line of output
		for (size_t categoryNum = 0; categoryNum < SURVEY_CATEGORIES; ++categoryNum) {

			fprintf(cFilePtr, "%f\t\t\t", rideShare.categoryAverages[categoryNum]);

		}
	}

	else if (!avgs) {
		fprintf(cFilePtr, "\nCategory Rating Averages for %s\t\n", rideShare.orgName);
		fputs("No surveys were Entered", cFilePtr);
		fprintf(cFilePtr, "%s\n", " ");
	}

	fprintf(cFilePtr, "\nTotals for %s\t\n", rideShare.orgName);
	if (rideShare.riderNum == COUNT_FOR_ADMIN_SUMMARY) {
		fprintf(cFilePtr, "\n%s\n", "There were no rides");
	}
	else {
		fputs("Rider    Number of Miles     Number of Minutes    Ride Fare Amount", cFilePtr);
		fprintf(cFilePtr, "%s\n", " ");
		fprintf(cFilePtr, "%d\t\t%f\t\t%f\t\t%f", rideShare.riderNum, rideShare.totalMiles, rideShare.totalMinutes, rideShare.totalFare);
	}

}


/*
Returns: nothing
Parameters: name of orginization
Description of Function: if name contains space it replaces with '_'
*/
void replaceSpace(char* myStrPtr) {
	
	for (size_t i = 0; i < MAX_STRING_SIZE; i++) {
		if (myStrPtr[i] == ' ') {
			myStrPtr[i] = '_';
		}
	}

}


/*
Returns: nothing
Parameters:string for final path to be saved to, initial path str, orgname string.
Description of Function: creates a file path for windows machine and saves to a string.
*/
void createFileName(char tempStr[MAX_STRING_SIZE], char myStr[MAX_STRING_SIZE], char orgName[MAX_STRING_SIZE]) {
	
	char txtStr[MAX_STRING_SIZE] = ".txt";
	bool firstNull = false;

	size_t leftOff = 0;
	for (size_t i = 0; i < MAX_STRING_SIZE; i++) {
		if (!firstNull) {
			if (myStr[i] != '\0') {
				tempStr[i] = myStr[i];
				leftOff = i;
			}
			else {
				firstNull = true;
			}
		}
	}

	firstNull = false;
	bool secondNull = false;

	size_t leftOffTwo = 0;
	for (size_t i = 0; i < MAX_STRING_SIZE; i++) {
		if (!firstNull) {
			if (orgName[i] != '\0') {
				tempStr[leftOff + 1 + i] = orgName[i];
				leftOffTwo = leftOff + 1 + i;
			}
			else {
				firstNull = true;
			}
		}
	}

	for (size_t i = 0; i < MAX_STRING_SIZE; i++) {
		if (!secondNull) {
			if (txtStr[i] != '\0') {
				tempStr[leftOffTwo + 1 + i] = txtStr[i];
			}
			else {
				secondNull = true;
			}
		}
	}
}


/*
Returns: Boolean for if sentinel entered or not
Parameters: one rideshare, and the survey categories
Description of Function: obtains miles and calcuates the fair for one rider
*/

bool riderMode(RideShare* rideShare, const char* surveyCategories[SURVEY_CATEGORIES]) {
	double fare = 0.0;
	double minMinutes = 0.0;
	double maxMinutes = 0.0;
	double randMinutes = 0.0;
	double miles = 0.0;
	bool notSentinel = true;

	printf("\n%s", "Enter the number of miles to your destination: ");
	miles = scanfDoubleSentinel(SENTINEL_VALUE);
	if (miles != SENTINEL_VALUE) {
		rideShare->riderNum += 1;
		minMinutes = miles * MIN_RAND_MINUTES_FACTOR;
		maxMinutes = miles * MAX_RAND_MINUTES_FACTOR;

		unsigned int intMaxMinutes = (int)maxMinutes;
		unsigned int intMinMinutes = (int)minMinutes;


		if (miles > MIN_MILES) {
			randMinutes = ((int)minMinutes + rand() % (intMaxMinutes - intMinMinutes));
		}
		else {
			randMinutes = maxMinutes;
		}

		fare = calculateFare(rideShare, miles, randMinutes);

		rideShare->totalMiles += miles;
		rideShare->totalMinutes += randMinutes;
		rideShare->totalFare += fare;

		printf("\n%s\n", "Current Ride Information");
		printFare(rideShare->riderNum, miles, randMinutes, fare);

		puts("\n\nDo you want to rate your rideShare experience? Y/N");
		bool rateRideShare = yesNoBool();

		if (rateRideShare) {
			getRatings(surveyCategories, rideShare);
			rideShare->surveyCnt++;
		}
		else {
			puts("Thanks for riding with us");
		}
	}
		
	else {
		notSentinel = false;
	}
	return notSentinel;
}


/*
Returns: nothing
Parameters: one rideShare
Description of Function: initializes the rideShare
*/
void initializeRideShare(RideShare* rideShare) {

	for (size_t i = 0; i < SURVEY_RIDERS; i++) {
		for (size_t j = 0; j < SURVEY_CATEGORIES; j++) {
			rideShare->rideShareSurvey[i][j] = 0;
		}
	}
	for (size_t i = 0; i < SURVEY_CATEGORIES; i++) {
		rideShare->categoryAverages[i] = 0;
	}

	rideShare->riderNum = 0;
	rideShare->totalFare = 0.0;
	rideShare->totalMiles = 0.0;
	rideShare->totalMinutes = 0.0;
	rideShare->surveyCnt = 0;
}


/*
Returns:nothing
Parameters:string
Description of Function:removes the new line char from string for admin pass and id comparison
*/
void removeNewLine(char* string) {

	size_t index = 0;
	for (size_t i = 0; i < MAX_STRING_SIZE; ++i) {
		if (string[i] == '\n') {
			index = i;
		}
	}
	string[index] = '\0';

}


/*
Returns: valid double
Parameters:sentinel value
Description of Function: if not sentinel it returns a valid number otherwise loops until valid or sentinel
*/
double scanfDoubleSentinel(int sentinel) {

	double theDouble = 0.0;
	char myString[MAX_STRING_SIZE];
	char* end;
	bool validDouble = false;
	errno = 0;

	while (!validDouble) {

		fgets(myString, MAX_STRING_SIZE, stdin);
		if (myString[strlen(myString) - 1] == '\n') {
			myString[strlen(myString) - 1] = '\0';
		}

		theDouble = strtod(myString, &end);

		if (*end != '\0') {
			puts("You have not entered a valid number");
			printf("%s", "Re-Enter:");
		}

		else if (ERANGE == errno) {
			puts("The number you have entered is out of the range");
			printf("%s", "Re-enter a number: ");
		}

		else if (theDouble == (double)sentinel) {
			validDouble = true;
		}

		else if (theDouble >= MIN_MILES && theDouble <= MAX_MILES) {
			validDouble = true;
		}

		else if (theDouble < MIN_MILES || theDouble > MAX_MILES) {

			if (theDouble == 0) {
				puts("You have not entered a valid number");
			}
			else {
				printf("The number you have entered is out of the range %d - %d\n", MIN_MILES, MAX_MILES);
			}
			printf("%s", "Re-enter a number: ");
		}
	}//while

	return theDouble;

}//get valid double


/*
Returns:double
Parameters:none
Description of Function: returns valid double loops until valid is entered
*/
double scanfDoubleAdmin() {
	double theDouble = 0.0;
	char myString[MAX_STRING_SIZE];
	char* end = NULL;
	bool validDouble = false;
	errno = 0;

	while (!validDouble) {

		fgets(myString, MAX_STRING_SIZE, stdin);
		if (myString[strlen(myString) - 1] == '\n') {
			myString[strlen(myString) - 1] = '\0';
		}

		theDouble = strtod(myString, &end);

		if (*end != '\0') {
			puts("You haven't entered a valid number");
			printf("%s", "Re-enter a number: ");
		}

		else if (ERANGE == errno) {
			puts("The number you have entered is out of the range");
			printf("%s", "Re-enter a number: ");
		}


		else if (theDouble < MIN_SETUP || theDouble > MAX_SETUP) {

			if (theDouble == 0) {
				puts("You have not entered a valid number");
			}
			else {
				puts("The number you have entered is out of the range 0.1 - 50");
			}
			printf("%s", "Re-enter a number: ");
		}

		else if (theDouble >= MIN_SETUP && theDouble <= MAX_SETUP) {
			validDouble = true;
		}
	}//while

	return theDouble;
}


/*
Returns: boolean true if was able to return valid int
Parameters: intPtr, (address of the integer in getRatings function)
Description of Function:
*/
bool scanfInt(int* myIntPtr) {
	char myString[MAX_STRING_SIZE];
	char* end;
	bool isInt = false;
	errno = 0;
	fgets(myString, MAX_STRING_SIZE, stdin);

	if (myString[strlen(myString) - 1] == '\n') {
		myString[strlen(myString) - 1] = '\0';
	}

	long testVal = strtol(myString, &end, 10);

	if (end == myString) {
		printf("\nERROR: %s: not a decimal number\n", myString);
		printf("%s", "Enter a valid Integer : ");
	}

	else if (ERANGE == errno) {
		puts("The number you have entered is out of the range");
		printf("%s", "Re-enter a number: ");
	}
	//if end is not null
	else if ('\0' != *end) {
		printf("\nERROR: %s: extra characters at end of input %s\n", myString, end);
		printf("%s", "Enter a valid Integer : ");
	}
	else if (testVal > MAX_RATING) {
		printf("\nERROR: %d > %d\n", (int)testVal, MAX_RATING);
		printf("%s", "Enter a valid Integer : ");
	}

	else if (testVal < MIN_RATING) {
		printf("\nERROR: %d < %d\n", (int)testVal, MIN_RATING);
		printf("%s", "Enter a valid Integer : ");
	}

	else {
		isInt = true;
		*myIntPtr = (int)testVal;
	}

	return isInt;
}


/*
Returns: boolean
Parameters: none
Description of Function: return true if y entered else returns false loops until valid input
*/
bool yesNoBool() {
	char myChar = ' ';
	bool yN = false;

	bool correctAnswer = false;
	while (!correctAnswer) {
		scanf("%c", &myChar);
		while (getchar() != '\n');

		switch (myChar) {
		case 'Y':
		case 'y':
			correctAnswer = true;
			yN = true;
			break;
		case 'N':
		case 'n':
			correctAnswer = true;
			break;
		default:
			puts("You did not enter Y/N");
			printf("%s", "Re-enter (Y/N): ");
			break;
		}
	}
	return yN;
}


/*
Returns:double
Parameters:rideShare, miles, minutes
Description of Function: calculates the fare for one rideShare
*/
double calculateFare(RideShare* rideShare, double miles, double minutes) {

	double fare = 0.0;
	fare = rideShare->baseFare + (rideShare->costPerMin * minutes) + (rideShare->costPerMile * miles);

	if (fare < rideShare->minFlatRate) {
		fare = rideShare->minFlatRate;
	}
	return fare;
}//calculate fare


/*
Returns: nothing
Parameters: riderNum, miles, minutes, and fare
Description of Function: prints values if any to print
*/
void printFare(int count, double miles, int minutes, double fare) {


	if (count == COUNT_FOR_ADMIN_SUMMARY) {
		printf("\n%s\n", "There were no rides");
	}
	else {
		puts("Rider    Number of Miles     Number of Minutes    Ride Fare Amount");
		printf("%d\t\t%f\t\t%d\t\t%f", count, miles, minutes, fare);
	}

}//print fare


/*
Returns: boolean
Parameters: none
Description of Function: until admin enters correct pass it loops if 
* the admin fails 4 times program is ended / ridermode loop continues depending on when
*/
bool adminLogin() {

	

	bool correctLogin = false;


	//int returnValue = 0;
	char enteredId[MAX_STRING_SIZE] = " ";
	char enteredPass[MAX_STRING_SIZE] = " ";
	int attempts = 0;
	puts("Admin Login");

	do {

		printf("\n%s", "Enter your Admin id: ");
		fgets(enteredId, MAX_STRING_SIZE, stdin);

		char* tempPtr = strchr(enteredId, '\n');
		if (tempPtr != NULL) {
			removeNewLine(enteredId);
		}

		printf("\n%s", "Enter your Admin Passcode: ");
		fgets(enteredPass, MAX_STRING_SIZE, stdin);

		char* tempPtr2 = strchr(enteredPass, '\n');
		if (tempPtr2 != NULL) {
			removeNewLine(enteredPass);
		}


		if (strcmp(ID, enteredId) == 0 && strcmp(PASSWORD, enteredPass) == 0) {
			correctLogin = true;
			attempts = 0;
		}

		else if (strcmp(ID, enteredId) != 0 || strcmp(PASSWORD, enteredPass) != 0) {
			if (strcmp(ID, enteredId) != 0) {
				puts("The id you have entered is incorrect.");
			}

			if (strcmp(PASSWORD, enteredPass) != 0) {
				puts("The Password you have entered is incorrect.");
			}
			attempts++;
		}
	} while (attempts > 0 && attempts < LOGIN_ATTEMPTS);

	if (attempts == LOGIN_ATTEMPTS) {
		correctLogin = false;
	}
	return correctLogin;
}


/*
Returns: nothing
Parameters: headPtr
Description of Function: sets up as many rideShares as the admin wants
*adds them to a linked list
*/
void adminSetup(Node** headPtr) {

	RideShare rideShare;
	initializeRideShare(&rideShare);

	bool wantsAnotherRideShare = true;
	while (wantsAnotherRideShare) {

		printf("%s", "\n---Ride Share Setup---\n");
		printf("%s", "Enter basFare: ");
		rideShare.baseFare = scanfDoubleAdmin();
		printf("%s", "\nEnter costPerMinute:");
		rideShare.costPerMin = scanfDoubleAdmin();
		printf("%s", "\nEnter costPerMile: ");
		rideShare.costPerMile = scanfDoubleAdmin();
		printf("%s", "\nEnter minFlatRate: ");
		rideShare.minFlatRate = scanfDoubleAdmin();
		printf("%s", "\nEnter Org Name: ");
		fgets(rideShare.orgName, MAX_STRING_SIZE, stdin);
		removeNewLine(rideShare.orgName);
		insertNode(headPtr, rideShare);
		printf("%s", "\nDo you want to create another RideShare? (y/n): ");
		wantsAnotherRideShare = yesNoBool();

	}

}


/*
Returns: void
Parameters: headptr, one rideShare
Description of Function: puts one node in its place (alphabetical order)
*/
void insertNode(Node** headPtr, RideShare rideShare) {

	Node* previous = NULL;
	Node* current = *headPtr;
	Node* toAdd = malloc(sizeof(Node));

	toAdd->rideShare = rideShare;
	toAdd->next = NULL;


	char tempName[80] = " ";
	char nameToAdd[80] = " ";


	for (size_t i = 0; i < sizeof(toAdd->rideShare.orgName); i++) {
		nameToAdd[i] = toupper(toAdd->rideShare.orgName[i]);
	}

	bool found = false;


	if (toAdd != NULL) {
		if (*headPtr == NULL) {
			*headPtr = toAdd;
		}

		else {
			while (current != NULL && !found) {
				for (size_t i = 0; i < sizeof(current->rideShare.orgName); i++) {
					tempName[i] = toupper(current->rideShare.orgName[i]);
				}

				if (strcmp(tempName, nameToAdd) > 0) {
					found = true;
				}
				else {
					previous = current;
					current = current->next;
				}
			}
			if (found && previous == NULL) {
				toAdd->next = current;
				*headPtr = toAdd;
			}
			else if (found && previous != NULL) {
				toAdd->next = current;
				previous->next = toAdd;
			}
			else if (current == NULL) {
				previous->next = toAdd;
			}
		}



	}

}


/*
Returns:void
Parameters:array of categories, one rideShare
Description of Function: gets ratings from one user
*/
void getRatings(const char* categories[], RideShare* rideShare) {


	puts("We want to know how your experience was on your ride today. Using the rating system 1 to 5 enter your rating for each category:");
	puts("enter your rating for each category:");

	for (size_t surveyCategory = 0; surveyCategory < SURVEY_CATEGORIES; ++surveyCategory) {
		printf("\t%zu. %s\t", surveyCategory + 1, categories[surveyCategory]);
	}
	puts("");

	for (size_t surveyCategory = 0; surveyCategory < SURVEY_CATEGORIES; ++surveyCategory) {
		puts("Enter your rating for");
		printf("%zu. %s: ", surveyCategory + 1, categories[surveyCategory]);
		//change the getvalidInt function

		int validInt = 0;
		bool loop = false;
		while (!loop) {
			loop = scanfInt(&validInt);
		}

		rideShare->rideShareSurvey[rideShare->surveyCnt][surveyCategory] = validInt;
	}



}


/*
Returns: nothing
Parameters:categories , one rideShare
Description of Function: prints the results of the survey for one rideShare
*/
void printSurveyResults(const char* categories[], RideShare rideShare) {

	bool noSurveys = true;


	if (rideShare.rideShareSurvey[0][SURVEY_CATEGORIES - 1] > 0) {
		noSurveys = false;
	}


	if (!noSurveys) {
		printf("%s", "Rating Categories:\t");
		for (size_t surveyCategory = 0; surveyCategory < SURVEY_CATEGORIES; ++surveyCategory)
		{
			printf("\t%zu.%s\t", surveyCategory + 1, categories[surveyCategory]);
		}

		for (size_t numRiders = 0; numRiders < SURVEY_RIDERS; numRiders++) {

			if (rideShare.rideShareSurvey[numRiders][SURVEY_CATEGORIES - 1] > 0) {
				printf("\nSurvey %zu:", numRiders + 1);

				for (size_t category = 0; category < SURVEY_CATEGORIES; category++) {
					printf("\t\t\t%d", rideShare.rideShareSurvey[numRiders][category]);
				}
			}
		}
	}
	else {
		puts("No Ratings Currently");
	}
}//printSurveyResults


/*
Returns: nothing
Parameters: one rideShare
Description of Function: calculates averages for each survey category
*/
void calculateCategoryAverages(RideShare* rideShare) {

	int numOfSurveys = 0;

	for (size_t findNumSurveys = 0; findNumSurveys < SURVEY_RIDERS; ++findNumSurveys) {
		if (rideShare->rideShareSurvey[findNumSurveys][SURVEY_CATEGORIES - 1] > 0) {
			numOfSurveys++;
		}
		else {}
	}


	for (size_t categoryNum = 0; categoryNum < SURVEY_CATEGORIES; ++categoryNum) {

		int avgNum = 0;

		for (size_t riderNum = 0; riderNum < SURVEY_RIDERS; ++riderNum) {
			avgNum += rideShare->rideShareSurvey[riderNum][categoryNum];
		}

		rideShare->categoryAverages[categoryNum] = avgNum / (double)numOfSurveys;
	}
}//calculate averages


/*
Returns: nothing
Parameters: categories, one rideShare
Description of Function: prints the category data
*/
void printCategoryData(const char* categories[], RideShare* rideShare) {

	bool avgs = false;


	if (rideShare->categoryAverages[0] > 0) {
		avgs = true;
	}

	if (avgs) {
		//loop to display each category horizontally
		printf("\nCategory Rating Averages for %s\t\n", rideShare->orgName);
		for (size_t surveyCategory = 0; surveyCategory < SURVEY_CATEGORIES; ++surveyCategory) {
			printf("%zu.%s\t\t", surveyCategory + 1, categories[surveyCategory]);
		}
		puts(""); // start new line of output
		for (size_t categoryNum = 0; categoryNum < SURVEY_CATEGORIES; ++categoryNum) {

			printf("%f\t\t\t", rideShare->categoryAverages[categoryNum]);

		}
	}

	else if (!avgs) {
		printf("\nCategory Rating Averages for %s\t\n", rideShare->orgName);
		puts("No surveys were Entered");
		puts(""); 
		puts("");
	}
}//print averages
