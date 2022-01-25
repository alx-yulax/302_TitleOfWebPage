#include <iostream>
#include <cpr/cpr.h>

void findH(std::string const text) {
    std::string::size_type n_start, n_finish = 0;
    for (int i = 1; i < 3; ++i) {
        std::string h = "h" + std::to_string(i);
        std::cout << h << ":" << std::endl;
        do {
            n_start = text.find("<" + h, n_finish);
            if (n_start != std::string::npos) {
                n_finish = text.find("</" + h + ">", n_start);
                if (n_finish != std::string::npos) {
                    n_start = text.rfind(">", n_finish - 1);
                    std::cout << text.substr(n_start + 1, n_finish - n_start - 1) << std::endl;
                }
            }
        } while (n_start != std::string::npos);
    }

}

int main() {
    cpr::Response r = cpr::Get(cpr::Url{"https://zetcode.com/cpp/string/"},
                               cpr::Header{{"accept", "text/html"}});
    if (r.status_code == 200) {
        findH(r.text);
    } else {
        std::cout << "Something wrong";
        return 1;
    }

    return 0;
}
