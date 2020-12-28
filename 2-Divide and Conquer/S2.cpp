// A divide and conquer based C++
// program to find OutLine of given Boxs
#include <iostream>
#include "assign2.h"
using namespace std;


// OutLine: To represent Output(An array of Points)
class OutLine {
	// Array of Points
	Point* arr;

	// Capacity of Point array
	int capacity;

	// Actual number of Points in array
	int n;

public:
  // destructor to free arr
	~OutLine() { delete[] arr; }
	int count() { return n; }

	// A function to merge another OutLine
	// to this OutLine
	OutLine* Merge(OutLine* other);

	// Constructor
	OutLine(int cap)
	{
		capacity = cap;
		arr = new Point[cap];
		n = 0;
	}

	// Function to add a Point 'st' to array
	void append(Point* st)
	{
		// Check for redundant Point, a Point is
		// redundant if it has same height or left as previous
		if (n > 0 && arr[n - 1].y == st->y)
			return;
		if (n > 0 && arr[n - 1].x == st->x) {
			arr[n - 1].y = max(arr[n - 1].y, st->y);
			return;
		}

		arr[n] = *st;
		n++;
	}

	// A utility function to print all Points of
	// OutLine
	void print()
	{
		for (int i = 0; i < n; i++) {
			cout << " (" << arr[i].x << ", "
			     << arr[i].y << "), ";
		}
	}

	void setlastheightzero() {
		if (n > 0) {
			arr[n - 1].y = 0;
		}
	}

	Point* copy_output_to_Point(int &outputsize) {
		Point* points = new Point[n];
		for (int i = 0; i < n; i++) {
			(points)[i] = arr[i];
		}
		outputsize = n;
		return points;
	}
};

// This function returns OutLine for a
// given array of Boxes arr[l..h].
// This function is similar to mergeSort().
OutLine* __findOutLine(Box arr[], int l, int h)
{
	if (l == h) {
		OutLine* res = new OutLine(2);
		res->append(
		new Point{
			arr[l].left, arr[l].ht});

		res->append(
		    new Point{arr[l].right, 0});

		return res;
	}

	int mid = (l + h) / 2;

	// Recur for left and right halves
	// and merge the two results
	OutLine* sl = __findOutLine(
	                  arr, l, mid);
	OutLine* sr = __findOutLine(
	                  arr, mid + 1, h);
	OutLine* res = sl->Merge(sr);

	// To avoid memory leak
	delete sl;
	delete sr;

	// Return merged OutLine
	return res;
}
__Outline* findOutLine(Box boxes[], int size) {
	OutLine* outline = __findOutLine(boxes, 0, size - 1);
	int outsiz;
	Point* points = outline->copy_output_to_Point(outsiz);
	__Outline *out = new __Outline;
	out->size = outsiz;
	out->points = points;
	return out;
}
// Similar to merge() in MergeSort
// This function merges another OutLine
// 'other' to the OutLine for which it is called.
// The function returns pointer to the
// resultant OutLine
OutLine* OutLine::Merge(OutLine* other)
{
	// Create a resultant OutLine with
	// capacity as sum of two OutLines
	OutLine* res = new OutLine(
	    this->n + other->n);

	// To store current heights of two OutLines
	int h1 = 0, h2 = 0;

	// Indexes of Points in two OutLines
	int i = 0, j = 0;
	while (i < this->n && j < other->n) {
		// Compare x coordinates of left sides of two
		// OutLines and put the smaller one in result
		if (this->arr[i].x < other->arr[j].x) {
			int x1 = this->arr[i].x;
			h1 = this->arr[i].y;

			// Choose height as max of two heights
			int maxh = max(h1, h2);

			res->append(new Point{x1, maxh});
			i++;
		}
		else {
			int x2 = other->arr[j].x;
			h2 = other->arr[j].y;
			int maxh = max(h1, h2);
			res->append(new Point{x2, maxh});
			j++;
		}
	}

	// If there are Points left in this
	// OutLine or other OutLine
	while (i < this->n) {
		res->append(&arr[i]);
		i++;
	}
	while (j < other->n) {
		res->append(&other->arr[j]);
		j++;
	}
	res->setlastheightzero();
	return res;
}
int main() {
	process();
	return 0;
}
