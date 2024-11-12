
#include <openssl/bn.h>
#include "cstdio"
#include "iostream"
#include "drq_operation.h"
#include "drq_data_structure.h"
void printfTime(char* desc,clock_t start) {
    double cpu_time_used = ((double)(clock() - start)) / CLOCKS_PER_SEC;

    printf("%s used: %f seconds\n",desc, cpu_time_used);
}
int main() {

    clock_t start, end;
    start = clock();
	// 写测试类
	drq_data_set set;
    init_algo(&set, "/root/heqi/encryption_algorithm/distributed_range_query/data/data.txt");
    printfTime("init",start);
    start = clock();
	query_algo(&set, "/root/heqi/encryption_algorithm/distributed_range_query/data/range.txt", "/root/heqi/encryption_algorithm/distributed_range_query/data/result.txt");
    printfTime("query",start);
}