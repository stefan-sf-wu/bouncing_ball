#ifndef LOGGER_H_
#define LOGGER_H_

#include <iostream>
#include <vector>

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



#endif // LOGGER_H_