#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DIM 3 //Dimensions
int main(void) {
	int i, j, k, n, c;
	double dmin, dx;
	double *x, *mean, *sum;
	int *cluster, *count, color;
	int flips;
	scanf("%d", &k); // The number of centroids
	scanf("%d", &n); // THe number of points
	x = (double *)malloc(sizeof(double)*DIM*n); //Creating an array for n points with 3 dimensional values
	mean = (double *)malloc(sizeof(double)*DIM*k); // Creating array for k centroids with 3D values to be calculated from point means.
	sum= (double *)malloc(sizeof(double)*DIM*k);
	cluster = (int *)malloc(sizeof(int)*n); // To represent the cluster to which the point belongs. 
	count = (int *)malloc(sizeof(int)*k); // to count the points in the cluster
	for (i = 0; i<n; i++) 
		cluster[i] = 0;
	for (i = 0; i<k; i++)
		scanf("%lf %lf %lf", mean+i*DIM, mean+i*DIM+1, mean+i*DIM+2); //Enter initial position of k centroids in the means array.
	for (i = 0; i<n; i++)
		scanf("%lf %lf %lf", x+i*DIM, x+i*DIM+1, x+i*DIM+2); //Enter position of n points in the x array.
	flips = n; //unchanged points.
	while (flips>0) {
		flips = 0; //No change till now
		for (j = 0; j < k; j++) {
			count[j] = 0; //Initialize count to 0.
			for (i = 0; i < DIM; i++) 
				sum[j*DIM+i] = 0.0; //Initialize sum to 0.
		}

		//One parallelization here
		for (i = 0; i < n; i++) {
			dmin = -1; color = cluster[i]; //Initialize color of point and min dist.
			for (c = 0; c < k; c++) { //assign the point to the nearest centroid.
				dx = 0.0;
				for (j = 0; j < DIM; j++) 
					dx +=  (x[i*DIM+j] - mean[c*DIM+j])*(x[i*DIM+j] - mean[c*DIM+j]); //(x-xk)^2 + (y-yk)^2 + (z-zk)^2
				if (dx < dmin || dmin == -1) { //It will always run first time. 
					color = c; // Point will get assigned to centroid with lowest dx 
					dmin = dx;
				}
			}
			if (cluster[i] != color) {
				flips++; //Cluster of point changed. Needs to re-calculte mean.
				cluster[i] = color;
	      	}
		}

		//One parallelization here. Have to create local count and sum array for each thead and then add finally. Lock section?
	    for (i = 0; i < n; i++) {
			count[cluster[i]]++; //Count the points in each cluster
			for (j = 0; j < DIM; j++) 
				sum[cluster[i]*DIM+j] += x[i*DIM+j]; //Calculate the sum of the x,y,z coordinates of points in each cluster.
		}
		for (i = 0; i < k; i++) {
			for (j = 0; j < DIM; j++) {
				mean[i*DIM+j] = sum[i*DIM+j]/count[i]; //Calculate new mean.
  			}
		}
	}
	for (i = 0; i < k; i++) {
		for (j = 0; j < DIM; j++)
			printf("%5.2f ", mean[i*DIM+j]);
		printf("\n");
	}
	#ifdef DEBUG
	for (i = 0; i < n; i++) {
		for (j = 0; j < DIM; j++)
			printf("%5.2f ", x[i*DIM+j]);
		printf("%d\n", cluster[i]);
	}
	#endif
	return(0);
}
