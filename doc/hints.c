SHELL


Shell History

Shell history is archived to ~/.bash_history when the shell is exited, however, history can be easily lost under certain circumstances such when multiple shells are open for the same user or when the shell is improperly shut down.

Shell hisory can be immediately archived at any time by executing:

history -[a]rchive 

To automate shell history archiving, the PROMPT_COMMAND can be helpful:

The PROMPT_COMMAND is a bash [env]ironment variable that is evaluated each time the shell prompt returns. This allows for interesting behavior such as in the following snippet that appends the last shell command to a [hist]ory file located in the user’s home directory.

PROMPT_COMMAND='history 1 >> /${HOME}/hist'
 
Upon returning, the last shell command is automatically appended to an external archive history file.


Misc

: >	//clobber a file to 0 len

1>filename	// redirect stdout to filename
2>filename	/// ... sterr ...
&>filename 	// ... both ...


D>N		// [D]iscriptor,defaults to 1  > file[Name] 		
D>&D		// [D] to another [D]


exec 3<> /tmp/fdtest	// Define a file descriptor.

			// Random access
read -n 4 <&3           // Read only 4 characters.
echo -n . >&3           //  # Write a decimal point there.
exec 3>&-               //  # Close fd 3.
    





File Descriptors








Loopback Filesystem - filesystem within a file.

Create an empty file populated with zero’s from input device /dev/zero:
dd if=/dev/zero of=myfs bs=1024 count=1024K // block size * count (1024 *1024 = 1GB) 
dd if=/dev/zero of=myfile bs=1 count=512M // 1 * 512,000,000 (512M) 

Make a file system: 
mkfs.ext3 myfs // ext3
...or mk2fs myfs // ext2

mount the file:
sudo mount -o loop myfs /mnt

resize2fs myfs [newsize][blocksize] // s=512,k=1024,m=1024K,g=1024m 
// ext2 ext3 or ext4 filesystem support

sudo unmount /myfs/path/to/mountpoint // or use device path /dev/loop0 
e2fsck -f myfs // forced fsck of UNMOUNTED file
resize2fs myfs 2000000k // 1,000,000 * 1,024 = 2GB // s=512 k=1024 m =1,000k g =1,000m



Cross Compiling

QEMU
qemu-system-mipsel -M malta -m 256 -kernel vmlinux -hda rootfs.ext2 -append "root=/dev/hda rw console=ttyS0" -nographic -net nic,model=rtl8139 -net user,net=192.168.1.0/24,host=192.168.1.199 -no-reboot

Linux Admin:

route add default gw x.x.x.x // add default gateway
ifconfig eth0 x.x.x.x // set ip address
ifconfig eth0 netmask x.x.x.x // set network mask
ifconfig eth0 dynamic up // set DHCP
echo “nameserver 8.8.8.8” >> /etc/resov.conf // append nameserver 


Shell
set -e // exit shell on error


Linux Kernel:

make mrproper
make malta_defconfig ARCH=mips
make menuconfig

// use VPATH make feature for multiple buiilds out of tree:
make O=/target/path

cd /target/path
make menuconfig ARCH=mips
make

Buildroot

uClibc


VIM

% - Jumps to matching bracket or brace.
CtrlO / CtrlI -page through files in working directory


Ctrl X +
	Crtl l -line completion
	Ctrl f - filename completion
	Ctlr k - dictionary

e: filename tab completion

set: invlist -Display control characters


:%s/Find/Replace/g - global search and replace (g=multiline??? and %=range is entire file)


Omni completion - aka Intellisense(tm)

Set in vimrc:
filetype plugin on
set ofu=syntaxcomplete#Complete

In insert mode, ^x ^o to activate 




























C Programming:

make filename -(where source file is named filename.c)
CC=/path/to/gcc/compiler/dejure
CFLAGS = -Wall (all warnings) -g (debug) -O3 (full optimize) -Os (small) --march=mycpuonly --mtune=tune2mycpu

Declare a pointer of type char:
char *ptr;
char buffer[255];

