#ifndef REG_TO_NFA_H
#define REG_TO_NFA_H

#include <string>
#include <unordered_map>
#include <unordered_set>

class NFAGraphState
{
public:
    NFAGraphState();
    NFAGraphState(bool isAccepting);
    std::unordered_map<std::string, std::unordered_set<NFAGraphState *>> edgeTransitions;
    bool isAccepting;
};

class NFAGraph
{
public:
    std::unordered_set<NFAGraphState *> States;
    // taking @ as epsilon
    std::unordered_set<std::string> alphabet;
    NFAGraphState *startState;
    std::unordered_set<NFAGraphState *> acceptingStates;
    std::unordered_set<NFAGraphState *> transitionFunction(NFAGraphState *currentState, std::string input);
    std::unordered_set<NFAGraphState *> epsilonClosure(NFAGraphState *currentState);
    bool isValidString(std::string);
};

class regToNFAConvertor
{
public:
    NFAGraph *mainNFA;
    NFAGraph *getNFAforAlphabet(std::string alphabet);
    NFAGraph *getStar(NFAGraph *nfa);
    NFAGraph *getConcat(NFAGraph *nfa1, NFAGraph *nfa2);
    NFAGraph *getUnion(NFAGraph *nfa1, NFAGraph *nfa2);
    NFAGraph *regToNFA(std::string reg);
    int get_precedence(char c);
    bool is_operator(char c);
    std::string regex_to_prefix(std::string regex);
};

#endif