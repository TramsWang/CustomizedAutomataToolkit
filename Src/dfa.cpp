#include "dfa.hpp"
#include <stdlib.h>
#include <string.h>

DFS::DFS(int tag_, Character alphabet_):State(tag_, alphabet_)
{
  transitions = (StateID*)calloc(alphabet, sizeof(StateID));
}

DFS::~DFS()
{
  free(transitions);
}

void DFS::setTransition(Character character, StateID dst_id)
{
  transitions[character] = dst_id;
}

StateID DFS::transmit(Character character)
{
  return transitions[character];
}

bool DFS::deletable()
{
  return true;
}


DFA::DFA(Character alphabet_):Automata(alphabet_), cur_state(0){}

DFA::~DFA()
{
  int len = states->size();
  for (int i = 0; i < len; i++)
    {
      delete (*states)[i];
    }
}

StateID DFA::addState(void *data)
{
  DFS* state = new DFS((NULL==data)?false:true, alphabet);
  state->self_id = states->size();
  states->push_back(state);

  /* Set new state to orbit around itself */
  for (int i = 0; i < alphabet; i++)
    {
      state->transitions[i] = state->self_id;
    }

  return state->self_id;
}

void DFA::deleteState(StateID id)
{
  if ((*states)[id]->deletable()) states->erase(states->begin() + id);
}

void DFA::setTransition(StateID src, StateID* dsts, unsigned int length, void* condition)
{
  ((DFS*)((*states)[src]))->setTransition(*(Character*)condition, dsts[0]);
}

//void DFA::setStartState(StateID id)
//{
//  start_state = id;
//}

void DFA::initiate()
{
  cur_state = start_state;
}

Character DFA::readInput(Character character)
{
  return character;
}

void DFA::transmit(Character character, bool* (&next_states))
{
  cur_state = ((DFS*)((*states)[cur_state]))->transmit(character);
}

bool DFA::reportAcceptance()
{
  return (*states)[cur_state]->getTag();
}

/********************************************************************************************/
bool DFA::isDead() {return false;}
void DFA::minimize(){}
void DFA::visualize(){}
void DFA::minimumSampling(Character* (&string)){}
void DFA::randomSampling(Character* (&string)){}
void DFA::setCurrentStates(StateID* id, unsigned int length){}
void DFA::clear(){}

