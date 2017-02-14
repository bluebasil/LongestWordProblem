/*
Finding longest valid word in a string in linear time

Elijah Moreau-Arnott

Please be aware that I made this in 3 hours... there may be spelling mistakes...
I would perfect it more (I know a good impression on an imployer is a good thing) 
but unfortunatly I have to write a bio essay and finish my SE Quality Assurance assignment

***********************************/
#include <iostream>
#include <string>
#include <stdlib.h>

using namespace std;

#define C 0
#define I 1
#define K 2
#define L 3
#define P 4
#define S 5
#define T 6
#define Y 7

/*We will use a subset of the english alphabet containing the letetrs
{C,I,K,L,P,S,T,Y}
and a subset of the english dictionary containing the words
{"clip", "clips", "lip", "lips", "lipstick", "stick", "sticky", "tic", "tick", "i", "sick", "slip", "slips"}
*/

const char alphabet[] = {'c','i','k','l','p','s','t','y'};
const int alphabetLength = 8;

//global final variables
string longestWord;
int ofLength;

struct letter{
	letter* next[alphabetLength];
	int level;
	bool done;

	letter(int level,bool wholeWord): level(level), done(wholeWord){
		for(int i=0;i<alphabetLength;i++){
			next[i] = NULL;
		}
	}

};

int asciiToAlphabet(int charCode){
	switch(charCode){
		case 67://C
			return 0;
		case 73://I
			return 1;
		case 75://K
			return 2;
		case 76://L
			return 3;
		case 80://P
			return 4;
		case 83://S
			return 5;
		case 84://T
			return 6;
		case 89://Y
			return 7;
		default:
			cerr << endl << "Error: Letter not in alphabet!" << endl;
			exit(1);
	}
}

void iterateAndInitialize(letter* node, letter* start, int hi){
	for(int i=0;i<alphabetLength;i++){
		if( node->next[i] == NULL ){
			node->next[i] = start->next[i];
		}
		else{
			iterateAndInitialize(node->next[i], start, ++hi);
		}
	}
}

void assembleDictionary(letter** head){
	letter* start = new letter(0,true);
	*head = start;
	
	start->next[C] = new letter(1,false);
	start->next[C]->next[L] = new letter(2,false);
	start->next[C]->next[L]->next[I] = new letter(3,false);
	start->next[C]->next[L]->next[I]->next[P] = new letter(4,true);
	start->next[C]->next[L]->next[I]->next[P]->next[S] = new letter(5,true);

	start->next[L] = new letter(1,false);
	start->next[L]->next[I] = new letter(2,false);
	start->next[L]->next[I]->next[P] = new letter(3,true);
	start->next[L]->next[I]->next[P]->next[S] = new letter(4,true);
	start->next[L]->next[I]->next[P]->next[S]->next[T] = new letter(5,false);
	start->next[L]->next[I]->next[P]->next[S]->next[T]->next[I] = new letter(6,false);
	start->next[L]->next[I]->next[P]->next[S]->next[T]->next[I]->next[C] = new letter(7,false);
	start->next[L]->next[I]->next[P]->next[S]->next[T]->next[I]->next[C]->next[K] = new letter(8,true);

	start->next[S] = new letter(1,false);
	start->next[S]->next[T] = new letter(2,false);
	start->next[S]->next[T]->next[I] = new letter(3,true);
	start->next[S]->next[T]->next[I]->next[C] = new letter(4,false);
	start->next[S]->next[T]->next[I]->next[C]->next[K] = new letter(5,true);
	start->next[S]->next[T]->next[I]->next[C]->next[K]->next[Y] = new letter(6,true);

	start->next[T] = new letter(1,false);
	start->next[T]->next[I] = new letter(2,false);
	start->next[T]->next[I]->next[C] = new letter(3,true);
	start->next[T]->next[I]->next[C]->next[K] = new letter(4,true);

	//added a couple words for testing
	start->next[S]->next[L] = new letter(2,false);
	start->next[S]->next[L]->next[I] = new letter(3,false);
	start->next[S]->next[L]->next[I]->next[P] = new letter(4,true);
	start->next[S]->next[L]->next[I]->next[P]->next[S] = new letter(5,true);

	start->next[S]->next[I] = new letter(2,false);
	start->next[S]->next[I]->next[C] = new letter(3,false);
	start->next[S]->next[I]->next[C]->next[K] = new letter(4,true);
	//now we have tree'd dictionary..what we may expect in isWord()


	//create all start nodes
	start->next[I] = new letter(1,true);
	start->next[K] = new letter(1,false);
	start->next[P] = new letter(1,false);
	start->next[Y] = new letter(1,false);

	//Now we link, which is the special part
	//set all null links back to the start, so that there are no null links
	iterateAndInitialize(start, start, 0);


	//now add some subset linking, this is dictionary dependant but could be automated
	//
	start->next[L]->next[I]->next[P]->next[S]->next[T]->next[I]->next[C]->next[K]->next[Y] = start->next[S]->next[T]->next[I]->next[C]->next[K]->next[Y];
	start->next[C]->next[L]->next[I]->next[P]->next[S]->next[T] = start->next[L]->next[I]->next[P]->next[S]->next[T];
	start->next[S]->next[L]->next[I]->next[P]->next[S]->next[T] = start->next[S]->next[T];
	start->next[S]->next[I]->next[C]->next[L] = start->next[C]->next[L];
	start->next[S]->next[L]->next[I]->next[P]->next[S]->next[I] = start->next[S]->next[I];
	start->next[C]->next[L]->next[I]->next[P]->next[S]->next[I] = start->next[S]->next[I];
	start->next[L]->next[I]->next[P]->next[S]->next[I] = start->next[S]->next[I];
	start->next[L]->next[I]->next[P]->next[S]->next[L] = start->next[S]->next[L];

}


void findString(string making, string full, letter* dictionary){
	cout << making << "|" << full << endl;
	
	
	if(dictionary->done){
		if(making.length() != dictionary->level){
			making.erase(making.begin(),making.begin()+making.length()-dictionary->level);
		}
		cout << "Word Found = " << making << " of length " << dictionary->level << endl;
		if(dictionary->level > ofLength){
			longestWord = making;
			ofLength = dictionary->level;
		}
	}
	
	if(full.length() == 0)
	{
		return;
	}
	char first = full[0];
	making.push_back(full[0]);
	full.erase(full.begin());

	findString(making,full,dictionary->next[asciiToAlphabet(first)]);
}

int main () {
	longestWord = "";
	ofLength = 0;

	letter* dictionary;
	assembleDictionary(&dictionary);
	//string use = "ITICSLIPSICKT";
	string use = "LIPSLIPS";
	findString("", use, dictionary);

	cout << "*******" << endl << "The longest word is " << longestWord << " which is of length " << ofLength << endl;
  	return 0;
}
