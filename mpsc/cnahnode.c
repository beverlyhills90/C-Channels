#include "cmpsc.h"
#include <stddef.h>


t_chanNode *create_node(void) {
    t_chanNode *new;

    new = ft_calloc(1, sizeof(t_chanNode));
    if (!new)
        return (NULL);
    return new;
}


void add_node_back(t_channel *channel,t_chanNode *newNode)
{
    t_chanNode *currentNode;

    currentNode = channel->channelQ;
    if (currentNode == NULL){
        channel->channelQ = newNode;
        return;
    }
    while (currentNode != NULL && currentNode->next != NULL) {
        currentNode = currentNode->next;
    }
    currentNode->next = newNode;
}

void createBufChan (t_channel *chan,size_t n) {

    size_t i;
    
    t_chanNode *newNode;
    i = 0;
    
    while (i < n) {
        newNode = ft_calloc(1, sizeof(t_chanNode));
        if (!newNode){
            clearChun(chan);
            return ;   
        }
        add_node_back(chan, newNode);    
        i++;
    }
}