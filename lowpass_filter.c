#include "lowpass_filter.h"
#include <windows.h>

//微秒时间戳
static unsigned long get_micros(void)
{
    static LARGE_INTEGER freq = {0};
    static int initialized = 0;
    LARGE_INTEGER counter;
    if (!initialized)
    {
        QueryPerformanceFrequency(&freq);
        initialized = 1;
    }
    QueryPerformanceCounter(&counter);
    return (unsigned long)(counter.QuadPart * 1000000ULL / freq.QuadPart);
}

static void Init(lowpass_filter *self, float Tf){
    self->Tf = Tf;
    self->y_prev = 0.0f;
    self->timestamp_prev = get_micros();
}

static float Filter(lowpass_filter *self, float x){
    unsigned long timestamp = get_micros();
    float dt = (float)(timestamp - self->timestamp_prev) * 1e-6f;

    //时间异常处理
    if(dt < 0.0f){
        dt = 1e-3f;
    }
    else if(dt > 0.3f){
        self->y_prev = x;
        self->timestamp_prev = timestamp;
        return x;
    }

    //低通滤波公式
    float alpha = self->Tf / (self->Tf + dt);
    float y = alpha * self->y_prev + (1.0f - alpha) * x;

    self->y_prev = y;
    self->timestamp_prev = timestamp;

    return y;
}

// 构造函数负责:分配内存->绑定方法->调用init初始化
lowpass_filter *lowpass_filter_Create(float Tf){
    //1.堆上分配内存
    lowpass_filter *self = (lowpass_filter *)malloc(sizeof(lowpass_filter));
    if(self == NULL){
        fprintf(stderr, "[lowpass_filter] 内存分配失败！\n");
        return NULL;
    }

    //2.绑定方法(类似C++的vtable)
    self->Init = Init;
    self->Filter = Filter;

    //3.调用初始化
    self->Init(self, Tf);

    return self;
}

void lowpass_filter_Destroy(lowpass_filter *self){
    if(self != NULL){
        free(self);
    }
}