# minishell

42 project, recoding our own little bash. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in functions.

<img width="794" alt="Screen Shot 2022-09-24 at 12 08 04 AM" src="https://user-images.githubusercontent.com/57335519/192068092-72f7e188-908b-47a6-9b43-dc74c441ed47.png">

## How to use it

First you need to install readline by using ``` brew install -k readline ```

Using ```make``` will create the ```minishell``` executable.

## Available options

Minishell runs executables from an absolute, relative or environment PATH ```(/bin/ls or ls)```, including arguments or options. ```'``` and ```"``` work the same as bash, except for multiline commands.

You can separate commands with ```;```, as well as use redirections ```>``` ```>>``` ```<``` and pipes ```|```.

Environment variables are handled, like ```$HOME```, including the return code ```$?```.

Finally, you can use ```Ctrl-C``` to interrupt and ```Ctrl-\``` to quit a program, as well as ```Ctrl-D``` to throw an EOF, same as in bash.

A few of the functions are "built-in", meaning we don't call the executable, we re-coded them directly. It's the case for ```echo```, ```pwd```, ```cd```, ```env```, ```export```, ```unset``` and ```exit```.
