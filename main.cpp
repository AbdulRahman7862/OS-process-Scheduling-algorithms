#include <iostream>
#include <vector>

struct Process
{
    int arrivalTime;
    int burstTime;
    int waitingTime;
    int turnaroundTime;
    int responseRatio;
};

void calculateWaitingTime(std::vector<Process> &processes)
{
    int totalWaitingTime = 0;

    processes[0].waitingTime = 0;

    for (size_t i = 1; i < processes.size(); i++)
    {
        processes[i].waitingTime = processes[i - 1].burstTime + processes[i - 1].waitingTime - processes[i].arrivalTime;

        if (processes[i].waitingTime < 0)
            processes[i].waitingTime = 0;

        totalWaitingTime += processes[i].waitingTime;
    }

    std::cout << "Total Waiting Time: " << totalWaitingTime << std::endl;
    std::cout << "Average Waiting Time: " << (float)totalWaitingTime / processes.size() << std::endl;
}

void calculateTurnaroundTime(std::vector<Process> &processes)
{
    int totalTurnaroundTime = 0;

    for (size_t i = 0; i < processes.size(); i++)
    {
        processes[i].turnaroundTime = processes[i].burstTime + processes[i].waitingTime;
        totalTurnaroundTime += processes[i].turnaroundTime;
    }

    std::cout << "Total Turnaround Time: " << totalTurnaroundTime << std::endl;
    std::cout << "Average Turnaround Time: " << (float)totalTurnaroundTime / processes.size() << std::endl;
}

void calculateResponseRatio(std::vector<Process> &processes)
{
    for (size_t i = 0; i < processes.size(); i++)
    {
        processes[i].responseRatio = (processes[i].waitingTime + processes[i].burstTime) / processes[i].burstTime;
    }
}

void hrrnScheduling(std::vector<Process> &processes)
{
    calculateResponseRatio(processes);

    std::cout << "Process\t Arrival Time\t Burst Time\t Waiting Time\t Turnaround Time\n";

    int currentTime = 0;

    for (size_t i = 0; i < processes.size(); i++)
    {
        int highestRatio = -1;
        int selectedProcess = -1;

        for (size_t j = 0; j < processes.size(); j++)
        {
            if (processes[j].arrivalTime <= currentTime && processes[j].responseRatio > highestRatio)
            {
                highestRatio = processes[j].responseRatio;
                selectedProcess = j;
            }
        }

        if (selectedProcess == -1)
        {
            std::cout << "No process to schedule at time " << currentTime << std::endl;
            currentTime++;
            i--;
            continue;
        }

        currentTime += processes[selectedProcess].burstTime;
        processes[selectedProcess].waitingTime = currentTime - processes[selectedProcess].arrivalTime - processes[selectedProcess].burstTime;

        std::cout << selectedProcess << "\t " << processes[selectedProcess].arrivalTime << "\t\t " << processes[selectedProcess].burstTime << "\t\t "
                  << processes[selectedProcess].waitingTime << "\t\t " << processes[selectedProcess].turnaroundTime << std::endl;

        processes[selectedProcess].responseRatio = -1;
    }

    calculateWaitingTime(processes);
    calculateTurnaroundTime(processes);
}

// code for srt
#include <climits>

struct SRTProcess
{
    int processID;
    int arrivalTime;
    int burstTime;
    int remainingTime;
    int waitingTime;
    int turnaroundTime;
};

void srtScheduling(std::vector<SRTProcess> &processes)
{
    int currentTime = 0;
    int completedProcesses = 0;
    int shortestProcessIndex;

    while (completedProcesses < processes.size())
    {
        shortestProcessIndex = -1;
        int shortestBurstTime = INT_MAX;

        for (size_t i = 0; i < processes.size(); i++)
        {
            if (processes[i].arrivalTime <= currentTime && processes[i].remainingTime < shortestBurstTime && processes[i].remainingTime > 0)
            {
                shortestProcessIndex = i;
                shortestBurstTime = processes[i].remainingTime;
            }
        }

        if (shortestProcessIndex == -1)
        {
            currentTime++;
            continue;
        }

        processes[shortestProcessIndex].remainingTime--;
        currentTime++;

        if (processes[shortestProcessIndex].remainingTime == 0)
        {
            completedProcesses++;

            processes[shortestProcessIndex].turnaroundTime = currentTime - processes[shortestProcessIndex].arrivalTime;
            processes[shortestProcessIndex].waitingTime = processes[shortestProcessIndex].turnaroundTime - processes[shortestProcessIndex].burstTime;
        }
    }
}

void calculateAverageTimes(const std::vector<SRTProcess> &processes)
{
    int totalWaitingTime = 0;
    int totalTurnaroundTime = 0;

    for (const auto &process : processes)
    {
        totalWaitingTime += process.waitingTime;
        totalTurnaroundTime += process.turnaroundTime;
    }

    float averageWaitingTime = static_cast<float>(totalWaitingTime) / processes.size();
    float averageTurnaroundTime = static_cast<float>(totalTurnaroundTime) / processes.size();

    std::cout << "Average Waiting Time: " << averageWaitingTime << std::endl;
    std::cout << "Average Turnaround Time: " << averageTurnaroundTime << std::endl;
}

