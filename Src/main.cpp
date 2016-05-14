#include "cat.hpp"
#include "dfa.hpp"
#include <vector>
#include <stdio.h>

using namespace std;

#define ALPHABET 26
#define BUFSIZE  20

/**
 * $1: source file path
 */
int main(int argc, char** argv)
{
  DFA *dfa = new DFA(ALPHABET);
  StateID ids[11];

  ids[0] = dfa->addState(NULL);
  ids[1] = dfa->addState(NULL);
  ids[2] = dfa->addState(NULL);
  ids[3] = dfa->addState(NULL);
  ids[4] = dfa->addState(NULL);
  ids[5] = dfa->addState(NULL);
  ids[6] = dfa->addState(NULL);
  ids[7] = dfa->addState(NULL);
  ids[8] = dfa->addState(NULL);
  ids[9] = dfa->addState(NULL);
  ids[10] = dfa->addState((void*)(NULL+1));

  /* Set transition */
  Character c = 'a' - 'a';
  for (int i = 1; i < 11; i++)
    {
      for (int j = 0; j < ALPHABET; j++)
	{
	  dfa->setTransition(ids[i], ids, 1, &j);
	}
      dfa->setTransition(ids[i], ids + 1, 1, &c);
    }

  dfa->setTransition(ids[0], ids + 1, 1, &c);
  c = 'b' - 'a';
  dfa->setTransition(ids[1], ids + 2, 1, &c);
  c = 'c' - 'a';
  dfa->setTransition(ids[2], ids + 3, 1, &c);
  c = 'd' - 'a';
  dfa->setTransition(ids[3], ids + 4, 1, &c);
  c = 'e' - 'a';
  dfa->setTransition(ids[4], ids + 5, 1, &c);
  c = 'f' - 'a';
  dfa->setTransition(ids[5], ids + 6, 1, &c);
  c = 'g' - 'a';
  dfa->setTransition(ids[6], ids + 7, 1, &c);
  c = 'h' - 'a';
  dfa->setTransition(ids[7], ids + 8, 1, &c);
  c = 'i' - 'a';
  dfa->setTransition(ids[8], ids + 9, 1, &c);
  c = 'j' - 'a';
  dfa->setTransition(ids[9], ids + 10, 1, &c);
  
  dfa->setStartState(ids[0]);
  dfa->initiate();

  int cnt = 0;

  FILE* file = fopen(argv[1], "r");
  if (NULL == file)
    {
      printf("File Not exist!\n");
      delete dfa;
      return 0;
    }

  int cc;
  while (EOF != (cc = fgetc(file)))
    {
      cnt += dfa->run(cc - 'a');
    }

  printf("Total: %d\n", cnt);

  fclose(file);
  delete dfa;
  
  return 0;
}
