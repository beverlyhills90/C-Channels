# include "channels.h"
# include "helpers.h"
# include "mpsc/cmpsc.h"
# include <stddef.h>

t_mpscRes *MPSCNew(size_t buffSize) {
    t_mpscRes *res;
    t_channel *chan;
    t_reciver *resReciver;
    t_sender *resSender;

    chan = create_channel(buffSize);
    if (!chan)
        return (NULL);
    resReciver = create_reciver(chan);
    if(!resReciver)
        return (NULL); //ADD cleanup
    resSender = create_sender(chan);
    if(!resSender)
        return (NULL); //ADD cleanup
    res = ft_calloc(1,sizeof(t_mpscRes));
    if (!res)
        return (NULL);
    res->reciver = resReciver;
    res->sender = resSender;
    return (res);
}
