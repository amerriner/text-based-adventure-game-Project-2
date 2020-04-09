/*Both of these files are filled with unoptimized code. I ran out of time, and had to stick with my brute force code. Sorry for the delay it will cause.*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>


//initialize definition for rooms
struct room {
	int id;
	char* name;
	int numCons;
	char* conRooms[6];
};

/********************************************
 * function name: IsGraphFull()
 * Description: this function checks
 * if each room in the array of room
 * structs has at least 3 room connections.
**********************************************/
int IsGraphFull(struct room* myRooms[]) //takes an array of structs
{
	int i;
	for (i = 0; i < 7; i++){
		if (myRooms[i]->numCons < 3){
			return 0;
		}
	}
	return 1;
}

/***********************************************
 * function name: CanAddConnectionFrom()
 * Description: this function checks if the 
 * room passed can be connected to.
***********************************************/
int CanAddConnectionFrom(struct room* a){
	if (a->numCons < 6){ //if the room has less than 6 rooms, return
		return 1;
	}
	//else, return 
	return 0;
}
/************************************************
 * function name: ConnectionAlreadyExists
 * Description: this function checks if the 
 * two rooms passed have already been connected.
*************************************************/
int ConnectionAlreadyExists(struct room* x, struct room* y){
	int n;
	for (n = 0; n < x->numCons; n++){
		if (strcmp(x->conRooms[n], y->name) == 0){
			return 1;
		}
	}
	return 0;
}

/*******************************************
 * function name: ConnectRoom
 * Description: this function connects two
 * rooms together forward and back
*********************************************/
void ConnectRoom(struct room* x, struct room* y){
	int num1 = x->numCons;
	int num2 = y->numCons;
	x->conRooms[num1] = y->name;
	y->conRooms[num2] = x->name;
	x->numCons += 1;
	y->numCons += 1;
}

/************************************************
 * function description: IsSameRoom
 * Description: this function checks if the two
 * rooms passed are actually the same room
************************************************/
int IsSameRoom(struct room* x, struct room* y){
	if (x->id == y->id){//if both ids are the same, same room
		return 1;
	}
	return 0;
}

/*****************************************************
 * function name: AddRaondomConnection
 * Description: this function finds two random rooms
 * from an array of rooms and tries to connect them
******************************************************/
void AddRandomConnection(struct room* myRooms[7]){
	struct room a;
	struct room b;
	int num1;
	while(1){
		num1 = rand()%(7); //find a random room
		a = *myRooms[num1];//dereference the pointer to the room chosen
		if (CanAddConnectionFrom(&a) == 1){ //check if it can be added from
			break;//if yes, quit loop, else keep looking
		}
	}

	int num2;
	do {
		num2 = rand()%(7); //second room to add
		b = *myRooms[num2];
	//while the rooms aren't the same, room 2 can add a connection
	// and the connection doesn't already exist
	}while ((num2 == num1) || (CanAddConnectionFrom(&b) == 0) || (ConnectionAlreadyExists(&a, &b) == 1));
	
	ConnectRoom(&a, &b); //connect the rooms
	
	int num3 = myRooms[num1]->numCons;
	int num4 = myRooms[num2]->numCons;
	
	//connect the map's rooms to the temp room struct info
	myRooms[num1]->conRooms[num3] = a.conRooms[num3];
	myRooms[num2]->conRooms[num4] = b.conRooms[num4];
	myRooms[num1]->numCons = a.numCons;
	myRooms[num2]->numCons = b.numCons;
}

