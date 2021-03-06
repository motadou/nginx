#include <ngx_config.h>
#include <ngx_core.h>
#include <ngx_event.h>

ngx_queue_t  ngx_posted_accept_events;
ngx_queue_t  ngx_posted_events;

void ngx_event_process_posted(ngx_cycle_t *cycle, ngx_queue_t *posted)
{
    ngx_queue_t  *q;
    ngx_event_t  *ev;

    while (!ngx_queue_empty(posted)) 
    {
        q  = ngx_queue_head(posted);
        ev = ngx_queue_data(q, ngx_event_t, queue);

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0, "posted event %p", ev);

        ngx_delete_posted_event(ev);

        printf("%s|%s|%d|%dCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCCC\n", __FILE__, __FUNCTION__, __LINE__, getpid());

        ev->handler(ev);
    }
}
