//
// Created by sanda on 27.04.2020.
//
#ifndef ANALYSER_H_
#define ANALYSER_H_
#include <iostream>
#include <string>
#include <fstream>
#include <vector>

struct flags {
    static bool _start_if;
    static bool _start_fun;
};
bool flags::_start_if = false;
bool flags::_start_fun = false;

void analyser(std::string path) {
    std::fstream source;
    std::vector<char> copyif;
    source.open(path);
    if (!source.is_open()) {
        throw std::runtime_error("Can't open source file");
    }
    else {
        char prev;
        char symb;
        char nxt;
        while (source.get(symb)) {
            switch (symb)
            {
                case '\'': {
                    source.get(nxt);
                    while (nxt != '\'' || symb == '\\') {
                        std::cout << symb;
                        symb = nxt;
                        source.get(nxt);
                    }
                    std::cout << symb;
                    std::cout << nxt;
                    break;
                }
                case '\"': {
                    source.get(nxt);
                    while (nxt != '\"' || symb == '\\') {
                        std::cout << symb;
                        symb = nxt;
                        source.get(nxt);
                    }
                    std::cout << symb;
                    std::cout << nxt;
                    break;
                }
                case '#': {
                    while (symb != '\n') {
                        source.get(symb);
                    }
                    std::cout << symb;
                    break;
                }
                case '/': {
                    source.get(nxt);
                    if (nxt == '*') {
                        while (symb != '*' || nxt != '/') {
                            symb = nxt;
                            source.get(nxt);
                        }
                    }
                    else
                    if (nxt == '/') {
                        symb = nxt;
                        while (symb != '\n') {
                            source.get(symb);
                        }
                        std::cout << symb;
                    }
                    break;
                }
                case ';': {
                    std::cout << ';';
                    if (flags::_start_if) {
                        std::cout << "\n\t}\n";
                        flags::_start_if = !flags::_start_if;
                    }
                    break;
                }
                case ')': {
                    std::cout << ')';
                    source.get(symb);
                    std::cout << symb;
                    while (symb == ' ' || symb == '\n' || symb == '\t' || symb == ')') {
                        source.get(symb);
                        std::cout << symb;
                    }
                    if (symb == '{') {
                        std::cout << "\"--check point, please--\"";
                    }
                    break;
                }
                case 's': {
                    std::cout << 's';
                    const char* word = "switch";
                    if (prev == ' ' || prev == '\t' || prev == '\n' || prev == '}' || prev == ';')
                        for (int i = 0; i < 5; ++i) {

                        }
                    break;
                }
                case 'i': {
                    source.get(nxt);
                    std::cout << symb << nxt;
                    if (nxt == 'f') {
                        source.get(symb);
                        if ((prev == ' ' || prev == '\n' || prev == '\t' || prev == '{' || prev == '}' || prev == ';') && (symb == ' ' || symb == '(' || symb == '\n' || symb == '\t')) {
                            flags::_start_if = true;
                            std::cout << " (";
                            while (symb != '(')
                            {
                                source.get(symb);
                            }
                            source.get(symb);
                            int cnt = 0;
                            while (symb != ')' || cnt != 0) {
                                if (symb == '(')
                                    ++cnt;
                                if (symb == ')')
                                    --cnt;
                                if (symb != '\n' && symb != '\t') {
                                    copyif.push_back(symb);
                                    std::cout << symb;
                                }
                                source.get(symb);
                            }
                            std::cout << ") ";
                            source.get(symb);
                            while (symb == ' ' || symb == '\n' || symb == '\t') {
                                source.get(symb);
                            }
                            cnt = 0;
                            if (symb != '{' && symb != ';') {
                                std::cout << "{\n\t";
                            }
                            std::cout << symb;
                            //std::cout  << '\t'<< "if ";
                            /*for (int i = 0; i < copyif.size(); ++i) {
                                std::cout << copyif[i];
                            }*/
                        }
                    }
                    break;
                }
                default:
                    std::cout << symb;
                    break;
            }
            prev = symb;
        }
    }


    source.close();
}
#endif
