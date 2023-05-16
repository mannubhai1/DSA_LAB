#include "regex_to_nfa.h"
#include <iostream>
#include <stack>
#include <string>
#include <algorithm>

using namespace std;

NFAGraphState::NFAGraphState()
{
    this->edgeTransitions["@"].insert(this);
    this->isAccepting = false;
}

NFAGraphState::NFAGraphState(bool isAccepting)
{
    this->edgeTransitions["@"].insert(this);
    this->isAccepting = isAccepting;
}

unordered_set<NFAGraphState *> NFAGraph::transitionFunction(NFAGraphState *currentState, std::string input)
{
    return currentState->edgeTransitions[input];
}

unordered_set<NFAGraphState *> NFAGraph::epsilonClosure(NFAGraphState *currentState)
{
    unordered_set<NFAGraphState *> closure = {currentState};
    stack<NFAGraphState *> stack;
    stack.push(currentState);
    while (!stack.empty())
    {
        NFAGraphState *state = stack.top();
        stack.pop();
        for (NFAGraphState *state2 : state->edgeTransitions["@"])
        {
            if (closure.find(state2) == closure.end())
            {
                closure.insert(state2);
                stack.push(state2);
            }
        }
    }
    return closure;
}

bool NFAGraph::isValidString(string input)
{
    unordered_set<NFAGraphState *> currentStates = epsilonClosure(startState);
    for (int i = 0; i < input.length(); i++)
    {
        unordered_set<NFAGraphState *> nextStates = {};
        for (NFAGraphState *state : currentStates)
        {
            unordered_set<NFAGraphState *> temp = transitionFunction(state, input.substr(i, 1));
            for (NFAGraphState *state2 : temp)
            {
                unordered_set<NFAGraphState *> temp2 = epsilonClosure(state2);
                nextStates.insert(temp2.begin(), temp2.end());
            }
        }
        currentStates = nextStates;
    }
    for (NFAGraphState *state : currentStates)
    {
        if (state->isAccepting)
        {
            return true;
        }
    }
    return false;
}

NFAGraph *regToNFAConvertor::getNFAforAlphabet(string alphabet)
{
    NFAGraph *nfa = new NFAGraph();
    nfa->alphabet.insert(alphabet);
    NFAGraphState *startState = new NFAGraphState();
    NFAGraphState *acceptingState = new NFAGraphState(true);
    startState->edgeTransitions[alphabet].insert(acceptingState);
    nfa->States.insert(startState);
    nfa->States.insert(acceptingState);
    nfa->startState = startState;
    nfa->acceptingStates.insert(acceptingState);
    return nfa;
}

NFAGraph *regToNFAConvertor::getConcat(NFAGraph *nfa1, NFAGraph *nfa2)
{
    NFAGraph *nfa = new NFAGraph();
    nfa->alphabet = nfa1->alphabet;
    nfa->alphabet.insert(nfa2->alphabet.begin(), nfa2->alphabet.end());
    nfa->States = nfa1->States;
    nfa->States.insert(nfa2->States.begin(), nfa2->States.end());
    nfa->startState = nfa1->startState;
    nfa->acceptingStates = nfa2->acceptingStates;
    for (NFAGraphState *state : nfa1->acceptingStates)
    {
        state->isAccepting = false;
        state->edgeTransitions["@"].insert(nfa2->startState);
    }
    delete nfa1;
    delete nfa2;
    return nfa;
}

NFAGraph *regToNFAConvertor::getUnion(NFAGraph *nfa1, NFAGraph *nfa2)
{
    NFAGraph *nfa = new NFAGraph();
    nfa->alphabet = nfa1->alphabet;
    nfa->alphabet.insert(nfa2->alphabet.begin(), nfa2->alphabet.end());
    nfa->States = nfa1->States;
    nfa->States.insert(nfa2->States.begin(), nfa2->States.end());

    nfa->startState = new NFAGraphState();
    nfa->States.insert(nfa->startState);
    nfa->startState->edgeTransitions["@"].insert(nfa1->startState);
    nfa->startState->edgeTransitions["@"].insert(nfa2->startState);

    NFAGraphState *newState = new NFAGraphState(true);
    nfa->States.insert(newState);
    nfa->acceptingStates.insert(newState);
    for (NFAGraphState *state : nfa1->acceptingStates)
    {
        state->edgeTransitions["@"].insert(newState);
    }
    for (NFAGraphState *state : nfa2->acceptingStates)
    {
        state->edgeTransitions["@"].insert(newState);
    }
    delete nfa1;
    delete nfa2;
    return nfa;
}

