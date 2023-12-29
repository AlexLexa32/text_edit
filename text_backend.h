#pragma GCC optimize("Ofast,unroll-loops,mfma,mavx,mavx2")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("Ofast,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize("unroll-loops")
#pragma GCC optimize("vpt")
#pragma GCC optimize("rename-registers")
#pragma GCC optimize("move-loop-invariants")
#pragma GCC optimize("unswitch-loops")
#pragma GCC optimize(3)
#pragma GCC optimize("O3")
#pragma GCC optimize("inline")
#pragma GCC optimize("-fgcse")
#pragma GCC optimize("-fgcse-lm")
#pragma GCC optimize("-fipa-sra")
#pragma GCC optimize("-ftree-pre")
#pragma GCC optimize("-ftree-vrp")
#pragma GCC optimize("-fpeephole2")
#pragma GCC optimize("-fsched-spec")
#pragma GCC optimize("-falign-jumps")
#pragma GCC optimize("-falign-loops")
#pragma GCC optimize("-falign-labels")
#pragma GCC optimize("-fdevirtualize")
#pragma GCC optimize("-fcaller-saves")
#pragma GCC optimize("-fcrossjumping")
#pragma GCC optimize("-fthread-jumps")
#pragma GCC optimize("-freorder-blocks")
#pragma GCC optimize("-fschedule-insns")
#pragma GCC optimize("inline-functions")
#pragma GCC optimize("-ftree-tail-merge")
#pragma GCC optimize("-fschedule-insns2")
#pragma GCC optimize("-fstrict-aliasing")
#pragma GCC optimize("-falign-functions")
#pragma GCC optimize("-fcse-follow-jumps")
#pragma GCC optimize("-fsched-interblock")
#pragma GCC optimize("-fpartial-inlining")
#pragma GCC optimize("-freorder-functions")
#pragma GCC optimize("-findirect-inlining")
#pragma GCC optimize("-fhoist-adjacent-loads")
#pragma GCC optimize("-frerun-cse-after-loop")
#pragma GCC optimize("inline-small-functions")
#pragma GCC optimize("-finline-small-functions")
#pragma GCC optimize("-ftree-switch-conversion")
#pragma GCC optimize("-foptimize-sibling-calls")
#pragma GCC optimize("-fexpensive-optimizations")
#pragma GCC optimize("inline-functions-called-once")
#pragma GCC optimize("-fdelete-null-pointer-checks")
#pragma once
#ifndef TEXT_EDIT_TEXT_BACKEND_H
#define TEXT_EDIT_TEXT_BACKEND_H
#endif //TEXT_EDIT_TEXT_BACKEND_H

#include <vector>
#include <string>

class Text {
private:
    std::vector<std::string*> lines_;
public:
    Text () {
        lines_ = {};
    }
    ~Text () {
        for (auto elem : lines_) {
            delete elem;
        }
        lines_ = {};
    }
    std::string getLine(int ind) {
        return *lines_[ind];
    }
    void pushLine(int ind, std::string line) {
        lines_.push_back(new std::string);
        for (int i = (int)lines_.size()-1; i > ind; --i) {
            std::swap(lines_[i], lines_[i-1]);
        }
        *lines_[ind] = line;
    }
    void popLine(int ind) {
        for (int i = ind; i < (int)lines_.size(); ++i) {
            std::swap(lines_[i-1], lines_[i]);
        }
        delete lines_.back();
        lines_.pop_back();
    }
    void pushSubstring(int ind_line, int ind_character, std::string subline) {
        std::string str = "";
        str.reserve((int)(*lines_[ind_line]).size() + (int)subline.size());
        for (int i = 0; i < ind_character; ++i) {
            str.push_back((*lines_[ind_line])[i]);
        }
        str += subline;
        for (int i = ind_character; i < (*lines_[ind_line]).size(); ++i) {
            str.push_back((*lines_[ind_line])[i]);
        }
        *lines_[ind_line] = str;
    }
    void replaceCharacte(int ind_line, int ind_character, char ch) {
        (*lines_[ind_line])[ind_character] = ch;
    }
    void replaceSubines(int ind_line, std::string& line, std::string& line2) {
        std::string str = "";
        std::string tmp = "";
        for (char elem : *lines_[ind_line]) {
            if (elem == line[(int)tmp.size()]) {
                tmp += elem;
            } else {
                str += tmp;
                str += elem;
                tmp = "";
            }
            if ((int)tmp.size() == (int)line.size()) {
                str += line2;
                tmp = "";
            }
        }
        str += tmp;
        *lines_[ind_line] = str;
    }
    void replaceSubines(int begin, int end, std::string line, std::string line2) {
        for (int i = begin; i <= end; ++i) {
            replaceSubines(i, line, line2);
        }
    }
    void delZero(int ind) {
        bool flag1 = true, flag2 = false;
        std::string str = "";
        for (auto e : *lines_[ind]) {
            if (e <= '9' && e >= '0') {
                if (flag1) {
                    if (flag1 && e == '0') {
                        flag2 = true;
                        continue;
                    } else {
                        str += e;
                        flag1 = false;
                        flag2 = false;
                    }
                } else {
                    str += e;
                }
            } else {
                if (flag2) {
                    str += '0';
                }
                str += e;
                flag2 = false;
                flag1 = true;
            }
        }
        if (flag1 && flag2) {
            str += "0";
        }
        *lines_[ind] = str;
    }
    void del(int ind1, int ind2) {
        int tmp = 0;
        for (int i = ind1; i <= ind2; ++i) {
            std::string str = "";
            for (auto e : *lines_[i]) {
                if (e == '{') {
                    ++tmp;
                }else if (e == '}') {
                    if (tmp) {
                        --tmp;
                        continue;
                    }
                }
                if (!tmp) {
                    str += e;
                }
            }
            *lines_[i] = str;
        }
    }
    void StarToPlus(int ind1, int ind2) {
        int tmp = 0;
        for (int i = ind1; i <= ind2; ++i) {
            std::string str = "";
            for (auto e : *lines_[i]) {
                if (e == '*') {
                    ++tmp;
                } else {
                    if (tmp == 1) {
                        str += '*';
                    } else if (tmp) {
                        for (int j = 0; j < -~tmp>>1; ++j) {
                            str += '+';
                        }
                    }
                    tmp = 0;
                    str += e;
                }
            }
            if (tmp == 1) {
                str += '*';
            } else if (tmp) {
                for (int j = 0; j < tmp>>1; ++j) {
                    str += '+';
                }
            }
            tmp = 0;
            *lines_[i] = str;
        }
    }
    void NumbersF(int ind1, int ind2) {
        bool flag = true;
        char tmp = '0';
        for (int i = ind1; i <= ind2; ++i) {
            std::string str = "";
            for (auto e : *lines_[i]) {
                if (e <= '9' && e >= tmp) {
                    if (flag) {
                        tmp = e;
                        str += e;
                    }
                } else {
                    tmp = '0';
                    if (e >= '0' && e <= '9') {
                        flag = false;
                        continue;
                    } else {
                        flag = true;
                        str += e;
                    }
                }
            }
            *lines_[i] = str;
        }
    }
    auto size() {
        return lines_.size();
    }
};
