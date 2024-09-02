#include <vector>
#include <string>

#ifndef COMMONS_H
#define COMMONS_H


class Commons {
public:

    static size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);
};

#endif //COMMONS_H
