# Tema 2 - SDA - Tudorica Eric Emanuel 313CC
## General description of the project
This project written in C implements a basic file indexing system, where it enables storing files based on keywords. 
Using the power of the linked list, trie and heap, we can retrive rapidly files metadata based on keywords, relevance etc.

### List of features 
* add file (ADD)
* delete file (DEL)

## Features descriptions
#### ADD file
We will store files based on the file name, a relevance score and a list of keywords. We can achieve this using the ADD operation. Firstly, we store the names and relevance score in the __fileSystemList__ which is a double linked list. We store the keywords in a trie (known as a prefix tree), where in every terminal node for a keyword we have a double linked list to the refrences of the files. Multiple files can share a keyword. By using the trie we facilitate searching for a word in O(logn) times which presents a big efficiency factor.
#### DEL file
We can delete a file based on its name. Subsequently, we also delete all the refrences to the file in the trie keyword. Anouther important step is cleaning up the trie. After deleting the refrences, there may appear some nodes that dont have a meaning anymore. So we need to delete all the nodes that were part of the now deleted keyword.