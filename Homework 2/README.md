## env README

**Author: Kori Vernon**
**UNIX SYSTEM PROGRAMMING**
**Professor Sterling**
**Date: 02/23/2021**

Description: This assignment's code models that of the env command. There are several parts of the code that work, such as:
- When issued without arguments, it simply displays the environment.
- When issued with arguments, the pattern is:
env [-i] [name=value]... [command [argument]...]
- The purpose of env with options is to execute a command with a modified environment. The command being run can have its own arguments.
- If the -i option is used, then the name/value pairs that are provided, completely replace the environment when running the command.
- If the -i option is not provided, then the name/value pairs modify the environment.
- If no command is provided then env simply displays the new / modified environment.

The code code should function as it does in the example. 

