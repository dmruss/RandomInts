//citing https://stackoverflow.com/questions/19870276/generate-a-random-number-from-0-to-10000000
//for information on generating random numbers greater than randmax
//citing https://www.geeksforgeeks.org/binary-search/
//for information on binary search

//Extra Credit:  One run of my program yielded these comparison and swap results for the three sorts:
			//  1st: Comparisons: 2509845085  Swaps: 99999
			//  2nd: Comparisons: 4999945032  Swaps: 99999
			//  3rd: Comparisons: 4999945032  Swaps: 99999
//The comparisons for the second sort and the third sort are close to double the number of comparisons for the first.
//These two sorts are so much more inefficient becuase they are both doing the two most cumbersome sorts possible:
//sorting an array in ascending order into descending order, and sorting an array in descending order into ascending order.
//To account for overflow of the comparison variable, I changed the type from an integer to a long long.

#include <iostream>
#include <fstream>
#include <random>
#include <time.h>
#include <sstream>

using namespace std;


int binarySearch(int arr[], int l, int r, int x);
void sortArray(int arr[], int numCount, bool isDescending);
void generateNums(int arr[], int numCount, string filePath);
void readNums(int arr[], string filePath);
void menuLoop(int arr[], int numCount);

int main() {

	//Variables
	const int totalNumbers = 100000;
	int nums[totalNumbers];
	srand(time(NULL));
	string filePath = "numbers.txt";


	//Functions
	generateNums(nums, totalNumbers, filePath);
	

	readNums(nums, filePath);


	sortArray(nums, totalNumbers, false);
	sortArray(nums, totalNumbers, true);
	sortArray(nums, totalNumbers, false);


	menuLoop(nums, totalNumbers);

	
	return 0;
}

void generateNums(int arr[], int numCount, string filePath) {
	ofstream outfile(filePath);
	//Generate random numbers, 5 to each line
	for (int n = 1; n <= numCount; n++)
	{

		//execute this branch every fifth number to make a new line
		if ((n % 5) == 0) {

			//Generate a random number, bit shift by 15 bits, 
			//raise that random number to the power of a new random number
			//modulo the product by one above the upper limit to keep it in bounds

			//CORRECTION: The above worked on my compiler but not on csgrid.
			//Csegrid's compiler produced negative numbers with this method.
			//The updated method is call rand() then modulo for 1000001 to keep in bounds.
			//Csegrid's compiler appears to produce a higher rand_max

			int x = rand();
					//x <<= 15;
					//x ^= rand();
			x %= 1000001;


			outfile << x << " \n";
			//nums[n - 1] = x;
		}


		else {
			int x = rand();
					//x <<= 15;
					//x ^= rand();
			x %= 1000001;


			outfile << x << " ";
			//nums[n - 1] = x;
		}




	}
	outfile.close();


}

void readNums(int arr[], string filePath) {
	//read numbers from the filepath into an array
	ifstream infile(filePath);
	int n = 0;
	string line;
	while (getline(infile, line)) {

		stringstream ss(line);

		while (ss >> arr[n]) {
			n++;

		}

	}
	infile.close();
}

void sortArray(int arr[], int numCount, bool isDescending) {

	if (isDescending) {
		int i, key, j, swaps = 0;
		long long comparisons = 0;
		for (i = 1; i < numCount; i++) {
			key = arr[i];
			j = i - 1;

			while (j >= 0 && arr[j] < key) {
				arr[j + 1] = arr[j];
				j--;
				comparisons++;
			}
			arr[j + 1] = key;
			swaps++;
		}
		cout << "Compares: " << comparisons << endl;
		cout << "Swaps: " << swaps << endl;
	}

	else {
		int i, key, j, swaps = 0;
		long long comparisons = 0;
		for (i = 1; i < numCount; i++) {
			key = arr[i];
			j = i - 1;

			while (j >= 0 && arr[j] > key) {
				arr[j + 1] = arr[j];
				j--;
				comparisons++;
			}
			arr[j + 1] = key;
			swaps++;
		}
		cout << "Compares: " << comparisons << endl;
		cout << "Swaps: " << swaps << endl;

	}
	
}

int binarySearch(int arr[], int l, int r, int x)
{
	if (r >= l) {
		int mid = l + (r - l) / 2;

		
		if (arr[mid] == x) {
			cout << x << " is in the list\n";
			return mid;
		}
	

		
		if (arr[mid] > x) {
			cout << x << " is less than " << arr[mid] << " from nums[" << (r - l) << "]\n";
			return binarySearch(arr, l, mid - 1, x);
		}
	
		cout << x << " is greater than " << arr[mid] << " from nums[" << (r - l) << "]\n";
		return binarySearch(arr, mid + 1, r, x);
	}

	
	cout << x << " is not in the list\n";
	return -1;
}

void menuLoop(int arr[], int numCount) {
	bool over = false;

	//Menu Loop
	while (!over) {
		cout << "Enter an integer from 0 to 1,000,000: \n";
		cout << "Or enter 'q' to quit\n";
		int choice;
		cin >> choice;
		
		//invalid entry checking
		while (choice < 0) {
			cout << "Invalid Entry.\n";
			cin.ignore();
			cin.clear();
			cout << "Enter an integer from 0 to 1,000,000: ";

			cin >> choice;
		}

		//end loop on a char input
		while (!cin) {
			over = true;
			cout << "Thanks for playing\n";
			return;
		}


		int end = numCount - 1;
		int middle = end / 2;
		int start = 0;
		int current = arr[middle];
		
		//call binary search
		binarySearch(arr, start, end, choice);

	}
}

