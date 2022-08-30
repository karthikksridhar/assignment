#include <iostream>
#include <string>
#include <algorithm>
#include <fstream>
#include <vector>
#include <iterator>
#include <sstream>
#include <unordered_map>
#include <map>
#include <iomanip>

using namespace std;

class ConcordanceTest {

private:
	string input_file;
	string result_file;
	stringstream file_contents;
	map <string, vector<unsigned int>> wordsMap;
public:
	ConcordanceTest(string file_name) {
		input_file = file_name;	
		result_file = "Concordance_" + input_file;
	}

	void runConcordanceTest();
	bool readFileContents();
	void generateConcordance();
	void printResults();
};

/**********************************************************

Function    : runConcordanceTest

Description : This method triggers the concordance test
	      based on the input file "input_file" and 
	      prints the result to "result_file"

***********************************************************/

void ConcordanceTest :: runConcordanceTest() {
	if (readFileContents())
	{
		cout << " Read File contents OK! " << endl;
		generateConcordance();
		printResults();
	} else {
		cout<<" Unable to read File Contents. Exiting! "<<endl;
		exit(1);
	}
}

/**********************************************************

Function    : readFileContents

Description : This method reads the input_file and stores 
              the file contents in class member file_contents
	      for further processing 

Returns	    : true  - if file was read successfully
              false - if file not exist/failed to open input file

***********************************************************/
bool ConcordanceTest :: readFileContents() 
{
	ifstream inFile;

	cout << " Read input file : " << input_file << endl;
	inFile.open(input_file);
	if (inFile.fail()) {
		cout << " Error Opening input File: " << input_file << endl;
		return false;
	}

	file_contents << inFile.rdbuf();
	inFile.close();
	return true;
}

/************************************************************************

Function    : generateConcordance

Description : This member function generates the actual concordance
              results based on the file contents read in class 
	      member file_contents and stores the result in class member
              wordsMap

*************************************************************************/
void ConcordanceTest :: generateConcordance() {

	string	word;
	/* Predefined set of abbrList to handle corner cases and 
	   abbreviations in the text file and not treat them as 
	   sentence completion */
	vector <string> abbrList = {"i.e.", "e.g.", "mr.", "mrs.",
				    "est.", "ms.", "dr.", "jr.",
				    "st.", "inc.", "co."};
	bool	isSentenceComplete = false;
	int 	sentenceCount = 1;
	bool 	isWordAbbr;

	cout << " Generating concordance " << endl;
	while (file_contents >> word) {
		if ( isSentenceComplete ) {
			sentenceCount++;
			isSentenceComplete = false;
		}

		// Convert all words to lowercase 

		transform(word.begin(), word.end(), word.begin(), ::tolower);

		for (int i = 0, len = word.size(); i < len; i++) {

			if (ispunct(word[i])) {
				isWordAbbr = find(abbrList.begin(), abbrList.end(), word) != abbrList.end();

				if (isWordAbbr) {
					/* If abbreviation just add to map */
					break;
				} else if (word[i] != '-' && 
					(word[i] == '.' || word[i] == '?' ||
					 word[i] == '!')) {
					/* Assume '.' '!' and '?' as 
					sentence completion characters */
					isSentenceComplete = true; 
				}
				word.erase(i--, 1);
				len = word.size();
			}
		}
		wordsMap[word].push_back(sentenceCount);
	}
	cout << " Finished Concordance generation " << endl;
}

/************************************************************************

Function    : printResults

Description : This member function prints the output generated to a file 
              result_file as pointed by the class member

*************************************************************************/
void ConcordanceTest :: printResults()
{
	int count = 1;
	ofstream outFile;
	outFile.open(result_file);

	for (pair<string, vector<unsigned>> w : wordsMap)
	{
		int firstOcc = 0;
		outFile << std::setw(10);
		outFile << w.first << "\t";
		outFile << "{" << w.second.size() << ":";
		for (unsigned location : w.second) {
			if (firstOcc)
				outFile << ",";
			outFile << location;
			firstOcc = 1;
		}
		outFile << "}\n";
	}
	cout << " Success! Concordance results written to " << result_file << endl;

}

/************************************************************************

Function    : main function

Description : Entry point function. main method creates a ConcordanceTest
              object by passing user defined input file name or static
	      predefined file "input.txt" and invokes the runConcordanceTest
	      method

*************************************************************************/
int main(int argc, char *argv[])
{
	cout << " Run Concordance Test " << endl;
	ConcordanceTest Test(argv[1] ? argv[1] : "input.txt");
	Test.runConcordanceTest();
	cout << " Exiting Concordance Test " << endl;
	return 0;
}
