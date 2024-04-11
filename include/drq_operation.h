/**
@author:heqi
@time:2024/04/10
@desc:分布式范围查询的数据结构头文件
*/
#ifndef DRQ_OPERATION_H
#define DRQ_OPERATION_H

#include "openssl/bn.h"
#include "eTPSS.h"
#include "utils.h"
#include <vector>
// 分布式查询的范围定义
typedef struct {
    int d;
    // 每个元素都是一个二维的数组，[0]代表了lower,[1]代表了upper
    eTPSS *** range;
}query_range;



/*---------------------操作方法---------------------*/
// 初始化查询范围

// 读取查询范围

// 将不同维度的查询范围发送过去，获取查询的结果

// 每个数据拥有者内部开始单查

// 对于指定的data_Set内部的数据拥有者的结果数据进行隐私集合求交集

#endif //DRQ_OPERATION_H