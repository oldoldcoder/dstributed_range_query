#include "openssl/bn.h"
#include "utils.h"
#include "drq_data_structure.h"
#include "drq_operation.h"
#include "sstream"
#include "fstream"
#include "iostream"
using namespace std;
// 初始化查询范围
RESULT drq_init_query_range(query_range * ranges,int d){
    ranges->d = d;
    ranges->range = (BIGNUM *** )malloc(sizeof (BIGNUM **) * d);

    for(int i = 0 ; i < d ; ++i){
        ranges->range[i] = (BIGNUM **) malloc(sizeof (BIGNUM *) * 2);
        ranges->range[i][0] = BN_new();
        ranges->range[i][1] = BN_new();
    }

    return SUCCESS;
}
// 读取查询范围
RESULT drq_read_query_range(query_range * ranges,const char *queryFile){
    ifstream infile(queryFile);
    if (!infile.is_open()) {
        cerr << "Error opening file: " << queryFile << endl;
        return ERROR;
    }
    

    string line;
    for (int i = 0; i < ranges->d; ++i) {
        if (!getline(infile, line)) {
            cerr << "Error reading line " << i+1 << " from file." << endl;
            return ERROR;
        }

        istringstream iss(line);
        string left_str, right_str;

        if (!(iss >> left_str >> right_str)) {
            cerr << "Error parsing line " << i+1 << " from file." << endl;
            return ERROR;
        }
        if (!BN_dec2bn(&ranges->range[i][0], left_str.c_str()) ||
            !BN_dec2bn(&ranges->range[i][1], right_str.c_str())) {
            cerr << "Error converting strings to BIGNUMs on line " << i+1 << "." << endl;
            return ERROR;
        }
    }

    infile.close();
    return SUCCESS;
}
// 将不同维度的查询范围发送过去，获取查询的结果
RESULT drq_send_range2owner(query_range * ranges,drq_data_set * set){
    // 将具体的查询维度分发过去
    int d = ranges->d;
    for(int i = 0 ; i < d ; ++i){
        // 对应的第i个维度的范围发送给对应的数据
        set->owners[i]->query_range = ranges->range[i];
    }
    return SUCCESS;
}
// 释放query_range
RESULT drq_free_query_range(query_range * ranges){
    int d = ranges->d;
    for(int i = 0 ; i < d ; ++i){
        BN_free(ranges->range[i][0]);
        BN_free(ranges->range[i][1]);
        free(ranges->range[i]);
    }
    free(ranges->range);
    return SUCCESS;
}