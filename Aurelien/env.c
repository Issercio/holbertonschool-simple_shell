#include <stdio.h>
#include "main.h"
#include <stddef.h>

void display_env(void)

{
extern char **environ;
int i = 0;

while (environ[i] != NULL)
{
printf("%s\n", environ[i]);
i++;
}

}
