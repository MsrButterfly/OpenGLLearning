#include <functional>
#include <iostream>
#include <string>
#include <vector>

#include "1_Open_a_window.hpp"
#include "2_Hello_dot_.hpp"
#include "3_First_Triangle.hpp"
#include "4_Shaders.hpp"
#include "5_Uniform_Variables.hpp"
#include "6_Translation_Transformation.hpp"
#include "7_Rotation_Transformation.hpp"
#include "8_Scaling_Transformation.hpp"
#include "9_Interpolation.hpp"

int main(int argc, const char *argv[]) {
    using namespace std;
#define OPT(ns) {ns::title, ns::main}
    const vector<pair<string, function<int(int, const char *[])>>> options = {
        OPT(_1_Open_a_window),
        OPT(_2_Hello_dot_),
        OPT(_3_First_Triangle),
        OPT(_4_Shader),
        OPT(_5_Uniform_Variables),
        OPT(_6_Translation_Transformation),
        OPT(_7_Rotation_Transformation),
        OPT(_8_Scaling_Transformation),
        OPT(_9_Interpolation)
    };
#undef OPT
    cout << "==> Select an option: " << endl;
    for (size_t i = 0; i < options.size(); ++i) {
        cout << i + 1 << ". " << options[i].first << endl;
    }
    size_t n;
    int exitStatus;
    if (cin >> n && n > 0 && n <= options.size()) {
        cout << endl;
        exitStatus = options[n - 1].second(argc, argv);
    }
    return exitStatus;
}
