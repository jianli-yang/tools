//
// Created by yangjianli on 2019-07-08.
//
/**
 * 缓存数据
 * 一个简易版的缓存队列系统，是对音频处理时动态开辟空间的
 * 的一层封装
 */
#ifndef CORRECTION_BUFFER_CACHE_H
#define CORRECTION_BUFFER_CACHE_H

#define ERROR_CODE_OK 0
#define ERROR_CODE_NO_CACHE -1
#define ERROR_CODE_WRONG_PARAMS -2

#include <iostream>
template<class T>
class CBufferCache {
public:
    CBufferCache();
    ~CBufferCache();
public:
    int Push(const T* pData, int nNum);
    int Get(T* pData, int nStart, int nEnd); //【nStart， nEnd)
    int Delete(int nNum, bool bHead=true); // bHead=true,从头部删除，删除个数
    int GetCacheSize();
private:
    T* mTQueue = nullptr;
    int mnNowLen = 0;
};

template<class T>
CBufferCache<T>::CBufferCache()
{
    mnNowLen = 0;
}

template<class T>
CBufferCache<T>::~CBufferCache()
{
    delete [] mTQueue;
}

/**
 * 返回当前缓存容量
 * @return
 */
template<class T>
int CBufferCache<T>::GetCacheSize()
{
    return mnNowLen;
}

template<class T>
int CBufferCache<T>::Push(const T *pData, int nNum)
{
    //开辟新空间
    T* pNewData = nullptr;
    pNewData = new T[mnNowLen + nNum];
    if(nullptr == pNewData)
    {
        return ERROR_CODE_NO_CACHE;
    }

    //拷贝数据到新空间
    memset(pNewData, 0, sizeof(T) * (mnNowLen + nNum));
    if(mnNowLen > 0)
    {
        memcpy(pNewData, mTQueue, sizeof(T) * mnNowLen);
    }
    memcpy(pNewData+mnNowLen, pData, sizeof(T)* nNum);
    mnNowLen += nNum;

    //释放原空间
    delete [] mTQueue;
    mTQueue = nullptr;
    mTQueue = pNewData;
    return ERROR_CODE_OK;
}

template<class T>
int CBufferCache<T>::Get(T *pData, int nStart, int nEnd)
{
    int nRet = ERROR_CODE_WRONG_PARAMS;
    if(nStart < nEnd && nStart >=0 && nEnd <=mnNowLen)
    {
        memcpy(pData, mTQueue+nStart, sizeof(T) * (nEnd - nStart));
        nRet = ERROR_CODE_OK;
    }
    return nRet;
}

template<class T>
int CBufferCache<T>::Delete(int nNum, bool bHead)
{
    int nRet = ERROR_CODE_WRONG_PARAMS;
    if(nNum <= mnNowLen)
    {
        int nNewSize = mnNowLen - nNum;
        if(nNewSize > 0)
        {
            T* pNewData = nullptr;
            pNewData = new T[nNewSize];
            if (nullptr == pNewData)
            {
                return ERROR_CODE_NO_CACHE;
            }
            memset(pNewData, 0, sizeof(T) * nNewSize);

            if(bHead)
            {
                //从头删除
                memcpy(pNewData, mTQueue+nNum, sizeof(T) * nNewSize);
            } else
            {
                memcpy(pNewData, mTQueue, sizeof(T) * nNewSize);
            }

            //释放空间
            delete [] mTQueue;
            mTQueue = nullptr;
            mTQueue = pNewData;
            mnNowLen = nNewSize;
        }else
        {
            // 删除干净
            delete [] mTQueue;
            mTQueue = nullptr;
            mnNowLen = nNewSize;
        }
        nRet = ERROR_CODE_OK;
    }
    return nRet;
}
#endif //CORRECTION_BUFFER_CACHE_H

