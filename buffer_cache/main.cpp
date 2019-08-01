//
// Created by yangjianli on 2019-08-01.
//

#include "BufferCache.h"
/**
 * 测试BufferCache
 */
int main(int argc, char* argv[])
{
    CBufferCache<float>* cBufferCache = new CBufferCache<float>;

    // 输入5个数据
    float* pData = new float[5];
    for(int i=0;i<5;i++)
    {
        pData[i] = i;
    }
    //
    cBufferCache->Push(pData, 5);
    cBufferCache->Get(pData, 1, 3);
    for(int i=0;i<2;i++)
    {
        printf("%f\n", pData[i]);
    }
    printf("-----size=%d-------\n", cBufferCache->GetCacheSize());
    cBufferCache->Delete(2, true);
    cBufferCache->Get(pData, 1, 3);
    for(int i=0;i<2;i++)
    {
        printf("%f\n", pData[i]);
    }
    printf("-----size=%d-------\n", cBufferCache->GetCacheSize());
    delete cBufferCache;
    return 0;
}