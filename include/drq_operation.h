/**
@author:heqi
@time:2024/04/10
@desc:分布式范围查询的数据结构头文件
*/
#ifndef DRQ_OPERATION_H
#define DRQ_OPERATION_H

#include "openssl/bn.h"
#include "utils.h"
#include "drq_data_structure.h"
#include <vector>
/*-----------------------------常量定义----------------------------*/
// 分布式查询的范围定义
typedef struct {
    int d;
    // 每个元素都是一个二维的数组，[0]代表了lower,[1]代表了upper
    BIGNUM *** range;
}query_range;

/*---------------------操作方法---------------------*/
// 初始化查询范围
RESULT drq_init_query_range(query_range * ranges);
// 读取查询范围
RESULT drq_read_query_range(query_range * ranges);
// 将不同维度的查询范围发送过去，获取查询的结果
RESULT drq_send_range2owner(query_range * ranges,drq_data_set * set);
// 释放query_range
RESULT drq_free_query_range(query_range * ranges);
#endif //DRQ_OPERATION_H