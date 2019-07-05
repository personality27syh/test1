#include <iostream>

#include "ShareMemory.h"


using namespace std;

//写共享内存
int main(void)
{
    int ret = -1;
    void *addr = NULL;

    //1. 创建共享内存对象
    ShareMemory *m = new ShareMemory(0x66, 1024);
    cout << "创建共享内存成功" << endl;


    //2. 关联共享内存
    addr = m->mapShm();

    cout << "关联共享内存成功" << endl;

    //3. 写共享内存
    memcpy(addr, "吃多了拉就是队列，吃多了吐就是栈", strlen("吃多了拉就是队列，吃多了吐就是栈"));

    //4. 取消关联共享内存
    m->unMapShm();

    cout << "取消关联共享内存成功" << endl;

    //5. 删除对象
    delete m;

    return 0;
}
