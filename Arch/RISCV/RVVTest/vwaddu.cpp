#include <riscv_vector.h>
#include <stdio.h>

void widen_to_u16(const uint8_t* data, size_t length, uint16_t* result) {
    size_t vl = __riscv_vsetvl_e8m1(length); 
    vuint8m1_t vec_u8 = __riscv_vle8_v_u8m1(data, vl);  

    vuint16m2_t vec_u16_zero = __riscv_vmv_v_x_u16m2(0, vl);
    vuint16m2_t vec_u16 = __riscv_vwaddu_wv_u16m2(vec_u16_zero, vec_u8, vl);

    __riscv_vse16_v_u16m2(result, vec_u16, vl);
}

int main() {
    const uint8_t data[] = {255, 128, 64, 32};
    uint16_t result[4];

    widen_to_u16(data, 4, result);

    for (int i = 0; i < 4; ++i) {
        printf("Result[%d] = %u\n", i, result[i]);
    }

    return 0;
}