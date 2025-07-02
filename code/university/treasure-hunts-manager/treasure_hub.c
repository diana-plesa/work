//Plesa Diana-Ioana - Faculty of Automation and Computing, Polytechnic University of Timisoara, year 2
//This project was created during week 6-11 for Operating Systems class. Containing the files treasure_hub.c,
//treasure_manager.c and calculate_score.c, it allows the user to manage a treasure hunt system in UNIX
//environment.

//Build:
//treasure_manager.c with 'gcc -Wall -o tm treasure_manager.c'
//treasure_hub.c with 'gcc -Wall -o th treasure_hub.c'
//calculate_score.c with 'gcc -Wall -o score calculate_score.c'

//treasure_hub.c presents a simple interface to the user, allowing them to start a monitor that executes
//various commands on treasure_manager.c. As per instructions, it contains inter-process communication
//with the usage of pipes, and external tool integration.

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

#define LOCAL_PATH "."
#define PATH_COMMAND_TXT LOCAL_PATH "/command.txt"
#define PATH_COMMAND LOCAL_PATH "/command"
#define EXEC "tm"
#define SCORE_EXEC "score"
#define COMMAND "./tm"
#define SCORE_COMMAND "./score"

volatile int monitor_working = 1; //variable to signal the monitor is working on a task
volatile int monitor_shutting_down = 0; //variable to signal the monitor is currently shutting down
volatile int shutdown = 0; //variable to signal the monitor's shutdown
pid_t pid = -1; //monitor pid

int pipefd[2]; //pipe file descriptors 


void error_exit(char* message)
{
    perror(message);
    exit(-1);
}

int open_file_read(char* filename)
{
    int f_out = 0;
    if ((f_out = open(PATH_COMMAND_TXT, O_RDONLY)) == -1)
    {
        if (errno != ENOENT && errno != 0) //if the file doesn't exist, then monitor keeps sleeping
        {
            error_exit("Error opening file");
        }
    }
    return f_out;
}

void close_file(int f_out)
{
    if (close(f_out) != 0)
    {
        error_exit("Error closing file");
    }
}

int open_file_write(char filename[])
{
    errno = 0;
    int f_out = 0;
    if ((f_out = open(filename, O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) == -1)
    {
        error_exit("Error opening file");
    }
    return f_out;
}

int get_file_size(char* filename)
{
    //This function returns the size of the given file in bytes.

    struct stat statbuf;
    int status = stat(filename, &statbuf); //get status of file

    if (status != 0)
    {
        error_exit("Error stat");
    }

    return statbuf.st_size; //get size of file
}

void write_in_command(char* text)
{
    //This function writes a given text in the command file, used by the monitor to check the command 
    //it needs to do. For safety reasons, the file is simply named "command" while the text is being
    //written, and once it's closed, it's renamed to "command.txt".

    int fd = open_file_write(PATH_COMMAND); 
    if (write(fd, text, strlen(text)) == -1) 
    {
        error_exit("Error writing in file");
    }
    close_file(fd);
    rename(PATH_COMMAND, PATH_COMMAND_TXT); 
}

void get_file_content(char* f_content)
{
    //This function writes the entire content of a file in a given buffer.
    //It requires the file's actual size in bytes in order to read the entire text.

    int fd = open_file_read(PATH_COMMAND_TXT);
    if (fd != -1) //if opening the file is valid
    {
        int file_size = get_file_size(PATH_COMMAND_TXT);
        if (read(fd, f_content, file_size) != file_size) //get the file's size to know how many bytes to read
        {
            error_exit("Error reading file");
        }
        f_content[file_size] = '\0'; //make sure it's properly ended
        close_file(fd);
    }
}

void handler(int signum) 
{
    //This is the monitor signal handler - for SIGTERM (termination) and 
    //SIGUSR1 (signal to execute a command). 

    if (signum == SIGTERM)
    {
        //sleeps 5000000 microseconds, then it's shut down
        usleep(5000000);
        shutdown = 1;
    }
    if (signum == SIGUSR1)
    {
         //signal to read from command.txt the necessary executing information, 
         //and then start a child process which executes the chosen command.

        char f_content[50] = {'\0'};
        char word[3][35] = {'\0'}; 
        get_file_content(f_content); //read all file content
        int i = 0; //incrementing value for command.txt
        char *token = strtok(f_content, " ");
        while(token != NULL)
        {
            strcpy(word[i], token);
            i++;
            token = strtok(NULL , " ");
        } //separate file content in words

        pid_t exec_pid = -1; 
        //start a child for executing command - assume treasure_manager.c and calculate_score.c have already been compiled
        int status = 0;

        if ((exec_pid = fork()) < 0) 
        {
            perror("Error fork");
            exit(1);
        }
        else if (exec_pid == 0)
        {
            if (dup2(pipefd[1], 1) == -1) //redirect stdout to pipe
            {
                perror("Error dup2");
                exit(-1);
            }

            close(pipefd[0]); //close reading end 

            //check the first word of the file content signaling the chosen command - 
            //depending on the chosen command, command.txt can either contain one, up to three words
            //representing the executable file, the hunt_id and the treasure_id (if necessary)

            if (strcmp(word[0], "--list_hunts") == 0) 
            {
                execl(EXEC, COMMAND, word[0], NULL); //-> ./tm --list_hunts

            }
            else if (strcmp(word[0], "--list") == 0) //-> ./tm --list hunt_id
            {
                execl(EXEC, COMMAND, word[0], word[1], NULL);
            }
            else if (strcmp(word[0], "--view") == 0) //-> ./tm --view hunt_id treasure_id
            {
                execl(EXEC, COMMAND, word[0], word[1], word[2], NULL);
            }
            else if (strcmp(word[0], "--calculate_score") == 0)
            {
                execl(SCORE_EXEC, SCORE_COMMAND, NULL); //-> ./score 
            }
        }

        if (waitpid(exec_pid, &status, 0) == -1) //waits for child to finish
        {
            error_exit("Error waitpid");
        }

        if (!WIFEXITED(status))
        {
            error_exit("Child exited abnormally");
        }

        pid_t p_pid = getppid(); //get parent pid
        if (kill(p_pid, SIGUSR2) < 0) //send SIGUSR2 to parent to signal the monitor has finished its task
        {
            error_exit("Error sending SIGUSR2 to parent");
        }

    }
}

int monitor_loop() 
{
    //This function creates an infinite loop for the monitor to run
    //and execute commands, if it's ordered to using the signal SIGUSR1. 
    //If the monitor receives the signal SIGTERM, it will start the 
    //termination process by delaying its shutdown by 5 seconds, followed by 
    //cleanly returning the function.

    close(pipefd[0]); //close reading end
    struct sigaction sa = { 0 }; 

    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGUSR1, &sa, NULL) == -1 || sigaction(SIGTERM, &sa, NULL) == -1)
    {
        error_exit("Error sigaction monitor");
    }

    while(1) 
    {
        if (!shutdown) //if it's not shutdown, keep running
        {
            sleep(1);
        }
        else 
        {
            printf("\nMonitor has shut down\n");
            return 0; //exit the monitor cleanly
        }
    }
}

