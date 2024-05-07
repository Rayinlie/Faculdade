import sys
import heapq
from collections import deque

class Process:
    def __init__(self, id, arrival_time, burst_time):
        # Inicializa um processo com identificador, tempo de chegada, e tempo de burst (execução).
        self.id = id
        self.arrival_time = arrival_time
        self.burst_time = burst_time
        self.remaining_time = burst_time  # Tempo restante para execução completa do processo.
        self.wait_time = 0  # Tempo de espera acumulado.
        self.response_time = None  # Tempo até o primeiro atendimento.
        self.completion_time = 0  # Tempo de finalização do processo.

    def __lt__(self, other):
        # Define a comparação de menor que, para o heap, baseado no tempo restante.
        return self.remaining_time < other.remaining_time


def input_processes():
    # Captura a entrada do usuário para a criação de uma lista de processos.
    processes = []
    n = int(input("Numero de processos: "))
    for i in range(n):
        arrival_time, burst_time = map(int, input(f"Tempo de chegada e Tempo de execução para o processo {i+1}: ").split())
        processes.append(Process(i+1, arrival_time, burst_time))
    return processes


def calculate_metrics(processes):
    total_wait_time = sum(p.wait_time for p in processes)   
    return total_wait_time

def display_results(processes, scheduling_type):
    print(f"Escalonamento: \n{scheduling_type}")
    for p in processes:
        print(f"Processo {p.id}: Tempo de chegada={p.arrival_time}, Tempo de execução={p.burst_time}, Tempo de espera={p.wait_time}, Tempo de resposta={p.response_time}, Completo={p.completion_time}")
    print(f"Tempo de espera total: {calculate_metrics(processes)}")

def fcfs_scheduling(processes):
    # Implementação do escalonamento First-Come, First-Served.
    time = 0
    for process in sorted(processes, key=lambda x: x.arrival_time):
        if time < process.arrival_time:
            time = process.arrival_time
        if process.response_time is None:
            process.response_time = time - process.arrival_time
        process.wait_time = time - process.arrival_time
        time += process.burst_time
        process.completion_time = time


def rr_scheduling(processes, quantum):
    # Implementação do escalonamento Round Robin.
    queue = deque(sorted(processes, key=lambda x: x.arrival_time))
    time = 0
    while queue:
        process = queue.popleft()
        if process.response_time is None:
            process.response_time = time - process.arrival_time
        execution_time = min(process.remaining_time, quantum)
        process.remaining_time -= execution_time
        time += execution_time
        if process.remaining_time > 0:
            queue.append(process)
        else:
            process.completion_time = time
            process.wait_time = process.completion_time - process.arrival_time - process.burst_time


def sjf_scheduling(processes, preemptive=False):
    # Implementação do Shortest Job First, com opção preemptiva.
    processes = sorted(processes, key=lambda x: (x.arrival_time, x.burst_time))
    time = 0
    ready_queue = []
    while processes or ready_queue:
        if not ready_queue:
            process = processes.pop(0)
            time = max(time, process.arrival_time)
        else:
            process = heapq.heappop(ready_queue)

        if process.response_time is None:
            process.response_time = time - process.arrival_time

        if preemptive and processes and processes[0].arrival_time <= time + process.remaining_time:
            next_process = processes.pop(0)
            needed_time = next_process.arrival_time - time
            process.remaining_time -= needed_time
            time += needed_time
            if process.remaining_time > 0:
                heapq.heappush(ready_queue, process)
            heapq.heappush(ready_queue, next_process)
        else:
            time += process.remaining_time
            process.completion_time = time
            process.wait_time = process.completion_time - process.arrival_time - process.burst_time
            process.remaining_time = 0
        
        while processes and processes[0].arrival_time <= time:
            heapq.heappush(ready_queue, processes.pop(0))


def main():
    # Coleta os processos de entrada e executa os algoritmos de escalonamento.
    processes_input = input_processes()
    quantum = int(input("Quantum para Round Robin: "))
    scheduling_algorithms = [
        (fcfs_scheduling, []),
        (rr_scheduling, [quantum]),
        (sjf_scheduling, [False])  # Não preemptivo
    ]
    for algorithm, args in scheduling_algorithms:
        processes = [Process(p.id, p.arrival_time, p.burst_time) for p in processes_input]
        algorithm(processes, *args)
        display_results(processes, algorithm.__name__)

if __name__ == "__main__":
    main()

