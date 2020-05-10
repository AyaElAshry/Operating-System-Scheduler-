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

void Priority_non_Preemptive(float *at, float *bt, string *processname, float *st, float *ct, 
	float *avg_wt, string *gantt_process, int *priority, int n)
{
	int P[100];
	float tat[100];
	float wt[1000];

	float temp;
	float total;
	int max_priority = 999;

	for (int i = 0; i < n; i++)
	{
		P[i] = i + 1;
	}

	for (int i = 0; i < n; i++) //
	{
		for (int j = i + 1; j < n; j++)
		{

			if (at[i] > at[j])
			{
				temp = at[i];
				at[i] = at[j];
				at[j] = temp;

				temp = float(priority[i]);
				priority[i] = priority[j];
				priority[j] = temp;

				temp = bt[i];
				bt[i] = bt[j];
				bt[j] = temp;

				temp = float(P[i]);
				P[i] = P[j];

				P[j] = temp;

				string temps = processname[i];
				processname[i] = processname[j];
				processname[j] = temps;
			}
			else if (at[i] == at[j] && priority[i] > priority[j])
			{
				temp = at[i];
				at[i] = at[j];
				at[j] = temp;

				temp = float(priority[i]);
				priority[i] = priority[j];
				priority[j] = temp;

				temp = bt[i];
				bt[i] = bt[j];
				bt[j] = temp;

				temp = P[i];
				P[i] = P[j];
				P[j] = temp;

				string temps = processname[i];
				processname[i] = processname[j];
				processname[j] = temps;
			}
		}
	}

	total = bt[0];
	for (int i = 1; i < n - 1; i++)
	{
		for (int j = i; j < n; j++)
		{
			if (total >= at[j] && max_priority > priority[j])
			{
				max_priority = priority[j];
				temp = at[i];
				at[i] = at[j];
				at[j] = temp;

				temp = priority[i];
				priority[i] = priority[j];
				priority[j] = temp;

				temp = bt[i];
				bt[i] = bt[j];
				bt[j] = temp;

				temp = P[i];
				P[i] = P[j];
				P[j] = temp;

				string temps = processname[i];
				processname[i] = processname[j];
				processname[j] = temps;
			}
		}
		max_priority = 999;
		total += bt[i];
	}

	st[0] = at[0];
	ct[0] = bt[0] + at[0];
	tat[0] = ct[0] - at[0];
	wt[0] = tat[0] - bt[0];
	total = 0;

	for (int i = 1; i < n; i++)
	{
		gantt_process[0] = processname[0];
		gantt_process[i] = processname[i];
		if (at[i] > ct[i - 1])
		{
			st[i] = at[i];
		}
		else
		{
			st[i] = ct[i - 1];
		}
		ct[i] = st[i] + bt[i];
		tat[i] = ct[i] - at[i];
		wt[i] = tat[i] - bt[i];
		total += wt[i];
	}
	*avg_wt = float(total) / n;

}