/**
 * @file   litter.c
 * @author Tero Isannainen <tero.isannainen@gmail.com>
 * @date   Mon Sep 16 19:51:23 2019
 * 
 * @brief  Litter - Miscellaneous functions.
 * 
 */


#include "litter.h"


st_none st_time_interval_start( st_time_interval_t interval )
{
    gettimeofday( &( interval->s_time ), NULL );
}


st_none st_time_interval_end( st_time_interval_t interval )
{
    gettimeofday( &( interval->e_time ), NULL );
}


st_flt_t st_time_interval_get( st_time_interval_t interval )
{
    st_flt_t s;
    st_flt_t e;

    s = ( (st_flt_t) interval->s_time.tv_sec ) + ( ( (st_flt_t) interval->s_time.tv_usec ) / 1000000.0 );
    e = ( (st_flt_t) interval->e_time.tv_sec ) + ( ( (st_flt_t) interval->e_time.tv_usec ) / 1000000.0 );

    return e - s;
}


st_flt_t st_time_interval_end_and_get( st_time_interval_t interval )
{
    st_time_interval_end( interval );
    return st_time_interval_get( interval );
}


st_time_meas_t st_time_meas_new( st_none )
{
    st_time_meas_t tm;

    tm = st_new( st_time_meas_s );
    tm->periods = sm_new( ST_TIME_MEAS_DEFAULT_PERIOD_CNT, sizeof( st_time_period_s ) );
    tm->first = NULL;
    tm->cur = NULL;
    return tm;
}


st_time_meas_t st_time_meas_del( st_time_meas_t tm )
{
    sm_del( tm->periods );
    st_del( tm );
    return NULL;
}


st_none st_time_meas_record_start( st_time_meas_t tm, st_str_t label )
{
    st_time_period_t period;
    
    period = (st_time_period_t) sm_get( tm->periods );

    /* Invalidate label for "end" sanity checking. */
    period->state = ST_TIME_STARTED;
    period->next = NULL;
    period->label = label;

    if ( tm->first == NULL ) {
        /* First period. */
        tm->first = period;
    } else {

        if ( tm->cur->state != ST_TIME_ENDED ) {
            fprintf( st_stderr, "st_time_meas ERROR: Period \"%s\" was not ended!\n", tm->cur->label );
            exit( 1 );
        }

        tm->cur->next = period;
    }
    tm->cur = period;
    st_time_interval_start( &period->interval );
}


st_none st_time_meas_record_end( st_time_meas_t tm, st_str_t label )
{
    st_time_period_t period;
    period = tm->cur;
    period->state = ST_TIME_ENDED;
    st_time_interval_end( &period->interval );
}


st_flt_t st_time_meas_total( st_time_meas_t tm )
{
    st_time_period_t cur;
    st_flt_t iv;
    st_flt_t sum = 0;

    cur = tm->first;
    while ( cur ) {
        iv = st_time_interval_get( &cur->interval );
        sum = sum + iv;
        cur = cur->next;
    }

    return sum;
}


st_none st_time_meas_report( st_time_meas_t tm )
{
    st_time_period_t cur;
    st_flt_t iv;
    st_flt_t sum = 0;
    cur = tm->first;

    while ( cur ) {
        iv = st_time_interval_get( &cur->interval );
        sum = sum + iv;
        if ( cur->label ) {
            printf( "  \"%s\": %lf\n", cur->label, iv );
        } else {
            printf( "  \"---\": %lf\n", iv );
        }
        cur = cur->next;
    }

    printf( "  TOTAL: %f\n", sum );
}


