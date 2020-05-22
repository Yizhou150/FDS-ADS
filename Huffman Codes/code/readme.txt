For Program:
There are three programs.
The first uses queues to generate the Huffman tree and use n^2 enumeration to judge the prefix.
The second uses queues to generate the Huffman tree and use a trie tree to judge the prefix.
The third uses min heap to generate the Huffman tree and use n^2 enumeration to judge the prefix.


For Test:
We have written three programs, the first one is the basic version, the second one is the optimization of judging prefix conflict, and the third one is the optimization of generating Huffman tree. Therefore, we detect the time needed for spanning trees and the time needed to distinguish prefix conflict, respectively.

Method of application:
1. write the n characters and m student submissions in "size.in"
2. follow the order (1-2-3) to test the time of GenerateTree or PrefixConflict.


As for INPUT&OUTPUT

data: input "size.in"   		output "input.in"

GenerateInput: input"input.in"  	output "input4program.in"

GenerateTree:TestForPR1/TestForPR3: input "input4program.in"

Prefix Conflict:TestForPR1/TestForPR2: input "input4program.in"

TestCorrectness: input "input4program.in"