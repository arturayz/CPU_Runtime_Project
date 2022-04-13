#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int main()
{
    ifstream inputFile;
    int number;

    //Get file name
    string name;
    cout<<"What is the name of the file you would like opened?"<<endl;
    cin>>name;

    // Open the file.
    inputFile.open(name);

    //Create the initial vectors for PID, Arrival Time, Burst Time, finish time, waiting time, turn around time and number of context switches.
    vector<int> pid;
    vector<int> arrival;
    vector<int> burst;
    vector<int> finish;
    vector<int> waiting;
    vector<int> turnaround;
    vector<int> context_switches;
    int counter = 0;

    // Read the numbers from the file and add them to their respective vectors
    while (inputFile >> number)
    {
        if(counter % 3 == 0){
            pid.push_back(number);
        }
        else if(counter % 3 == 1){
            arrival.push_back(number);
        }
        else{
            burst.push_back(number);
        }
        counter++;
    }

    // Close the file.
    inputFile.close();

    int user_choice;
    bool finished = false;

    while(!finished){

        cout<<endl;
        cout<<"Press 1 for FCFS (first come first serve)\nPress 2 for RR (Round Robin)\nPress 3 for SRTF (shortest run time first preemptive)\nPress 0 to exit\n";
        cin>>user_choice;
        cout<<endl;

        //FCFS Portion
        if(user_choice == 1){
            cout<<"**********FCFS**********"<<endl;
            cout<<"************************"<<endl;

            finish.push_back(burst[0]);
            waiting.push_back(0);
            turnaround.push_back(burst[0]);
            context_switches.push_back(0);

            //Actually doing the math
            for(int i = 0; i< pid.size()-1; i++){
                finish.push_back(finish[i]+burst[i+1]);
                waiting.push_back(finish[i]-arrival[i+1]);
                turnaround.push_back(finish[i+1]-arrival[i+1]);
                context_switches.push_back(0);
            }

            //Displaying All Data
            cout<<"PID  Arrival  Burst  Finish  Waiting  Turnaround  Context_Switches"<<endl;
            for(int i = 0; i<pid.size(); i++){
                cout<<pid[i]<<"    ";
                cout<<arrival[i]<<"        ";
                cout<<burst[i]<<"        ";
                cout<<finish[i]<<"       ";
                cout<<waiting[i]<<"       ";
                cout<<turnaround[i]<<"        ";
                cout<<context_switches[i]<<endl;
            }

            //Flow
            cout<<"************************"<<endl;
            cout<<""<<endl;
            for(int i = 0; i<pid.size(); i++){
                cout<<"P"<<pid[i];
                for(int j = 0; j<burst[i]; j++){
                    cout<<"*";
                }
            }

            //Overall Stats
            cout<<""<<endl;
            cout<<""<<endl;
            cout<<"************************"<<endl;
            double avg_burst = 0;
            double wait_time = 0;
            double avg_turnaround = 0;
            int total_switches = 0;

            //getting the final numbers
            for(int i = 0; i<pid.size(); i++){
                avg_burst+=burst[i];
                wait_time+=waiting[i];
                avg_turnaround+=turnaround[i];
                total_switches+=context_switches[i];
            }
            avg_burst= avg_burst/pid.size();
            wait_time = wait_time/pid.size();
            avg_turnaround = avg_turnaround/pid.size();

            //Printing results
            cout<<"Average burst time: "<<avg_burst<<"ms"<<endl;
            cout<<"Average wait time: "<<wait_time<<"ms"<<endl;
            cout<<"Average turn around time: "<<avg_turnaround<<"ms"<<endl;
            cout<<"Total num of context switches: "<<total_switches<<endl;

        }

        //Round Robin
       else  if(user_choice == 2){
            vector<int> burst_remaining;

            cout<<"***********RR***********"<<endl;
            cout<<"************************"<<endl;
            cout<<""<<endl;

            //Zeros all varied data and gets burst remaining
            for(int i = 0; i<pid.size(); i++){
                finish.push_back(0);
                waiting.push_back(0);
                turnaround.push_back(0);
                context_switches.push_back(0);
            }
            for(int i = 0; i<burst.size(); i++){
                burst_remaining.push_back(burst[i]);
            }

            //Basically total burst time and other key values
            int value = 3;
            int elapsed = 0;
            int total_rem = 0;
            for(int i = 0; i<burst.size(); i++){
                total_rem+=burst[i];
            }

            //Doing the math and flow
            int index = 0;
            while(total_rem>0){
                if(burst_remaining[index]< value && burst_remaining[index]>0){
                    cout<<"P"<<pid[index];
                    for(int i = 0; i< burst_remaining[index]; i++){
                        cout<<"*";
                    }
                    total_rem-=burst_remaining[index];
                    elapsed+=burst_remaining[index];
                    burst_remaining[index]=0;
                    finish[index]=elapsed;
                    for(int i = 0; i<pid.size(); i++){
                        if(i!=index){
                            waiting[i]+=burst_remaining[index];
                        }
                    }
                    index++;
                }
                else if(burst_remaining[index] >= value){
                    cout<<"P"<<pid[index]<<"***";
                    burst_remaining[index]-=value;
                    elapsed+=3;
                    for(int i = 0; i<pid.size(); i++){
                        if(i!=index){
                            waiting[i]+=3;
                        }
                    }
                    if(burst_remaining[index]>0){
                        context_switches[index]+=1;
                    }
                    else{
                        finish[index]=elapsed;
                    }
                    total_rem-=3;
                    index++;
                }
                else{
                    index++;
                }
                if(index==pid.size()){
                    index = 0;
                }
            }
            cout<<""<<endl;
            cout<<""<<endl;

            //getting turnaround time
            for(int i = 0; i< pid.size(); i++){
                turnaround[i]= finish[i]-arrival[i];
            }

            //printing chart
            cout<<"PID  Arrival  Burst  Finish  Waiting  Turnaround  Context_Switches"<<endl;
            for(int i = 0; i<pid.size(); i++){
                cout<<pid[i]<<"    ";
                cout<<arrival[i]<<"        ";
                cout<<burst[i]<<"        ";
                cout<<finish[i]<<"       ";
                cout<<waiting[i]<<"       ";
                cout<<turnaround[i]<<"        ";
                cout<<context_switches[i]<<endl;
            }

            cout<<""<<endl;
            cout<<"************************"<<endl;
            double avg_burst = 0;
            double wait_time = 0;
            double avg_turnaround = 0;
            int total_switches = 0;

            //getting the final numbers
            for(int i = 0; i<pid.size(); i++){
                avg_burst+=burst[i];
                wait_time+=waiting[i];
                avg_turnaround+=turnaround[i];
                total_switches+=context_switches[i];
            }
            avg_burst= avg_burst/pid.size();
            wait_time = wait_time/pid.size();
            avg_turnaround = avg_turnaround/pid.size();

            //Printing results
            cout<<"Average burst time: "<<avg_burst<<"ms"<<endl;
            cout<<"Average wait time: "<<wait_time<<"ms"<<endl;
            cout<<"Average turn around time: "<<avg_turnaround<<"ms"<<endl;
            cout<<"Total num of context switches: "<<total_switches<<endl;

        }

        //SRTF Portion
        else if(user_choice==3){
            vector<int> burst_remaining;

            int total_rem = 0;
            for(int i = 0; i<burst.size(); i++){
                total_rem+=burst[i];
            }

            cout<<"**********SRTF**********"<<endl;
            cout<<"************************"<<endl;
            cout<<""<<endl;

            //Zeros all varied data and gets burst remaining
            for(int i = 0; i<pid.size(); i++){
                finish.push_back(0);
                waiting.push_back(0);
                turnaround.push_back(0);
                context_switches.push_back(0);
            }
            for(int i = 0; i<burst.size(); i++){
                burst_remaining.push_back(burst[i]);
            }

            int index = 0;
            int last_index = 0;
            int elapsed = 0;
            int smallest = 100;
            while (total_rem>0){
                int smallest = 100;
                last_index = index;
                for(int i = 0; i< pid.size(); i++){
                    if((burst_remaining[i] > 0) && (burst_remaining[i] < smallest) && (elapsed>=arrival[i])){
                        smallest=burst_remaining[i];
                        index = i;
                    }
                }
                cout<<"P"<<pid[index]<<"*";
                elapsed++;
                for(int i = 0; i< pid.size(); i++){
                    if(i!=index){
                        waiting[i]++;
                    }
                }
                burst_remaining[index]--;
                if(burst_remaining[index]==0){
                    finish[index]=elapsed;
                }
                if(last_index!=index){
                    context_switches[last_index]++;
                }
                total_rem--;
            }

            //getting turnaround time
            for(int i = 0; i< pid.size(); i++){
                turnaround[i]= finish[i]-arrival[i];
            }

            //printing chart
            cout<<""<<endl;
            cout<<"************************"<<endl;
            cout<<"PID  Arrival  Burst  Finish  Waiting  Turnaround  Context_Switches"<<endl;
            for(int i = 0; i<pid.size(); i++){
                cout<<pid[i]<<"    ";
                cout<<arrival[i]<<"        ";
                cout<<burst[i]<<"        ";
                cout<<finish[i]<<"       ";
                cout<<waiting[i]<<"       ";
                cout<<turnaround[i]<<"        ";
                cout<<context_switches[i]<<endl;
            }

            cout<<""<<endl;
            cout<<"************************"<<endl;
            double avg_burst = 0;
            double wait_time = 0;
            double avg_turnaround = 0;
            int total_switches = 0;

            //getting the final numbers
            for(int i = 0; i<pid.size(); i++){
                avg_burst+=burst[i];
                wait_time+=waiting[i];
                avg_turnaround+=turnaround[i];
                total_switches+=context_switches[i];
            }
            avg_burst= avg_burst/pid.size();
            wait_time = wait_time/pid.size();
            avg_turnaround = avg_turnaround/pid.size();

            //Printing results
            cout<<"Average burst time: "<<avg_burst<<"ms"<<endl;
            cout<<"Average wait time: "<<wait_time<<"ms"<<endl;
            cout<<"Average turn around time: "<<avg_turnaround<<"ms"<<endl;
            cout<<"Total num of context switches: "<<total_switches<<endl;

        }

        //Exit
        else if(user_choice == 0){
            cout<<"Program exited";
            finished = true;
        }

        else{
            cout<<"Response not valid, please provide valid response."<<endl;
        }

    }

    return 0;
}