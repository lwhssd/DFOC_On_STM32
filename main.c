#include <stdio.h>
#include "lowpass_filter.h"

int main(int argc, char const *argv[])
{
    /* 创建: 时间常数 = 0.01秒 */
    lowpass_filter *lf = lowpass_filter_Create(0.01f);
    if (lf == NULL)
        return 1;

    float input[] = {0.0f, 10.0f, 10.0f, 10.0f, 5.0f, 5.0f};
    int n = sizeof(input) / sizeof(input[0]);

    printf("低通滤波器测试 (Tf=0.01s):\n");
    printf("%-8s  %-10s  %-10s\n", "Step", "Input", "Output");

    for (int i = 0; i < n; i++)
    {
        Sleep(100); /* 模拟100ms采样间隔 */
        float y = lf->Filter(lf, input[i]);
        printf("%-8d  %-10.2f  %-10.2f\n", i, input[i], y);
    }

    /* 销毁 */
    lowpass_filter_Destroy(lf);
    
    return 0;
}
