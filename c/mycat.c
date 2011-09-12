#include <stdio.h>
#include <stdlib.h>

// IO throughput with varying performance -
// ioGetc reads/write one char at a time
// ioFgets reads/writes one line at a time.
// ioFread reads and writes buffered chunks using fread().


void ioGetc(char *fname);
void ioFgets(char * fname);
void ioFread(char * fname);
void usage(void);


int main(int argc, char*argv[])	{

	if( argc < 3 ) {
	
		usage();	
	}

	int opt = atoi(argv[2]);
	char * fname = argv[1];
	
	if( 1 > opt | opt  > 3)
		usage();


	if(opt == 1) 
		ioGetc(fname); 

	else if(opt ==2) 

		ioFgets(fname);
	
	else if(opt ==3)

		ioFread(fname);
	return 0;
}

void ioGetc(char * fname){

	// Here we read and write one character at a time.
	
	fprintf(stderr, "Pumping file: %s to stdout using fgetc() --> putc()\n", fname);
	
	FILE *f;
	int i;
	
	f=fopen(fname,"r");
	
	while( (i=fgetc(f)) !=EOF)
		putc(i,stdout);

	fclose(f);
}

void ioFgets(char * fname){

	// The problem here is we dont know the line length, so n or less characters are read.
	// If the last char is not EOL, the the line was truncated and continues.

	fprintf(stderr, "Pumping file: %s to stdout using fgets() --> fputs()\n", fname);
	
	FILE * f;
	int n = 1024;
	char str[n];
	char * ptr = &str[0];
	
	f = fopen(fname, "r");
	
	while ( (fgets(ptr, n, f) !=NULL ) )
		fputs(str, stdout);

	fclose(f);
}


void ioFread(char * fname) {

	// Here we read size*n chunks with the possibility of optimizing the chunk size.

	fprintf(stderr, "Pumping file: %s to stdout using buffered fread() --> fputs())\n", fname);

	FILE *f;
	size_t size =1;
	size_t n=1024;
	int i[size * n];
	void * ptr;
	
	ptr = &i;
	
	f=fopen(fname, "r");

	while( (fread(ptr, size, n, f)) !=0 )
		fputs(ptr, stdout);

	fclose(f);

}


void usage(void) {

		fprintf(stderr, "Usage -- mycat filename [1 | 2 | 3]\n");
		exit(1);


}

