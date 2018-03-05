#include <iostream>
#include "../include/pilot_nt_jni.hpp"

using JNI::Pilot_NT_JNI;

int main() {
    Pilot_NT_JNI *pilot = new Pilot_NT_JNI();
    int res = pilot->closeDay();
    delete pilot;
    pilot = 0;

    std::cout << "Result: " << res << std::endl;

    return 0;
}
