#include "../../../includes/main.h"
#include "../../../includes/executor.h"

int lbash_cd(char **args)
{
  char cwd[256];
  
  printf ("%s\n%s\n", args[0], args[1]);
  printf("%s\n", getcwd(cwd, sizeof(cwd)));
  if (args[1] == NULL) {
    fprintf(stderr, "lbash: expected argument to \"cd\"\n");
  }
  else 
  {
    if (chdir(args[1]) != 0) 
    {
      perror("lbash");
    }
  }
  printf("%s\n", getcwd(cwd, sizeof(cwd)));
  return 1;
}

// int     main(void)
// {
//     char *cmd[2];
    
//     cmd[0] = "cd";
//     cmd[1] = "../..";
//     lbash_cd(cmd);
//     printf("successful");
//     return (0);
// }