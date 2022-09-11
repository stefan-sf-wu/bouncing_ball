#ifndef Logger_H_
#define Logger_H_

#include <iostream>
#include <vector>

namespace Logger {

void log_state(struct state st) {
    std::string c;
    std::string v;
    c = "[ " + std::to_string(st.position.x) + ' ' +
               std::to_string(st.position.y) + ' ' +
               std::to_string(st.position.z) + 
        " ]";
    v = "[ " + std::to_string(st.velocity.x) + ' ' +
               std::to_string(st.velocity.y) + ' ' +
               std::to_string(st.velocity.z) + 
        " ]";
    std::cout << "coordinate: " << c << "; velocity: " << v << std::endl;
}

} // namespace Logger

#endif // Logger_H_