NFAGraph *regToNFAConvertor::getStar(NFAGraph *nfa)
{
    NFAGraph *newNFA = new NFAGraph();
    newNFA->alphabet = nfa->alphabet;
    newNFA->States = nfa->States;
    newNFA->startState = new NFAGraphState(true);
    newNFA->States.insert(newNFA->startState);
    newNFA->acceptingStates.insert(newNFA->startState);
    newNFA->startState->edgeTransitions["@"].insert(nfa->startState);
    NFAGraphState *newState = new NFAGraphState(true);
    newNFA->States.insert(newState);
    newNFA->acceptingStates.insert(newState);
    for (NFAGraphState *state : nfa->acceptingStates)
    {
        state->edgeTransitions["@"].insert(nfa->startState);
        state->edgeTransitions["@"].insert(newState);
    }
    delete nfa;
    return newNFA;
}

NFAGraph *regToNFAConvertor::regToNFA(string reg)
{
    string prefix = regex_to_prefix(reg);
    stack<NFAGraph *> nfa_stack;
    for (int i = prefix.length(); i >= 0; i--)
    {
        if (prefix[i] == '*')
        {
            NFAGraph *nfa = nfa_stack.top();
            nfa_stack.pop();
            nfa_stack.push(getStar(nfa));
        }
        else if (prefix[i] == '.')
        {
            NFAGraph *nfa1 = nfa_stack.top();
            nfa_stack.pop();
            NFAGraph *nfa2 = nfa_stack.top();
            nfa_stack.pop();
            nfa_stack.push(getConcat(nfa1, nfa2));
        }
        else if (prefix[i] == '+')
        {
            NFAGraph *nfa1 = nfa_stack.top();
            nfa_stack.pop();
            NFAGraph *nfa2 = nfa_stack.top();
            nfa_stack.pop();
            nfa_stack.push(getUnion(nfa1, nfa2));
        }
        else
        {
            nfa_stack.push(getNFAforAlphabet(string(1, prefix[i])));
        }
    }
    mainNFA = nfa_stack.top();
    return nfa_stack.top();
}

int regToNFAConvertor::get_precedence(char c)
{
    if (c == '*')
        return 3;
    else if (c == '.')
        return 2;
    else if (c == '+')
        return 1;
    else
        return 0;
}

bool regToNFAConvertor::is_operator(char c)
{
    if (c == '*' || c == '.' || c == '+' || c == '(' || c == ')')
        return true;
    return false;
}

string regToNFAConvertor::regex_to_prefix(string infix)
{
    infix = '(' + infix + ')';

    std::reverse(infix.begin(), infix.end());

    int l = infix.size();
    stack<char> char_stack;
    string output;

    for (int i = 0; i < l; i++)
    {
        if (!is_operator(infix[i]))
            output += infix[i];

        else if (infix[i] == ')')
            char_stack.push(')');

        else if (infix[i] == '(')
        {
            while (char_stack.top() != ')')
            {
                output += char_stack.top();
                char_stack.pop();
            }

            char_stack.pop();
        }

        else
        {
            if (is_operator(char_stack.top()))
            {
                while (
                    get_precedence(infix[i]) < get_precedence(char_stack.top()))
                {
                    output += char_stack.top();
                    char_stack.pop();
                }

                char_stack.push(infix[i]);
            }
        }
    }
    while (!char_stack.empty())
    {
        output += char_stack.top();
        char_stack.pop();
    }
    std::reverse(output.begin(), output.end());
    return output;
}