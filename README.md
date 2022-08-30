# Concordance Generator
This process generate a concordance, i.e. an alphabetical list of all
word occurrences, labeled with word frequencies

# Bonus
label each word with the sentence numbers in which each occurrence appeared.

## Sample Output 
```
         a      {2:1,1}
       all      {1:1}
alphabetical    {1:1}
        an      {2:1,1}

```
## Libraries used
- N/A

## Assumptions
```
1: '.' '!' '?' considered as sentence completion
2: Predefined set of abbreviation assumed 
3: If user does not provide input file, "input.txt" is default  input file
```

# Local Execution steps
```
Command to build utility
make OR make all

Command to execute
./concordance_test.exe <input_file_name>
E.g. : 
1) ./concordance_test sample.txt

Console Output : 
 Run Concordance Test
 Read input file : sample.txt
 Read File contents OK!
 Generating concordance
 Finished Concordance generation
 Success! Concordance results written to Concordance_sample.txt
 Exiting Concordance Test

Output File Generated :  Concordance_sample.txt


2) ./concordance_test

Console Output :
Run Concordance Test
 Read input file : input.txt
 Read File contents OK!
 Generating concordance
 Finished Concordance generation
 Success! Concordance results written to Concordance_input.txt
 Exiting Concordance Test
 


```
