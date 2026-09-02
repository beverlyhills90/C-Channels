# include "cmpsc.h"
#include <pthread.h>
#include <string.h>


struct s_sender {
    t_channel *channel_q;
} ;

t_sender *create_sender(t_channel *channel)
{
    t_sender *sender;

    sender = ft_calloc(1, sizeof(t_sender));
    if (!sender)
        return (NULL);
    pthread_mutex_lock(&channel->mu);
    channel->RC++;
    pthread_mutex_unlock(&channel->mu);
    sender-> channel_q = channel;
    return sender;
}


t_sender *clone_sender(t_sender *origin)
{
    t_sender *sender;
    sender = ft_calloc(1, sizeof(t_sender));
    if (!sender)
        return (NULL);
    sender-> channel_q = origin->channel_q;
    pthread_mutex_lock(&origin->channel_q->mu);
    origin->channel_q->RC++;
    pthread_mutex_unlock(&origin->channel_q->mu);
    
    return sender;
}

void pushToChan(t_channel *chan,void *data)
{
    t_chanNode *new;
    t_chanNode *tmp;
    new = ft_calloc(1,sizeof(t_chanNode));
    if(!new){
        return;
    }
    new->data = data;
    pthread_mutex_lock(&chan->mu);
    tmp = chan->channelQ;
    if (tmp == NULL){
        chan->channelQ = new;
    }
    else {
        while (tmp && tmp->next) {
            tmp = tmp->next;
        }
        tmp->next = new;
    }
    pthread_cond_signal(&chan->state);
    pthread_mutex_unlock(&chan->mu);
}


void send_data(t_sender *sender,void *data)
{
    pushToChan(sender->channel_q, data);
}