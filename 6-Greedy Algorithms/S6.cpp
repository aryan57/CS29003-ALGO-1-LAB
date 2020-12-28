#include <algorithm>
#include <cmath>
#include <stdio.h>
using namespace std;
int i,j, n, caseNo = 1, order[8], order_temp[8];
double a[8], b[8], timeGap, maxTimeGap; // timeGap is the variable L mentioned in text
double greedyLanding() 
{ // with certain landing order, and certain timeGap,
// try landing those planes and see what is the gap to b[order[n - 1]]
	double lastLanding = a[order[0]]; // greedy, first aircraft lands immediately
	for (i = 1; i < n; i++) 
	{ // for the other aircrafts
		double targetLandingTime = lastLanding + timeGap;
		if (targetLandingTime <= b[order[i]])
			// this aircraft can land, greedily choose max of a[order[i]] or targetLandingTime
			lastLanding = max(a[order[i]], targetLandingTime);
		else
			return 1; // returning positive value will force binary search to reduce timeGap
	}
// returning negative value will force binary search to increase timeGap
return lastLanding - b[order[n - 1]];
}

int main() 
{
	while (scanf("%d", &n), n) 
	{ // 2 <= n <= 8
		for (i = 0; i < n; i++) 
		{
			scanf("%lf %lf", &a[i], &b[i]); // [ai, bi] is the interval where plane i can land safely
			a[i] *= 60; b[i] *= 60; // originally in minutes, convert to seconds
			order[i] = i;
		}
		maxTimeGap = -1; // variable to be searched for
		do 
		{ 
			//for (j=0;j<n;j++)
        		//{
			//	order_temp[j] = order[j]
                	//	printf("%d",order_temp[j]);
        		//}
			printf("\n");
			// permute plane landing order, 8!
			double lowVal = 0, highVal = 86400; // min 0s, max 1 day = 86400s
			timeGap = -1; // start with infeasible solution
			// This example code uses double data type. This is actually not a good practice
			// Some other programmers avoid the test below and simply use loop 100 times (precise enough)
			while (fabs(lowVal - highVal) >= 1e-3) 
			{ // binary search timeGap, ERROR = 1e-3 is OK here
				timeGap = (lowVal + highVal) / 2.0; // we just want the answer to be rounded to nearest int
				double retVal = greedyLanding(); // round down first
				if (retVal <= 1e-2) // must increase timeGap
					lowVal = timeGap;
				else // if (retVal > 0) // infeasible, must decrease timeGap
					highVal = timeGap;
			}
			if (timeGap>maxTimeGap){
			for (j=0;j<n;j++)
                        {
                                order_temp[j] = order[j];
                                //printf("%d",order_temp[j]);
                        }
                        //printf("\n");
			printf("%lf %lf",maxTimeGap, timeGap);
			}
			maxTimeGap = max(maxTimeGap, timeGap); // get the max over all permutations
		}
	while (next_permutation(order, order + n)); // keep trying all permutations
	// another way for rounding is to use printf format string: %.0lf:%0.2lf
	maxTimeGap = (int)(maxTimeGap + 0.5); // round to nearest second
	printf("Case %d: %d:%0.2d\n", caseNo++, (int)(maxTimeGap / 60), (int)maxTimeGap % 60);
	for (j=0;j<n;j++)
	{
		printf("%d",order_temp[j]);
	}
	} 
} // return 0;
// Challenge: rewrite this code to avoid double!
