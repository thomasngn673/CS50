#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define BLOCKSIZE 512
typedef uint8_t BYTE;

bool isJpgHeader(uint8_t buffer[])
{
    return buffer[0] == 0xff
    && buffer[1] == 0xd8
    && buffer[2] == 0xff
    && (buffer[3] & 0xf0) == 0xe0;
}

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Usage: ./recover image");
        return 1; // quit program
    }
    char* inputFile = argv[1];

    // Open inputFile and read it
    FILE* inputPtr;
    inputPtr = fopen(inputFile, "r"); 
    
    // Check if input pointer/file is valid
    if(inputPtr==NULL) 
    {
        printf("Unable to open file: %s\n", inputFile);
        return 1;
    }

    char filename[8]; // xxx.jpg'\0' has 8 characters
    FILE* outputPtr = NULL; // set ouput pointer to NULL
    uint8_t buffer[BLOCKSIZE]; // buffer reads into the output file, buffer is the "buffer" between the input and output file
    int jpgCounter = 0; // create jpgCounter for number of jpg images in the input file
    
    // While loop: run until file can be read no more, or until end of file is reached
    // feof = file end of file
    // fread(address where data read is assigned, size of buffer, bytes read per cycle, pointer for file being read from)
    // read from inputPtr to buffer file
    while(fread(buffer, sizeof(uint8_t), BLOCKSIZE, inputPtr)||(!feof(inputPtr))) 
    {
        // if text read to buffer is a jpg header ...
        // if jpg file output does not exist yet, create/write new jpg file ouput
        if(isJpgHeader(buffer))
        {
            // outputPtr can not be opened if its already being used, must be closed to then be fopen'ed
            if(outputPtr!=NULL)
            {
                fclose(outputPtr);
            }
            // sprintf = string file print
            // ... print outputPtr and then store to filename 
            sprintf(filename, "%03i.jpg", jpgCounter);
            // ensures 3 digit %i 
            outputPtr = fopen(filename, "w");
            jpgCounter++;
        }
        // if jpg file output already exists, write to it
        if(outputPtr != NULL)
        {
            // fwrite(file reading from, size of file reading from, 1 byte per cycle, pointer that is fopen'ed)
            // write from buffer to ouputPtr
            fwrite(buffer, sizeof(buffer), 1, outputPtr);
        }
    }
    
    if(inputPtr == NULL)
    {
        fclose(inputPtr);
    }
    
    if(outputPtr == NULL)
    {
        fclose(outputPtr);
    }
    return 0;
}

// Steps
// 1. Declare input pointer
// 2. Open target file to input pointer
// 3. Check validity of input pointer
// 4. Declare output pointer (as NULL if there is not initial value)
// 5. Declare buffer
// 6. Read data from input pointer to buffer
// 7. Declare file name that we want to write to
// 8. Open file name to output pointer
// 9. Write from buffer to output pointer
// 10. Close input and output pointer