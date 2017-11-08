__kernel void calculate(__global float* data,
                        __global int* group_result) {

    uint local_addr = get_local_id(0);
    uint global_addr = get_global_id(0);

    for(int i = 0; i < 40000; i++) {
        group_result[local_addr * 40000 + i] = 15.0f;
    }
}