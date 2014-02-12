#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	creat("/tmp/moo", 0666);
	return 0;
}
