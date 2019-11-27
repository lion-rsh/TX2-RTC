#include <stdio.h>
#include <stdlib.h>
#include <linux/rtc.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <time.h>

#define DEV_NAME "/dev/rtc"
/*
*get RTC date and time from hardware RTC
* @param[:] <*rtc> { struct rtc_time }
* @return     { -1:open failed
*               -2:get RTC failed
*               0:get RTC success}
*/
int rtc_get(struct rtc_time *rtc)
{
	int fd, retval;

	fd = open(DEV_NAME, O_RDONLY);
	if(fd == -1)
	{
		printf("open failed %s\n",DEV_NAME);
		return -1;
	}
	/*get the RTC date & time*/
	retval = ioctl(fd, RTC_RD_TIME, rtc);
	if (retval == -1 )
	{
		printf("get RTC failed !\n");
		return -2;
	}
	rtc->tm_mon = rtc->tm_mon + 1;
	rtc->tm_year = rtc->tm_year + 1900;
	rtc->tm_hour = rtc->tm_hour + 8;
	printf("rtc_get: %d/%d/%d %02d:%02d:%02d \n", rtc->tm_mday, rtc->tm_mon,rtc->tm_year,
		rtc->tm_hour, rtc->tm_min, rtc->tm_sec);
	close(fd);
	return 0;
}

/*
*Set RTC date and time to hardware RTC
* @param[:] <*rtc> { struct rtc_time }
* @return     { -1:open failed
*               -2:set RTC failed
*               0:set RTC success}
 */
int rtc_set(struct rtc_time *rtc)
{
	int fd, retval;
	struct rtc_time set_rtc;

	/*set the RTC date & time*/
	fd = open(DEV_NAME, O_WRONLY);
	if (fd == -1)
	{
		printf("open failed %s\n",DEV_NAME);
		return -1;
	}
	set_rtc.tm_mday = rtc->tm_mday;
	set_rtc.tm_mon = rtc->tm_mon - 1;
	set_rtc.tm_year = rtc->tm_year - 1900;
	set_rtc.tm_hour = rtc->tm_hour - 8;
	set_rtc.tm_min = rtc->tm_min;
	set_rtc.tm_sec = rtc->tm_sec;

	printf("set_rtc: %d/%d/%d %02d:%02d:%02d \n", set_rtc.tm_mday, set_rtc.tm_mon,set_rtc.tm_year,
		set_rtc.tm_hour, set_rtc.tm_min, set_rtc.tm_sec);
	retval = ioctl(fd,RTC_SET_TIME, &set_rtc);
	if (retval == -1)
	{
		printf("set RTC failed !\n");
		return -2;
	}
	close(fd);

	return 0;
}
