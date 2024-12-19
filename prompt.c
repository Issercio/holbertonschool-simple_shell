#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "simple_shell.h"

int main(void)
{
char *line = NULL;
size_t len = 0;
ssize_t nread;
while (1)
{
printf("$ ");
nread = getline(&line, &len, stdin);
if (nread == -1)
{
printf("\nEnd of input.\n");
break;
}
if (nread > 1)
{
printf("You entered: %s", line);
}
}
free(line);
return (0);
}