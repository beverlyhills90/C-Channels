#include "cmpsc.h"
#include <pthread.h>
#include <stdlib.h>



struct s_reciver {
    t_channel *channel_q;
} ;


t_reciver *create_reciver(t_channel *channel)
{
    t_reciver *reciver;
    
    reciver = ft_calloc(1, sizeof(t_reciver));
    if (!reciver)
        return (NULL);
    
    pthread_mutex_lock(&channel->mu);
    if (channel->singleReciver == true)
        return (pthread_mutex_unlock(&channel->mu),free(reciver), NULL);
    channel->singleReciver = true;
    pthread_mutex_unlock(&channel->mu);
    
    reciver->channel_q = channel;
    return reciver;
}


t_chanNode *pop(t_channel *chan) {
    t_chanNode *tmp;
    pthread_mutex_lock(&chan->mu);
    
    while (chan->channelQ == NULL)
        pthread_cond_wait(&chan->state, &chan->mu);
    tmp = chan->channelQ;
    chan->channelQ = tmp->next;
    pthread_mutex_unlock(&chan->mu);
    return  tmp;
}

void *reciv(t_reciver *reciver)
{
    t_chanNode *rcv;
    void *data;
    rcv = pop(reciver->channel_q);
    if (rcv){
        data = rcv->data;
        free(rcv);
        return data;
    }
    return (NULL);
}