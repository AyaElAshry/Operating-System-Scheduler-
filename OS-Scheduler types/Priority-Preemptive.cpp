#include <algorithm>
#include <iostream>
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
void swap(int *xp, int *yp)
{
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void Priority_Preemptive(float *arrival, float *burst, string *process_name, 
	float *start, float *end, float *avg_wt, string *gantt_process, 
	int *priority, int process_number)
{
	string pro[1000];
	int process[1000];
	float bt_new[1000];
	float b_time[1000];
	float completion[1000];
	int array[1000];
	float at_new[1000];
	int finalpro[1000];

	float turn_around[1000];

	float wait[1000];

	int max_priority = 1000;
	int proc_index = 0;
	float total_wt = 0;
	float total = arrival[0] * 10;
	int counter = 0;
	int count = 0;

	for (int i = 0; i < process_number; i++)
	{

		pro[i] = process_name[i];
		process[i] = i + 1;
	}

	for (int i = 0; i < process_number; i++)
	{

		burst[i] = burst[i] * 10;
		bt_new[i] = burst[i];
		b_time[i] = burst[i];
		total += burst[i];
	}

	for (int i = 0; i < process_number; i++)
	{
		arrival[i] = arrival[i] * 10;
	}

	for (int i = 0; i < process_number; i++) // sorting priority[20],bt[20],P[20]
	{
		for (int j = i + 1; j < process_number; j++)
		{
			if (arrival[i] > arrival[j]) //sort ascendingly according to arrival time
			{
				swap(&arrival[i], &arrival[j]);
				swap(&priority[i], &priority[j]);
				swap(&burst[i], &burst[j]);
				swap(&process_name[i], &process_name[j]);
				swap(&process[i], &process[j]);
				swap(&pro[i], &pro[j]);
			}
		}
	}

	for (int i = 0; i < total; i++)
	{
		for (int j = 0; j < process_number; j++)
		{
			if (arrival[j] <= i && burst[j] > 0) // we have to interrupt
			{
				if (max_priority > priority[j])
				{

					max_priority = priority[j];
					proc_index = j;
				}
			}
		}

		burst[proc_index]--;
		if (burst[proc_index] == 0)
		{
			max_priority = 999;
			completion[i] = i + 1;
		}
		else
		{
			completion[i] = 0;
		}

		array[i] = process[proc_index];
		finalpro[i] = process[proc_index];
		at_new[i] = arrival[proc_index];
		b_time[i] = bt_new[proc_index];
		process_name[i] = pro[proc_index];
	}

	//completion time
	int j = 0;
	for (int i = 0; i < total; i++)
	{
		if (completion[i] != 0)
		{
			completion[j] = completion[i];
			process[j] = finalpro[i];
			arrival[j] = at_new[i];
			bt_new[j] = b_time[i];
			j++;
		}
	}

	// CHART DRAWINNG*//

	for (int i = 0; i < total; i++)
	{

		for (int j = i + 1; j < total + 1; j++)
		{
			if (array[i] == array[j])
			{
				i = j;
			}
			else
			{

				counter = i + 1;
				end[i] = counter;

				break;
			}
		}

		at_new[count] = at_new[i];
		start[0] = at_new[0];
		start[count + 1] = end[i];
		end[count] = end[i];
		gantt_process[count] = process_name[i];
		count++;
	}

	for (int i = 0; i < count; i++)
	{
		start[i] = start[i] / 10;
		end[i] = end[i] / 10;
	}

	//*calculating waiting time & turnaround time
	for (int i = 0; i < process_number; i++)
	{
		turn_around[i] = completion[i] - arrival[i];
		wait[i] = turn_around[i] - bt_new[i];
		wait[i] = wait[i] / 10;
		total_wt += wait[i];
	}

	*avg_wt = total_wt / process_number;
	
}