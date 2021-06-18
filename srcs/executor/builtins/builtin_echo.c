#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int     check_n(char *args, int *flag)
{
    if (strcmp(args, "-n") == 0)
        *flag = 1;
    return (0);
}

int     lbash_echo(char **args)
{
    int flag;
    int i;

    flag = 0;
    if (args[1] == NULL)
    {
        write(1, "\n", 1);
        return (1);
    }
    args++;
    check_n(*args, &flag);
    if (flag == 1)
    {
        args++;
        i = 2;
        while (*args != NULL)
        {
            ft_putstr_fd(*args, STDOUT_FILENO);
            if (*(args + 1))
                write(1, " ", 1);
            args++;
        }
    }
    else
    {
        while (*args != NULL)
        {
            ft_putstr_fd(*args, 1);
            args++;
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