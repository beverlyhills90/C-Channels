#ifndef CHANNELS_H
# define CHANNELS_H

#include "mpsc/cmpsc.h"

typedef struct s_mpscRes {
    t_reciver *reciver;
    t_sender *sender;
} t_mpscRes;

t_mpscRes *MPSCNew(size_t buffSize);
void send_data(t_sender *sender,void *data);
void *reciv(t_reciver *reciver);

#endif
