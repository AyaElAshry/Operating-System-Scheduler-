#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QtCore>
#include <QtGui>
#include <QMessageBox>
#include <QDebug>
#include <QColorDialog>
#include "about_us.h"
#include <algorithm>
#include <QColor>


int color_index(QString process , QString * gantt_process , int drawing_counter ){

        for (int j = 0; j < drawing_counter ;j++){

            if (process == gantt_process[j]){

                return j;

            }
    }

    return 0;
}
void swap(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void swap(QString *xp, QString *yp)
{
    QString temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void sjf_preemptive(float *arr, float * bur, QString *proc, float *st, float * comp, float *avg_wt, QString *gantt_process, int *drawing_count, int num) {

    float bur2[1000]; // burst time
    float wait[1000]; // waiting time
    float turn_around[1000]; // turn around time
    QString turn_process[1000];//in pre // process which take the cpu
    float total_wait = 0; // total wait time

    int z = 1;// as a flag for comp in pre-sjf
    int count = 0; // counter to know size of comp
    float total_service_Time = 0; // total time of all burst
    double min_service = 999;
    //int finished[5]; // flag that decrement for every -- in burst time
    int proc_index = 0;



    //for (int i = 0; i < num; i++) {bur[i] = bur[i] * 10;  bur2[i] = bur[i]; total_service_Time = bur[i] + total_service_Time; }


    for (int i = 0; i < num; i++) {arr[i] = arr[i] * 10; }


    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (arr[i] > arr[j])
            {
                /*sort the process names */
                QString  temp2 = proc[i];
                proc[i] = proc[j];
                proc[j] = temp2;

                /*sort the burst time */
                float temp = bur[i];
                bur[i] = bur[j];
                bur[j] = temp;

                /*sort the arrival time */
                float temp3 = arr[i];
                arr[i] = arr[j];
                arr[j] = temp3;
            }
        }
    }
    total_service_Time = arr[0] * 10;
        for (int i = 0; i < num; i++) { bur[i] = bur[i] * 10;  bur2[i] = bur[i]; total_service_Time = bur[i] + total_service_Time; }

    for (int i = arr[0]; i < total_service_Time; i++) {

        min_service = 999;

        for (int j = 0; j < num; j++) {

            if (arr[j] <= i && bur[j] > 0) {

                if (min_service > bur[j]) {

                    min_service = bur[j];
                    proc_index = j;
                }
            }

        }

        bur[proc_index] = bur[proc_index] - 1;

        min_service = int(bur[proc_index]);

        comp[proc_index] = i + 1;

        turn_around[proc_index] = comp[proc_index] - arr[proc_index];

        turn_process[i] = proc[proc_index];

        if (min_service == 0) { min_service = 999; }

        comp[proc_index] = comp[proc_index] / 10;

    }

    for (int i = arr[0]; i < total_service_Time; i++) {

        for (int j = i; j < total_service_Time; i++) {

            if (turn_process[i] != turn_process[i + 1]) {


                count++;

                st[0] = arr[0] / 10;

                gantt_process[0] = proc[0];

                comp[z - 1] = i + 1;

                comp[z - 1] = comp[z - 1] / 10;

                //cout << comp[z-1] << "  " << z << endl;


                if (i == total_service_Time - 1) break;


                gantt_process[z] = turn_process[i + 1];

                st[z] = i + 1;

                st[z] = st[z] / 10;

                //cout << st[z] << " " << i << "  " << total_service_Time << endl;

                z++;

                break;

            }
        }
    }
    for (int i = 0; i < num ; i++)
    {
        wait[i] = turn_around[i] - bur2[i];
        wait[i] = wait[i] / 10;
        total_wait = wait[i] + total_wait;
    }
    *avg_wt = total_wait / float(num);
    *drawing_count = count;
    //cout << avg_wt;
}
void sjf_non_preemptive(float *arr, float * bur, QString *proc, float *st, float * comp, float *avg_wt, QString *gantt_process, int *drawing_count, int num) {


    float wait[1000];
    float tat[1000];// waiting time
    float total_wait = 0; // total wait time

    int pending_burst = 0;

    int x = 1;




    for (int i = 0; i < num; i++) { wait[i] = 0; } // initialize wait array
    for (int i = 0; i < 20; i++) { comp[i] = 0; } // initialize comp array
    for (int i = 0; i < 20; i++) { st[i] = 0; } // initialize st array


            ////////////////////*** SORTING ACC TO ARRIVAL ***/////////////////////

            //sort_arrival(num, arr, proc, bur);

    for (int i = 0; i < num; i++)
    {
        for (int j = i + 1; j < num; j++)
        {
            if (arr[i] > arr[j])
            {
                /*sort the process names */
                QString  temp2 = proc[i];
                proc[i] = proc[j];
                proc[j] = temp2;

                /*sort the burst time */
                float temp = bur[i];
                bur[i] = bur[j];
                bur[j] = temp;

                /*sort the arrival time */
                float temp3 = arr[i];
                arr[i] = arr[j];
                arr[j] = temp3;

            }
            if (arr[i] == arr[j] && bur[i] > bur[j]) { // if they have the same arrival time

                /*sort the process names */
                QString  temp2 = proc[i];
                proc[i] = proc[j];
                proc[j] = temp2;

                /*sort the burst time */
                float temp = bur[i];
                bur[i] = bur[j];
                bur[j] = temp;

                /*sort the arrival time */
                float temp3 = arr[i];
                arr[i] = arr[j];
                arr[j] = temp3;



            }

        }

    }
    //////////////////*** SORTING ACC TO ARRIVAL+BURST ***/////////////////////

    pending_burst = int(bur[0]);

    for (int i = 1; i < num; i++)
    {
        //min = bur[x];


        for (int j = i; j < num; j++)
        {
            if (arr[i] <= pending_burst && arr[j] <= pending_burst && bur[j] < bur[i])
            {
                /*sort the process names */
                QString  temp2 = proc[x];
                proc[x] = proc[j];
                proc[j] = temp2;

                /*sort the burst time */
                float temp = bur[x];
                bur[x] = bur[j];
                bur[j] = temp;

                /*sort the arrival time */
                float temp3 = arr[x];
                arr[x] = arr[j];
                arr[j] = temp3;
            }

        }

        pending_burst = pending_burst + int(bur[x]);
        x++;
    }

    //////////////////*** END-time ***/////////////////////

    //////////////////*** wait-time *** Start-Time ****/////////////////////
    st[0] = arr[0];
    comp[0] = bur[0] + arr[0];
    tat[0] = comp[0] - arr[0];
    wait[0] = tat[0] - bur[0];

    for (int i = 1; i < num; i++)
    {
        gantt_process[0] = proc[0];
        gantt_process[i] = proc[i];
        if (arr[i] > comp[i - 1])
        {
            st[i] = arr[i];
        }
        else
        {
            st[i] = comp[i - 1];
        }
        comp[i] = st[i] + bur[i];
        tat[i] = comp[i] - arr[i];
        wait[i] = tat[i] - bur[i];
        total_wait += wait[i];
    }
    *avg_wt = (total_wait) / num;
    *drawing_count = num;
        //cout << avg_wt;
}
void Priority_non_Preemptive(float *at, float *bt, QString *processname, float *st, float *ct, float *avg_wt, QString *gantt_process, int *drawing_count, int *priority, int n)
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

                QString temps = processname[i];
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

                QString temps = processname[i];
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
            //cout << "total:  " << total << endl;
            if (total >= at[j] && max_priority > priority[j])
            {
                max_priority = priority[j];
                //  cout << "max:  " << max_priority << "--" << processname[j] << endl;
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

                QString temps = processname[i];
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
    *drawing_count = n;

    /*cout << "process\tarrival\tburst_time\tpriority\tstart time\tcompletiontime\twaiting_time\tturnaround_time\t" << endl;
    for (int i = 0; i < n; i++)
    {
        cout << processname[i]
            << "\t" << at[i]
            << "\t" << bt[i] << "\t" << priority[i] << "\t" << st[i] << "\t" << ct[i] << "\t" << wt[i] << "\t" << tat[i] << endl;*/
            //}

            //cout << "average waiting time is :" << avg_wt << endl;
}
void Priority_Preemptive(float *arrival, float *burst, QString *process_name, float *start, float *end, float *avg_wt, QString *gantt_process, int *drawing_counter, int *priority, int process_number)
{
    QString pro[1000];
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
    *drawing_counter = count;
}
void FCFS_RR(int process_number, float *arrival_t, float *burst_t, QString *process_name, float remaining_bt[])
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
void RoundRobin(int process_number, QString *process_name, float *arrival_t,float *burst_t, int quantum, float *start_time, float *end_time,float* average_wt, int *count1,QString*gantt_process)
{

    int count = 0;
    float time = 0;
    float* remaining_burst_t = new float[process_number];
    float* arrival2 = new float[process_number];
    float* waiting_t = new float[process_number];
    float* completion_time = new float[process_number];
    float total_burst_t = 0;

    for (int i = 0; i < process_number; i++)
    {
        total_burst_t += burst_t[i];
    }
    //cout << "total burst time=" << total_burst_t << endl;

    //initially the remaining time equals the actual burst time
    for (int i = 0; i < process_number; i++)
    {
        remaining_burst_t[i] = burst_t[i];
        arrival2[i] = arrival_t[i];
    }

    //sort the processes with respect to their arrival time
    FCFS_RR(process_number, arrival_t, burst_t, process_name, remaining_burst_t);


    start_time[0] = arrival_t[0];
    int k=0;

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
                        //shows the time a process has been processed
                        time += quantum;
                        start_time[++count] = time;
                        //decrease the remaining time by the quantum progressed
                        remaining_burst_t[i] -= quantum;
                        completion_time[i] = time;
                        gantt_process[k++]=process_name[i];
                    }
                    //If burst time is smaller than or equal to quantum(Last cycle for this process)
                    else
                    {
                        //shows the time a process has been processed
                        time += remaining_burst_t[i];
                        start_time[++count] = time;
                        //the process is fully executed
                        remaining_burst_t[i] = 0;
                        completion_time[i] = time;
                        gantt_process[k++]=process_name[i];
                    }

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
void FCFS(int processes_number, float *arrival_t, float *burst_t, QString *process_name,float *start_time, float *end_time,QString*gantt_process, int * drawing_counter, float *average_wt)
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
    end_time[0] = burst_t[0]+arrival_t[0];

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

    for (int i = 0; i <= processes_number; i++)
    {
         gantt_process[i]=process_name[i] ;

    }


    *average_wt = total_waiting_t / processes_number;
    *drawing_counter = processes_number;

}
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    scene = new QGraphicsScene(this);
    ui ->graphicsView ->setScene(scene);

    ////////////////////////////////////////////////////////
    /////////////////////////help///////////////////////////
    ////////////////////////////////////////////////////////

    ui->pushButton_delete->setToolTip("this button to clear the drawing window");
    ui->pushButton->setToolTip("Draw the gantt chart ");
    ui->pushButton_2->setToolTip("Update the data base of processes");
    ui->doubleSpinBox->setToolTip("burst time for the process");
    ui->doubleSpinBox_arrival->setToolTip("arrival time for the process");
    ui->spinBox_time_slice->setToolTip("time slice for Round Robin scheduler");
    ui->spinBox_priority->setToolTip("Priority value for priority type scheduler");
    ui->lineEdit_process_name->setToolTip("Number of processes");

    ////////////////////////////////////////////////////////
    ///////////////////backGround image/////////////////////
    ////////////////////////////////////////////////////////

    QPixmap background("C:/Users/Aya El Ashry/Downloads/OS PROJECT/aya/image1.jpeg");
    background = background.scaled(this->size(),Qt::IgnoreAspectRatio);
    QPalette pallete;
    pallete.setBrush(QPalette::Background, background);
    this->setPalette(pallete);

    ////////////////////////////////////////////////////////
    ///////////////////shaafe2 image////////////////////////
    ////////////////////////////////////////////////////////

    QPixmap pic("C:/Users/Aya El Ashry/Downloads/OS PROJECT/aya/image3.png");
    ui->label_image->setPixmap(pic);
    ui->label_image->setScaledContents(true);
    ui-> label_image->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

    ////////////////////////////////////////////////////////
    ///////////////////hidding widgets//////////////////////
    ////////////////////////////////////////////////////////

    ui->pushButton_delete->hide();
    ui->spinBox_priority->hide();
    ui->label_priority->hide();
    ui->label_time_slice->hide();
    ui->spinBox_time_slice->hide();
    ui->pushButton->hide();

    ////////////////////////////////////////////////////////
    ///////////////////setting colors///////////////////////
    ////////////////////////////////////////////////////////

    //ui->label_arrival->setStyleSheet("QLabel {  color : blue; }");
    //ui->label_burst->setStyleSheet("QLabel {  color : blue; }");
    //ui->label_num->setStyleSheet("QLabel { color : blue; }");
    //ui->label_priority->setStyleSheet("QLabel { color : blue; }");
    //ui->label_select_mode->setStyleSheet("QLabel { color : blue; }");
    //ui->label_process_name->setStyleSheet("QLabel { color : blue; }");
    //ui->label_time_slice->setStyleSheet("QLabel { color : blue; }");
    //ui->comboBox_mode->setStyleSheet(" QComboBox { background-color : green;}");
    //ui->pushButton_2->setStyleSheet(" QPushButton { background-color : green; border-style: outset; border-width: 3px; border-color: white; }"); // push_button_update
    //ui->groupBox->setStyleSheet(" QGroupBox{ color : white ; border-style:dashed ; border-width: 2px; border-color: white; }");
    //ui->pushButton->setStyleSheet(" QPushButton { background-color : green ; border-style: outset; border-width: 3px; border-color: white; }");
    //ui->pushButton_delete->setStyleSheet(" QPushButton { background-color : green ; border-style: outset; border-width: 3px; border-color: white; }");
    //ui->groupBox->setStyleSheet(" QGroupBox { background-color : white}");

    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////
    ////////////////////////////////////////////////////////

}

