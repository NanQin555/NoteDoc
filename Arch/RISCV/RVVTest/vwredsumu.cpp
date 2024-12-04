#include <riscv_vector.h>
#include <stdio.h>


int main() {
    const uint8_t data[] = {255, 128, 64, 32};
    uint16_t result;

    size_t vl = __riscv_vsetvl_e8m1(4); 
    vuint8m1_t vec_u8 = __riscv_vle8_v_u8m1(data, vl);  
    vuint16m1_t vec_u16_zero = __riscv_vmv_v_x_u16m1(0, vl);
    vuint16m1_t vec_u16 = __riscv_vwredsumu_vs_u8m1_u16m1(vec_u8, vec_u16_zero, vl);
    __riscv_vse16_v_u16m1(&result, vec_u16, vl);

    printf("Result = %u\n", result);
    
    return 0;
}