#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int exitDecistion(){
    int i;
    scanf("%i", &i);
    printf("\n");
    return i;
}

void createFile(int numberOfFiles){
    FILE *files;
    printf("Number of files: %i", numberOfFiles);
    char fileName[10];
    for(int i = 1; i <= numberOfFiles; ++i){
        itoa(i, fileName, 10);
        files = fopen(fileName, "w");
        fclose(files);
    }
}

void rmFile(int numberOfFiles){
    int stat = 1;
    FILE *files;
    char fileName[10];
    for(int i = 1; i <= numberOfFiles; i++){
        itoa(i, fileName, 10);
        stat = remove(fileName);

        if(stat == 0){
            printf("%s file deleted successfully.\n", fileName);
        }
        else{
            printf("%s file deleted un-successfully.\n", fileName);
            perror("Following error occurred: ");
        }
    }
}

void writeFile(){
    int fileEdit = 0;
    char fileName[10];
    char str[20];
    FILE *outfile;
    do{
        printf("Please enter the file that you want to write(from 0-99): ");
        scanf("%i", &fileEdit);
        itoa(fileEdit, fileName, 10);
        printf("\nPlease enter below what do you want to write: \n");
        scanf("%s", &str);
        outfile = fopen (fileName, "w+");
        if (outfile == NULL) {
                fprintf(stderr, "\nError opend file\n");
                exit (1);
        }
        fprintf(outfile, str);
        fclose(outfile);
        printf("\nWrite more? (0 = YES, 1 = NO)");
    }while(exitDecistion() == 0);
}

void readFile(int numberOfFiles){
    FILE *files;
    char fileName[3];
    printf("Reading files from 1 to %d", numberOfFiles);
    for(int i = 1; i <= numberOfFiles; i++){
        char read[100] = "";
        itoa(i, fileName, 10);
        files = fopen(fileName, "r");
        if(files == NULL){
            fprintf(stderr, "\nError opend file\n");
            exit (1);
        }
        while(!feof(files)){
            fgets(read, 100, files);
            puts(read);
        }

        printf("\nThe file is: %i\n", i);
        printf("The file data is: %s\n", read);
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
            writeFile();
            readFile(fileCounters);
            rmFile(fileCounters);
        }
        printf("Run bench again? (0 = YES, 1 = NO)");
    }while(exitDecistion() == 0);
}
