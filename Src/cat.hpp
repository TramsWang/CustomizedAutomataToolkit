#ifndef _CAT_H_
#define _CAT_H_

#include <stdio.h>
#include <vector>
#include <map>

typedef unsigned int StateID;
typedef unsigned int Character;

/**
 *   'State' is the class for composing states in an automata. It can be tagged variously and
 * be inherited to store user-defined data.
 */
class State
{
public:
  State(int tag_, Character alphabet_);
  virtual ~State() = 0;
  virtual bool deletable() = 0;
  int getTag();

protected:
  int tag;  /* Tag status such as 'accepted', 'unaccepted' or anything you need */
  Character alphabet;  /* Alphabet according to this state */
  StateID self_id;  /* ID of this state itself */
};

/**
 *   'Automata' is basis of all other types of automaton. From a formalized point of view, it
 * contains only (Q, Sigma, q0, F), composing the basic trunck of entire automata family tree.
 */
class Automata
{
public:
  Automata(Character alphabet_);  /* An automaton should be initiated with its alphabet */
  ~Automata();

  bool run(Character character); /* Feed automata with only one character, and return whether
				    automata is now accepting */
  bool run(Character* char_array, unsigned int length);  /* Feed automata with an array of
							    characters, and return whether 
							    automata is now accepting */
  /* These functions below are necessary for an automaton to run safe and sound. After these
     function calls, an executable automaton should already be constructed */
  virtual StateID addState(void *data) = 0;  /* Add a state in automata */
  virtual void deleteState(StateID id) = 0;  /* Delete a state in automata */
  virtual void setTransition(StateID src, StateID* dsts,
			     unsigned int length, void* condition) = 0; /* Construct transitions */
  virtual void setStartState(StateID id);  /* Set start state */
  virtual void initiate();  /* Do some other initiating tasks here */

  /* Auxiliary functions */
  virtual bool isDead() = 0;  /* Check whether its language is empty */
  virtual void minimize() = 0;  /* Minimize this automaton if appliable */
  virtual void visualize() = 0;  /* Output a visual for this automaton */
  virtual void minimumSampling(Character* (&string)) = 0;  /* Construct a minimum sample */
  virtual void randomSampling(Character* (&string)) = 0;  /* Construct a random sample */
  virtual void setCurrentStates(StateID* id, unsigned int length);  /* Set current state */
  virtual void clear();  /* Clear this instance to status where it's just been created */
  
protected:
  /* A run of an automaton could be abstracted as following five stages:
       1. Read                 : Read an input character and process the character if necessary
       2. Transmit             : Perform transmition according to input character
       3. Report               : Report automaton current status(whether accepting)
     Those three functions below perform tasks accordingly. Since non-determined automata
     behaves different from determined ones the transmit function varies */
  virtual Character readInput(Character character) = 0;
  virtual void transmit(Character character, bool* (&next_states)) = 0;
  virtual bool reportAcceptance() = 0;

  /* Data members(Q, Sigma, q0, F) that composes an automaton, where set 'F' is already 
     integrated in every state, namely, set 'Q' */
  std::vector<State*> *states;  /* Q: Set of all states */
  Character alphabet;           /* Sigma: Set of all characters */
  StateID start_state;          /* q0: Start state */

  /* Members needed to run non-determinedly */
  bool *cur_states;  /* Mark current state set */

  /* Mapping from State addr to its relative ID in vector 'states' */
  std::map<State*, StateID> *id_pool;
};


#endif
