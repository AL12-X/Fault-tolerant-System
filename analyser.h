#ifndef ANALYSER_H_
#define ANALYSER_H_
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <stack>

class GreaterHandler {
protected:
    GreaterHandler() : currentLevel(0), currentFunction() {}
    int currentLevel;
    std::string currentFunction;

public:
    void incLevel() {
        ++currentLevel;
    }
    void decLevel() {
        --currentLevel;
    }
    int getLevel() {
        return currentLevel;
    }
};

struct record {
    std::string name;
    int type;
    int level;
    record(std::string _name = "", int _type = 0, int _level = 0) : level(_level), name(_name), type(_type) {}
    record(const record& other) : name(other.name), type(other.type), level(other.level) {}
    record& operator=(const record& other) {
        if (0)
            if (1) {
            }
        int res;
        name = other.name;
        type = other.type;
        level = other.level;
        return *this;
    }
    // TODO:
    /* bool operator==(const record& other) {
         if (name == other.name)
             return (level == other.level);
         return false;
     }
     bool operator!=(const record& other) {
         return !(*this == other);
     }
     bool operator*/
    ~record() {}
};

class WordDetector : public GreaterHandler {
    std::set<record> data;
    std::string buffer;
    bool is_started;
    bool is_ended;
public:
    WordDetector() : GreaterHandler(), is_started(false), data(), buffer(), is_ended(false) {
        // TODO:
        //data.insert(record(" ", 0, 0));
    }
    bool finder(const char& symbol) {
        if (!is_started) {
            if (symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z' || symbol == '_') {
                is_started = true;
                if (!buffer.empty()) {
                    buffer.clear();
                }
                buffer.push_back(symbol);
                return false;
            }
        }
        else {
            if (symbol >= 'A' && symbol <= 'Z' || symbol >= 'a' && symbol <= 'z' || symbol >= '0' && symbol <= '9'
                || symbol == '_') {
                buffer.push_back(symbol);
                return false;
            }
            is_ended = true;
            is_started = false;
        }
        return true;
    }
    record wordHandler(std::map<std::string, int>& key_words) {
        // TODO:
        //std::pair<std::set<record>::iterator, bool> result;
        record result("", -1, 0);
        if (!buffer.empty()) {
            std::map<std::string, int>::iterator iter = key_words.find(buffer);
            if (iter != key_words.end()) {
                result = record(buffer, iter->second, currentLevel + 1);
            }
            else {
                result = record(buffer, 0, currentLevel + 1);
            }
            buffer.clear();
            is_ended = false;
        }
        return result;

    }
    bool status() {
        return is_ended;
    }
    size_t size() {
        return data.size();
    }
    // TODO:
    /*std::string& operator[](size_t num) {
        return data[num].name;
    }*/
};

void setKeyWords(std::map<std::string, int>& key_words) {
    std::ifstream kw("key_words.txt");
    if (!kw.is_open()) {
        throw std::runtime_error("Open key_words.txt fail");
    }
    std::string tmp;
    while (!kw.eof()) {
        tmp.clear();
        std::pair<std::string, int> tmp;
        kw >> tmp.first;
        kw >> tmp.second;
        key_words.insert(tmp);
    }
    kw.close();
}

