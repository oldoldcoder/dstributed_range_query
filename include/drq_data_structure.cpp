#include "openssl/bn.h"
#include "eTPSS.h"
#include "utils.h"
#include "drq_data_structure.h"

// data_set创建数据拥有者
RESULT drq_init_set(drq_data_set * set){

}
// 读取分散数据到data_owner
RESULT drq_read_data_to_owner(drq_data_set * set){

}
// data_owner对于自己持有的每一个数据进行加密，分散到三方上面去
RESULT drq_encrypt_data_owner(drq_data_owner * owner){

}
// 销毁data_set
RESULT drq_free_data_set(drq_data_set * set){

}

// 发送通信每个data_owner开始自查
RESULT drq_notify_do_query(drq_data_set * set){

}
// 进行隐私集合求交
RESULT drq_PSI(drq_data_owner * res,drq_data_owner * a,drq_data_owner * b){

}