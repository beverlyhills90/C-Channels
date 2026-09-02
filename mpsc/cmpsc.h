#ifndef CMPSC_H
# define CMPSC_H


# include "../helpers.h"

typedef struct s_sender t_sender;
typedef struct s_reciver t_reciver;

typedef struct s_chanNode {
    void *data;
    struct s_chanNode *next;
} t_chanNode;

typedef struct s_channel
{
    pthread_mutex_t mu;
    pthread_cond_t state;
    size_t RC;
    t_chanNode *channelQ;
    bool singleReciver;
} t_channel;


t_sender *create_sender(t_channel *channel);
t_reciver *create_reciver(t_channel *channel);
t_sender *clone_sender(t_sender *origin);

void send_data(t_sender *sender,void *data);
void *reciv(t_reciver *reciver);

//Channel OPS
t_channel *create_channel(size_t buf_size);
void createBufChan (t_channel *chan,size_t n);
void *clearChun(t_channel *channel);
t_chanNode *pop(t_channel *chan);
void pushToChan(t_channel *chan,void *data);

#endif