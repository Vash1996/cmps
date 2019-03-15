#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int exitDecistion(){
    int i;
    scanf("%i", &i);
    printf("\n");
    return i;
}

void createFile(int numberOfFiles){
    FILE *files;
    printf("Number of files: %i", numberOfFiles);
    char *fileName[10];

    for(int i = 1; i <= numberOfFiles; i++){
        char filePath[] = "//home//vash//cmps//asg4//testfile//";
        sprintf(fileName, "%d", i);
        strcat(filePath, fileName);
        files = fopen(filePath, "w");
        fclose(files);
    }
}

void rmFile(int numberOfFiles){
    int stat = 1;
    FILE *files;
    char *fileName[10];
    char str[20];
    scanf("%s", &str);
    //char *filePath[50] = "path";
    for(int i = 1; i <= numberOfFiles; i++){
        char filePath[] = "//home//vash//cmps//asg4//testfile//";
        sprintf(fileName, "%d", i);
        //strcat(filePath, fileName);
        strcat(filePath, fileName);
        stat = remove(filePath);
        if(stat == 0){
            printf("%s file deleted successfully.\n", fileName);
        }
        else{
            printf("%s file deleted un-successfully.\n", fileName);
            perror("Following error occurred: ");
        }
    }
}

void writeFile(int numberOfFiles){
    int fileEdit = 0;
    char *fileName[3];
    char str[10001];
    int random;
    time_t t;
    FILE *outfile;
    srand((unsigned)time(&t));

    printf("Ramdom generating file size... \n");

    for(int i = 1; i <= numberOfFiles; i++){    //from file 1-numberOfFiles start to add size to files
        char filePath[] = "//home//vash//cmps//asg4//testfile//";
        random = rand()%10;
        if(random <= 5){ //2kb
            for(int n = 0; n < 2000; n++){
                str[n] = 'a';
            }
        }
        else if (random > 8){  //10kb
            for(int n = 0; n < 10000; n++){
                str[n] = 'a';
            }
        }
        else{ //6kb
            for(int n = 0; n < 6000; n++){
                str[n] = 'a';
            }
        }
        sprintf(fileName, "%d", i);
        strcat(filePath, fileName);

        outfile = fopen (filePath, "w+");
        if (outfile == NULL) {
                fprintf(stderr, "\nError opend file\n");
                exit (1);
        }
        fprintf(outfile, str);
        fclose(outfile);
        memset(str, 0, sizeof str);
    }
}

void readFile(int numberOfFiles){
    FILE *files;
    char *fileName[3];
    struct stat filestat;
    long int res;
    long int size;

    printf("Reading files from 1 to %d", numberOfFiles);
    for(int i = 1; i <= numberOfFiles; i++){
        char filePath[] = "//home//vash//cmps//asg4//testfile//";
        printf("File Name: %i\n", i);
        sprintf(fileName, "%d", i);

        strcat(filePath, fileName);
        stat(filePath,&filestat);

        printf("file path %s\n",filePath);

        printf("    File access time %s", ctime(&filestat.st_atime));
        printf("    File modify time %s", ctime(&filestat.st_mtime));
        printf("    File changed time %s", ctime(&filestat.st_ctime));
        filePath[strlen(filePath) - 1] = '\0';

        files = fopen(filePath, "r");


        if(files == NULL){
            fprintf(stderr, "\nError opend file\n");
            exit (1);
        }
        fseek(files, 0L, SEEK_END);
        res = ftell(files);
        if (res != -1) {
            res = res / 1000;
            printf("    Size of the file is %ld KB \n", res);
        }
        else{
            printf("        Failed to read file size \n");
        }
        fclose(files);
    }
}

int main() {
    int fileCounters = 0;

    do{
        printf("This is the bench mark for the file system\n");
        printf("Please enter how many files that you want to Create: ");
        scanf("%i", &fileCounters);
        printf("Number of files: %i", fileCounters);
        if(fileCounters == 0){
            printf("The numbers of file can not be 0!\n");
        }
        else{
            createFile(fileCounters);
            printf("\nfile Created!\n");
            writeFile(fileCounters);
            readFile(fileCounters);
            rmFile(fileCounters);
        }
        printf("Run bench again? (0 = YES, 1 = NO)");
    }while(exitDecistion() == 0);
}



