#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 

int exitDecistion(){
    int i;
    i = getchar();
    printf("\n");
    return i;
}

void craeteFile(int numberOfFiles){
    FILE *files[numberOfFiles];
    for(int i = 0; i < numberOfFiles; i++){
        char fileName[20];
        sprintf(fileName, "%f", i);
        files[i] = fopen(fileName, "w");
    }
    fclose(files);
}

void writeFile(){
    char result[3];
    int fileEdit = 0;
    char str[100];
    FILE *outfile;
    do{
        printf("Please enter the file that you want to write(from 1-100): ");
        fileEdit = getchar();
        sprintf(result, "%f", fileEdit); 
        printf("\nPlease enter below what do you want to write: \n");
        gets(str);
        outfile = fopen (result, "w+"); 
        if (outfile == NULL) { 
                fprintf(stderr, "\nError opend file\n"); 
                exit (1); 
        }
        fwrite(str , 1 , sizeof(str) , outfile); 
        fclose(outfile);
        printf("\nWrite more? (0 = YES, 1 = NO)");
    }while(exitDecistion() == 0);
}

void readFile(int numberOfFiles){
    char result[3];
    char read[100];
    FILE *files;
    printf("Reading files from 1 to %d", numberOfFiles);
    for(int i = 0; i < numberOfFiles; i++){
        char fileName[3];
        sprintf(fileName, "%f", i);
        files = fopen(fileName, "w+");
        if(files == NULL){
            fprintf(stderr, "\nError opend file\n"); 
            exit (1); 
        }
        fseek(files, 0, SEEK_SET);
        fread(read, strlen(read)+1, 1, files);
        printf("\nThe file is: %d\n", i);
        printf("The file data is: %s\n", read);
        fclose(files);
    }
}

void rmFile(int numberOfFiles){
    int stat = 1;
    FILE *files;
    char fileName[3];

    for(int i = 0; i < numberOfFiles; i++){
        sprintf(fileName, "%f", i);
        stat = remove(fileName);

        if(stat == 0){
            printf("%s file deleted successfully.\n", fileName);
        }
        else{
            printf("%s file deleted un-successfully.\n", fileName);
            perror("Following error occurred");
        }
    }
}

main() {
    int fileCounters = 0;

    do{
        printf("This is the bench mark for the file system\n");
        printf("Please enter how many files that you want to Create: ");
        fileCounters = getchar();
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