/*
	MIDI 2 WS MML conversion
	win32 application
	beatsgo (c) 2016
	note: the intent of this tool is to generate clean WonderSwan MML files
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <errno.h>
#include <string.h>

int systemPause()
{
	#if defined(_WIN64) || defined(_WIN32)
		system("pause");
	#elif defined(__CYGWIN) || defined(__unix__) || defined(__linux)
		system("read -n1 -r key");
	#endif
	return 0;
}

char *remove_ext(char* mystr, char dot, char sep)
{
	char *retstr, *lastdot, *lastsep;
	
	if(mystr == NULL)
		return NULL;
	if((retstr = malloc (strlen(mystr) + 1 )) == NULL)
		return NULL;
	
	strcpy (retstr, mystr);
	lastdot = strrchr(retstr, dot);
	lastsep = (sep == 0) ? NULL : strchr (retstr, sep);
	
	if (lastdot != NULL) {
        // and it's before the extenstion separator.

        if (lastsep != NULL) {
            if (lastsep < lastdot) {
                // then remove it.

                *lastdot = '\0';
            }
        } else {
            // Has extension separator with no path separator.

            *lastdot = '\0';
        }
    }

    // Return the modified string.

    return retstr;
}

int main(int argc, char *argv[])
{
	
	char songName[] = "\0";
	unsigned int format, trackRes, numTracks, beatsPerMin;
	
	//pointer variables
	int fileLength;
	char buffer[]="\0";
	char *buffPtr, *midiDump, *mmlOutput, *hexDumpOutput = "midi_hexdump.txt";
	char *curPtr, *parPtr, *endPtr; //Parsing pointers
	FILE *inputPtr, *outputPtr;
	
	/*
		Step 1 | Read and verify MIDI file
	*/
	printf("Step 1: read and verify %s is a MIDI file\n", argv[1]);
	//Read file and check if it exist/valid 
	inputPtr = fopen(argv[1],"r");
	if(inputPtr == NULL)
	{
		printf("ERROR! NOT A VALID FILE\nPress a key to exit");
		fflush(stdout);
		systemPause();
		exit(EXIT_FAILURE);
	}
	printf("...\n");
	
	//read file
	fseek(inputPtr, 0, SEEK_END); //goes to end of file
	fileLength = ftell(inputPtr); //"tells" where the pointer is at (at the end of the file)
	rewind(inputPtr); //goes back to the beginning of the file
	midiDump = (char *)calloc((fileLength+1), sizeof(char)); //allocate in memory size of the file + 1
	fread(midiDump, fileLength, 1, inputPtr);
	fclose(inputPtr);
	free(inputPtr);
	printf("...\n");
	
	//write hex dump to text file for logging purposes
	outputPtr = fopen(hexDumpOutput, "w+b"); //create/update save file in binary mode
	for(int idx = 0; idx < fileLength; idx++)
	{
		fwrite(&midiDump[idx], 1, 1, outputPtr);
	}
	fclose(outputPtr);
	free(outputPtr);
	printf("...\n\n");
	
	
	/*//==================
		Read Header data
	*///==================
	printf("%\n", midiDump[0]);
	if(midiDump[0] == 0x4D)
		printf("true!\n\n\n");
	if(midiDump[0] != 0x4D || midiDump[1] != 0x54 || midiDump[2] != 0x68 || midiDump[3] != 0x64 ||
	midiDump[4] != 0x00 || midiDump[5] != 0x00 || midiDump[6] != 0x00 || midiDump[7] != 0x06 )
	{
		printf("ERROR! Not a MIDI file!");
		fflush(stdout);
		systemPause();
		exit(EXIT_FAILURE);
	}	
	
	//Copy filename to local array, remove extension
	strcpy(buffer, argv[1]);
	buffPtr = remove_ext(buffer, '.', 0);
	memcpy(songName, buffPtr, strlen(buffPtr));
	printf("Song Name: %s\n", songName);
	
	//Read format
	format = (unsigned int)(midiDump[9]);
	switch(format)
	{
		case 0:
			printf("Format: Single Track\n");
			break;
		case 1:
			printf("Format: Multi-Track, Synchronous\n");
			break;
		case 2:
			printf("Format: Multi-Track, Asynchronous\n");
			break;
		default:
			printf("ERROR! Not a MIDI file!");
			fflush(stdout);
			systemPause();
			exit(EXIT_FAILURE);
			break;
	}
	
	//Read number of tracks
	numTracks = (unsigned int)(midiDump[11]);
	printf("Number of Tracks: %u\n", numTracks);
	
	//Read track resolution
	trackRes = (unsigned int)(midiDump[13]);
	printf("Track Resolution: %u\n\n\n", trackRes);
	
	/*
		TODO: Step 2 | Parse Data For Format 0,1,201
	*/
	
	printf("Step 2: Parse Data\n");
	
	/*
		Format 1
	*/
	
	//Move pointer to MTrk entry 
	midiDump++;
	endPtr = &midiDump[fileLength-1];
	
	printf("Mem Addr:%p%20sHex Value:%2X\n", midiDump, "", midiDump[0]);
	printf("Mem Addr:%p%20sHex Value:%2X\n", &midiDump[fileLength-1], "", midiDump[fileLength-1]);
	printf("Mem Addr:%p%20sHex Value:%2X\n", endPtr, "", endPtr[0]);
	while(midiDump[0] != 0x4D && midiDump != endPtr)
	{
		midiDump++;
		printf("midiDump Mem Addr:%p%20sendPtr MemAddr:%p\n", midiDump, "", endPtr);
	}
	
	
	/*
		TODO: Step 3 | Write Parsed Data to MML file
	*/
	
	
	printf("DONE! Press a key to exit");
	fflush(stdout);
	systemPause();
	
	
	return 0;
	
}
