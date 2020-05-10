#include<iostream> 
#include <string>
using namespace std;


/*******************************FCFS**********************************/
void swap(float *xp, float *yp)
{
	float temp = *xp;
	*xp = *yp;
	*yp = temp;
}
void swap(string *xp, string *yp)
{
	string temp = *xp;
	*xp = *yp;
	*yp = temp;
}

// A function to implement first come first served  
void FCFS(int processes_number, float arrival_t[], float burst_t[], string process_name[],
	float start_time[], float end_time[], float *average_wt)
{
	float* waiting = new float[processes_number];
	float total_waiting_t = 0;


	for (int i = 0; i < processes_number - 1; i++)
	{
		// Last i elements are already in place  
		for (int j = 0; j < processes_number - i - 1; j++)
		{
			if (arrival_t[j] > arrival_t[j + 1])
			{
				swap(&arrival_t[j], &arrival_t[j + 1]);
				swap(&burst_t[j], &burst_t[j + 1]);
				swap(&process_name[j], &process_name[j + 1]);
			}


			//to avoid convey effect(short processes behind long processes)
			else if (arrival_t[j] == arrival_t[j + 1])
			{
				if (burst_t[j] > burst_t[j + 1])
				{
					swap(&arrival_t[j], &arrival_t[j + 1]);
					swap(&burst_t[j], &burst_t[j + 1]);
					swap(&process_name[j], &process_name[j + 1]);
				}

			}
		}
	}
	start_time[0] = arrival_t[0];
	end_time[0] = burst_t[0] + arrival_t[0];

	for (int i = 0; i < processes_number - 1; i++)
	{
		if (arrival_t[i + 1] <= end_time[i])
		{
			start_time[i + 1] = burst_t[i] + start_time[i];
			end_time[i + 1] = burst_t[i + 1] + end_time[i];
		}
		else
		{
			start_time[i + 1] = arrival_t[i + 1];
			end_time[i + 1] = burst_t[i + 1] + start_time[i + 1];
		}
	}

	// waiting time for first process is 0 
	waiting[0] = 0;

	// calculating waiting time 
	for (int i = 1; i < processes_number; i++)
	{
		waiting[i] = end_time[i] - burst_t[i] - arrival_t[i];
	}

// calculate total waiting time and total turn around time
	for (int i = 0; i < processes_number; i++)
	{
		total_waiting_t += waiting[i];

	}

	*average_wt = total_waiting_t / processes_number;

}
