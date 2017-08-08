//////////////////////////////////////////////////////////////////////////////
/// @file       QTSDataFieldDefine.h 
/// @brief      数据类定义文件，包括数据缓存模板类，按字段访问类，字段数据类定义
/// @copyright  Copyright (C), 2008-2014, GTA Information Tech. Co., Ltd.
/// @version    2.0
/// @date       2014.7.18
//////////////////////////////////////////////////////////////////////////////
#ifndef GTA_QTS_DATA_FIELD_DEFINE_H_
#define GTA_QTS_DATA_FIELD_DEFINE_H_
#include <memory>
#include "QTSDataType.h"
#include "QTSStruct.h"

/// 数据缓存模板，用于管理返回数据内存
template<class T> class GTA_API_EXPORT CDataBuffer 
{
public:
    /// 构造函数
    /// @param  bAutoDel    -- 对象析构时自动删除内存标志
    CDataBuffer(bool bAutoDel = true)
        :m_DataBuffer(NULL),m_nSize(0),m_nStore(0),m_bAutoDel(bAutoDel){}
    virtual ~CDataBuffer()
    {
        if (NULL != m_DataBuffer && m_bAutoDel)
        {
            delete [] m_DataBuffer;
        }
    }

    /// 清空数据，重置缓存大小
    void ReSize(int nSize)
    {
        m_nSize = nSize;
        if (nSize > m_nStore)
        {
            if (NULL != m_DataBuffer)
            {
                delete [] m_DataBuffer;
                m_DataBuffer = NULL;
            }
            m_nStore = nSize;
            m_DataBuffer = new T[nSize];
        }
        memset(m_DataBuffer, 0, sizeof(T) * m_nStore);
    }
    /// 返回数据首地址
    operator T *()
    {
        return m_DataBuffer;
    }
    T& operator [](int nIndex)
    {
        if (nIndex >= m_nSize || nIndex < 0)
        {
            nIndex = 0;
        }
        return m_DataBuffer[nIndex];
    }
    int Size()
    {
        return m_nSize;
    }
private:
    CDataBuffer(const CDataBuffer<T>& other){}
    CDataBuffer& operator = (const CDataBuffer<T> &other){}
    T*      m_DataBuffer;       ///< 数据指针
    int     m_nSize;            ///< 实际数据大小
    int     m_nStore;           ///< 缓存容量大小
    bool    m_bAutoDel;         ///< 自动删除内存标志，C接口需要保留内存返回用户，单独接口调用删除内存
};

/// 公告数据缓存，用于管理返回数据内存
template<> class GTA_API_EXPORT CDataBuffer<SZSEL1_Bulletin>
{
public:
    /// 构造函数
    /// @param  bAutoDel    -- 对象析构时自动删除内存标志
    CDataBuffer(bool bAutoDel = true)
        :m_DataBuffer(NULL),m_nSize(0),m_nStore(0),m_bAutoDel(bAutoDel){}
    virtual ~CDataBuffer()
    {
        if (NULL != m_DataBuffer && m_bAutoDel)
        {
            delete [] (char*)m_DataBuffer;
        }
    }

    /// 返回数据首地址
    operator SZSEL1_Bulletin *()
    {
        return m_DataBuffer;
    }
    
    int Size()
    {
        return m_nSize;
    }

    SZSEL1_Bulletin& operator [](int nIndex)
    {
        if (nIndex >= m_nSize || nIndex < 0)
        {
            nIndex = 0;
        }
        SZSEL1_Bulletin *pbuf = m_DataBuffer;
        for (int i = 0; i < nIndex; i++)
        {
            pbuf += sizeof(SZSEL1_BulletinHead) + pbuf->RawHead.RawDataLength;
        }
        return *pbuf;
    }

    /// 重置数据指针
    /// @param buff 数据起始地址
    /// @param nsize SZSEL1_Bulletin的个数
    void Reset(void* buff, int nsize)
    {
        if (NULL != m_DataBuffer)
        {
            delete [] m_DataBuffer;
            m_DataBuffer = NULL;
        }
        m_DataBuffer = (SZSEL1_Bulletin*)buff;
        m_nSize = nsize;
    }
private:
    CDataBuffer(const CDataBuffer<SZSEL1_Bulletin>& other){}
    CDataBuffer& operator = (const CDataBuffer<SZSEL1_Bulletin> &other){return *this;}
    SZSEL1_Bulletin*      m_DataBuffer;       ///< 数据指针
    int     m_nSize;            ///< 实际数据大小
    int     m_nStore;           ///< 缓存容量大小
    bool    m_bAutoDel;         ///< 自动删除内存标志，C接口需要保留内存返回用户，单独接口调用删除内存
};


#endif // GTA_QTS_DATA_FIELD_DEFINE_H_
