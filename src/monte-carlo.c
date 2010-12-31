/*** 
	This program is under GPL Licence
	Project: "C-Code energy estimation of embedded systems"
	Coordinator: Prof. Dr. Raimundo Barreto - UFAM
	Co-Coordinator: Prof. Dr. Meuse Nogueira - CEFET (PE)

	Author: Carlos Mar, Master student of Federal University of Amazonas (UFAM)
	E-mail: carlos.augusto.mar@gmail.com / caam@dcc.ufam.edu.br
	History: 
	2007-12-10: version 0.1 implemented
*/

#include <math.h>
#include <monte-carlo.h>
#include <stdio.h>

tsamples *start_samples = NULL;

/***
	This functiosn produces a file wich content is the result of simulation
*/
void dumpStatistics(const char *outfile){

	FILE *fpesti = fopen(outfile, "wb");
	tsamples *axsample = start_samples;

	while(axsample){
		fprintf(fpesti, "%11.3f:%11.3f\n", axsample->energy, axsample->cycles);
		axsample = axsample->next;
	}
	fclose(fpesti);
}



/***
	This function free memory allocated by Samples
*/
void freeSample(void){
	tsamples *axsample = start_samples;

	while(start_samples){
		start_samples = start_samples->next;
		free(axsample);
		axsample =  start_samples;
	}
}
/***
	This function add a new element of the sample in a list of samples
	new_energy: energy spends in one execution cycle of the simulation
*/
void addSample(double new_energy, double cycles){
	tsamples *new;

	new = (tsamples *) malloc(sizeof(tsamples));
	new->energy = new_energy;
	new->cycles = cycles;
	new->next = start_samples;
	start_samples = new;
}

/***
	This function sums each element of the list of the samples
*/
double sumEnergy(void){
	tsamples *axsample = start_samples;
	double sum=0.0;

	while (axsample){
		sum += axsample->energy;
		axsample = axsample->next;
	}

	return (sum);	
}

/***
	This function calculates sample mean
	nrsamples: number of execution cycles
*/
double calculateMean(double nrsamples){
	return (sumEnergy() / nrsamples);
}


/***
	This function calculates sample standard deviation
	mean: Sample mean
	nrsamples: number of execution cycles
*/
double calculateSn(double mean, double nrsamples){
	tsamples *axsample = start_samples;
	double sum=0.0;

	while (axsample){
//		printf("energy: %g	mean: %g\n", axsample->energy, mean);
		sum = sum + ((axsample->energy-mean) * (axsample->energy-mean));
		axsample = axsample->next;
	}
//	printf("mean: %g	sum: %g		nrsamples: %g\n", mean, sum, nrsamples);
	return (sqrtf(sum/nrsamples));			
}


/***
	This function returns t student variable based on confidence and execution cycles executed
	nrsamples: number of execution cycles of the simulation
	confidence: simluation confidence 
*/
double getT(unsigned int nrsamples, double confidence){
	unsigned int n = nrsamples -1;
	unsigned int col, axconfidence;

	axconfidence = 10000 * confidence;

	switch (axconfidence){
		case 7500:   col = 0;
		case 8000:   col = 1;
		case 8500:   col = 2;
		case 9000:   col = 3;
		case 9500:   col = 4;
		case 9750:  col = 5;
		case 9900:   col = 6;
		case 9950:  col = 7;
		case 9975: col = 8;
		case 9990: col = 9;
		case 9995: col = 9;
	}

	if (n <= 30)
		return (table_T[n-1][col]);
	else if ((n >= 31) && (n <= 40)) 
			return (table_T[30][col]);
		else if ((n >= 41) && (n <= 50)) 
			return (table_T[31][col]);
		else if ((n >= 51) && (n <= 60)) 
			return (table_T[32][col]);
		else if ((n >= 61) && (n <= 80)) 
			return (table_T[33][col]);
		else if ((n >= 81) && (n <= 100)) 
			return (table_T[34][col]);
		else if ((n >= 101) && (n <= 120)) 
			return (table_T[35][col]);
		else return (table_T[36][col]);

}

/***
	This is responsible to evaluate Monte Carlo's criteria
	nrsamples: number of execution cycles of the simulation
	max_err: maximum error between populational mean and sample mean
	confidence: intervalo de confianca
*/
int stopSimulation(double nrsamples, double max_err, double confidence){
	double P, Sn, t;

	P = calculateMean(nrsamples);
	Sn = calculateSn(P, nrsamples);
	t = getT(nrsamples, confidence);

//	printf("nrsamples: %g	P: %g	Sn: %g	t:%g	erro: %g\n", nrsamples, P, Sn, t, max_err);
	
	return (nrsamples >= (((t * Sn) / (max_err * P)) * ((t * Sn) / (max_err * P))) );	
}
