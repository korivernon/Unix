/*

What is `puts` ? 

`puts` ->  used to write a line or string to the 
output( stdout ) stream. It prints the passed string 
with a newline and returns an integer value.

*/
#include <stdio.h>

int
main ()
{
  bar ();
  foo ();

  return 0;
}

void
bar ()
{
  int i = puts ("Bar");

  printf ("%d", i);
}

int
foo ()
{
  int i = puts ("Foo");
  printf ("%d", i);
}
