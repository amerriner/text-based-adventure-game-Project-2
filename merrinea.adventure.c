#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <pthread.h>

//global mutex for all threads to use
static pthread_mutex_t myMutex = PTHREAD_MUTEX_INITIALIZER;


//struct definition for Rooms
struct Room {
	char* name;
	char* type;
	char* possibleCons[6];
	int numCons;
};



/************************************************
 * Function name: tell_time()
 * Description: this function gets the current
 * time and formats it correctly. It then 
 * saves the time to a file called 
 * "currentTime.txt.
************************************************/
void tell_time(){
	//create variables to get time
	time_t sysTime = time(NULL);
	struct tm *myTime = localtime(&sysTime);
	char tellTime[100] = "currentTime.txt"; //file name variable
	char time[64];
	FILE* timeFile = fopen(tellTime, "w"); //open file
	strftime(time, sizeof time, "%I:%M%P, %A, %B %e, %Y", myTime); //format string correctly
	fprintf(timeFile, "%s\n", time); //write string to file
	fclose(timeFile); //close file
}



/*************************************************
 * function name: write_time
 * Description: this function is the start 
 * function for the second thread of this
 * program. It opens the time file created
 * by tell_time() and prints the contents to 
 * stdout.
*************************************************/
void* write_time(void* argument){
	//attempt to lock locked mutex, which will block thread 2 until main unlocks it
	pthread_mutex_lock(&myMutex);  
	tell_time();	//get current time
	char* time = "currentTime.txt";
	FILE* myFile = fopen(time, "r");	//open file created by tell_time()
	if (myFile != NULL){
		char myLine[256] = "";
		fgets(myLine, sizeof myLine, myFile); //read contents, print to stdout
		printf("%s\n", myLine);
	}
	pthread_mutex_unlock(&myMutex); //unlock mutex so main can go again
	pthread_exit(0); //officially destroy thread
}





