#include "cat.hpp"
#include <string.h>
#include <stdlib.h>

State::State(int tag_, Character alphabet_):
  tag(tag_), self_id(0), alphabet(alphabet_){}
State::~State(){};
int State::getTag(){return tag;}

Automata::Automata(Character alphabet_):
  alphabet(alphabet_), start_state(0)
{
  states = new std::vector<State*>();
  cur_states = NULL;
  id_pool = new std::map<State*, StateID>();
}

Automata::~Automata()
{
  delete states;
  if (NULL != cur_states) free(cur_states);
  delete id_pool;
}

bool Automata::run(Character character)
{
  bool* next_states = (bool*)calloc(states->size(), sizeof(bool));
  transmit(readInput(character), next_states);
  free(cur_states);
  cur_states = next_states;
  return reportAcceptance();
}

bool Automata::run(Character* char_array, unsigned int length)
{
  for (int i = 0; i < length; i++)
    {
      bool* next_states = (bool*)calloc(states->size(), sizeof(bool));
      transmit(readInput(char_array[i]), next_states);
      free(cur_states);
      cur_states = next_states;
    }
  return reportAcceptance();
}

void Automata::setStartState(StateID id)
{
  start_state = id;
}

void Automata::initiate()
{
  if (NULL != cur_states) free(cur_states);
  cur_states = (bool*)calloc(states->size(), sizeof(bool));
  cur_states[start_state] = true;
}

void Automata::setCurrentStates(StateID* idx, unsigned int length)
{
  if (NULL != cur_states) free(cur_states);
  cur_states = (bool*)calloc(states->size(), sizeof(bool));
  for (int i = 0; i < length; i++)
    {
      cur_states[idx[i]] = true;
    }
}

void Automata::clear()
{
  states->clear();
  start_state = 0;
  if (NULL != cur_states) free(cur_states);
  id_pool->clear();
}
