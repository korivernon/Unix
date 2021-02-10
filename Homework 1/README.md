## Conway's Game of Life README

**Author: Kori Vernon**
**UNIX SYSTEM PROGRAMMING**
**Professor Sterling**
**Date: 02/09/2021**

Description: This assignment's code models that of Conway's Game of Life. There are several parts of the code that work, such as:
- Correctly taking all variations of arguments
- Successfully initializing game board
- Successfully printing arbitrary game board
- Correctly deciding between different modes
- Checking all 8 neighbors
- Checking for neighbors and creating temporary board
- Successfully accessing and reading in characters of file
- Successfully converting single integer

There are some functionalities that do not correctly work
- Loading in file and printing game board based on the file
- Checking for neighbors and printing game board

Reasoning: I was running into an issue bringing in the file's contents. I used fgets in order to grab each line in the file up to the maximum column These problems were apparent on lines 150 through 165. The second issue I was having had to deal with checking for neighbors and printing the game board. I logically figured the coordinates that needed to be checked and depending on the neighbors assign the correct status, however this doesn't seem to be working in practice.  

Apart from those two issues, the code rest of the code should function as it does in the example. 