MainWindow::~MainWindow()
{
    delete ui;
}
    int num;
    int quantum;
    QString proc[1000]; // processes
    int coloring_index;
    QString scheduler_mode;
    float bur[1000]; // burst time
    float arr[1000]; // arrival  time
    float comp[1000]; // comp time // in pre the comp hass al start and end time
    float st[1000]; // start time
    int  priority[1000];
    QString gantt_process[1000];//in pre // process for the chart
    float avg_wt;
    int drawing_counter;
    int total_service_Time ;
    int index;
    int factor;
    int i = 0;

 void MainWindow::on_comboBox_mode_activated(int index1)
 {
     if (index1 == 0 ||index1 == 4 || index1 == 3) // FCFS // SJF non // SJF pre
      {
             ui->label_priority->hide();
             ui->spinBox_priority->hide();
             ui->label_time_slice->hide();
             ui->spinBox_time_slice->hide();

      }else if (index1 == 1 || index1 ==2 ){

             ui->label_priority->show();
             ui->spinBox_priority->show();
             ui->label_time_slice->hide();
             ui->spinBox_time_slice->hide();

      }else if (index1 == 5 ){ // RR

         ui->label_priority->hide();
         ui->spinBox_priority->hide();
         ui->label_time_slice->show();
         ui->spinBox_time_slice->show();


     }
index = index1;
}
void MainWindow::on_pushButton_2_clicked()  //update
{   
        table = new QTableWidget(this);
       num = ui->spinBox_number_of_process ->value();
       if (num == 0)
       {
           QMessageBox::warning(this , "WARNING", "please enter right number of processes");
       }
       if(i==0){total_service_Time = arr[0];} // to put the first arrival in total service

       if (num!=0){// if number of process == 0

           proc[i] = ui->lineEdit_process_name->text();

           if (proc[i] != NULL){ // if process has no name

                arr[i] = ui->doubleSpinBox_arrival->value();

                bur[i] = ui->doubleSpinBox->value();
                 total_service_Time= total_service_Time+bur[i];

                 if (index == 5) {quantum = ui->spinBox_time_slice->value();} // RR // time_slice
                 if(index == 2 || index == 1) {priority[i] = ui->spinBox_priority->value();} // priority

                 if(index==1 || index==2)
                 {
                     int row=ui->table->rowCount();
                       ui->table->insertRow(row);

                 ui->table->setItem(row,0,new QTableWidgetItem(proc[i]));

                 ui->table->setItem(row,1,new QTableWidgetItem(QString::number(arr[i])));

                 ui->table->setItem(row,2,new QTableWidgetItem(QString::number(bur[i])));
                 
                 ui->table->setItem(row,3,new QTableWidgetItem(QString::number(priority[i])));

                 }
                 else

                 {
                     int row=ui->table->rowCount();
                       ui->table->insertRow(row);

                      ui->table->hideColumn(3);
                     ui->table->setItem(row,0,new QTableWidgetItem(proc[i]));

                     ui->table->setItem(row,1,new QTableWidgetItem(QString::number(arr[i])));

                     ui->table->setItem(row,2,new QTableWidgetItem(QString::number(bur[i])));
                 }

         ui->doubleSpinBox_arrival->clear();
         ui->doubleSpinBox->clear();
         ui->lineEdit_process_name->clear();
         ui->spinBox_priority->clear();
         if (i == num-1)
         {
             ui->pushButton_2->hide();
             ui->pushButton->show();
         } // push_button_update
         else i= i+1 ;

}
           else QMessageBox::warning(this , "WARNING", "please enter right name for process");
}

}