int main() {
	srand((unsigned)time(NULL)); //to randomize numbers
	int myRoomCons[7] = {0};

//make new directory
	int dirID = getpid();
	char idString[8] = "";
	sprintf(idString, "%d", dirID);
	char direct[32] = "";
	strcat(direct, "merrinea.rooms.");
	strcat(direct, idString);//create directory string
	mkdir(direct, 0755);

//make files for each room
	char file1[50] = "";
	strcat(file1, direct);
	strcat(file1, "/room1");	//create string for file 1
	int fileDes1;
	fileDes1 = open(file1, O_RDWR | O_CREAT, 0755);

	char file2[50] = "";
	strcat(file2, direct);
	strcat(file2, "/room2");        //create string for file 2
	int fileDes2;
	fileDes2 = open(file2, O_RDWR | O_CREAT, 0755);
	
	char file3[50] = "";
	strcat(file3, direct);
	strcat(file3, "/room3");       //create string for file 3
	int fileDes3;
	fileDes3 = open(file3, O_RDWR | O_CREAT, 0755);
	
	char file4[50] = "";
	strcat(file4, direct);
	strcat(file4, "/room4");      //create string for file 4
	int fileDes4;
	fileDes4 = open(file4, O_RDWR | O_CREAT, 0755);
	
	char file5[50] = "";
	strcat(file5, direct);
	strcat(file5, "/room5");        //create string for file 5
	int fileDes5;
	fileDes5 = open(file5, O_RDWR | O_CREAT, 0755);
	
	char file6[50] = "";
	strcat(file6, direct);
	strcat(file6, "/room6");          //create string for file 6
	int fileDes6;
	fileDes6 = open(file6, O_RDWR | O_CREAT, 0755);

	char file7[50] = "";
	strcat(file7, direct);
	strcat(file7, "/room7");           //create string for file 7
	int fileDes7;
	fileDes7 = open(file7, O_RDWR | O_CREAT, 0755);
	//hardcode room names
	char rName1[9] = "bedroom";
	char rName2[9] = "yard";
	char rName3[9] = "office";
	char rName4[9] = "kitchen";
	char rName5[9] = "bathroom";
	char rName6[9] = "garage";
	char rName7[9] = "foyer";
	char rName8[9] = "TVRoom";
	char rName9[9] = "nursery";
	char rName10[9] = "library";

	//enter room names into an array of strings
	char* myRoomNames[10];
	myRoomNames[0] = rName1;
	myRoomNames[1] = rName2;
	myRoomNames[2] = rName3;
	myRoomNames[3] = rName4;
	myRoomNames[4] = rName5;
	myRoomNames[5] = rName6;
	myRoomNames[6] = rName7;
	myRoomNames[7] = rName8;
	myRoomNames[8] = rName9;
	myRoomNames[9] = rName10;

	//hardcode room types
	char rType1[11] = "START_ROOM";
	char rType2[11] = "MID_ROOM";
	char rType3[11] = "END_ROOM";

	//put room types into array of strings
	char* myRoomTypes[7];
	myRoomTypes[0] = rType1;
	myRoomTypes[1] = rType2;
	myRoomTypes[2] = rType2;
	myRoomTypes[3] = rType2;
	myRoomTypes[4] = rType2;
	myRoomTypes[5] = rType2;
	myRoomTypes[6] = rType3;

	//initialize map arrays
	int roomNums[7] = {[0 ... 6] = 0};
	struct room* myRooms[7] = {[0 ... 6] = NULL};

	//initialize room structs 
	struct room firstRoom;
	firstRoom.id = 0;
	firstRoom.name = calloc(16, sizeof(char)); //make space for room name
	firstRoom.numCons = 0;
	ssize_t nwrittenN1;  //initialize variables for writing to files
	ssize_t nwrittenT1;
	int rand1 = rand()%(10); //pick a random room name
	strcpy(firstRoom.name, myRoomNames[rand1]); //copy it to room's name
	char rn1[20] = "";
	strcat(rn1, "ROOM NAME: ");
	strcat(rn1, myRoomNames[rand1]);
	strcat(rn1, "\n"); // create string to write to file
	nwrittenN1 = write(fileDes1, rn1, strlen(rn1) * sizeof(char)); //write room name to room's file
	int rtype1 = rand()%(7); //randomize room types
	char rt1[20] = "";
	strcat(rt1, "ROOM TYPE: ");
	strcat(rt1, myRoomTypes[rtype1]);
	strcat(rt1, "\n"); //create string for room type to write to file
	myRooms[0] = &firstRoom; //save to map array
	
	//initialize second room
 	struct room secRoom;
	secRoom.id = 1;
	secRoom.numCons = 0;
	secRoom.name = calloc(16, sizeof(char));
	ssize_t nwrittenN2;
	ssize_t nwrittenT2;
	int rand2 = rand()%(10);
	while (rand2 == rand1){ //make sure the rooms are different
		rand2 = rand()%(10);
	}
	strcpy(secRoom.name, myRoomNames[rand2]);
	char rn2[20] = "";
	strcat(rn2, "ROOM NAME: ");
	strcat(rn2, myRoomNames[rand2]);
	strcat(rn2, "\n");
	nwrittenN2 = write(fileDes2, rn2, strlen(rn2) * sizeof(char));
	int rtype2 = rand()%7;
	while (rtype2 == rtype1){
		rtype2 = rand()%(7); //get unique room type
	}
	char rt2[20] = "";
	strcat(rt2, "ROOM TYPE: ");
	strcat(rt2, myRoomTypes[rtype2]);
	strcat(rt2, "\n");
	myRooms[1] = &secRoom; //save to room array
	
	//initialize third room
	struct room thirdRoom;
	thirdRoom.id = 2;
	thirdRoom.numCons= 0;
	thirdRoom.name = calloc(16, sizeof(char));
	ssize_t nwrittenN3;
	ssize_t nwrittenT3;
	int rand3 = rand()%(10);
	while ((rand3 == rand1) || (rand3 == rand2)){
		rand3 = rand()%(10); //get unique room names
	}	
	strcpy(thirdRoom.name, myRoomNames[rand3]);
	char rn3[20] = "";
	strcat(rn3, "ROOM NAME: ");
	strcat(rn3, myRoomNames[rand3]);
	strcat(rn3, "\n");
	nwrittenN3 = write(fileDes3, rn3, strlen(rn3) * sizeof(char));
	int rtype3 = rand()%(7);
	while ((rtype3 == rtype2) || (rtype3 == rtype1)){
		rtype3 = rand()%(7); //get unique room type
	}
	char rt3[20] = "";
	strcat(rt3, "ROOM TYPE: ");
	strcat(rt3, myRoomTypes[rtype3]);
	strcat(rt3, "\n");
	myRooms[2] = &thirdRoom; //save to room array

	//initialize fourth room
	struct room fourthRoom;
	fourthRoom.id = 3;
	fourthRoom.numCons = 0;
	fourthRoom.name = calloc(16, sizeof(char));
	ssize_t nwrittenN4;
	ssize_t nwrittenT4;
	int rand4 = rand()%(10);
	while ((rand4 == rand1) || (rand4 == rand2) || (rand4 == rand3)){
		rand4 = rand()%(10); //get unique rooms
	}
	strcpy(fourthRoom.name, myRoomNames[rand4]);
	char rn4[20] = "";
	strcat(rn4, "ROOM NAME: ");
	strcat(rn4, myRoomNames[rand4]);
	strcat(rn4, "\n");
	nwrittenN4 = write(fileDes4, rn4, strlen(rn4) * sizeof(char));
	int rtype4 = rand()%(7);
	while ((rtype4 == rtype3) || (rtype4 == rtype2) || (rtype4 == rtype1)){
		rtype4 = rand()%(7); //get unique type
	}
	char rt4[20] = "";
	strcat(rt4, "ROOM TYPE: ");
	strcat(rt4, myRoomTypes[rtype4]);
	strcat(rt4, "\n");
	myRooms[3] = &fourthRoom; //save to room array


	//initialize fifth room
	struct room fifthRoom;
	fifthRoom.id = 4;
	fifthRoom.numCons = 0;
	fifthRoom.name = calloc(16, sizeof(char));
	ssize_t nwrittenN5;
	ssize_t nwrittenT5;
	int rand5 = rand()%(10);
	while ((rand5 == rand4) || (rand5 == rand3) || (rand5 == rand2) || (rand5 == rand1)){
		rand5 = rand()%(10); //get unique rooms
	}
	strcpy(fifthRoom.name, myRoomNames[rand5]);
	char rn5[20] = "";
	strcat(rn5, "ROOM NAME: ");
	strcat(rn5, myRoomNames[rand5]);
	strcat(rn5, "\n");
	nwrittenN5 = write(fileDes5, rn5, strlen(rn5) * sizeof(char));
	int rtype5 = rand()%(7);
	while ((rtype5 == rtype4) || (rtype5 == rtype3) || (rtype5 == rtype2) || (rtype5 == rtype1)){
		rtype5 = rand()%(7); //get unique type
	}
	char rt5[20] = "";
	strcat(rt5, "ROOM TYPE: ");
	strcat(rt5, myRoomTypes[rtype5]);
	strcat(rt5, "\n");
	myRooms[4] = &fifthRoom; //save to rooms array


	//initialize sixth room
	struct room sixthRoom;
	sixthRoom.id = 5;
	sixthRoom.numCons = 0;
	sixthRoom.name = calloc(16, sizeof(char));
	ssize_t nwrittenN6;
	ssize_t nwrittenT6;
	int rand6 = rand()%(10);
	while ((rand6 == rand5) || (rand6 == rand4) || (rand6 == rand3) || (rand6 == rand2) || (rand6 == rand1)){
		rand6 = rand()%(10); //get unique room
	}
	strcpy(sixthRoom.name, myRoomNames[rand6]);
	char rn6[20] = "";
	strcat(rn6, "ROOM NAME: ");
	strcat(rn6, myRoomNames[rand6]);
	strcat(rn6, "\n");
	nwrittenN6 = write(fileDes6, rn6, strlen(rn6) * sizeof(char));
	int rtype6 = rand()%(7);
	while ((rtype6 == rtype5) || (rtype6 == rtype4) || (rtype6 == rtype3) || (rtype6 == rtype2) || (rtype6 == rtype1)){
		rtype6 = rand()%(7); //get unique type
	}
	char rt6[20] = "";
	strcat(rt6, "ROOM TYPE: ");
	strcat(rt6, myRoomTypes[rtype6]);
	strcat(rt6, "\n");
	myRooms[5] = &sixthRoom; //save to map array


	//initialize seventh room
	struct room sevRoom;
	sevRoom.id = 6;
	sevRoom.numCons = 0;
	sevRoom.name = calloc(16, sizeof(char));	
	ssize_t nwrittenN7;
	ssize_t nwrittenT7;
	int rand7 = rand()%(10);
	while ((rand7 == rand6) || (rand7 == rand5) || (rand7 == rand4) || (rand7 == rand3) || (rand7 == rand2) || (rand7 == rand1)){
		rand7 = rand()%(10); //get unique room
	}
	strcpy(sevRoom.name, myRoomNames[rand7]);
	char rn7[20] = "";
	strcat(rn7, "ROOM NAME: ");
	strcat(rn7, myRoomNames[rand7]);
	strcat(rn7, "\n");
	nwrittenN7 = write(fileDes7, rn7, strlen(rn7) * sizeof(char));
	int rtype7 = rand()%(7);
	while ((rtype7 == rtype6) || (rtype7 == rtype5) || (rtype7 == rtype4) || (rtype7 == rtype3) || (rtype7 == rtype2) || (rtype7 == rtype1)){
		rtype7 = rand()%(7); //get unique room type
	}
	char rt7[20] = "";
	strcat(rt7, "ROOM TYPE: ");
	strcat(rt7, myRoomTypes[rtype7]);
	strcat(rt7, "\n");
	myRooms[6] = &sevRoom;//save to map array
	
	//while the graph is not full, keep adding connections
	while (IsGraphFull(myRooms) == 0){
		AddRandomConnection(myRooms);	//pass room array	
	}
	//print connections to files for all rooms
	int i;
	ssize_t nwrittenC1; //room1 connection variable
	for (i = 0; i < myRooms[0]->numCons; i++){
		int num = i;
		num += 1;
		char castNum[3] = "";
		sprintf(castNum, "%d", num);
		char rc1[20] = "";
		strcat(rc1, "CONNECTION ");
		strcat(rc1, castNum);
		strcat(rc1, ": ");
		strcat(rc1, myRooms[0]->conRooms[i]);
		strcat(rc1, "\n");//create formatted connection string
		//write to file
		nwrittenC1 = write(fileDes1, rc1, strlen(rc1) * sizeof(char));
	}
	int j;
	ssize_t nwrittenC2; //connection for room 2
	for ( j = 0; j < myRooms[1]->numCons; j++){ //for all connections 
		int num = j;
		num += 1;
		char castNum2[3] = "";
		sprintf(castNum2, "%d", num);
		char rc2[20] = "";
		strcat(rc2, "CONNECTION ");
		strcat(rc2, castNum2);
		strcat(rc2, ": ");
		strcat(rc2, myRooms[1]->conRooms[j]);
		strcat(rc2, "\n");//create connection string to write
		//write connections to room 2 file
		nwrittenC2 = write(fileDes2, rc2, strlen(rc2) * sizeof(char));
	}

	int k;
	ssize_t nwrittenC3; //connection var for room3
	for (k = 0; k < myRooms[2]->numCons; k++){
		int num = k;
		num += 1;
		char castNum3[3] ="";
		sprintf(castNum3, "%d", num);
		char rc3[20] = "";
		strcat(rc3, "CONNECTION ");
		strcat(rc3, castNum3);
		strcat(rc3, ": ");
		strcat(rc3, myRooms[2]->conRooms[k]);
		strcat(rc3, "\n");// create connection string
		//write string to room 3 file
		nwrittenC3 = write(fileDes3, rc3, strlen(rc3) * sizeof(char));
	}

	int m;
	ssize_t nwrittenC4; //connection var for room 4
	for (m = 0; m < myRooms[3]->numCons; m++){
		int num = m;
		num += 1;
		char castNum4[3] = "";
		sprintf(castNum4, "%d", num);
		char rc4[20] = "";
		strcat(rc4, "CONNECTION ");
		strcat(rc4, castNum4);
		strcat(rc4, ": ");
		strcat(rc4, myRooms[3]->conRooms[m]);
		strcat(rc4, "\n"); //create connection string for room 4
		//write string to room 4 file
		nwrittenC4 = write(fileDes4, rc4, strlen(rc4) * sizeof(char));
	}

	int n;
	ssize_t nwrittenC5; //connection var for room 5
	for (n = 0; n < myRooms[4]->numCons; n++){
		int num = n;
		num += 1;
		char castNum5[3] = "";
		sprintf(castNum5, "%d", num);
		char rc5[20] = "";
		strcat(rc5, "CONNECTION ");
		strcat(rc5, castNum5);
		strcat(rc5, ": ");
		strcat(rc5, myRooms[4]->conRooms[n]);
		strcat(rc5, "\n");//create connection string for room 5
		//write string to room 5 file
		nwrittenC5 = write(fileDes5, rc5, strlen(rc5) * sizeof(char));
	}

	int p;
	ssize_t nwrittenC6; //connection var for room 6
	for (p = 0; p < myRooms[5]->numCons; p++){
		int num = p;
		num += 1;
		char castNum6[3] = "";
		sprintf(castNum6, "%d", num);
		char rc6[20] = "";
		strcat(rc6, "CONNECTION ");
		strcat(rc6, castNum6);
		strcat(rc6, ": ");
		strcat(rc6, myRooms[5]->conRooms[p]);
		strcat(rc6, "\n"); //create connection string for room 6
		//write string to room 6 file
		nwrittenC6 = write(fileDes6, rc6, strlen(rc6) * sizeof(char));
	}


	int q;
	ssize_t nwrittenC7; //connection var for room 7
	for (q = 0; q < myRooms[6]->numCons; q++){
		int num = q;
		num += 1;
		char castNum7[3] = "";
		sprintf(castNum7, "%d", num);
		char rc7[20] = "";
		strcat(rc7, "CONNECTION ");
		strcat(rc7, castNum7);
		strcat(rc7, ": ");
		strcat(rc7, myRooms[6]->conRooms[q]);
		strcat(rc7, "\n"); //create connection string for room 7
		//write string to room 7 file
		nwrittenC7 = write(fileDes7, rc7, strlen(rc7) * sizeof(char));
	}
	

	//write room type to each file
	nwrittenT1 = write(fileDes1, rt1, strlen(rt1) * sizeof(char));
	nwrittenT2 = write(fileDes2, rt2, strlen(rt2) * sizeof(char));
	nwrittenT3 = write(fileDes3, rt3, strlen(rt3) * sizeof(char));
	nwrittenT4 = write(fileDes4, rt4, strlen(rt4) * sizeof(char));
	nwrittenT5 = write(fileDes5, rt5, strlen(rt5) * sizeof(char));
	nwrittenT6 = write(fileDes6, rt6, strlen(rt6) * sizeof(char));
	nwrittenT7 = write(fileDes7, rt7, strlen(rt7) * sizeof(char));

	//close all files
	close(fileDes1);
	close(fileDes2);
	close(fileDes3);
	close(fileDes4);
	close(fileDes5);
	close(fileDes6);
	close(fileDes7);


	//free allocated memory
	free(firstRoom.name);
	free(secRoom.name);
	free(thirdRoom.name);
	free(fourthRoom.name);
	free(fifthRoom.name);
	free(sixthRoom.name);
	free(sevRoom.name);

	return 0;
}
