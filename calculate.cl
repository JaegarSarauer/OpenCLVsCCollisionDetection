__kernel void calculate(__global float4* data,
                        __global int* group_result) {

    uint global_addr = get_global_id(0) * 2;
    uint local_size = get_local_size(0) * 2;

    if (get_local_id(0) == 0) {
        for(uint i = 0; i < local_size; i++) {
            float4 me = data[global_addr + i];
            
            group_result[global_addr + i] = -1;

            for(uint j = 0; j < get_global_size(0) * 2; j++) {
                if (global_addr + i != j) {
                    float4 you = data[j];

                    if (sqrt((you.x - me.x) * (you.x - me.x) + (you.y - me.y) * (you.y - me.y)) <= (you.z + me.z)) {
                        group_result[global_addr + i] = j;
                    }
                }
            }    
        }
    }
}