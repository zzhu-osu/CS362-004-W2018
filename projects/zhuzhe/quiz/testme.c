#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // return random ascii character between #32 (Space) and #126 (~)
    char randomChar = rand() % (126 + 1 - 32) + 32;
	return randomChar;
}

char *inputString()
{

	// 1. declare string
	char * randomStr = malloc(sizeof(char) * 6);

	// 2. random ascii characters between 97('a') and 122('z') in the string

	int i;
	for (i=0; i < 5; i++) {
        randomStr[i] = 97 + (int) (26.0 * ( rand() / (RAND_MAX + 1.0) ) );
		//randomStr[i] = rand() % (122 + 1 - 97) + 97;
	}

    /*
    randomStr[0] = 114;
    randomStr[1] = 101;
    randomStr[2] = 115;
    randomStr[3] = 101;
    randomStr[4] = 116;
    */
	randomStr[5] = '\0';

    return randomStr;
}

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
