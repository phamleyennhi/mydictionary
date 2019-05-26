#include "binarySearch.h"
#include<vector>
#include<iostream>
using namespace std;

void binarySearch(vector<string>* data, string word, int left, int right, int comparisons, int number, int pos, int type){
	//type1: case 1 with one full word, type 2: case 2 with *, type 3: case 3 with '?'


	//Check for the correctness of the input range (if input range is <0, word has not been found)
	if (right < left){
		cout << "Word not found." << endl;
		return;
	}

	//Find the middle point in dataset
	int mid = (left+right)/2;

	//Check if the middle element matches with the query word/prefix.
	if (word.substr(0,pos) == data->at(mid).substr(0,pos)){
		
		//case 1 when the seach was performed for an entire word
		if (type == 1){
			cout << "Word found!" << endl;
			cout << comparisons << " word comparisons carried out." << endl;

		}

		//case 2 and case 3
		else {
			//We find all the words that contain the searched prefix (in case 2 the part before the '*', in case 3 the part before the '?')
			//Performed by running through 2 while loops to the left and the right of mid (Data is sorted, so the words with the same prefix are grouped together)
			int tmp1 = mid;
			while (tmp1 > 0){
				//Move left
				--tmp1;
				if (word.substr(0,pos) != data->at(tmp1).substr(0,pos)){
					//If the required prefix has changed, back off and stop
					++tmp1;
					break;
				}
			}
			int tmp2 = mid;
			while (tmp2 < data->size()-1){
				//Move right
				++tmp2;
				if (word.substr(0,pos) != data->at(tmp2).substr(0,pos)){
					//If the required prefix has changed, back off and stop
					--tmp2;
					break;
				}
			}

			//For queries of type 2, we compare tmp1+number and tmp2+1 to find the number of words to ouput.
			if(type == 2){
				int num = min(tmp1 + number, tmp2+1);

				//Output data
				cout << num-tmp1 << " matches found!" << endl;
				for (int i = tmp1; i < num; ++i){
					cout << data->at(i) << endl;
				}
				cout << comparisons << " word comparisons carried out." << endl;
			} 

			//For queries of type 3, we continue to search for the word the match the postfix through a for loop in the range (tmp1, tmp2) and increase num every time we find the match. 
			//Then we find num = min(num, number) and output the required matching words with the number of comparisons.
			else if(type == 3){

				int num = 0;
				int flag = false;

				//Looking for matching words
				for (int i = tmp1; i <= tmp2; ++i){
					if (data->at(i).length() > pos && word.substr(0,pos) == data->at(i).substr(0,pos) && word.substr(pos+1, string::npos) == data->at(i).substr(pos+1, string::npos)){
						//Counting matches
						++num;
					}
					++comparisons;
				}

				//Find the number of words to output
				num = min(num, number);

				//Output data
				cout << num << " matches found!" << endl;
				for (int i = tmp1; i <= tmp2; ++i){
					if (data->at(i).length() > pos && word.substr(0,pos) == data->at(i).substr(0,pos) && word.substr(pos+1, string::npos) == data->at(i).substr(pos+1, string::npos) && num > 0){
						cout << data->at(i) << endl;
						num--;
					}
				}
				cout << comparisons << " word comparisons executed." << endl;
			}
		}

	}
	//if the word/prefix > mid, we call the function on the range (mid+1, right) because the dictionary is sorted.
	else if (word.substr(0, pos) > data->at(mid).substr(0, pos)){
		binarySearch(data, word, mid+1, right, comparisons+1, number, pos, type);
	}
	//if the word/prefix < mid, we call the function on the range (left, mid-1) because the dictionary is sorted.
	else{
		binarySearch(data, word, left, mid-1, comparisons+1, number, pos, type);
	}

	return;	
}