void create_command_and_send_sig(pid_t pid, char* text) 
{
    //Function to write the appropriate commands in the file and send signal to monitor to read from command.txt
    //once the file is closed.

    write_in_command(text);
    if (kill(pid, SIGUSR1) < 0)
    {
        error_exit("Error sending SIGUSR1 to monitor");
    }
}

void calculate_score(pid_t pid)
{
    create_command_and_send_sig(pid, "--calculate_score");
}

void list_hunts(pid_t pid)
{
    create_command_and_send_sig(pid, "--list_hunts");
}

void read_line(char* str, size_t size)
{
    //Function that reads a line from stdin.

	fgets(str, size, stdin);
	str[strcspn(str, "\n")] = '\0';
}

void list_treasures(pid_t pid)
{
    //Function that gets stdin input for hunt_id, writes the command "--list" and hunt_id in command.txt

    char hunt_id[35] = {'\0'};
    printf("Type hunt_id: ");
    read_line(hunt_id, sizeof(hunt_id));
    char comm[35] = {'\0'};
    strcpy(comm, "--list ");
    strcat(comm, hunt_id);

    create_command_and_send_sig(pid, comm);
}

void view_treasure(pid_t pid)
{
    //Function that gets stdin input for hunt_id and treasure_id, writes the command 
    //"--view", hunt_id and treasure_id in command.txt.

    char hunt_id[35] = {'\0'};
    printf("Type hunt_id: ");
    read_line(hunt_id, sizeof(hunt_id));
    char comm[35] = {'\0'};
    strcpy(comm, "--view ");
    strcat(comm, hunt_id);
    char tr_id[11] = {'\0'};
    printf("Type treasure_id: ");
    read_line(tr_id, sizeof(tr_id));
    strcat(comm, " ");
    strcat(comm, tr_id);

    create_command_and_send_sig(pid, comm);
}

void p_handler(int signum) 
{
    //Parent's signal handler if parent receives SIGUSR2 from monitor, 
    //then the monitor stopped working on a task and parent can continue.

    if (signum == SIGUSR2)
    {
        monitor_working = 0;
    }
}

void wait_for_monitor()
{
    //Function to wait for monitor before restarting menu loop.

    struct sigaction sa2;
    sa2.sa_handler = p_handler;
    sigemptyset(&sa2.sa_mask);
    sa2.sa_flags = 0;

    if (sigaction(SIGUSR2, &sa2, NULL) == -1)
    {
        perror("Error sigaction parent");
    }

    while (monitor_working)
    {
        usleep(1000000); 
    }
}

