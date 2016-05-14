#ifndef _DFA_H_
#define _DFA_H_

#include "cat.hpp"

class DFA;

class DFS : public State
{
  friend DFA;
public:
  DFS(int tag_, Character alphabet_);
  virtual ~DFS();

  void setTransition(Character character, StateID dst_id);
  StateID transmit(Character character);

  virtual bool deletable();
  
protected:
  StateID* transitions;
};

class DFA : public Automata
{
public:
  DFA(Character alphabet_);
  ~DFA();

  /* Necessary functions */
  virtual StateID addState(void *data);
  virtual void deleteState(StateID id);
  virtual void setTransition(StateID src, StateID* dsts,
			     unsigned int length, void* condition);
  //virtual void setStartState(StateID id);
  virtual void initiate();

  /* Auxiliary functions */
  virtual bool isDead();
  virtual void minimize();
  virtual void visualize();
  virtual void minimumSampling(Character* (&string));
  virtual void randomSampling(Character* (&string));
  virtual void setCurrentStates(StateID* id, unsigned int length);
  virtual void clear();

protected:
  virtual Character readInput(Character character);
  virtual void transmit(Character character, bool* (&next_states));
  virtual bool reportAcceptance();

  StateID cur_state;
};

#endif
