#include <stdio.h>
#include <stdlib.h>

void print_binary_char(char c) {/*the negative numbers are represented usin 2's complement*/
	int i;
    for (int i = 7; i >= 0; i--)
    {
       if(c&(1<<i)) printf("1");
       else printf("0");
    }
   printf("\n");
}
/*
 *
 */
void question1() {
	printf("printing from -16 to 15 in binary\n");
	char c;
	for(c=-16; c<16; c++) {
		printf("%d\t", c);
		print_binary_char(c);
		printf("\n");
	}
}
union Hexa{
float a;
int b;
}x;
void print_binary_float(float f) {
x.a=f;
printf("%x",x.b);
}
/*
 *
 */
void question2() {                    /*      IEEE's double precision as the computer runs '64 bits'*//*little Endian*/
	float numbers[] = {0.0f, 1.0f, 2.0f, 0.1f};
	int count = sizeof(numbers) / sizeof(numbers[0]);
	int i;

	for(i=0; i<count; i++) {
		printf("%.2f is represented as: ", numbers[i]);
		print_binary_float(numbers[i]);
		printf("\n");
	}
}
union Q3{
int i;
float f;
}y;
float get_smallest_positive_float() {

	y.i=1<<23;             /* to get the bits'0 00000001 00000000000000000000000' which is the least floating number "normalized"*/
 return y.f;

}
union Q3_{
double d;
int l;
}z;
double get_double_epsilon() {
    z.d=1;
    z.l++;
    return  z.d-1;

}
/*
 *
 */
int get_longdouble_exponent_bias() {
	/*PUT YOUR CODE HERE*/
	return 0;
}
/*
 *
 */
void question3() {
	printf("The smallest positive 'float' is: %e\n", get_smallest_positive_float());
	printf("Epsilon for 'double' is: %le\n", get_double_epsilon());
	printf("'long double' has a bias of %d for its exponent\n", get_longdouble_exponent_bias());

}
/*
 *
 */
int get_command() {
	int choice;
	printf("\n\n");
	printf("*********************************************\n");
	printf("* Enter 1 for Signed Integer Representation *\n");
	printf("* Enter 2 for Floating-Point Endianness     *\n");
	printf("* Enter 3 for Floating-Point Representation *\n");
	printf("* Enter anything else to exit               *\n");
	printf("*********************************************\n");
	printf("Your choice: ");
	scanf("%d", &choice);
	fseek(stdin, 0, SEEK_END);
	printf("\n");
	return choice;
}
/*
 *
 */
main() {
	int choice;
	while(1) {
		switch(get_command()) {
			case 1:
				question1();
				break;
			case 2:
				question2();
				break;
			case 3:
				question3();
				break;
			default:
				printf("Invalid Choice. Exiting...\n");
				exit(1);
		}
	}
	return 0;
}