int get_command()
{
    //Function that returns the value of the given command from user in stdin,
    //which is used in the menu loop.

    char command[50] = {'\0'};
    read_line(command, sizeof(command));
    if (strcmp(command, "start_monitor") == 0)
    {
        return 1;
    }
    else if (strcmp(command, "list_hunts") == 0)
    {
        return 2;
    }
    else if (strcmp(command, "list_treasures") == 0)
    {
        return 3;
    }
    else if (strcmp(command, "view_treasure") == 0)
    {
        return 4;
    }
    else if (strcmp(command, "stop_monitor") == 0)
    {
        return 5;
    }
    else if (strcmp(command, "exit") == 0)
    {
        return 6;
    }
    else if (strcmp(command, "calculate_score") == 0)
    {
        return 7;
    }
    else
    {
        return 8;
    }
}

void read_from_pipe(int pipefd[])
{
    //Function that reads pipe content in a buffer and prints it.

     char buffer[1024] = {'\0'};
     read(pipefd[0], buffer, sizeof(buffer));
     printf("Child output: \n%s\n", buffer);
}

int main()
{
    while (1) //infinite loop for interactive menu
    {

        int monitor_status = 0, waitpid_return = -1;

        printf("\nChoose a command:\n- start_monitor\n- list_hunts\n- list_treasures\n- view_treasure\n- stop_monitor\n- exit\n- calculate_score\n====================================\n");
        int option = 0;
        printf("Type your command: ");
        option = get_command();
        
        if (pid > 0)
        {
            waitpid_return = waitpid(pid, &monitor_status, WNOHANG); //checks if monitor is still running but doesn't wait
            if (waitpid_return == -1)
            {
                perror("Error waitpid");
                exit(-1);
            }
            else if (waitpid_return != 0)
            {
                monitor_shutting_down = 0; //monitor no longer in the process of shutting down because it's shut down
                pid = 0; 
            }
        }
        
        switch(option)
        {
            case 1: //start monitor
            {
                if (monitor_shutting_down)
                {
                    printf("Error - monitor is shutting down, please wait...\n");
                }
                else if (pid > 0) 
                {
                    printf("Monitor is already open\n");
                }
                else 
                {
                    if(pipe(pipefd)<0)
                    {
                        perror("Pipe error\n");
                        exit(-1);
                    }
                    if ((pid = fork()) < 0)
                    {
                        perror("Error fork");
                        exit(1);
                    }
                }
                if (pid == 0) 
                {
                    return monitor_loop(); //monitor ends cleanly
                }               
                break;
            }
            case 2: //list hunts
            {
                if (monitor_shutting_down)
                {
                    printf("Error - monitor is shutting down, please wait...\n");
                }
                else if (pid > 0)
                {
                    monitor_working = 1;
                    list_hunts(pid);
                    wait_for_monitor();

                    read_from_pipe(pipefd);
                }
                else 
                {
                    printf("Monitor is not open!\n");
                }
                break;
            }
            case 3: //list treasures
            {
                if (monitor_shutting_down)
                {
                    printf("Error - monitor is shutting down, please wait...\n");
                }
                else if (pid > 0)
                {
                    monitor_working = 1;
                    list_treasures(pid);  
                    wait_for_monitor();

                    read_from_pipe(pipefd);
                } 
                else 
                {
                    printf("Monitor is not open!\n");
                }
                break;
            }
            case 4: //view treasure
            {
                if (monitor_shutting_down)
                {
                    printf("Error - monitor is shutting down, please wait...\n");
                }
                else if (pid > 0) 
                {
                    monitor_working = 1;
                    view_treasure(pid);
                    wait_for_monitor();

                    read_from_pipe(pipefd);
                }
                else 
                {
                    printf("Monitor is not open!\n");
                }
                break;
            }
            case 5: //stop monitor
            {
                if (monitor_shutting_down)
                {
                    printf("Error - monitor is shutting down, please wait...\n");
                }
                else if (pid > 0) //is in parent program
                {
                    printf("Monitor is shutting down, please wait...\n");
                    monitor_shutting_down = 1;
                    kill(pid, SIGTERM); //sends termination signal to monitor
                }
                else 
                {
                    printf("Monitor is not open!\n");
                }
                break;
            }
            case 6: //exit
            {
                if (monitor_shutting_down)
                {
                    printf("Error - monitor is shutting down, please wait...\n");
                }
                else if (pid > 0)
                {
                    printf("Error - monitor is still open!\n");
                }
                else if (pid <= 0)
                {
                    close(pipefd[0]); //closes pipe
                    return 0;
                }
                break;
            }
            case 7: //calculate_score
            {
                if (monitor_shutting_down)
                {
                    printf("Error - monitor is shutting down, please wait...\n");
                }
                else if (pid > 0)
                {
                    monitor_working = 1;
                    calculate_score(pid);
                    wait_for_monitor();

                    read_from_pipe(pipefd);
                }
                else 
                {
                    printf("Monitor is not open!\n");
                }
                break;
            }
            default:
            {
                printf("Incorrect command\n");
                break;
            }
        }
    }
    return 0;
}