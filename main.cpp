// The demo. Build and run:
//
//     c++ -std=c++17 -O2 -o main main.cpp
//     ./main
//
// `imei.cpp` is the snippet from the reel, generated from the episode. It is INCLUDED rather
// than linked because it is exactly what was on screen — one bare function with no headers of
// its own — so the file you read is byte-for-byte the file you watched.
//
// 490154203237518 is the worked example IMEI references use to explain its check digit. Dial
// *#06# on your own phone to check yours.

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

#include "imei.cpp"

/** A check that survives `-DNDEBUG`: `assert` is compiled out there, and this demo's output
    is a claim, so a failure has to stop it rather than print "verifies" anyway. */
static void require(bool ok, const char* what) {
    if (!ok) {
        cerr << "FAILED: " << what << "\n";
        exit(1);
    }
}

/** What doubling leaves of a digit: lines 6 and 7 of the snippet. */
static int fold(int d) { return d * 2 > 9 ? d * 2 - 9 : d * 2; }

int main() {
    const string imei = "490154203237518";
    const string typo = "409154203237518"; // the reel's catch: the 90 typed as 09

    require(valid(imei.c_str()), "the specimen is valid");
    require(valid(typo.c_str()), "the 90 typed as 09 is still valid");
    cout << imei << " -> valid\n" << typo << " -> still valid\n";

    // Doubling leaves exactly two digits where they were.
    cout << "doubled and folded: ";
    for (int d = 0; d <= 9; ++d) cout << d << "->" << fold(d) << (d < 9 ? "  " : "\n");
    for (int d = 0; d <= 9; ++d) require((fold(d) == d) == (d == 0 || d == 9), "only 0 and 9 are fixed");

    // Every single wrong digit is caught.
    for (size_t i = 0; i < imei.size(); ++i)
        for (char c = '0'; c <= '9'; ++c) {
            if (c == imei[i]) continue;
            string t = imei;
            t[i] = c;
            require(!valid(t.c_str()), "a single wrong digit is caught");
        }
    cout << "every single wrong digit: caught\n";

    // Every swap of two different neighbours is caught, except 0 and 9 — on any number. Each pair
    // is tried at both alignments, so both the left and the right digit get a turn at being doubled.
    for (int a = 0; a <= 9; ++a)
        for (int b = 0; b <= 9; ++b) {
            if (a == b) continue;
            for (int pad = 0; pad < 2; ++pad) {
                string body = string(pad, '0') + char('0' + a) + char('0' + b) + "1234567890";
                body.resize(14, '0');
                string fixed;
                for (char check = '0'; check <= '9'; ++check)
                    if (valid((body + check).c_str())) fixed = body + check;
                string swapped = fixed;
                swap(swapped[pad], swapped[pad + 1]);
                bool slips = valid(swapped.c_str());
                require(slips == ((a == 0 && b == 9) || (a == 9 && b == 0)), "only 09 and 90 slip through");
            }
        }
    cout << "every neighbour swap: caught, except 09 <-> 90\n";
    return 0;
}
