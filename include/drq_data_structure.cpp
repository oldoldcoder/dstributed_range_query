#include <cstring>
#include "openssl/bn.h"
#include "utils.h"
#include "drq_data_structure.h"

using namespace std;

// data_set创建数据拥有者
RESULT drq_init_set(drq_data_set * set){
    set->ctx = BN_CTX_new();
    set->d = -1;
    set->n = -1;
    set->owners = nullptr;
    return SUCCESS;
}
// 读取分散数据到data_owner
RESULT drq_read_data_to_owner(drq_data_set * set,const char * filePath){
    FILE  * file = nullptr;
    if(filePath == nullptr){
        file = fopen(filePath,"r");
    }
    if(file == nullptr){
        perror("Error opening file");
        return ERROR;
    }
    char *line = nullptr;
    size_t len = 0;
    // 初始化data
    int totalLines, dim;
    fscanf(file, "%d %d\n", &totalLines, &dim); // 读取第一行中的两个数字
    set->n = totalLines;
    set->d = dim;
    // 创建d个数据拥有者
    set->owners = (drq_data_owner **) malloc(sizeof (drq_data_owner *) * set->d);
    for(int i = 0 ; i < dim ; ++i){
        set->owners[i] = (drq_data_owner *)malloc(sizeof (drq_data_owner));
        // 初始化units
        set->owners[i]->units = (drq_data_owner_unit ** ) malloc(sizeof (drq_data_owner_unit *) * set->n);
        set->owners[i]->n = set->n;
        set->owners[i]->query_res = new vector<int>;
        // 初始化range
        set->owners[i]->query_range = (BIGNUM **) malloc(sizeof (BIGNUM *) * 2);
        set->owners[i]->query_range[0] = BN_CTX_get(set->ctx);
        set->owners[i]->query_range[1] = BN_CTX_get(set->ctx);
        for(int j = 0 ; j < set->n ; ++j){
            set->owners[i]->units[j] = (drq_data_owner_unit *) malloc(sizeof (drq_data_owner_unit));
            // 数据拥有者的编号
            set->owners[i]->units[j]->id = j;
        }
    }

    // 下面进行读取文件的数据
    /*
     * 按行读取，然后每一行用空格隔开，然后读取数字
     * */
    int n = 0;
    while (getline(&line, &len, file) != -1) {
        int idx = 0;
        char *token = strtok(line, " ");
        while (token != nullptr) {
            BIGNUM *tmp = BN_CTX_get(set->ctx);
            fflush(stdout);
            if(!BN_dec2bn(&tmp,token)){
                fprintf(stdout,"file have some error format about data\n");
                return ERROR;
            }
            set->owners[idx++]->units[n]->de_val = tmp;
            token = strtok(nullptr, " ");
        }
        if(idx != dim){
            fprintf(stderr,"Error reading data dimension from file\n");
            return ERROR;
        }
        n++;
    }
    if(n != set->n){
        fprintf(stderr,"Error reading data rows from file\n");
        return ERROR;
    }
    return SUCCESS;
}
// data_owner对于自己持有的每一个数据进行加密，分散到三方上面去
RESULT drq_encrypt_data_owner(drq_data_owner * owner){
    // 暂时不需要加密
    return SUCCESS;
}
// 销毁data_set
RESULT drq_free_data_set(drq_data_set * set){
    // 销毁data_set
    int n = set->n;
    int d = set->d;
    for(int i = 0 ; i < d ; ++i){
        for(int j = 0 ; j < n ; j++){
            free(set->owners[i]->units[j]);
        }
        free(set->owners[i]->units);
        free(set->owners[i]->query_range);
        delete set->owners[i]->query_res;

    }
    free(set->owners);
    BN_CTX_free(set->ctx);
    return SUCCESS;
}

static RESULT query_self(drq_data_owner * owner){
    int n  = owner->n;
    BIGNUM * left = owner->query_range[0];
    BIGNUM * right = owner->query_range[1];
    auto ve = owner->query_res;
    for(int i = 0 ; i < n ; ++i){
        BIGNUM * unit = owner->units[i]->de_val;
        // 判断 unit 是否在 [left, right] 范围内
        if (BN_cmp(unit, left) >= 0 && BN_cmp(unit, right) <= 0) {
            ve->push_back(owner->units[i]->id);  // 如果在范围内，将其添加到 query_res 中
        }
    }

    return SUCCESS;
}
// 发送通信每个data_owner开始自查
RESULT drq_notify_do_query(drq_data_set * set){
    // 这个时候已经将范围提供给了每一个data_owner
    int d = set->d;
    for(int i = 0 ; i < d; ++i){
        // 自查之后结果存储到vector之中
        query_self(set->owners[i]);
    }
    return SUCCESS;
}

// 进行隐私集合求交
RESULT drq_PSI(drq_data_owner * res,drq_data_owner * a,drq_data_owner * b){

}