void analyser(std::istream& source, std::ostream& out) {

    const std::string check(" // CHECKPOINT ");
    char prev;
    char cur;
    bool can_ends = false;
    int string_counter = 0;;
    int symbol_in_string_counter = 0;

    // TODO:
    /*   unsigned short _flags = 0;
       unsigned short _class = 16;
       unsigned short _if = 1;
       unsigned short _else = 2;
       unsigned short _switch = 4;
       unsigned short _while = 8;*/

    std::map<std::string, int> key_words;
    setKeyWords(key_words);

    WordDetector detector;
    record tmp;
    std::string if_condition;

    int block_without_braces = 0;
    int block_with_braces = 0;
    bool ch;
    bool struct_mode = false;
    bool case_mode = false;
    std::stack<int> currentLayer;
    std::stack<int> braces;
    currentLayer.push(block_with_braces);
    while (source.get(cur)) {
        symbol_in_string_counter++;
        if (detector.finder(cur)) {
            if (detector.status()) {
                tmp = detector.wordHandler(key_words);
                if (tmp.type != -1) {
                    ch = false;

                    if (tmp.name == "return" || tmp.name == "break" || tmp.name == "continue") {
                        out << check;
                    }
                    if (tmp.name == "class" || tmp.name == "struct" || tmp.name == "union" || tmp.name == "switch") {
                        struct_mode = true;
                    }
                    if (tmp.name == "case") {
                        case_mode = true;
                    }
                    if (tmp.name == "if" || tmp.name == "switch" || tmp.name == "for" || tmp.name == "while") {
                        while (cur != '(') {
                            prev = cur;
                            source.get(cur);
                        }
                        int counter = 0;
                        prev = cur;
                        if_condition.push_back(cur);
                        source.get(cur);

                        while (cur != ')' || counter > 0) {
                            switch (cur) {
                            case '(': {
                                if_condition.push_back(cur);
                                prev = cur;
                                source.get(cur);
                                ++counter;
                                break;
                            }
                            case ')': {
                                if_condition.push_back(cur);
                                prev = cur;
                                source.get(cur);
                                --counter;
                                break;
                            }
                            case '"': {
                                prev = cur;
                                source.get(cur);
                                while (cur != '"' || (prev == '\\' && !can_ends)) {
                                    if (can_ends)
                                        can_ends = false;
                                    if_condition.push_back(prev);
                                    prev = cur;
                                    source.get(cur);
                                    if (prev == '\\' && cur == '\\') {
                                        can_ends = true;
                                    }
                                }
                                can_ends = false;
                                if_condition.push_back(prev);
                                if_condition.push_back(cur);
                                prev = cur;
                                source.get(cur);
                                break;
                            }
                            case '\'': {
                                prev = cur;
                                source.get(cur);
                                while (cur != '\'' || (prev == '\\' && !can_ends)) {
                                    if_condition.push_back(prev);
                                    prev = cur;
                                    source.get(cur);
                                    if (prev == '\\' && cur == '\\') {
                                        can_ends = true;
                                    }
                                }
                                can_ends = false;
                                if_condition.push_back(prev);
                                if_condition.push_back(cur);
                                prev = cur;
                                source.get(cur);
                                break;
                            }
                            default: {
                                if_condition.push_back(cur);
                                prev = cur;
                                source.get(cur);
                                break;
                            }
                            }
                        }
                        if_condition.push_back(cur);
                        out << tmp.name;
                        ch = true;
                        out << '[' << if_condition << ']';
                        if_condition.clear();
                        source.get(cur);
                        while (cur == '\t' || cur == '\n' || cur == ' ') {
                            source.get(cur);
                        }
                        out << ' ';
                        if (cur != '{') {
                            detector.incLevel();
                            out << " // CHECKPOINT: WBR (start)\n";
                            ++string_counter;
                            int tmp = detector.getLevel();
                            while (tmp-- > 0) {
                                out << "    ";
                            }
                            currentLayer.push(block_with_braces);
                            ++block_without_braces;
                            if (!detector.finder(cur)) {
                                continue;
                            }
                        }
                    }
                    if (!ch)
                        out << tmp.name;
                }
            }
            switch (cur) {
                // TODO:
                /*case ':': {

                    if (case_mode) {
                        source.get(cur);
                        while (cur == '\t' || cur == '\n' || cur == ' ') {
                            source.get(cur);
                        }
                        out << ' ';
                        if (cur != '{') {
                            detector.incLevel();
                            out << " //[CHECKPOINT][WBR][start]\n";
                            int tmp = detector.getLevel();
                            while (tmp-- > 0) {
                                out << "    ";
                            }
                            currentLayer.push(block_with_braces);
                            ++block_without_braces;
                            if (!detector.finder(cur)) {
                                break;
                            }
                        }
                        case_mode = false;
                    }

                }*/
            case '{': {
                detector.incLevel();
                ++block_with_braces;
                if (struct_mode) {
                    braces.push(1);
                    out << cur;
                    struct_mode = false;
                }
                else {
                    braces.push(0);
                    out << cur;
                    out << "/* CHECKPOINT: BR (start) */\n";
                    ++string_counter;
                    int tmp = detector.getLevel();
                    while (tmp-- > 0) {
                        out << "    ";
                    }
                }
                break;
            }

            case '}': {
                detector.decLevel();
                --block_with_braces;
                if (braces.top() == 0) {
                    out << "/* CHECKPOINT: BR (end) */";
                }
                out << cur;
                braces.pop();
                if (block_without_braces && currentLayer.top() == block_with_braces) {
                    out << '\n';
                    ++string_counter;
                    detector.decLevel();
                    int tmp = detector.getLevel();
                    while (tmp-- > 0) {
                        out << "    ";
                    }
                    out << "// CHECKPOINT: WBR (end)\n";
                    ++string_counter;
                    tmp = detector.getLevel();
                    while (tmp-- > 0) {
                        out << "    ";
                    }
                    --block_without_braces;
                    currentLayer.pop();
                }
                break;
            }
            case ';': {
                out << cur;
                if (block_without_braces) {
                    --block_without_braces;
                    detector.decLevel();
                    out << '\n';
                    int tmp = detector.getLevel();
                    while (tmp-- > 0) {
                        out << "    ";
                    }
                    out << "// CHECKPOINT: WBR (end)\n";
                    ++string_counter;
                }
                break;
            }
            case '\n': {
                string_counter++;
                symbol_in_string_counter = 0;
                out << cur;
                break;
            }
            case '\'': {
                prev = cur;
                source.get(cur);
                while (cur != '\'' || (prev == '\\' && !can_ends)) {
                    out << prev;
                    prev = cur;
                    source.get(cur);
                    if (prev == '\\' && cur == '\\') {
                        can_ends = true;
                    }
                }
                can_ends = false;
                out << prev;
                out << cur;
                break;
            }

            // TODO: rewrite this case
            case '"': {
                prev = cur;
                source.get(cur);
                while (cur != '"' || (prev == '\\' && !can_ends)) {
                    if (can_ends)
                        can_ends = false;
                    out << prev;
                    prev = cur;
                    source.get(cur);
                    if (prev == '\\' && cur == '\\') {
                        can_ends = true;
                    }
                }
                can_ends = false;
                out << prev;
                out << cur;
                break;
            }
            case '#': {
                while (cur != '\n' && source.get(cur)) {
                }
                out << "//preprocessor\n";
                string_counter++;
                break;
            }
            case '/': {
                if (prev == '/') {
                    while (cur != '\n' && source.get(cur)) {
                    }
                    out << "//one string comment\n";
                    string_counter++;
                }
                break;
            }
            case '*': {
                if (prev == '/') {
                    out << "/*multiple-line comment";
                    while (cur != '/' || prev != '*') {
                        prev = cur;
                        if (prev == '\n') {
                            string_counter++;
                            out << "\nmultiple-line comment";
                        }
                        source.get(cur);
                    }
                    out << "*/";
                }
                break;
            }
            default: {
                out << cur;
                break;
            }
            }
        }
        prev = cur;
    }
    out << "\n ----- Keywords and identificators ----- \n";
    // TODO:
    /* for (int i = 0; i < detector.size(); ++i) {
         for (int j = 0; j < detector[i].size(); ++j) {
             out << detector[i][j];
         }
         out << std::endl;
     }*/
    out << "\n ----- Number of lines ----- \n";
    out << string_counter;
    out << "\n ----- List of keywords ----- \n";
    for (auto iter : key_words) {
        for (size_t i = 0; i < iter.first.size(); ++i)
            out << iter.first[i];
        out << std::endl;
    }
}
#endif
