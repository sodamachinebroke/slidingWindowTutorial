Tömörítő eljárás optimalizálása
Tömörítő eljárások optimalizálási módjainak vizsgálata
Elterjedt tömörítő eljárások összehasonlítása és optimalizálása
Tömörítési hatékonyság javítása párhuzamosítással

A tömörítéshez használt algoritmusok igen elterjedtek, és igen sokféle változatuk van. A dolgozat célja egy olyan
algoritmus kidolgozása és implementálása, amely a meglévő eszközökhöz képest tömörítési arány és/vagy számítási
teljesítmény szempontjából jobb eredményt ad. Ehhez áttekintésre kerülnek az elterjedt tömörítő eljárások (például a
DEFLATE), azok elméleti háttere és a hozzájuk tartozó implementációk. A saját algoritmus implementálására, mérésekre
C++14 programozási nyelv használatával kerül sor.

Párhuzamosítás.
C++14, assembly
Microbenchmarking
Statisztikák, például akár külön a gzip -1 ... -9 opcióira.
Létező implementációk áttekintése, módszeres összehasonlítása: például programozási nyelv, interfész kialakítása,
tömörítési hatékonyság, sebesség, akár kód szintjén is.
Blokkméretre történő optimalizáció.
Áttekintésre kerülnek az elterjedt tömörítő eljárások, azok elméleti háttere és a hozzájuk tartozó implementáció.
Egyaránt vizsgálatra kerül a tömörítési arány és a számítási idő optimalizálása is.
Összehasonlítások főként a DEFLATE algoritmussal.

```c++
// C++ program to encode and decode a string using
// Huffman Coding.
#include
<bits/stdc++.h>

#define
MAX_TREE_HT 256

// to map each character its huffman value
std::map<char, std::string> codes;

// To store the frequency of character of the input data
std::map<char, int> freq;

// A Huffman tree node
struct MinHeapNode {
char data; // One of the input characters
int freq; // Frequency of the character
MinHeapNode *left, *right; // Left and right child

MinHeapNode(char data, int freq) {
left = right = NULL;
this->data = data;
this->freq = freq;
}
};

// utility function for the priority queue
struct compare {
bool operator()(MinHeapNode *l, MinHeapNode *r) {
return (l->freq > r->freq);
}
};

// utility function to print characters along with
// there huffman value
void printCodes(struct MinHeapNode *root, std::string str) {
if (!root)
return;
if (root->data != '$')
std::cout << root->data << ": " << str << "\n";
printCodes(root->left, str + "0");
printCodes(root->right, str + "1");
}

// utility function to store characters along with
// there huffman value in a hash table, here we
// have C++ STL map
void storeCodes(struct MinHeapNode *root, std::string str) {
if (root == NULL)
return;
if (root->data != '$')
codes[root->data] = str;
storeCodes(root->left, str + "0");
storeCodes(root->right, str + "1");
}

// STL priority queue to store heap tree, with respect
// to their heap root node value
std::priority_queue<MinHeapNode *, std::vector<MinHeapNode *>, compare>
minHeap;

// function to build the Huffman tree and store it
// in minHeap
void HuffmanCodes(int size) {
struct MinHeapNode *left, *right, *top;
for (std::map<char, int>::iterator v = freq.begin();
v != freq.end(); v++)
minHeap.push(new MinHeapNode(v->first, v->second));
while (minHeap.size() != 1) {
left = minHeap.top();
minHeap.pop();
right = minHeap.top();
minHeap.pop();
top = new MinHeapNode('$',
left->freq + right->freq);
top->left = left;
top->right = right;
minHeap.push(top);
}
storeCodes(minHeap.top(), "");
}

// utility function to store map each character with its
// frequency in input string
void calcFreq(std::string str, int n) {
for (int i = 0; i < str.size(); i++)
freq[str[i]]++;
}

// function iterates through the encoded string s
// if s[i]=='1' then move to node->right
// if s[i]=='0' then move to node->left
// if leaf node append the node->data to our output string
std::string decode_file(struct MinHeapNode *root, std::string s) {
std::string ans = "";
struct MinHeapNode *curr = root;
for (int i = 0; i < s.size(); i++) {
if (s[i] == '0')
curr = curr->left;
else
curr = curr->right;

// reached leaf node
if (curr->left == NULL and curr->right == NULL) {
ans += curr->data;
curr = root;
}
}
// cout<<ans<<endl;
return ans + '\0';
}

// Driver code
int main() {
//TODO understand this. HOW DOES THIS WORK????? It supposedly makes a Huffman Tree out of something, but aaaaaaaaaaaaaaaaa
std::string str = "AAAABBBCCD";
std::string encodedString, decodedString;
calcFreq(str, str.length());
HuffmanCodes(str.length());
std::cout << "Character With there Frequencies:\n";
for (auto v = codes.begin(); v != codes.end(); v++)
std::cout << v->first << ' ' << v->second << std::endl;

for (auto i: str)
encodedString += codes[i];

std::cout << "\nEncoded Huffman data:\n"
<< encodedString << std::endl;

// Function call
decodedString
= decode_file(minHeap.top(), encodedString);
std::cout << "\nDecoded Huffman Data:\n"
<< decodedString << std::endl;
return 0;
}
```