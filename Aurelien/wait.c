#include "main.h"
#include <sys/wait.h>

/* Fonction pour attendre la fin des processus fils*/
void wait_for_process(pid_t pid) {
    int status;
    waitpid(pid, &status, 0);
    if (WIFEXITED(status)) {
        printf("Processus terminé avec le code de sortie %d\n", WEXITSTATUS(status));
    }
}