int main(void){

	//track number of steps taken by user and stores rooms visited
	int steps = 0;
	char* roomsVisited[100] = {[0 ... 99] = NULL}; //initialize array of strings to clear memory
	int resultInt;

	//create new thread and block it with locked mutex
	pthread_mutex_lock(&myMutex);
	pthread_t myThreadID = pthread_self();
	resultInt = pthread_create(&myThreadID, NULL, write_time, NULL); //start function is write_time
	
	//find the newest directory that begins with "merrinea.rooms"
	int newestAccess = -1;
	char dirPrefix[32] = "merrinea.rooms.";
	char newestDir[256];
	memset(newestDir, '\0', sizeof(newestDir));

	DIR* dir;
	struct dirent *myDirectory;
	struct stat dirAttributes;

	dir = opendir(".");
	if (dir > 0)
	{
		while ((myDirectory = readdir(dir)) != NULL)
		{
			if (strstr(myDirectory->d_name, dirPrefix) != NULL){
				stat(myDirectory->d_name, &dirAttributes);
				if ((int)dirAttributes.st_mtime > newestAccess) //if this directory is newer than last seen
				{
					newestAccess = (int)dirAttributes.st_mtime; //save the time directory was accessed as int
					memset(newestDir, '\0', sizeof(newestDir)); 
					strcpy(newestDir, myDirectory->d_name);  //save name of directory as string 
				}
			}
		}
	}

	struct Room* myMap[7]; //map of game, includes all rooms used


	//initialize first room
	struct Room firstRoom;
	firstRoom.numCons = 0;
	char first_Room[32] = "";
	strcat(first_Room, newestDir);
	strcat(first_Room, "/room1"); //get string of file name to open
	FILE* room1 = fopen(first_Room, "r"); //open that file
	if (room1 != NULL){
		char myLine[256];
		while (fgets(myLine, sizeof myLine, room1) != NULL){ //while the file has information
			char variable[32] = "";
			if(strstr(myLine, "NAME") != NULL){ //if line read is giving room name
				sscanf(myLine, "%*s %*s %s", variable); //scan the line, pick out only the room name
				firstRoom.name = calloc(16, sizeof(char)); //allocate memory, set room's name to variable
				strcpy(firstRoom.name, variable); 
			}
			else if (strstr(myLine, "CONNECTION") != NULL){ //if line is giving room connections
				sscanf(myLine, "%*s %*s %s", variable);
				firstRoom.possibleCons[firstRoom.numCons] = calloc(16, sizeof(char)); //place room in room's possible
				strcpy(firstRoom.possibleCons[firstRoom.numCons], variable);		//connections array
				firstRoom.numCons += 1;	//increment number of rooms in room's possible connections array
			}
			else if (strstr(myLine, "TYPE") != NULL){ //if line is giving room type
				sscanf(myLine, "%*s %*s %s", variable);
				firstRoom.type = calloc(16, sizeof(char));
				strcpy(firstRoom.type, variable);
			}
		}
	}
	myMap[0] = &firstRoom; //save first room in map array
	

	//initialize second room;
	struct Room secRoom;
	secRoom.numCons = 0;
	char sec_Room[32] = "";
	strcat(sec_Room, newestDir);
	strcat(sec_Room, "/room2");
	FILE* room2 = fopen(sec_Room, "r");
	if (room2 != NULL){
		char myLine2[256];
		while (fgets(myLine2, sizeof myLine2, room2) != NULL){
			char variable2[32] = "";
			if (strstr(myLine2, "NAME") != NULL){
				sscanf(myLine2, "%*s %*s %s", variable2);
				secRoom.name = calloc(16, sizeof(char));
				strcpy(secRoom.name, variable2);
			}
			else if (strstr(myLine2, "CONNECTION") != NULL){
				sscanf(myLine2, "%*s %*s %s", variable2);
				secRoom.possibleCons[secRoom.numCons] = calloc(16, sizeof(char));
				strcpy(secRoom.possibleCons[secRoom.numCons], variable2);
				secRoom.numCons += 1;
			}
			else if (strstr(myLine2, "TYPE") != NULL){
				sscanf(myLine2, "%*s %*s %s", variable2);
				secRoom.type = calloc(16, sizeof(char));
				strcpy(secRoom.type, variable2);
			}
		}
	}
	myMap[1] = &secRoom;//save second room in map


	//initialize third room
	struct Room thirdRoom;
	thirdRoom.numCons = 0;
	char third_Room[32] = "";
	strcat(third_Room, newestDir);
	strcat(third_Room, "/room3");
	FILE* room3 = fopen(third_Room, "r");
	if (room3 != NULL){
		char myLine3[256];
		while (fgets(myLine3, sizeof myLine3, room3) != NULL){
			char var3[32] = "";
			if (strstr(myLine3, "NAME") != NULL){
				sscanf(myLine3, "%*s %*s %s", var3);
				thirdRoom.name = calloc(16, sizeof(char));
				strcpy(thirdRoom.name, var3);
			}
			else if (strstr(myLine3, "CONNECTION") != NULL){
				sscanf(myLine3, "%*s %*s %s", var3);
				thirdRoom.possibleCons[thirdRoom.numCons] = calloc(16, sizeof(char));
				strcpy(thirdRoom.possibleCons[thirdRoom.numCons], var3);
				thirdRoom.numCons += 1;
			}
			else if (strstr(myLine3, "TYPE") != NULL){
				sscanf(myLine3, "%*s %*s %s", var3);
				thirdRoom.type = calloc(16, sizeof(char));
				strcpy(thirdRoom.type, var3);
			}
		}
	}
	myMap[2] = &thirdRoom;//save third room in map


	//initialize fourth room
	struct Room fourthRoom;
	fourthRoom.numCons = 0;
	char fourth_Room[32] = "";
	strcat(fourth_Room, newestDir);
	strcat(fourth_Room, "/room4");
	FILE* room4 = fopen(fourth_Room, "r");
	if (room4 != NULL){
		char myLine4[256];
		while (fgets(myLine4, sizeof myLine4, room4) != NULL){
			char var4[32] = "";
			if (strstr(myLine4, "NAME") != NULL){
				sscanf(myLine4, "%*s %*s %s", var4);
				fourthRoom.name = calloc(16, sizeof(char));
				strcpy(fourthRoom.name, var4);
			}
			else if (strstr(myLine4, "CONNECTION") != NULL){
				sscanf(myLine4, "%*s %*s %s", var4);
				fourthRoom.possibleCons[fourthRoom.numCons] = calloc(16, sizeof(char));
				strcpy(fourthRoom.possibleCons[fourthRoom.numCons], var4);
				fourthRoom.numCons += 1;
			}
			else if (strstr(myLine4, "TYPE") != NULL){
				sscanf(myLine4, "%*s %*s %s", var4);
				fourthRoom.type = calloc(16, sizeof(char));
				strcpy(fourthRoom.type, var4);
			}
		}
	}
	myMap[3] = &fourthRoom;//save fourth room in map
	
	//initialize fifth room
	struct Room fifthRoom;
	fifthRoom.numCons = 0;
	char fifth_Room[32] = "";
	strcat(fifth_Room, newestDir);
	strcat(fifth_Room, "/room5");
	FILE* room5 = fopen(fifth_Room, "r");
	if (room5 != NULL){
		char myLine5[256];
		while (fgets(myLine5, sizeof myLine5, room5) != NULL){
			char var5[32] = "";
			if (strstr(myLine5, "NAME") != NULL){
				sscanf(myLine5, "%*s %*s %s", var5);
				fifthRoom.name = calloc(16, sizeof(char));
				strcpy(fifthRoom.name, var5);
			}
			else if (strstr(myLine5, "CONNECTION") != NULL){
				sscanf(myLine5, "%*s %*s %s", var5);
				fifthRoom.possibleCons[fifthRoom.numCons] = calloc(16, sizeof(char));
				strcpy(fifthRoom.possibleCons[fifthRoom.numCons], var5);
				fifthRoom.numCons += 1;
			}
			else if (strstr(myLine5, "TYPE") != NULL){
				sscanf(myLine5, "%*s %*s %s", var5);
				fifthRoom.type = calloc(16, sizeof(char));
				strcpy(fifthRoom.type, var5);
			}
		}
	}
	myMap[4] = &fifthRoom;//save fifth room in map

	//initialize sixth room
	struct Room sixthRoom;
	sixthRoom.numCons = 0;
	char sixth_Room[32] = "";
	strcat(sixth_Room, newestDir);
	strcat(sixth_Room, "/room6");
	FILE* room6 = fopen(sixth_Room, "r");
	if (room6 != NULL){
		char myLine6[256];
		while (fgets(myLine6, sizeof myLine6, room6) != NULL){
			char var6[32] = "";
			if (strstr(myLine6, "NAME") != NULL){
				sscanf(myLine6, "%*s %*s %s", var6);
				sixthRoom.name = calloc(16, sizeof(char));
				strcpy(sixthRoom.name, var6);
			}
			else if (strstr(myLine6, "CONNECTION") != NULL){
				sscanf(myLine6, "%*s %*s %s", var6);
				sixthRoom.possibleCons[sixthRoom.numCons] = calloc(16, sizeof(char));
				strcpy(sixthRoom.possibleCons[sixthRoom.numCons], var6);
				sixthRoom.numCons += 1;
			}	
			else if (strstr(myLine6, "TYPE") != NULL){
				sscanf(myLine6, "%*s %*s %s", var6);
				sixthRoom.type = calloc(16, sizeof(char));
				strcpy(sixthRoom.type, var6);
			}
		}
	}
	myMap[5] = &sixthRoom;//save sixth room in map

	//initialize seventh room
	struct Room sevRoom;
	sevRoom.numCons = 0;
	char sev_Room[32] = "";
	strcat(sev_Room, newestDir);
	strcat(sev_Room, "/room7");
	FILE* room7 = fopen(sev_Room, "r");	
	if (room7 != NULL){
		char myLine7[256];
		while (fgets(myLine7, sizeof myLine7, room7) != NULL){
			char var7[32] = "";
			if (strstr(myLine7, "NAME") != NULL) {
				sscanf(myLine7, "%*s %*s %s", var7);
				sevRoom.name = calloc(16, sizeof(char));
				strcpy(sevRoom.name, var7);
			}
			else if (strstr(myLine7, "CONNECTION") != NULL){
				sscanf(myLine7, "%*s %*s %s", var7);
				sevRoom.possibleCons[sevRoom.numCons] = calloc(16, sizeof(char));
				strcpy(sevRoom.possibleCons[sevRoom.numCons], var7);
				sevRoom.numCons += 1;
			}
			else if (strstr(myLine7, "TYPE") != NULL){
				sscanf(myLine7, "%*s %*s %s", var7);
				sevRoom.type = calloc(16, sizeof(char));
				strcpy(sevRoom.type, var7);
			}
		}
	}
	myMap[6] = &sevRoom;//save seventh room in map


	struct Room roomIn; //temp room to move around myMap
	int k;
	char* start = "START_ROOM";
	//find room of type "START_ROOM" to initialize temp room
	for (k = 0; k < 7; k++){
		if (strcmp(myMap[k]->type, start) == 0){
			roomIn = *myMap[k];
		}
	}

	char* end = "END_ROOM";
	while (strcmp(roomIn.type, end) != 0){ 
		//initialize variables to get user input
		int numCharsEntered = -5;
		int currChar = -5;
		size_t bufferSize = 0;
		char* lineEntered = NULL;

		//print out current location, possible room connections, and ask where user wants to go
		printf("CURRENT LOCATION: %s\n", roomIn.name);
		printf("POSSIBLE CONNECTIONS: ");
		int j;
		for (j = 0; j < roomIn.numCons; j++){
			int num = roomIn.numCons;
			if (j == (num - 1)){
				printf("%s.\n", roomIn.possibleCons[j]);
			}
			else{
				printf("%s, ", roomIn.possibleCons[j]);
			}
		}
		//loop for correct output after time display
		while(1){
			printf("WHERE TO? >");
			numCharsEntered = getline(&lineEntered, &bufferSize, stdin); //user input
			printf("\n");
			int s;
			char* startThread = "time";
			//if the user input == "time", start time keeping thread
			if (strstr(lineEntered, startThread) != NULL){
				pthread_mutex_unlock(&myMutex); //main unlocks mutex so thread2 can unbreak
				pthread_join(myThreadID, NULL);	//main joins with thread2 so main won't keep going
				pthread_mutex_lock(&myMutex);	//thread2 is done, relock mutex to restart cycle
				pthread_t myThreadID = pthread_self(); //recreate thread2
				int res = pthread_create(&myThreadID, NULL, write_time, NULL);
				//free(lineEntered);
			}
			else {
				//loop through possible room connections of current room to look
				//for a match to what the user put in
				for (s = 0; s < roomIn.numCons; s++){
					char* myCon = roomIn.possibleCons[s];
					if (strstr(lineEntered, myCon) != NULL){ //room found
						roomsVisited[steps] = roomIn.name;
						steps += 1;
						int x;
						//loop through myMap to find correct room to move to
						for (x = 0; x < 7; x++){
							if (strstr(lineEntered, myMap[x]->name) != NULL){ 
								roomIn = *myMap[x]; //copy struct of chosen room to temp room struct
							}
						}	
					}
				}
				if (strstr(lineEntered, roomIn.name) == NULL){ //if room moved to or stayed in--didn't change rooms--
					printf("HUH? I DON'T UNERSTAND THAT ROOM. TRY AGAIN.\n\n");  //isn't a possible room, tell user to try again
				}
				break; //need to go back to the beginning of the first loop
			}
		}
		free(lineEntered); //free memory for user input line
	}
	//record last room, but don't add more steps to account for first room
	roomsVisited[steps] = roomIn.name;
	printf("YOU HAVE FOUND THE END ROOM. CONGRATULATIONS!\n");
	printf("YOU TOOK %d STEPS. YOUR PATH TO VICTORY WAS:\n", steps);
	//loop through rooms, starting at roomsVisited[1] to not show starting room
	int y;
	for (y = 1; y <= steps; y++){
		printf("%s\n", roomsVisited[y]);
	}

	return 0;
}
	
