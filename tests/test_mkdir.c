#include <sys/stat.h>

int main(int argc, char **argv)
{
	mkdir("/tmp/moo", 0777);
	return 0;
}
