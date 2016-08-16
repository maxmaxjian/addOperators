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
            vector<string> temp;
            temp.push_back(num.substr(0, i));
            int curr = stoi(temp.back());
            temp = addOpRecurr(num, curr, i, target, temp);
            for (auto str : temp)
                result.push_back(str);
        }

        return result;
    }

  private:
    vector<string> addOpRecurr(string num, int curr_val, size_t pos, int target, const vector<string> & expr)
    {
        vector<string> result;
        if (pos == num.length()) {
            if (curr_val == target)
                result = expr;
            else
                return result;
        }
        else {
            if (pos < num.length()) {
                for (size_t i = 1; i+pos <= num.length(); i++) {
                    int opd = stoi(num.substr(pos, i));
                    if (opd && num[pos] == '0')
                        continue;
                    if (i+pos <= num.length()) {
                        vector<string> temp1, tmp1;
                        for (auto str : expr) {
                            str.append("+");
                            str.append(std::to_string(opd));
                            temp1.push_back(str);
                        }
                        tmp1 = addOpRecurr(num, opd, pos+i, target-curr_val, temp1);
                        for (auto str : tmp1)
                            result.push_back(str);

                        vector<string> temp2, tmp2;
                        for (auto str : expr) {
                            str.append("-");
                            str.append(std::to_string(opd));
                            temp2.push_back(str);
                        }
                        tmp2 = addOpRecurr(num, -opd, pos+i, target-curr_val, temp2);
                        for (auto str : tmp2)
                            result.push_back(str);

                        vector<string> temp3, tmp3;
                        for (auto str : expr) {
                            str.append("*");
                            str.append(std::to_string(opd));
                            temp3.push_back(str);
                        }
                        tmp3 = addOpRecurr(num, opd*curr_val, pos+i, target, temp3);
                        for (auto str : tmp3)
                            result.push_back(str);
                    }
                }    
            }
        }
        return result;
    }
};

int main()
{
    // string numStr{"2323456"};
    // int target = 20;
    string numStr{"2435345768"};
    int target = 987;

    solution soln;
    auto vec = soln.addOperators(numStr, target);

    std::cout << "All possible expressions are:\n";
    for (auto str : vec)
        std::cout << str << std::endl;

    return 0;
}
