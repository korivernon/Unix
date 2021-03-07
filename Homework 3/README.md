## du README

**Author: Kori Vernon**
**UNIX SYSTEM PROGRAMMING**
**Professor Sterling**
**Date: 03/06/2021**

Implement the utility du.

- If no arguments, then do du on the current working directory. Otherwise, the argument (you only have to handle one) is a directory to run du on.
- You do not have to support any options/flags.
- Note what happens when the du command is run and there is a file that is linked to (has a hard link) more than once from within the directory tree.
- a soft / symbolic link.
- Remember, the target platform is Linux.

The code does not work entirely as expected. The code resorts in a segmentation fault when running on a larger directory tree. I couldn't seem to find the issue that made this an issue, but I will be exploring this more in the future.