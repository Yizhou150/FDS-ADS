We first randomly generate the result of a hash table as the input of the program, then put the program’s results into the hash table again, and compare the results of the two hash tables to check the correctness of the program.
The number in the file name is the order in which our program runs.
Firstly we run the file"1-GenerateRandomHashResult.exe" to get the "HashResult_1.out".
Next we run the file"2-GenerateNewHashInput.exe" to get the "HashInput.out".
Then we run the file"3-GenerateNewHashResult.exe" to get the "HashResult_2.out".
Finally, we compare "HashResult_1" and "HashResult_2" to  validate the correctness of the program.
To make it simple, you just need to click"compare.exe", program will automatically generate data and compare them.
If you want to change the "TableSize" and "Number of Digits", you right-click the file "input.in" and click open with, then select the program from a list, then select notepad. Then in the notepad, you can change the TableSize and the Number of Digits.(Number of Digits <=TableSize)
The first digit---->Number of Digits (How many number in the table)
The second digit---->TableSize
