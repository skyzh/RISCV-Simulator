#include <iostream>
#include <iomanip>
#include "Session.h"
#include "Pipeline/Fetch.h"
#include "Pipeline/Decode.h"
#include "Pipeline/Execute.h"
#include "Pipeline/MemoryAccess.h"
#include "Pipeline/WriteBack.h"

#include <cassert>

void run_session(const char *path, unsigned ret_value, bool use_hex_parser = false) {
    std::clock_t c_start = std::clock();
    std::clog << " | " << path << " | ";
    Session *session = new Session(false);
    if (use_hex_parser) session->load_hex(path); else session->load_memory(path);
    int pc_cnt = 0;
    while (true) {
        // std::cout << std::endl << std::endl << "Cycle " << pc_cnt << std::endl;
        session->tick();

        // std::cout << std::hex << session->e->e_pc.read() << std::endl;

        ++pc_cnt;

        if (session->memory[0x30004]) {
            break;
        }
    }
    auto ret_val = session->rf.read(10) & 0xff;
    // std::clog << "\t" << ret_val << " == " << ret_value << std::endl;
    std::clog << pc_cnt << " | " << 1000.0 * (std::clock() - c_start) / CLOCKS_PER_SEC << "ms | ";
    /* std::clog << "\t" << pc_cnt << " inst in " << 1000.0 * (std::clock() - c_start) / CLOCKS_PER_SEC << "ms"
              << std::endl; */
    std::clog << (1 - 1.0 * session->s.mis_pred / session->s.branches) * 100.0 << "% | " << std::endl;
    // std::clog << "\t" << session->s.mis_pred << "/" << session->s.branches << "("<< (1 - 1.0 * session->s.mis_pred / session->s.branches) * 100.0 <<"%)" << std::endl;
    assert(ret_val == ret_value);
    delete session;
}

int run_all_tests() {
    run_session("../data/naive.data", 94);
    run_session("../tests/data-hazard-1.hex", 0x1f, true);
    run_session("../tests/data-hazard-2.hex", 0x1f, true);
    run_session("../tests/control-hazard-1.hex", 0x8, true);
    run_session("../tests/control-hazard-2.hex", 0x8, true);
    run_session("../data/array_test1.data", 123);
    run_session("../data/array_test2.data", 43);
    run_session("../data/basicopt1.data", 88);
    run_session("../data/bulgarian.data", 159);
    run_session("../data/expr.data", 58);
    run_session("../data/gcd.data", 178);
    run_session("../data/hanoi.data", 20);
    run_session("../data/lvalue2.data", 175);
    run_session("../data/magic.data", 106);
    run_session("../data/manyarguments.data", 40);
    run_session("../data/multiarray.data", 115);
    run_session("../data/qsort.data", 105);
    run_session("../data/queens.data", 171);
    run_session("../data/statement_test.data", 50);
    run_session("../data/superloop.data", 134);
    run_session("../data/tak.data", 186);
    run_session("../data/pi.data", 137);
    return 0;
}

int main() {
    run_all_tests();
    return 0;
}
