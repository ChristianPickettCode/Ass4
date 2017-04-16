#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "program.c"
typedef struct {
	
	int manna;
	int gold;
	int occupied;
	
} Room;

void printInput(char string[], int n);
void fixSpaces(char string[], int n);
void getValue(char newArr[], char array[], int index);

void checkCMD(char *cmd, char *URL, int *mannaANDgold, Room room);
void cmdDROP();
void cmdPLAY();
void cmdEXIT();
void cmdREFRESH(char data, char *URL, int *mannaANDgold);

void decode(char *string, int *mannaANDgold, char *URL, Room room);

int mannaANDgold[2];

Room readCSV(char *fileName);

void writeToCSV(char *fileNmae, int manna, int gold, int occupied);



int main() {
	
	//printf("csv: %s\n", readCSV("resources.csv");

	//printf("Content-Type: text/html\n\n");
	//printf("This is Working");	
	char string[200];
	
	int mannaANDgold[2];
	int lengthOfInput = atoi(getenv("CONTENT_LENGTH"));
	
	char *URL = getenv("HTTP_REFERER");

	//printf("ref: %s", URL);

	//char *data = getenv("QUERY_STRING");	
	
	char a[200];
	char b[200];
	
	//sscanf(data, "inventory=%i%%2C%i", mannaANDgold[0], mannaANDgold[1]);
	
	//sscanf(data,"inventory=%&%",&a,&b);	
	
	//printf("<p>data: %s<p>\n", data);

	string[lengthOfInput] = '\0';
	
	fixSpaces(string, lengthOfInput);

	//printInput(string, lengthOfInput);

	Room room = readCSV("resources.csv");
	decode(string, mannaANDgold, URL, room);
	
	//printf("<p>csv: %i </p>", readCSV("resources.csv").gold);
	
	//printf("<p>Room Manna: %i</p>", room.manna);

	//printf("<p>Room Gold: %i</p>", room.gold);

	//printf("<p>Room Occupied: %i</p>", room.occupied);

	return 0;
}

Room readCSV(char *fileName) {
	
	Room room;

	FILE *file = fopen(fileName, "r");

	char buffer[50];
	
	fgets(buffer, sizeof(buffer), file);

	char *tok = strtok(buffer, ",");

	room.manna = atoi(tok);
	
	//printf("<p>Room Manna: %i</p>", room.manna);

	tok = strtok(NULL, ",");

	room.gold = atoi(tok);

	//printf("<p>Room Gold: %i</p>", room.gold);

	tok = strtok(NULL, ",");

	room.occupied = atoi(tok);

	//printf("<p>Room Occupied: %i</p>", room.occupied);


	fclose(file);

	return room;

}

void writeToCSV(char *fileName, int manna, int gold, int occupied) {
	
	FILE *file = fopen(fileName, "w");
	fprintf(file, "%i,%i,%i", manna, gold, occupied);
	fclose(file);

}

void checkCMD(char *cmd, char *URL, int *mannaANDgold, Room room) {
	//printf("command: %s", cmd);
	
	if (strstr(cmd, "DROP") != NULL) {

		cmdDROP(cmd, URL, mannaANDgold, room);
	}
	
	else if (strcmp(cmd, "PLAY") == 0) {
		cmdPLAY();
	}

	else if (strcmp(cmd, "EXIT") == 0) {
		cmdEXIT();
	}
	else if (strcmp(cmd, "REFRESH") == 0) {
		char *data = "non";
		cmdREFRESH(data,URL, mannaANDgold);
	}	
	else {
		printf("NOT A COMMAND");	
	}

}

void decode(char *string, int *mannaANDgold, char *URL, Room room) {

	char temp[100];
	
	int index = 0;
	
	while (string[index] && string[index] != '=') {
		index++;
	}

	index++;
	int n = 0;	
	while (string[index] && string[index] != '%') {
		temp[n] = string[index];
		n++;
		index++;
	}
	
	temp[n] = '\0';
	
	int manna  = atoi(temp);
	//printf("<p>manna: %i</p>\n", manna);
	
	n = 0;
	memset(&temp[0], 0, sizeof(temp));
	index = index + 3;

	while (string[index] && string[index] != '&') {
		temp[n] = string[index];
		index++;
		n++;
	}

	temp[n] = '\0';

	int gold = atoi(temp);
	//printf("<p>gold: %i</p>", gold);
	
	/* After this is for getting command can move somewhere else  */
	memset(&temp[0], 0, sizeof(temp));

	while (string[index] && string[index] != '=') {
		index++;
	}

	index++;
	n = 0;
	while (string[index] && string[index] != '&') {
		temp[n] = string[index];
		n++;
		index++;
	}
	//printf("<p>source: %s</p>", string);

	temp[n] = '\0';
	
	char *CMD = temp;

	//printf("CMD: %s", CMD);

	//memset(&temp[0], 0, sizeof(temp));
	

	//printf("<p>length: %i</p>", strlen(mannaANDgold));

	mannaANDgold[0] = manna;
	mannaANDgold[1] = gold;

	//printf("<p>length: %i</p>", strlen(mannaANDgold));
	checkCMD(CMD, URL, mannaANDgold, room);

}

