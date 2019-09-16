#ifndef LITTER_H
#define LITTER_H


/**
 * @file   litter.h
 * @author Tero Isannainen <tero.isannainen@gmail.com>
 * @date   Mon Sep 16 19:51:23 2019
 *
 * @brief  Litter - Miscellaneous functions.
 *
 */



#include <sixten.h>
#include <segman.h>
#include <sys/time.h>


/* ------------------------------------------------------------
 * Time interval:
 */

/**
 * Time interval, i.e. start and end time pair.
 */
st_struct( st_time_interval )
{
    struct timeval s_time; /**< Start time. */
    struct timeval e_time; /**< End time. */
};


/**
 * Time measurement state.
 */
st_enum( st_time_period_state ){ ST_TIME_STARTED, ST_TIME_ENDED };


st_struct_type( st_time_period );

/**
 * Time period struct.
 */
st_struct( st_time_period )
{
    st_time_interval_s     interval;
    st_time_period_t       next;
    st_str_t               label;
    st_time_period_state_t state;
};


/**
 * Collection of time intervals.
 */
st_struct( st_time_meas )
{
    sm_t             periods;
    st_time_period_t first;
    st_time_period_t cur;
};


/** Default alloction for time measurement periods. */
#define ST_TIME_MEAS_DEFAULT_PERIOD_CNT 128


/**
 * Store time interval start time.
 * 
 * @param interval Interval.
 * 
 * @return NA
 */
st_none  st_time_interval_start( st_time_interval_t interval );


/**
 * Store time interval end time.
 * 
 * @param interval Interval.
 * 
 * @return NA
 */
st_none  st_time_interval_end( st_time_interval_t interval );


/**
 * Return time interval value.
 * 
 * Differences between end and start timestamps.
 * 
 * @param interval Interval.
 * 
 * @return Interval value.
 */
st_flt_t st_time_interval_get( st_time_interval_t interval );


/**
 * End interval and return its value.
 * 
 * @param interval Interval.
 * 
 * @return Interval value.
 */
st_flt_t st_time_interval_end_and_get( st_time_interval_t interval );


/**
 * Create time measurement container.
 * 
 * @param st_none 
 * 
 * @return Time measurement container.
 */
st_time_meas_t st_time_meas_new( st_none );


/**
 * Delete time measurement container.
 * 
 * @param tm Time measurement container.
 * 
 * @return NULL.
 */
st_time_meas_t st_time_meas_del( st_time_meas_t tm );


/**
 * Start recording time measurement.
 * 
 * @param tm    Container.
 * @param label Label for measurement.
 * 
 * @return NA
 */
st_none        st_time_meas_record_start( st_time_meas_t tm, st_str_t label );


/**
 * End recording time measurement.
 * 
 * @param tm    Container.
 * @param label Label for measurement.
 * 
 * @return NA
 */
st_none        st_time_meas_record_end( st_time_meas_t tm, st_str_t label );


/**
 * Calculate accumulated time of all time measurements in Container.
 * 
 * @param tm   Container.
 * 
 * @return Total time.
 */
st_flt_t       st_time_meas_total( st_time_meas_t tm );


/**
 * Report all measurements and accumulated time.
 * 
 * @param tm   Container.
 * 
 * @return NA
 */
st_none        st_time_meas_report( st_time_meas_t tm );


#endif
