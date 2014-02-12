#include <stdio.h>

int main(int argc, char **argv)
{
	FILE* f = fopen("/tmp/moo", "w");
	fclose(f);
	return 0;
}
