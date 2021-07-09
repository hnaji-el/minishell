#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int     check_n(char *args, int *flag)
{
    if (strcmp(args, "-n") == 0)
        *flag = 1;
    return (0);
}

int     lbash_echo(char **cmd)
{
    int flag;
    int i;

    flag = 0;
    if (cmd[1] == NULL)
    {
        write(1, "\n", 1);
        return (1);
    }
    cmd++;
    check_n(*cmd, &flag);
    if (flag == 1)
    {
        cmd++;
        i = 2;
        while (*cmd != NULL)
        {
            ft_putstr_fd(*cmd, STDOUT_FILENO);
            if (*(cmd + 1))
                write(1, " ", 1);
            cmd++;
        }
    }
    else
    {
        while (*cmd != NULL)
        {
            ft_putstr_fd(*cmd, 1);
            cmd++;
        }
        write(1, "\n", 1);
    }
    return (0);
}

// int main()
// {
//     char *cmd[20] = {"echo", "-n", "sdjf", "dfgkdghsdfgs"};
//     lbash_echo(cmd);
//     return 0;
// }