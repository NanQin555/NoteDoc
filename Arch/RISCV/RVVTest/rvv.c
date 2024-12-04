#include <riscv_vector.h>
#include <stdio.h>

int x[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
int y[10] = {0, 9, 8, 7, 6, 5, 4, 3, 2, 1};
int z[10];

void vec_add_rvv(int* dst, int* lhs, int* rhs, size_t avl) {
    vint32m2_t vlhs, vrhs, vres;
    for (size_t vl; (vl = __riscv_vsetvl_e32m2(avl));avl -= vl, lhs += vl, rhs += vl, dst += vl) {
        vlhs = __riscv_vle32_v_i32m2(lhs, vl);
        vrhs = __riscv_vle32_v_i32m2(rhs, vl);
        vres = __riscv_vadd_vv_i32m2(vlhs, vrhs, vl);
        __riscv_vse32_v_i32m2(dst, vres, vl);
    }
}

int main(int argc, char const* argv[]) {
    vec_add_rvv(z, x, y, 10);
    for (int i = 0; i < 10; ++i) printf("%d ", z[i]);
    printf("\n");
    return 0;
}
