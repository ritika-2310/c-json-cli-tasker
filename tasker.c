#include<stdio.h>
#include<stdlib.h>
#include"cJSON.h"
#include<string.h>
#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define YELLOW  "\033[0;33m"
#define PINK "\033[95m"
#define BRIGHT_BLUE "\033[1;34m"
#define RESET   "\033[0m"
/*
RESET : It changes the terminal's text color (in this case, to bright red), and that color stays active until you reset it.
So if you don’t reset, everything printed afterward will stay red — which can mess up the output.
*/
void print_intro_message() {
    printf(YELLOW"\n=====================================\n"RESET);
    printf(YELLOW"   Welcome to the Task Runner Tool!  \n"RESET);
    printf(YELLOW"=====================================\n"RESET);

    printf(YELLOW"\nHey there! Here's how to use this tool:\n"RESET);

    printf(YELLOW"\nTo run a task: ./tasker_runner <task_name>\n"RESET);
    printf(YELLOW"    Example: ./tasker_runner build\n"RESET);

    printf(YELLOW"\nIf you're unsure, just type: ./tasker_runner --help    to get help\n"RESET);
    printf(YELLOW"    It'll show all available tasks and how things work.\n"RESET);

    printf(YELLOW"\n Make sure your task.json file is ready!\n"RESET);
    printf(YELLOW"    (It should include task name, steps, and optionally dependencies)\n"RESET);

    printf(YELLOW"\nThis tool is meant to run tasks written in JSON format.\n"RESET);

    printf(YELLOW"\n=====================================\n"RESET);
    printf(YELLOW"-----------------------------------------------------------\n"RESET);
}

