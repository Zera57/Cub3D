#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd;
	int fdsimple;
	char *line;
	int r = -1;

	fd = open("/Users/hapryl/Desktop/Projects/get_next_line/my_git/test", O_RDONLY);
	fdsimple = open("settings.cub", O_RDONLY);
	//обычная проверка
	/*while(get_next_line(fd, &line))
	{
		printf("|%s\\\n----------------------\n", line);
		free(line);
	}
	printf("|%s\\\n----------------------\n", line);
	free(line);*/
	//из консоли
	/*get_next_line(0, &line);
	printf("%s\n", line);*/
	//2 файла
	while(r++ < 10)
	{
		/*if (r % 2 == 1)
			get_next_line(fd, &line);
		if (r % 2 == 0)*/
			get_next_line(fdsimple, &line);
		printf("%d\n|%s\\\n----------------------\n", r % 2, line);
	}
	close(fdsimple);
	close(fd);
	/*while (1)
		;*/
	return 0;
}