#include <iostream>
#include <vector>
#include <string>

using std::vector;
using std::string;

class solution {
  public:
    vector<string> addOperators(string num, int target) {
        vector<string> result;

        for (size_t i = 1; i < num.length(); i++) {
            result.push_back(num.substr(0, i));
            int curr = stoi(result.back());
            addOpRecurr(num, curr, i, target, result);
        }

        return result;
    }

  private:
    void addOpRecurr(string num, int curr_val, size_t pos, int target, vector<string> & expr)
    {
        if (curr_val == target && pos == num.length())
            return;
        else {
            if (pos < num.length()) {
                for (size_t i = 1; i+pos < num.length(); i++) {
                    int opd = stoi(num.substr(pos, i));
                    vector<string> temp1, temp2, temp3;
                    if (i+pos < num.length()) {
                        for (auto str : expr) {
                            str.append("+");
                            str.append(std::to_string(opd));
                            temp1.push_back(str);
                        }
                        addOpRecurr(num, opd, pos+i, target-curr_val, temp1);

                    
                        for (auto str : expr) {
                            str.append("-");
                            str.append(std::to_string(opd));
                            temp2.push_back(str);
                        }
                        addOpRecurr(num, opd, pos+i, curr_val-target, temp2);


                        for (auto str : expr) {
                            str.append("*");
                            str.append(std::to_string(opd));
                            temp3.push_back(str);
                        }
                        addOpRecurr(num, opd*curr_val, pos+i, target, temp3);

                        expr.clear();
                        for (auto tmp : temp1)
                            expr.push_back(tmp);
                        for (auto tmp : temp2)
                            expr.push_back(tmp);
                        for (auto tmp : temp3)
                            expr.push_back(tmp);
                    }
                }    
            }
        }
    }
};

int main()
{
    string numStr{"123"};
    int target = 6;

    solution soln;
    auto vec = soln.addOperators(numStr, target);

    std::cout << "All possible expressions are:\n";
    for (auto str : vec)
        std::cout << str << std::endl;

    return 0;
}
