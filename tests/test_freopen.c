#include <stdio.h>

int main(int argc, char **argv)
{
	FILE* f = freopen("/tmp/moo", "w", stdout);
	fclose(f);
	return 0;
}
