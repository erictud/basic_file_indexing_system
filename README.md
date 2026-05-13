# Tema 2 - SDA - Tudorica Eric Emanuel 313CC
## General description of the project
This project simulates a simple indexing file system, where a file will be stored based on its name, a relevance score and a list of keywords. The projects has multiple features, which enable the user to add, delete and find files based on certains crieteria.

## Implementation
The role of the project is to master working with data structures such as linked lists, heaps and tries (prefix trees). We use them as such: 
we store the name and relevance score in a double linked list which enable fast insertions and deletions.
We also store the keywords in a trie, where in every last letter node of a keyword we have a list of refrences to the nodes in the double linked list.
In order to find files based on a priority, we put them in a heap based on the relevance scores

### List of features 
* add file (ADD)
* delete file (DEL)
* add keyword to file (ADDKW)
* delete keyword from file (DELKW)
* find all files ref by a keyword (FIND)
* K most relevant files with a keyword (TOPK)
* print all keywords (PRINT)

## Features descriptions
#### ADD file
This operation enables storing files based on the name, a relevance score and a list of keywords. Firstly, we store the names and relevance score in the __fileSystemList__ which is a double linked list. We store the keywords in a trie (known as a prefix tree), where in every terminal node for a keyword we have a double linked list to the refrences of the files. Multiple files can share a keyword. By using the trie we facilitate searching for a word in O(logn) times which presents a big efficiency factor.
#### DEL file
This operation can delete a file based on its name. Subsequently, we also delete all the refrences to the file in the keyword trie. Another important step is cleaning up the trie. After deleting the refrences, there may appear some nodes that dont have a meaning anymore. So we need to delete all the nodes that were part of the now deleted keyword.
#### ADDKW
This option makes possible adding a keyword to a certin file based on its name. The operation consists in adding a new keyword in the trie, where in the last letter node we pass the reffrence to it.
#### DELKW
Enables deleting a keyword from a certain file. It also makes sure to delete the entire keyword if it doesnt point to a file anymore. This operation is done using the same function from the DEL operation.
#### FIND
It shows all the files which start with a certain keyword, this operation being a showcase of the power of the trie. We can search very fast for a number, in aproxiamtely O(logN) time. Based on this operation, we see the power of the trie
#### TOPK
Based on a keyword and a number k, it puts into a max-heap all the refrenced files by the keyword. Priority is determined by the relevance score, and in case of equality by lexographical order. Then it extracts the first k relevant files and prints the names 
#### PRINT
This command is implemented to test the implementation of the trie because it prints all the keywords, the number of referenced files and the name of the files that it references.
#### PREFIX
This option enables printing all the files who have a keyword that starts with the certain prefix. This is the best usecase of the trie in the project, because it showcases the fast speed of searches of words in a trie

## Project structure
The project is structured in multiple module, one for every data structure (linked list, heap, trie) and one file for certain functions specific to the files that the project uses. I tried implmenting the data structures generally, using generic comparision functions that can be defined based on usecase