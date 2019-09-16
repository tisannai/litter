#include "unity.h"
#include "litter.h"
#include <unistd.h>


void test_basic( void )
{
    st_time_meas_t tm;
    st_flt_t period;
    
    tm = st_time_meas_new();
    st_time_meas_record_start( tm, "test1" );
    usleep( 1000 );
    st_time_meas_record_end( tm, "test1" );
    period = st_time_meas_total( tm );
    st_time_meas_report( tm );

    TEST_ASSERT_TRUE( period > 0.0001 );
    TEST_ASSERT_TRUE( period < 0.01 );
}
