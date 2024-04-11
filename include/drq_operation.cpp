#include "openssl/bn.h"
#include "eTPSS.h"
#include "utils.h"
#include "drq_data_structure.h"
#include "drq_operation.h"

// 初始化查询范围
RESULT drq_init_query_range(query_range * ranges){
    
}
// 读取查询范围
RESULT drq_read_query_range(query_range * ranges){
    
}
// 将不同维度的查询范围发送过去，获取查询的结果
RESULT drq_send_range2owner(query_range * ranges,drq_data_set * set){

}
// 释放query_range
RESULT drq_free_query_range(query_range * ranges){

}