void cmdDROP(char *cmd, char *URL, int *mannaANDgold, Room room) {
	int i;
	char num[4];
	int n  = 0;
	int val;

	while (*cmd) {
		if (isdigit(*cmd)) {
			val = strtol(cmd, &cmd, 10);
			//printf("%d", val);
		}else {
			cmd++;
		}
	}
	

	mannaANDgold[1] -= val;

 	if (mannaANDgold[1] < 0) {
		mannaANDgold[1] += val;
		cmdREFRESH("none",URL, mannaANDgold);
		//printf("<p>YOU DON'T HAVE ENOUGH GOLD. SORRY</p>");
	} else {
		int j;
		for (j = val; j > 0; j--) {
			if (j % 2 == 0 & j != 0) {
				printf("<p> 1 manna</p>");
				mannaANDgold[0] ++;
			}
		}
		//printf("<h1>New Manna: %i</h1>", mannaANDgold[0]);
		writeToCSV("resources.csv", room.manna, room.gold+val, room.occupied);
		cmdREFRESH("non",URL, mannaANDgold);
		printf("<p>DROPPED %i GOLD</p>", val);
		
	}
	
	//printf("<p>DROPPED %i GOLD</p>", val);
	//printf("<p>New gold is %i</p>", mannaANDgold[1]);
	//decode(string,mannaANDgold, URL);
	//cmdREFRESH(URL, mannaANDgold);
}
void cmdPLAY() {
	printf("<p>PLAY</p>");
}

void cmdEXIT() {
    printf("Content-Type:text/html\n\n");
		printf("<!DOCTYPE html>\n");
		printf("<html>\n");
		printf("<head>\n");
		printf("<title>JIM/CHRIS/BEN</title>\n");
		printf("<link rel='stylesheet' type='text/css' href='styles.css'>\n");
		printf("</head>\n");
		printf("<body bgcolor='white' text='black'>\n");
		printf("<div class='fill-screen'>\n");
		printf("<img class='make-it-fit' src='Dino.jpg' width=\"100%\" height=\"100%\">\n");
		printf("<h3><span>It is a shame your minimal intellectual capacity could not handle this riddle<span class='spacer'></span><br /><span class='spacer'></span> Please come back. We're lonely :(");
		printf("</span></h3>\n");
		printf("</div>\n");
		printf("</body>\n");
		printf("</html>\n");
}


void cmdREFRESH(char *data, char *URL, int *mannaANDgold) {
	//printf("REFRESHING");
	printf("Content-Type:text/html\n\n");	
	printf("<!DOCTYPE html>\n");
	printf("<html>\n");
	printf("<head>\n");
	//printf("<meta http-equiv='refresh' content='0; url=http://cs.mcgill.ca/~cpicke5/room.html'>");
	printf("<title>JIM/CHRIS/BEN</title>\n");
	printf("<link rel='stylesheet' type='text/css' href='styles.css'>\n");
	printf("</head>\n");
	printf("<body bgcolor='white' text='black'>\n");
	printf("<div class='fill-screen'>\n");
	printf("<img class='make-it-fit' src='Dino.jpg' width=\"100%\" height=\"100%\">\n");
	printf("<h3><span>%s</span></h3>", data);
	printf("</div>\n");
	printf("<center><form class='placement'>\n");
	printf("<west><span><a href='http://www.facebook.com' class='button'>West</a></span></west>\n");
	printf("<east><span><a href='http://www.facebook.com' class='button'>East</a></span></east>\n");
	printf("<north><span><a href='http://www.facebook.com' class='button'>North</a></span></north>\n");
	printf("<south><span><a href='http://www.facebook.com' class='button'>South</a></span></south>\n");
	printf("</form></center>\n");
	//printf("\n");
	//printf("\n");
	//printf("\n");


	//printf("</div>\n");
	printf("<center><form action='test.cgi' method='post'>\n");
	printf("<input type='text' name='cmd' required class='search-box'>\n");
	printf("<submits><input type='submit' class='button' value='Submit'></submits>\n");
	printf("</form></center>\n");
	printf("</body>\n");
	printf("</html>\n");

	

	//printf(page, mannaANDgold[0], mannaANDgold[1], mannaANDgold[0], mannaANDgold[1]);
}

void getValue(char newArr[], char array[], int index) {
	
	int i = 0;
	
	while(array[index] != '&' && i < 10) {
		
		newArr[i] = array[index];	
		//printf("new: %s", newArr);
		//printf("arr: %s", array);
		index++;
		i++;
	
	}

}


void fixSpaces(char string[], int n) {
	
	char c;
	int a = 0;

	while ((c = getchar()) != EOF && a < n) {
		
		if (a < 200) {
			
			if (c != '+') string[a] = c;
		 		
				else string[a] = ' ';
		  
			a++;
			
			}
		}
}

void printInput(char string[], int n) {
	
	int i;
	
	for(i = 0; i < n; i++ ) {
		printf("\n");
		printf("%i: %c\n",i,string[i]);
	}

	printf("In loop: | %s | ", string);

}

