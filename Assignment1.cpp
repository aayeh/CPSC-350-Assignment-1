#include<iostream>
#include<algorithm>
#include<cmath>
#include<fstream>

using namespace std;
// a function to return a character depending on what index is needed
char getCharFromIndex(int index) {
  char str[] = {'A', 'C', 'T', 'G'};
  return str[index];
}
//main function
int main(int argc, char* argv[]) {
  //creating/opening the file and outputting my name and id number
  ofstream studentfile;

  studentfile.open ("AaronYeh.txt");

  studentfile << "Aaron Yeh" << endl;

  studentfile << "2311707" << endl;

  while(true) {
    //getting the input file from the line argument
    ifstream myfile;

    myfile.open(argv[1]);

    string line;

    // counts of A, C, T, G
    int counts[4] = {0};

    // counts of biagrams
    int biagramCounts[4][4] = {0};

    // total dna strings
    int dnaCount = 0;

    // total sum of dna strings
    int totalDnaLength = 0;

    double avg, variance, standard_deviation;

    //read each line of the file
    while (getline(myfile, line)) {
      //if the line is empty skip this
      if(line.empty()) {
        continue;
      }

      // convert to uppercase
      transform(line.begin(), line.end(),line.begin(), ::toupper);
      //calculating thisChar
      int thisChar = -1;
      for(int i=0; i<line.size(); i++) {
        if(line.at(i) == 'A') {
          thisChar = 0;
        }
        if(line.at(i) == 'C') {
          thisChar = 1;
        }
        if(line.at(i) == 'T') {
          thisChar = 2;
        }
        if(line.at(i) == 'G') {
          thisChar = 3;
        }
        // increase count of single DNA char
        counts[thisChar] += 1;

        if(i != 0) {
          int lastChar = -1;
          if(line.at(i-1) == 'A') {
            thisChar = 0;
          }
          if(line.at(i-1) == 'C') {
            thisChar = 1;
          }
          if(line.at(i-1) == 'T') {
            thisChar = 2;
          }
          if(line.at(i-1) == 'G') {
            thisChar = 3;
          }
          // increase count of biagram
          biagramCounts[thisChar][lastChar] += 1;
        }
      }
      //calculating the totalDnaLength and increasing dnaCount
      totalDnaLength += line.size();
      dnaCount += 1;
    }
    //closing the file
    myfile.close();
    //calculating average
    avg = totalDnaLength / dnaCount;

    // for finding variance, we need to again read file:
    myfile.open(argv[1]);

    //read each line of the file
    while (getline(myfile, line)) {
      variance += pow(line.size() - avg, 2);
    }
    //calculate variance
    variance = variance / dnaCount;
    //calculate standard_deviation
    standard_deviation = sqrt(variance);

    //output
    studentfile << "The sum is " << totalDnaLength << endl;
    studentfile << "The count is " << dnaCount << endl;
    studentfile << "The average is " << avg << endl;
    studentfile << "The variance is " << variance << endl;
    studentfile << "The Standard Deviation is: " << standard_deviation << endl;

    //printing the counts of A, C, T, G to the studentfile
    for(int i=0; i<4; i++) {
      if(counts[i] != 0) {
        studentfile << getCharFromIndex(i) << ": " << counts[i] << endl;
      }
    }

    //printing the biagramCounts
    for(int i=0; i<4; i++) {
      for(int j=0; j<4; j++) {
        if(biagramCounts[i][j] != 0) {
          studentfile << getCharFromIndex(i) << getCharFromIndex(j);
          studentfile << ": " << biagramCounts[i][j] << endl;
        }
      }
    }
    //ask the user if they want to go again
    char input;
    cout << "Finished!" << endl;
    cout << "Do you want to process another list(y/n) ?" << endl;
    cin >> input;
    input = toupper(input);
    if(input == 'N') {
      break;
    }

  }
  return 0;

}
