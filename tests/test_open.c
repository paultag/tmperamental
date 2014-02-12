#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
	open("/tmp/moo", O_RDWR | O_CREAT | O_TRUNC, 0666);
	return 0;
}
