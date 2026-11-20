#include <stdio.h>
#include <unistd.h>
#include <pigpio.h>
#include <math.h>
#define PIN 17
#define READING_COUNT 5
/*FILE *fp = fopen("temps.txt", "w");
for (int i= 0; i < READING_COUNT; i++)
{
	printf("Enter reading %d: ", i + 1);
	scanf("%lf" , &readings[i]);
	fpintf(fp, "%.1f\n", readings[i]);
}
saveReadingsToFile(readings, READING_COUNT, "temps.txt");
fclose(fp);
*/


double calculateAverage(double readings[],int count) {
	double total = 0;
	for (int i = 0; i < count; i++) total += readings[i];
	return total / count;
}

int determineRange (double temperature, int l, int h) {
	return (temperature < l || temperature > h) ? 1:0;
}

void displayReadings(double readings[], int count) {
	printf("Temperature Readings:\n");
	for (int i = 0; i < count; i++) printf("%.1f F\n", readings[i]);
}

void checkReadings(double readings, int low, int high)
 {
	
		FILE *fp = fopen("status.txt", "a");
		if (determineRange(readings, low, high)) {
			printf("%.1f F WARNING\n", readings);
			fprintf(fp,"%.1f F WARNING\n", readings);
			gpioWrite(PIN,1);
			getchar();
			
		}
		else {
			printf("%.1f F NORMAL\n", readings); 
			fprintf(fp,"%.1f F NORMAL\n", readings);
			gpioWrite(PIN,0);
			getchar();
			
		}
		fclose(fp);
	
}


int main(void){
	FILE *fp = fopen("status.txt", "w");
	fprintf(fp,"");
	fclose(fp);
	gpioInitialise();
	gpioSetMode (PIN, PI_OUTPUT);
	
	int lowTemp;
	int highTemp;
	printf("Enter lowest temperature: ");
	scanf("%d" , &lowTemp);
	
	getchar();
	
	printf("Enter highest temperature: ");
	scanf("%d" , &highTemp);
	
	getchar();
	
	double readings[READING_COUNT];
	for (int i = 0; i < READING_COUNT; i++)
	{
		printf("Enter reading %d; ", i);
		scanf("%lf" , &readings[i]);
		checkReadings(readings[i], lowTemp, highTemp);
	
	}
	displayReadings(readings, READING_COUNT);
	printf("\nAverage tempertaure: %.1f F\n", calculateAverage(readings, READING_COUNT));
	FILE *fpp = fopen("status.txt", "a");
	fprintf(fpp,"\nAverage tempertaure: %.1f F\n", calculateAverage(readings, READING_COUNT));
	fclose(fpp);
	
	gpioTerminate();
	
	return 0;
}



	/*
	gpioInitialise();
	gpioSetMode (PIN, PI_OUTPUT);
	gpioWrite(PIN,1);
	getchar();
	gpioWrite(PIN,0);
	gpioTerminate();
	return 0;
	*/