Set pointer’s address:
prt = &buffer[0];
buffer[1[=’a’;

// inc pointer
ptr++;

// dereference pointer
putc(*ptr, stdout);

Printing

printf(“Hello, %s\n”, “World.”); // Formatted printing to console.
fprintf(stdout, “Hello, %s\n”, “World.”); // Formatted printing to stream.

putc(mychar, stream); Print char to stream.
puts(mychar*); // Print char* to console. 

There are essentially three uses of the preprocessor--directives, constants, and macros. Directives are commands that tell the preprocessor to skip part of a file, include another file, or define a constant or macro. Directives always begin with a sharp sign (#) and for readability should be placed flush to the left of the page. All other uses of the preprocessor involve processing #define'd constants or macros. Typically, constants and macros are written in ALL CAPS to indicate they are special (as we will see).

Header Files

#include directive tells the preprocessor to grab the text of the file and place it directly into the current file

#define [identifier_name] [value] // preprocessor replaces text identifier_name with value
#define PI_PLUS_ONE (3.14 +1);


Pointers

void alloc(int **); // Declare alloc. Takes address of a pointer
void main(int argc, char *argv[]) {

int *a; // pointer to integer
*a = malloc( 1 * sizeof (*a) ); // Size to 1 integer.
*a = 1;
alloc(&a); // call alloc with a’s address
printf(“a[1] now = %i”, a[1]); 
return 0;
}

void alloc(int ** b){

*b=malloc(2 * sizeof (*b) );
 // *(*b) =1; // De-reference and set value of first location.
*(*b)[1]=2; // Another way to de-reference and set value of 2nd location.

}

Conditional Compilation
They include #if, #elif, #else, #ifdef, and #ifndef. An #if or #if/#elif/#else block or a #ifdef or #ifndef block must be terminated with a closing #endif. 


Avoid including headers multiple times:

#ifndef _FILE_NAME_H_
#define _FILE_NAME_H_

/* code */

#endif // #ifndef _FILE_NAME_H_


Macros

#define MULTI(x,y) x *y

int z = MULTI(3+2, 4+2) ….> 3+2 * 4 +2 =13
int z = MULTI((3+2), (4+2)) ….> (3+2) * (4 +2) =30

Macro tokens to string.
#define PRINT_TOKEN(token) printf(#token " = %s\n", token);
char *token = “mytoken”;
PRINT_TOKEN(token); // token = mytoken

Malloc

double *p;
p = malloc ( n * sizeof *p );


C Pointers and Memory Allocation


The Problem - Passing the pointer's value rather than its address:

int main(int argc, char *argv[]) 
{
	
	int *a; 	// &a = 0xAAAAAA 	- int pointer a's address 
	int b = 10;	// &b = 0xBBBBBB	- int b's address holds the value 10

	
			// a =  0x102938 	- a points to a random address because it's unassigned
			// *a = 10034093	- a points to a random value held a 0x102938

	a=&b					- assign int b's address to int pointer a

			// &a = 0xAAAAAA	- a is still at the same address
			//  a = 0xBBBBBB	- a now points to b's memory address
			// *a = 10		- a now points to the value 10 held at 0xBBBBBB


			// int * a and int * c are the same type...
	f(a);		// This means we are passing int pointer a by value to f(int *) ....

	return 0;

}

	
f(int *c){

			// &c = 0xCCCCCC	- int pointer c's address
			// c  = 0xBBBBBB	- c now points to b's memory address
			// *c = 10		- c now points to the value 10 held at 0xBBBBBB

			// int pointer a's value was bassed to c 
			// both int pointers a and c point to b now

	*c=20; 		// b now = 20.

	c = realloc(c, 1 * sizeof (c) ) // INVALID realloc because block was assigned outside this scope

	c = malloc(1 * sizeof (c) ); // &c is now a new address block eg, 0xcccccc of which a and b are unaware...
	
	// These above methods do not allow the calling function to access new memory

	// we could return c by value so that a would point to c's new block
	// OR
	// we could pass a's address by reference, f(&a) --> f(int **c) so 
	// c's address = 0xAAAAAA
}


Pass by reference


Returning by reference 




Return by value




Git

Show difference between HEAD^ (previous HEAD) and HEAD (current HEAD)

git diff HEAD^ HEAD 

Show difference bewteen 3 heads-ago and now, limited to filename
git diff HEAD~3 HEAD -- filename

Selectively apply (chunks) of working directory filename changes to the staging area (index).
git add --patch filename







sprintf

int  sprintf ( char * buffer, const char * format [ , argument , ...] ); 

Ill explain the following piece by peice:

Buffer:
The buffer is the place to store the resulting string from using the function(notice its also a pointer. so it points to the specific buffer in memory)

Format:
This is the string that contains the text to be printed.
It can also be used to contain format tags

Format flags should follow this:

%[flags][width][.precision][modifiers]type

The types that youll insert are explained here:
Type - Description - Example
c      | Character    | a 
e      |Sci Notation  | 1.42e34
E      |Sci Notation  | 1.42E34
f       |Dec. Float    | 193.53
o      |Signed Octal | 610
d or i |Integer        | 32
s      | String         | sprintf rocks
u      |unsigned Dec| 43525
p      |Address point| A340:0000
x      |Hexadecimal  | 3fa
X      |Hexadecimal  | 3FA
n      |Nothing         |

The diffences between x and X or e and E is that they print capital letters instead of lower case(3fa would be printed with x and 3FA would be printed with X)

The flags, width, .precision, modifiers are completely optional but if youd like to input them heres what they are:

Flags          -          Description
-               | Left align the with given width(right is default)
+              | Forces to preced with positive/negative sign(- is default)
blank         | If the arg is + signed then a blank is inserted before
#              |1. Used with f, e, E makes output contain decimal
               |2. Used with x, X, o value is preced with 0, 0x, 0X


width         -         Description
number       |   Minimum number of characters to be printed   If the value to be printed is shorter than this number the result is padded with blanks. The value is never truncated even if the result is larger. 

0number      | Same as above but filled with 0s instead of blanks. 

*                | The width is not specified in the format string, it is specified by an integer value preceding the argument thas has to be formatted. 
*
*                .precision:
*                for d, i, o, u, x, X types: precision specifies the minimum number of decimal digits to be printed. If the value to be printed is shorter than this number the result is padded with blanks. The value is never truncated even if the result is larger.(if nothing specified default is 1).
*                for e, E, f types: number of digits to be printed after de decimal point. (if nothing specified default is 6).
*                for g, G types : maximum number of significant numbers to be printed.
*                for s type: maximum number of characters to be printed. (default is to print until first null character is encountered).
*                for c type : (no effect).
*
*                Thats the best description i could find
*
*                modifier                 -          Description
*                h                         | Interpreted as a short int
*                l                          | Interpreted as a long int(integers) or double (floats)
*                L                         | Interpreted as a long double(floats)
*
*                The [arguments] command is an elipses so you can put as many types of arguments as you want.
time program args ... returns time to return
