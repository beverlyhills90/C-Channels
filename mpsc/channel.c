#include "cmpsc.h"
#include <pthread.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>


void *clearChun(t_channel *channel){
    return NULL; //TODO
}

t_channel *create_channel(size_t buf_size) {
    t_channel *chan;

    chan = ft_calloc(1, sizeof(t_channel));
    if (!chan)
        return (NULL);
    chan->singleReciver = false;
    if (pthread_mutex_init(&chan->mu, NULL) != 0)
        return (free(chan), NULL);
    if (pthread_cond_init(&chan->state, NULL) != 0)
        return (pthread_mutex_destroy(&chan->mu), free(chan), NULL);
    createBufChan(chan,buf_size);

    return (chan);
}

