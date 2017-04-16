#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void play(char *data) {
    int activator = 0;
		    
		if(strstr(data, "Larry") || strstr(data, "larry")) activator = 1;
		else if(strstr(data, "QUIT") || strstr(data, "Quit")|| strstr(data, "quit")) activator = 3;
		else activator = 2;

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
		printf("<h3><span> Larry's Father had five kids. Their names were: Ten, Twenty, Thirty, and Forty. <span class='spacer'></span><br /><span class='spacer'></span> What was is fifth kids name? </span></h3>\n");
																																    
		if(activator == 1) printf("<h2><span> Congratulations! <span class='spacer'></span><br /><span class='spacer'></span> You answered correctly. </span></h2>\n");
		if(activator == 2) printf("<h2><span> Incorrect. <span class='spacer'></span><br /><span class='spacer'></span> Please Try Again. </span></h2>\n");

		printf("</div>\n");

		printf("<center><form action='program.cgi' method='post'>\n");
		printf("<input type='text' name='cmd' required class='search-box'>\n");
		printf("<submits><input type='submit' class='button' value='Submit'></submits>\n");
		printf("</form></center>\n");

		printf("</body>\n");
		printf("</html>\n");
																																																				    
		if(activator == 1 || activator == 3) 
			printf("<meta http-equiv='refresh' content='5; url=http://cs.mcgill.ca/~cpicke5/room.html'>");
}

