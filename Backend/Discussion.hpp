#include <iostream>


class Discussion 
{
private:
    struct Idea 
    {
        char* text;
        int numImpressions;
        int numForVotes;
        int numResponses;
        int ratio;
    };


public:
    char* topic;
    Idea idea;

    Discussion(char* topic, Idea& idea) :topic(topic), idea(idea) { std::cout << "New Discussion Created" << std::endl; }

};