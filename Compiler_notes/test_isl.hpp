#include <iostream>
#include <isl/ctx.h>
#include <isl/val.h>
#include <isl/id.h>
#include <isl/space.h>
#include <isl/set.h>
#include <isl/map.h>
#include <isl/union_set.h>
#include <isl/union_map.h>
#include <isl/printer.h>
using namespace std;
class Test {
public:
    void test_isl() {
        test_isl_ctx();
        test_isl_bool();
        test_isl_val();
        test_isl_id();
        test_isl_space();
        test_isl_set_map();
        test_isl_printer();
    }
    void test_isl_ctx() {
        isl_ctx* ctx = isl_ctx_alloc();
        cout << "isl_ctx_alloc(): " << ctx << endl;
        isl_ctx_set_max_operations(ctx, (unsigned long) 10);
        cout << "isl_ctx_get_max_operations(ctx): " << isl_ctx_get_max_operations(ctx) << endl;
        isl_ctx_free(ctx);
        cout << endl;
    }

    void test_isl_bool() {
        // isl_bool_true
        cout << "isl_bool_ok(1): " << isl_bool_ok(1) << endl;
        // isl_bool_false
        isl_bool result =  isl_bool_ok(0);
        cout << "isl_bool_ok(0): " << result << endl;

        cout << "isl_bool_not(result)" << isl_bool_not(result) << endl;
        
        cout << endl;
    }

    void test_isl_val() {
        isl_ctx* ctx = isl_ctx_alloc();
        isl_val* val = isl_val_zero(ctx);
        cout << "isl_val_zero(ctx): " << val << endl;
        
        isl_val* copy = isl_val_copy(val);
        cout << "isl_val_copy(val)" << copy << endl;

        isl_val_free(val);
        isl_val_free(copy);
        isl_ctx_free(ctx);
        cout << endl;
    }

    void test_isl_id() {
        isl_ctx* ctx1 = isl_ctx_alloc();
        isl_ctx* ctx2 = isl_ctx_alloc();
        isl_id* id1 = isl_id_alloc(ctx1, "ID1", nullptr);
        isl_id* id2 = isl_id_alloc(ctx2, "ID2", nullptr);
        cout << "isl_id_get_name(id1): " << isl_id_get_name(id1) << endl;
        cout << "isl_id_get_name(id2): " << isl_id_get_name(id2) << endl;
        isl_id_free(id1);
        isl_id_free(id2);
        isl_ctx_free(ctx1);
        isl_ctx_free(ctx2);
        cout << endl;
    }

    void test_isl_space() {
        isl_ctx* ctx = isl_ctx_alloc();
        isl_space* space = isl_space_unit(ctx);
        cout << "isl_space_is_params(space): " << isl_space_is_params(space) << endl;
        cout << "isl_space_is_map(space): " << isl_space_is_map(space) << endl;
        cout << "isl_space_is_set(space): " << isl_space_is_set(space) << endl;
        isl_space_free(space);
        isl_ctx_free(ctx);
        cout << endl;
    }

/* isl_basic_set, isl_basic_map,
 * isl_set, isl_map, 
 * isl_union_set, isl_union_map
 */
    void test_isl_set_map() {
        isl_ctx* ctx = isl_ctx_alloc();
        isl_space* space = isl_space_unit(ctx);
        isl_basic_set* b_set = isl_basic_set_empty(space); 
        isl_basic_map* b_map = isl_basic_map_empty(space);
        isl_set* set = isl_set_empty(space);
        isl_map* map = isl_map_empty(space);
        isl_union_set* u_set = isl_union_set_empty(space);
        isl_union_map* u_map = isl_union_map_empty(space);
        isl_basic_set_free(b_set);
        isl_basic_map_free(b_map);
        isl_set_free(set);
        isl_map_free(map);
        isl_union_set_free(u_set);
        isl_union_map_free(u_map);
        isl_space_free(space);
        isl_ctx_free(ctx);
    }

    void test_isl_printer() {
	    isl_ctx *ctx = isl_ctx_alloc();
	    isl_basic_set *bset;
	    bset = isl_basic_set_read_from_str(ctx, "[n] -> { [i] : exists (a = [i/10] : 0 <= i and i <= n and i - 10 a <= 6) }");
	    char *out = isl_basic_set_to_str(bset);
	    printf("%s\n", out);
    
	    isl_printer *p = isl_printer_to_str(ctx);
	    p =  isl_printer_print_basic_set(p, bset); //表示输出basic_set
	    char *out2 = isl_printer_get_str(p);
	    printf("%s", out2);
    
	    isl_printer_free(p);
	    isl_basic_set_free(bset);
	    isl_ctx_free(ctx);
    }
};