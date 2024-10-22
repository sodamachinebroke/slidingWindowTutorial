# _**OBSOLETE**_

# Commons

<details>
<summary style="cursor: pointer; user-select: none">Header</summary>

```c++
#include <vector>
#include <string>

#ifndef COMMONS_H
#define COMMONS_H


class Commons {
public:

    static size_t split(const std::string &txt, std::vector<std::string> &strs, char ch);
};

#endif //COMMONS_H
```

</details>

<details>
<summary style="user-select: none; cursor: pointer">Source file</summary>

```c++
#include "header/commons.h"

#include <string>
#include <vector>

size_t Commons::split(const std::string &txt, std::vector<std::string> &strs, char ch) {

    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();

}

```

</details>

## Split

<a name="split"></a>

<details>
<summary style="cursor: pointer; user-select: none;">Full source code</summary>

```c++
size_t Commons::split(const std::string &txt, std::vector<std::string> &strs, char ch) {

    size_t pos = txt.find(ch);
    size_t initialPos = 0;
    strs.clear();

    while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }

    strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

    return strs.size();

}
```

</details>

This function splits a full string into a vector, so it's easier to detect duplicates. It also doesn't really work with
end of sentence marks, but that's not really too important. The important part is to split the string somehow.

### 3 inputs:

- `const std::string &txt` - Input text
- `std::vector<std::string> &strs` - Output vector
- `char ch` - Delimiter
- Return value is `size_t`, which means it returns the length of the output vector

### Initializing values

```c++
size_t pos = txt.find(ch);
size_t initialPos = 0;
strs.clear();
```

# Everything after this is bullshit

### Copying everything to the vector

```c++
while (pos != std::string::npos) {
        strs.push_back(txt.substr(initialPos, pos - initialPos));
        initialPos = pos + 1;

        pos = txt.find(ch, initialPos);
    }
```

It runs until the end of the string (`std::string::npos`) and it adds the substring to the end of the output vector.
Then moves "initialPos" to after "pos". Then sets "pos" to find the next delimiter from "initialPos".

### Finding duplicates

```c++

strs.push_back(txt.substr(initialPos, std::min(pos, txt.size()) - initialPos + 1));

```
