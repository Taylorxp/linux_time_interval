/**
 * @brief
 * @details
 * @mainpage
 */
 
/* 获取时间差 */
inline unsigned long get_time_diff(struct timespec* old, struct timespec* new_time)
{
    unsigned long interval;
    
    if (new_time->tv_nsec >= old->tv_nsec)
    {
        interval = (new_time->tv_sec - old->tv_sec) * 1000;
        interval += ((new_time->tv_nsec - old->tv_nsec)/1000000);
    }
    else
    {
        interval = (new_time->tv_sec - old->tv_sec - 1) * 1000;
        interval += ((new_time->tv_nsec + (1000000000 - old->tv_nsec))/1000000);
    }
    return interval;
}

/* 获取时间间隔 */
inline unsigned long get_time_interval(struct timespec* old)
{
    unsigned long interval;
    struct timespec new_time;

    clock_gettime(CLOCK_MONOTONIC, &new_time);

    if (new_time.tv_nsec >= old->tv_nsec)
    {
        interval = (new_time.tv_sec - old->tv_sec) * 1000;
        interval += ((new_time.tv_nsec - old->tv_nsec)/1000000);
    }
    else
    {
        interval = (new_time.tv_sec - old->tv_sec - 1) * 1000;
        interval += ((new_time.tv_nsec + (1000000000 - old->tv_nsec))/1000000);
    }
        
    return interval;
}

/* 检查时间间隔 */
inline int check_time_interval(struct timespec* old, unsigned int diff)
{
    unsigned long interval;
    struct timespec new_time;

    clock_gettime(CLOCK_MONOTONIC, &new_time);

    if (new_time.tv_nsec >= old->tv_nsec)
    {
        interval = (new_time.tv_sec - old->tv_sec) * 1000;
        interval += ((new_time.tv_nsec - old->tv_nsec)/1000000);
    }
    else
    {
        interval = (new_time.tv_sec - old->tv_sec - 1) * 1000;
        interval += ((new_time.tv_nsec + (1000000000 - old->tv_nsec))/1000000);
    }

    // interval /= 1000000;
    // LOG_INFO("interval:%ld, diff:%d", interval, diff);
    if (interval > diff)
    {
        memcpy(old, &new_time, sizeof(struct timespec));
        return 1;
    }

    return 0;
}