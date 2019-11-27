/*
*示例代码：
*
* 设置RTC时钟之前，先禁用系统的NTP，可使用命令 sudo timedatectl set-ntp no
 */
#include <stdio.h>
#include <stdlib.h>
#include <linux/rtc.h>
#include <sys/time.h>
#include <errno.h>
#include "rtc_op.h"

int main(void)
{
	int ret;
	struct rtc_time set,get;
	/* 设置RTC时钟为 2019-11-13 19:40:20 */
	set.tm_mday = 13;
	set.tm_mon = 11;
	set.tm_year = 2019;
	set.tm_hour = 19;
	set.tm_min = 40;
	set.tm_sec = 20;
    /* 调用接口函数 rtc_set() 将时间写入RTC中 */
	ret = rtc_set(&set);
	if(ret != 0)
	{
		printf("call rtc_set() failed ! err=%d \n", ret);
		return -1;
	}
	printf("set RTC: %d/%d/%d %02d:%02d:%02d \n", set.tm_mday, set.tm_mon, set.tm_year,
		set.tm_hour, set.tm_min, set.tm_sec);
    /* 调用接口函数 rtc_get() 从RTC中获取时间 */
	ret = rtc_get(&get);
	if(ret != 0)
	{
		printf("call rtc_get() failed ! err=%d \n", ret);
		return -1;
	}
	printf("get RTC: %d/%d/%d %02d:%02d:%02d \n", get.tm_mday, get.tm_mon, get.tm_year,
		get.tm_hour, get.tm_min, get.tm_sec);	


	return 0;
}
