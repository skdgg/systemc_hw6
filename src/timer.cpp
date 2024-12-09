#include "timer.h"

void timer::runtimer() {
    timeout.write(0); // 初始化 timeout 信號
    count = 0;        // 初始化計數器

    while (true) {
        if (start.read()) {
            count = 5;       // 當 start = 1 時，重置計數器
            timeout.write(0); // timeout 清 0
        } else {
            if (count == 0) {
                timeout.write(1); // 當 count = 0 時，設置 timeout 為 1
            } else {
                count--;           // 否則減少計數
                timeout.write(0);  // timeout 保持為 0
            }
        }
        wait(); // 等待下一個時鐘週期
    }
}