void displayProcessInfo(const std::vector<SRTProcess> &processes)
{
    std::cout << "Process\t Arrival Time\t Burst Time\t Waiting Time\t Turnaround Time\n";

    for (const auto &process : processes)
    {
        std::cout << process.processID << "\t " << process.arrivalTime << "\t\t " << process.burstTime << "\t\t "
                  << process.waitingTime << "\t\t " << process.turnaroundTime << std::endl;
    }
}

// code for srt ended here

// final
struct AlgoProcess
{
    int processID;
    int arrivalTime;
    int burstTime;
};

void runProcessScheduling()
{
    int algo_nop, algo_count = 0, algo_y, algo_i, algo_quant, algo_waitingTime = 0, algo_turnAroundTime = 0;
    float algo_averageWaitingTime, algo_averageTurnaroundTime;

    std::cout << "Total number of processes in the system: ";
    std::cin >> algo_nop;
    algo_y = algo_nop;

    std::vector<int> algo_arrivalTime(algo_nop);
    std::vector<int> algo_burstTime(algo_nop);
    std::vector<int> algo_temp(algo_nop);

    for (algo_i = 0; algo_i < algo_nop; algo_i++)
    {
        std::cout << "\nEnter the arrival time and burst time of process " << algo_i + 1 << ":\n";
        std::cout << "Arrival time: ";
        std::cin >> algo_arrivalTime[algo_i];
        std::cout << "Burst time: ";
        std::cin >> algo_burstTime[algo_i];
        algo_temp[algo_i] = algo_burstTime[algo_i];
    }

    std::cout << "\nEnter the time quantum: ";
    std::cin >> algo_quant;

    std::cout << "\nProcess No\tBurst Time\tTurnaround Time\tWaiting Time\n";
    for (int algo_sum = 0, algo_i = 0, algo_done = 0; algo_done != algo_nop;)
    {
        if (algo_temp[algo_i] <= algo_quant && algo_temp[algo_i] > 0)
        {
            algo_sum += algo_temp[algo_i];
            algo_temp[algo_i] = 0;
            algo_count = 1;
        }
        else if (algo_temp[algo_i] > 0)
        {
            algo_temp[algo_i] -= algo_quant;
            algo_sum += algo_quant;
        }
        if (algo_temp[algo_i] == 0 && algo_count == 1)
        {
            algo_done++;
            std::cout << "Process " << algo_i + 1 << "\t\t" << algo_burstTime[algo_i] << "\t\t" << algo_sum - algo_arrivalTime[algo_i] << "\t\t" << algo_sum - algo_arrivalTime[algo_i] - algo_burstTime[algo_i] << std::endl;
            algo_waitingTime += algo_sum - algo_arrivalTime[algo_i] - algo_burstTime[algo_i];
            algo_turnAroundTime += algo_sum - algo_arrivalTime[algo_i];
            algo_count = 0;
        }
        if (algo_i == algo_nop - 1)
        {
            algo_i = 0;
        }
        else if (algo_arrivalTime[algo_i + 1] <= algo_sum)
        {
            algo_i++;
        }
        else
        {
            algo_i = 0;
        }
    }

    algo_averageWaitingTime = algo_waitingTime * 1.0 / algo_nop;
    algo_averageTurnaroundTime = algo_turnAroundTime * 1.0 / algo_nop;
    std::cout << "\nAverage Turnaround Time: " << algo_averageTurnaroundTime << std::endl;
    std::cout << "Average Waiting Time: " << algo_averageWaitingTime << std::endl;
}


int main()
{

    int choice;
    std::cout << "Process Scheduling Menu" << std::endl;
    std::cout << "1. HRRN" << std::endl;
    std::cout << "2. SRT" << std::endl;
    std::cout << "3. Round Robin" << std::endl;
    std::cout << "Enter your choice (1-3): ";
    std::cin >> choice;

    switch (choice)
    {
    case 1:
    {
        int n;
        std::cout << "Enter the number of processes: ";
        std::cin >> n;

        std::vector<Process> processes(n);

        std::cout << "Enter arrival time and burst time for each process:" << std::endl;

        for (int i = 0; i < n; i++)
        {
            std::cout << "Process " << i << ":" << std::endl;
            std::cout << "Arrival Time: ";
            std::cin >> processes[i].arrivalTime;
            std::cout << "Burst Time: ";
            std::cin >> processes[i].burstTime;
        }

        hrrnScheduling(processes);
    }
    break;
    case 2:
    {
        int numProcesses;
        std::cout << "Enter the number of processes: ";
        std::cin >> numProcesses;

        std::vector<SRTProcess> processes(numProcesses);

        std::cout << "Enter arrival time and burst time for each process:" << std::endl;

        for (int i = 0; i < numProcesses; i++)
        {
            std::cout << "Process " << i << ":" << std::endl;
            std::cout << "Arrival Time: ";
            std::cin >> processes[i].arrivalTime;
            std::cout << "Burst Time: ";
            std::cin >> processes[i].burstTime;

            processes[i].processID = i;
            processes[i].remainingTime = processes[i].burstTime;
        }

        srtScheduling(processes);
        calculateAverageTimes(processes);
        displayProcessInfo(processes);
    }
    break;
    case 3:
        runProcessScheduling();
        break;
    default:
        std::cout << "Invalid choice!" << std::endl;
        break;
    }

    return 0;
}