void MainWindow::on_pushButton_clicked() //draw
{
    ui->pushButton->hide();

   int index = ui->comboBox_mode->currentIndex();

   if (i==num-1 && num != 0){

/*FCFS*/
 if (index == 0)
 {
   FCFS(num, &arr[0], &bur[0], &proc[0], &st[0], &comp[0], &gantt_process[0], &drawing_counter , &avg_wt);
 }

/*pri pre*/
 if (index == 1)
{
    Priority_Preemptive(&arr[0], &bur[0], &proc[0], &st[0], &comp[0], &avg_wt, &gantt_process[0], &drawing_counter, &priority[0], num);
}

/*pri non*/
 if (index == 2)
 {
     Priority_non_Preemptive(&arr[0], &bur[0], &proc[0], &st[0], &comp[0], &avg_wt, &gantt_process[0], &drawing_counter, &priority[0], num);
 }

/*SJF pre*/
 if (index == 3)
 {
     sjf_preemptive(&arr[0], &bur[0], &proc[0], &st[0], &comp[0], &avg_wt, &gantt_process[0], &drawing_counter, num);
 }

/*SJF non*/
 if (index == 4)
 {
     sjf_non_preemptive(&arr[0], &bur[0], &proc[0], &st[0], &comp[0], &avg_wt, &gantt_process[0], &drawing_counter, num);
 }

/*RR pre*/
 if (index == 5)
 {
     RoundRobin(num, &proc[0], &arr[0], &bur[0], quantum, &st[0], &comp[0], &avg_wt, &drawing_counter , &gantt_process[0]);
 }

factor = 1400/total_service_Time;

QBrush brush[13];
    brush[0]=(Qt::magenta);
    brush[1]=(Qt::red);
    //brush[1].setColor(QColor(204,37,41));
    brush[2]=(Qt::green);
    //brush[2].setColor(QColor(0,200,0));
    brush[3]=(Qt::blue);
    //brush[3].setColor(QColor(255,151,76));
    brush[4]=(Qt::yellow);
    //brush[4].setColor(QColor(255,151,76));
    brush[5]=(Qt::cyan);
    brush[6]=(Qt::magenta);
    brush[7]=(Qt::gray);
    brush[8]=(Qt::darkGreen);
    brush[9]=(Qt::darkYellow);
    brush[10]=(Qt::darkMagenta);
    brush[11]=(Qt::darkCyan);
    brush[12]=(Qt::darkRed);



for (int i = 0 ;i < drawing_counter ; i++){

   coloring_index = color_index(gantt_process[i], &gantt_process[0], drawing_counter);

    float current_width = comp[i] - st[i];
    float current_start = st[i];
    float current_end = comp[i];

    if (arr[0] != 0){current_start = st[i] - arr[0]; current_end = comp[i] - arr[0];}

        rectangle = scene ->addRect(current_start*factor,0,current_width*factor,20);
        //rectangle->setBrush(QBrush(Qt::GlobalColor(i+6)));

         rectangle->setBrush(brush[coloring_index]);

        QGraphicsTextItem *text = scene->addText(gantt_process[i]);
        text->setPos((((current_start+current_end)*factor)-(text->boundingRect().width()))/2,0);

        QGraphicsTextItem *number_start = scene->addText(QString::number(st[i]));
        number_start->setPos(current_start*factor,19);

        QGraphicsTextItem *number_end = scene->addText(QString::number(comp[i]));
        number_end->setPos(current_end*factor,19);

        QGraphicsItem * waiting_time =  scene->addText("average waiting time: "+QString::number(avg_wt));
        waiting_time->setPos((st[0]-arr[0])*factor,80);

        }
        ui->pushButton_delete->show();
     }
   else QMessageBox::warning(this,"WARNING","PLEASE ENTER DATA FIRST");
}


void MainWindow::on_pushButton_delete_clicked() //clear
{
    ui->pushButton_2->show();  //update
    ui->table->setRowCount(0);
   scene = new QGraphicsScene(this);
   ui->graphicsView->setScene(scene);
   scene->clear();
   ui->spinBox_number_of_process->clear();
   ui->graphicsView->viewport()->update();

   total_service_Time =0;
   factor = 0;
   avg_wt = 0;
   i = 0;
   ui->pushButton_delete->hide();
}


void MainWindow::on_actionabout_us_triggered()
{

}

void MainWindow::on_actionabout_AAY_triggered()
{
    about_us aboutus;// making an object
    aboutus.setModal(true);
    aboutus.exec();

}
