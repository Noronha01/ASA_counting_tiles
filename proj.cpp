
// 1ºProjeto de ASA
// Pedro Guilherme de Noronha Guimarães   ist102543
// Bárbara Reis Silva                     ist102545

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

int rows;
int cols;
vector<int> points;
map<vector<int>, long long> memory;
vector<int> c;
vector<int> prev;


// store console input
void storeInput() {
	int point;
	vector<int> coordInit;

	cin >> rows;
	cin >> cols;

	for (int i = 0; i < rows; i++) {
		cin >> point;
		points.push_back(point);
		coordInit.push_back(0);
	}
	memory.insert({coordInit, 1});

}


// find the point most to the right and bottom 
vector<int> findRightCoord(vector<int> points) {
	vector<int> maxRight = {rows, 0};
	for (long unsigned int i = 0; i < points.size(); i++) {
		if (points[i] >=  maxRight[1])
			maxRight = {(int)i, points[i]};
	}

	return maxRight;
}


// find the biggest square possible in certain coords from origin
int findBigSquareSize(vector<int> coords, vector<int> origin) {
	int maxSqHeight = 1;
	int maxSqLength = origin[1];
	int i = origin[0]-1;

	if (origin[0] == 0)
		return 1;

	while(i >= 0) {
		if (coords[i] == origin[1])
			maxSqHeight++;
		else
			break;
		i--;
	}

	return min(maxSqHeight, maxSqLength);
}


// find the new coordinates without the square of sqSize size in the originCoord
vector<int> findNewCoords(vector<int> coords, int sqSize, vector<int> originCoord) {
	for (int i = originCoord[0]; i > originCoord[0]-sqSize; i--)
		coords[i] -= sqSize;

	return coords;
}


// check if vector of int is all equal to 0
bool checkEqZero(vector<int> v) {
	for (long unsigned int i = 0; i < v.size(); i++) {
		if (v[i] != 0)
			return false;
	}
	return true;
}
 

// Recusive function to find combinations
long long recursiveSqFind(vector<int> coords) {

	long long c = 0;
	vector<int> originCoord = findRightCoord(coords);
	int bigSqSize = findBigSquareSize(coords, originCoord);

	//try to find pre computed solution for coords
	if (memory.find(coords) == memory.end()) {
		// for each square possible to find in originCoord call recursive function
		for (int i = 0; i < bigSqSize; i++) {
			c += recursiveSqFind(findNewCoords(coords, i+1, originCoord));
		}
		// insert combinations in map
		memory.insert({coords, c});
	}

	// return combinations
	return memory.find(coords)->second;

}

int main() {

	storeInput();

	// if all points are zero, solution is 0
	if (checkEqZero(points))
		cout << 0 << endl;
	//call recursive function
	else {
		recursiveSqFind(points);
		cout << memory.find(points)->second << endl;
	}

	return 0;
}

