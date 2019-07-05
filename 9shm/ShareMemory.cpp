#include "ShareMemory.h"

#include <stdio.h>
#include <iostream>

using namespace std;

//构造函数 打开共享内存
ShareMemory::ShareMemory(int key)
{
    mShmId = shmget(key, 0, 0);
    if (-1 == mShmId)
    {
        perror("shmget");
    }
}

//构造函数 打开共享内存
ShareMemory::ShareMemory(char *pathName)
{
    key_t key = -1;

    //生成Key
    key = ftok(pathName, 'X');
    if (-1 == key)
    {
        perror("ftok"); 
        return;
    }

    //打开共享内存
    mShmId = shmget(key, 0, 0);
    if (-1 == mShmId)
    {
        perror("shmget"); 
        return;
    }
}

//构造函数 创建共享内存
ShareMemory::ShareMemory(int key, int shmSize)
{
    //创建共享内存
    mShmId = shmget(key, shmSize, IPC_CREAT | 0644); 
    if (-1 == mShmId)
    {
        perror("shmget"); 
        return;
    }
}

//构造函数 创建共享内存
ShareMemory::ShareMemory(char *pathName, int shmSize)
{
    key_t key = -1;
    //生成key
    key = ftok(pathName, 'X'); 
    if (-1 == key)
    {
        perror("ftok"); 
        return;
    }

    //创建共享内存
    mShmId = shmget(key, shmSize, IPC_CREAT | 0644);
    if (-1 == mShmId)
    {
        perror("shmget"); 
        return;
    }
}


//关联共享内存
void *ShareMemory::mapShm(void)
{
    mShmAddr = shmat(mShmId, NULL, 0);
    if ((void*)-1 == mShmAddr)
    {
        perror("shmat"); 
        return NULL;
    }

    return mShmAddr;
}

//解除关联共享内存
int ShareMemory::unMapShm(void)
{
    int ret = -1;

    ret = shmdt(mShmAddr);
    if (-1 == ret)
    {
        perror("shmdt"); 
        return -1;
    }

    return 0;
}

//删除共享内存
int ShareMemory::delShm(void)
{
    int ret = -1;

    ret = shmctl(mShmId, IPC_RMID, NULL);
    if (-1 == ret)
    {
        perror("shmctl"); 
        return -1;
    }


    return 0;
}

