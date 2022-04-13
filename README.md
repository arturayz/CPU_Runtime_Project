# CPU_Runtime_Project

The following was an assignment completed for an OPerating Systems class.

Given a file that will contain 3 numbers per line in the format:
x y z
x y z 
x y z
x y z
etc...

Where x will be the unique process ID (PID)
y will be the arrival time
z will be the CPU burst time

The objective output was to create a program capable of simulating the following processes.
FCFS: First Come First Serve
RR: Round Robin (no context switch value was provided, so decided to use a burst time of 3)
SRTF: Shortest Run Time First (preemptive, meaning if a new arriving process has a shorter run time, the program will switch to that one)

As provided by the screenshots the program was a success. 

Self-reflection:
As a point of self-critique and understanding the simplicity of the task at hand, the entire program was completed within the main function.

However, for purpose of both professional standards and efficiency the two solutions that would have been superior/more efficient to the one used, it would have been best to either create 3 separate functions for each process type with the passing of certain vectors as parameters, or even better creating a process class, and creating 3 child classes for; FCFS, RR and SRTF.

Note provided are the:
Sample .txt file used for the screenshots
The screenshots of the main file
And the main.cpp file itself.
