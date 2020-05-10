#include<iostream> 
#include <string>
using namespace std;

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
void FCFS_RR(int process_number, float *arrival_t, float *burst_t,
	string *process_name, float remaining_bt[])
{

	for (int i = 0; i < process_number - 1; i++)
	{
		// Last i elements are already in place  
		for (int j = 0; j < process_number - i - 1; j++)
		{
			if (arrival_t[j] > arrival_t[j + 1])
			{
				swap(&arrival_t[j], &arrival_t[j + 1]);
				swap(&burst_t[j], &burst_t[j + 1]);
				swap(&process_name[j], &process_name[j + 1]);
				swap(&remaining_bt[j], &remaining_bt[j + 1]);
			}


			//to avoid convey effect(short processes behind long processes)
			else if (arrival_t[j] == arrival_t[j + 1])
			{
				if (burst_t[j] > burst_t[j + 1])
				{
					swap(&arrival_t[j], &arrival_t[j + 1]);
					swap(&burst_t[j], &burst_t[j + 1]);
					swap(&process_name[j], &process_name[j + 1]);
					swap(&remaining_bt[j], &remaining_bt[j + 1]);
				}

			}
		}
	}

}

/****************************************ROUND ROBIN *************************************************/

void RoundRobin(int process_number, string *process_name, float *arrival_t,
	float *burst_t, int quantum, float *start_time, float *end_time,
	float* average_wt, int *count1)
{
	int count = 0;
	float time = 0;
	float* remaining_burst_t = new float[process_number];

	float* waiting_t = new float[process_number];
	float* completion_time = new float[process_number];
	float total_burst_t = 0;

	for (int i = 0; i < process_number; i++)
	{
		total_burst_t += burst_t[i];
	}


	//initially the remaining time equals the actual burst time
	for (int i = 0; i < process_number; i++)
	{
		remaining_burst_t[i] = burst_t[i];
	}

	//sort the processes with respect to their arrival time 
	FCFS_RR(process_number, arrival_t, burst_t, process_name, remaining_burst_t);


	start_time[0] = arrival_t[0];
	int count2 = 0;

	while (1)
	{

		bool done = true;
		// Traverse all processes one by one repeatedly 
		for (int i = 0; i < process_number; i++)
		{
			if (arrival_t[i] <= time)
			{
				if (remaining_burst_t[i] > 0)
				{
					done = false; // There is a pending process 

					if (remaining_burst_t[i] > quantum)
					{

						cout << time << "==>";
						//shows the time a process has been processed 
						time += quantum;
						if (arrival_t[i + 1] > time)
						{
							start_time[++count] = arrival_t[i + 1];
						}
						else
						{
							start_time[++count] = time;
						}
						//decrease the remaining time by the quantum progressed
						remaining_burst_t[i] -= quantum;
						completion_time[i] = time;
						end_time[count2++] = time;
					}
					//If burst time is smaller than or equal to quantum(Last cycle for this process)
					else
					{

						//shows the time a process has been processed 
						time += remaining_burst_t[i];
						if (arrival_t[i + 1] > time)
						{
							start_time[++count] = arrival_t[i + 1];
						}
						else
						{
							start_time[++count] = time;
						}
						//the process is fully executed
						remaining_burst_t[i] = 0;
						completion_time[i] = time;
						end_time[count2++] = time;
					}



				}
			}
			else if (arrival_t[i] > time)
			{
				bool flag = 0;
				for (int j = 0; j < i; j++)
				{
					if (remaining_burst_t[j] > 0)
					{
						flag = 1;
						break;
					}

				}
				if (flag == 0)
				{
					time = arrival_t[i];
					break;
				}
			}
		}

		// If all processes are done 
		if (done == true)
			break;
	}

	*count1 = count;
	for (int i = 0; i < *count1; i++)
	{
		end_time[i] = start_time[i + 1];

	}


	for (int i = 0; i < process_number; i++)
	{
		waiting_t[i] = completion_time[i] - arrival_t[i] - burst_t[i];
	}


	//function to calculate the average waiting time 
	float total_waiting_t = 0;

	for (int i = 0; i < process_number; i++)
	{
		total_waiting_t += waiting_t[i];
	}

	*average_wt = total_waiting_t / process_number;
}
