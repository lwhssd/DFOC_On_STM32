#ifndef _LOWPASS_FILTER_H
#define _LOWPASS_FILTER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    低通滤波器结构体(模拟C++类)
*/
typedef struct lowpass_filter{
    // 成员变量
    float Tf;
    unsigned long timestamp_prev;
    float y_prev;

    //成员函数
    void (*Init)(struct lowpass_filter *self, float Tf);
    float (*Filter)(struct lowpass_filter *self, float x);
    // 函数指针的签名中,第一个参数永远都是struct lowpass_filter *self
} lowpass_filter;

/*
    构造函数:在堆上分配并初始化一个滤波器
    @param TF 时间常数
    @return  实例指针
*/
lowpass_filter *lowpass_filter_Create(float Tf);

/*
    析构函数:释放实例
    @param self 实例指针
*/
void lowpass_filter_Destroy(lowpass_filter *self);

#endif
