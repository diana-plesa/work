//Plesa Diana-Ioana - Faculty of Automation and Computing, Polytechnic University of Timisoara, year 2
//This project was created during week 6-11 for Operating Systems class. Containing the files treasure_hub.c,
//treasure_manager.c and calculate_score.c, it allows the user to manage a treasure hunt system in UNIX
//environment.

//Build:
//treasure_manager.c with 'gcc -Wall -o tm treasure_manager.c'
//treasure_hub.c with 'gcc -Wall -o th treasure_hub.c'
//calculate_score.c with 'gcc -Wall -o score calculate_score.c'

//calculate_score.c creates a process for each existing hunt that calculates and 
//outputs the scores of users in that hunt.

#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/wait.h>

#define LOCAL_PATH "."
#define MAX_PATH 256
#define HUNTS_DIR "/hunts"

typedef struct
{
	float x;
	float y;
} GPS;


typedef struct
{
	char treasure_id[11];
	char username[35];
	GPS coord;
	char clue[51];
	int value;
} TREASURE;

typedef struct 
{
    int value;
    char username[35];
} SCORE; //structure to memorise username and its actual score

void concat_path(char* path1, char *path2)
{
	strcat(path1, "/");
	strcat(path1, path2);
}

int open_file_read(char filename[])
{
	int f_out = 0;
	if ((f_out = open(filename, O_RDONLY)) == -1)
	{
		perror("Error opening file");
		exit(-1);
	}

	return f_out;
}

void close_file(int f_out)
{
	if (close(f_out) != 0)
	{
		perror("Error closing file");
		exit(-1);
	}
}

int get_score(int fd, SCORE score[])
{
    //Function that calculates score of each username and returns number of scores.

    int read_out = 0;
    TREASURE tr;
    int nb_scores = 0;
	read_out = read(fd, &tr, sizeof(TREASURE));

    while (read_out == sizeof(TREASURE))
    {
        int found_username = 0; //initialize variable to check if username was already found
        if (nb_scores == 0)
        {
            found_username = 1;
            score[0].value = tr.value;
            strcpy(score[0].username, tr.username);
            nb_scores++;
        }
        else
        {
            for (int i = 0; i < nb_scores; i++)
            {
                if (strcmp(score[i].username, tr.username) == 0)
                {
                    score[i].value = score[i].value + tr.value;
                    found_username = 1; //username was already found in the hunt 
                }
            }

            if (found_username == 0)
            {
                //add another score structure with the username and value of actual score
                strcpy(score[nb_scores].username, tr.username);
                score[nb_scores].value = tr.value;
                nb_scores++;
            }
        }
    	read_out = read(fd, &tr, sizeof(TREASURE));
    }

    return nb_scores;

}

void print_scores(SCORE score[], int nb_scores)
{
    for (int i = 0; i < nb_scores; i++)
    {
        printf("%s: %d points\n", score[i].username, score[i].value);
    }
}

void calc_score(char* huntpath)
{
    SCORE score[50];
    char filepath[100];
    strcpy(filepath, huntpath);
    strcat(filepath, "/treasures.bin");

    int fd = open_file_read(filepath);
    int nb_scores = get_score(fd, score);
    print_scores(score, nb_scores);
    close_file(fd);
}

void parse_hunts(char *dirpath)	
{
    //Function to parse hunts, print a hunt's name and and calculates its users' score.

    strcat(dirpath, HUNTS_DIR);
    DIR *dir = opendir(dirpath);
	if (dir == NULL)
	{
		perror("Could not open directory");
		exit(-1);
	}
	
	struct dirent* entry;
	char filepath[100];

	errno = 0; //set to 0 to distinguish end of stream from an error
	while ((entry = readdir(dir)) != NULL)
	{
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
		continue; //skips . and .. from directory
		if(entry->d_type == DT_DIR)
		{
            strcpy(filepath, dirpath);
		    concat_path(filepath, entry->d_name);
            printf("Hunt: %s\n------------\n", entry->d_name);
            calc_score(filepath);
            printf("\n");
		}
        errno = 0;
	}

	if (errno != 0)
	{
		perror("Error reading directory\n");
		exit(-1);
	}

	if (closedir(dir) != 0)
	{
		perror("Error closing directory\n");
		exit(-1);
	}
}

int main()
{
    char pathname[MAX_PATH];
	strcpy(pathname, LOCAL_PATH);
    parse_hunts(pathname);
    return 0;
}