/**
@author:heqi
@time:2024/04/10
@desc:分布式范围查询的操作头文件
*/
#ifndef DRQ_DATA_STRUCTURE_H
#define DRQ_DATA_STRUCTURE_H

#include "openssl/bn.h"
#include "eTPSS.h"
#include "utils.h"
#include "vector"
// 数据拥有者

typedef struct {
    // id
    int id;
    // 一个加密数据
    eTPSS * en_val;
    // 一个解密数据
    BIGNUM * de_val;
}drq_data_owner_unit;

typedef struct {
    // 长度
    int n;
    // 一个数据
    drq_data_owner_unit ** units;
    // 记录查询的范围
    eTPSS ** query_range;
    // 记录查询的结果
    std::vector<int> query_res;
}drq_data_owner;

// 数据总的持有者
typedef struct {
    // 维度也是数据拥有者的量
    int d;
    // 数据拥有者的集合
    drq_data_owner ** owners;
}drq_data_set;

// data_set创建数据拥有者
RESULT drq_init_set(drq_data_set * set);
// 读取分散数据到data_owner
RESULT drq_read_data_to_owner(drq_data_set * set);
// data_owner对于自己持有的每一个数据进行加密，分散到三方上面去
RESULT drq_encrypt_data_owner(drq_data_owner * owner);
// 销毁data_set
RESULT drq_free_data_set(drq_data_set * set);

#endif //DRQ_DATA_STRUCTURE_H