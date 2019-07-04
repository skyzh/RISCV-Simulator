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
    std::cerr << "Running: " << path << " ... ";
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
    std::cerr << ret_val << " == " << ret_value << "  ";
    std::cerr << pc_cnt << " inst in " << 1000.0 * (std::clock() - c_start) / CLOCKS_PER_SEC << "ms" << std::endl;
    assert(ret_val == ret_value);
    delete session;
}

int main() {
    Session* session = new Session;
    session->load_memory(std::cin);
    while (true) {
        session->tick();
        if (session->memory[0x30004]) {
            break;
        }
    }
    std::cout << (session->rf.read(10) & 0xff) << std::endl;
    delete session;
    return 0;
}
