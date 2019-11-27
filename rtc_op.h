/*
*Descrpstion:
*Autor:RSH <tianying414@126.com>
*Date:2019.11.13
* 
 */

#ifndef __RTC_OP_H__
#define __RTC_OP_H__
#include <sys/types.h>



int rtc_get(struct rtc_time *rtc);
int rtc_set(struct rtc_time *rtc);
#endif