cJSON *read_file(){ //cause returns root which is cJSON
    FILE *fptr = fopen("task.json","rb"); //opening file in binary mode cause text mode caused error as it skipped sequence characters
    if(!fptr){
        fprintf(stderr, RED"Error: task.json not found in current directory.\n"RESET);
        fprintf(stderr, RED"Make sure your file is named 'task.json' and placed properly.\n"RESET);
        return NULL;
    }
    printf(GREEN"[log] file opened in fptr pointer succesfully!\n"RESET);
    fseek(fptr,0,SEEK_END);
    long length = ftell(fptr);
    if(length<=0){
        printf(RED"file is empty or ftell() failed\n"RESET);
        fclose(fptr);
        return NULL;
    }
    printf(GREEN"[log] file is not empty and ftell() function is working!\n"RESET);
    rewind(fptr); 
    char *data = malloc(length+1);
    if(!data){
        printf(RED"Memory allocation failed!\n"RESET);
        fclose(fptr);
        return NULL;
    }
    printf(GREEN"[log] Memory allocation successfull!\n"RESET);
    size_t bytes_read = fread(data,1,length,fptr); //size_t returns size of fread reading
    if(length != bytes_read){
        printf(RED"fread function is not working, expected bytes %ld to read, but read only %zu bytes\n"RESET,length,bytes_read); //ld for long length and zu for size_t
        free(data);
        fclose(fptr);
        return NULL;
    }
    data[length] = '\0';
    printf(GREEN"[log] whole file is read successfully!\n"RESET);
    fclose(fptr);
    cJSON *root = cJSON_Parse(data);
    if (!root) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr) {
            fprintf(stderr,RED"JSON parse error before: %s\n"RESET, error_ptr); //stderr is standard error
        }
        else{
            fprintf(stderr,RED"unknown JSON parse error\n"RESET); //stderr is standard error
        }
        free(data);
        return NULL;
    }
    printf(GREEN"[log] Parsing is successfully done!\n"RESET);
    free(data);
    return root;
}
int help(){
    printf(BRIGHT_BLUE"\nHelp Menu\n"RESET);
    printf(BRIGHT_BLUE" Usage : ./tasker_runner <tasker_name>\n"RESET);
    printf(BRIGHT_BLUE"example : ./tasker_runner run\n"RESET);
    printf(BRIGHT_BLUE"there are other options like : \n"RESET);
    printf(BRIGHT_BLUE"--help  shows this help message\n"RESET);
    printf(BRIGHT_BLUE"--version OR --about shows info about the tool's creator\n"RESET);
    printf(BRIGHT_BLUE"--list  shows all the available tasks in task.json files\n"RESET);
    printf(BRIGHT_BLUE"task.json file should be in the directory\n"RESET);
    printf(GREEN"[log] help function successfully!\n"RESET);
    return 0;
}
int list(cJSON *all_data){
    cJSON *data;
    cJSON_ArrayForEach(data,all_data){
        if(!data){
            return 1; //data might be NULL
        }
        char *task_name = data->string;
        printf(PINK"Task :       %s\n"RESET,task_name);
        //get commands
        cJSON *task_cmd = cJSON_GetObjectItemCaseSensitive(data,"cmd");
        if(task_cmd && cJSON_IsString(task_cmd)){
            printf(PINK"Command :      %s\n"RESET,task_cmd->valuestring);
        }
        //get dependencies
        cJSON *task_dep= cJSON_GetObjectItemCaseSensitive(data,"deps");
        if(task_dep && cJSON_IsArray(task_dep)){
            printf(PINK"Dependencies : "RESET);
            cJSON *dep;
            int dep_count = 0;
            cJSON_ArrayForEach(dep,task_dep){
                printf(PINK"%s\n"RESET,dep->valuestring);
                dep_count++;
            }
            if(dep_count==0){
                printf(PINK"None\n"RESET);
            }
        }
    }
    printf(GREEN"[log] list function successfully!\n"RESET);
    return 0;
}
void task_run(cJSON *tasks,char *task_name){
    //get task from json
    cJSON *task = cJSON_GetObjectItemCaseSensitive(tasks,task_name);
    if(!task){
        printf(RED"didn't find %s task\n"RESET,task_name);
        return;
    }
    printf(GREEN"[log] %s found!\n"RESET,task_name);
    //get dependencies from task 
    cJSON *deps = cJSON_GetObjectItemCaseSensitive(task,"deps");
    cJSON *dep;
    if(deps && cJSON_IsArray(deps)){
        cJSON_ArrayForEach(dep,deps){
            if (!cJSON_GetObjectItemCaseSensitive(tasks, dep->valuestring)) {
                fprintf(stderr, RED"Missing dependency task: %s\n"RESET, dep->valuestring);
                return;
            }
            if (!cJSON_IsString(dep)) {
                fprintf(stderr, RED"Error: 'dependency' should be a string for task '%s'\n"RESET, task_name);
                return;
            }
            task_run(tasks,dep->valuestring);
        }
        printf(GREEN"[log] dependency found!\n"RESET);
    }
    //get command from task
    cJSON *cmd = cJSON_GetObjectItemCaseSensitive(task,"cmd");
    if (!cJSON_IsString(cmd)) {
        fprintf(stderr, RED"Error: 'cmd' should be a string for task '%s'\n"RESET, task_name);
        return;
    }
    if(cmd && cJSON_IsString(cmd)){
        printf(BRIGHT_BLUE"Running : %s\n"RESET,cmd->valuestring);
        printf(GREEN"[log] command found!\n"RESET);
        int ret = system(cmd->valuestring);
        if (ret != 0) {
            fprintf(stderr, RED"Command '%s' failed with exit code %d\n"RESET,cmd->valuestring,ret);
        }
        printf(GREEN"\n[log] command ran successfully!\n"RESET);
    }
    printf(GREEN"[log] %s ran successfully!\n"RESET,task_name);
}
int main(int argc,char *argv[]){
    if(argc<2){
        print_intro_message();
        printf(PINK"\nHint: try '--help' to learn how to use this tool.\n\n"RESET);
        printf(PINK"usage : %s\n"RESET,argv[0]);
        return 1;
    }
    char *task_name = argv[1];
    //about me 
    if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "--about") == 0) {
        printf(PINK"Task Runner v1.0\nbuilt for Developers by Ritika Bhasin\n\n"RESET);
        return 0;
    }
    //help flag
    if(strcmp(argv[1],"--help")==0){
        help();
        return 0;
    }
    //list flag
    if(strcmp(argv[1],"--list")==0){
        cJSON *all_data = read_file();
        if(!all_data){
            return 1; //all_data might be NULL
        }
        list(all_data);
        cJSON_Delete(all_data);
        return 0;
    }
    //file reading 
    cJSON *root = read_file();
    if(!root){
        return 1; //to pass in function check root is NULL or not
    }
    printf(GREEN"[log] file read successfully!\n"RESET);
    task_run(root,task_name);
    cJSON_Delete(root);
    printf(GREEN"[log] all data deleted successfully!\n"RESET);
    return 0;
}
/*
how to compile 
when u did an edit or modification in the code first open the terminal and write to recompile things
gcc tasker.c cJSON.c -o tasker_runner.exe

then when u did recompilation then write to onn the program 
./tasker_runner run
(this run is the name of the task u want to perform)
*/