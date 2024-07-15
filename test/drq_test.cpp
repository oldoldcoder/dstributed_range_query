
#include <openssl/bn.h>
#include "cstdio"
#include "iostream"
#include "drq_operation.h"
#include "drq_data_structure.h"

int main() {
	// 写测试类
	drq_data_set set;
    init_algo(&set, "D:\\study\\code\\ClionProject\\dstributed_range_query\\data\\DRQ_DATA_FILE.txt");
    free_algo(&set);
	query_algo(&set, "D:\\study\\code\\ClionProject\\dstributed_range_query\\data\\DRQ_QUERY_FILE.txt", "D:\\study\\code\\ClionProject\\dstributed_range_query\\data\\DRQ_RES_FILE.txt");

}