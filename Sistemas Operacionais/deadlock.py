def init_resources(total_resources):
    # Retorna uma cópia da lista de recursos totais disponíveis.
    return [total_resources[i] for i in range(len(total_resources))]

def init_allocation(n_processes, n_resources):
    # Cria uma matriz de alocação para os processos com todos os valores iniciados em 0.
    return [[0] * n_resources for _ in range(n_processes)]

def init_max_demand(n_processes, n_resources, demands):
    # Retorna a lista de demandas máximas para cada processo.
    return [demands[i] for i in range(n_processes)]

def find_deadlock(allocation, max_demand, available):
    # Implementação de detecção de deadlock usando um algoritmo baseado no estado seguro.
    n_processes = len(allocation)
    work = available[:]  # Cópia dos recursos disponíveis.
    finish = [False] * n_processes  # Estado de finalização de cada processo.
    
    while True:
        made_progress = False
        for i in range(n_processes):
            # Verifica se o processo pode ser concluído com os recursos disponíveis.
            if not finish[i] and all(max_demand[i][j] - allocation[i][j] <= work[j] for j in range(len(available))):
                for k in range(len(available)):
                    work[k] += allocation[i][k]  # Libera recursos do processo concluído.
                finish[i] = True  # Marca o processo como concluído.
                made_progress = True
                break
        if not made_progress:
            break
    return not all(finish)  # Retorna True se houver deadlock, isto é, se nem todos os processos puderem terminar.


def test_without_deadlock():
    # Testa um cenário onde não existe deadlock.
    total_resources = [3, 2]
    available = init_resources(total_resources)
    allocation = [[1, 0], [1, 1]]
    max_demand = [[2, 1], [2, 2]]
    print("Testando ambiente sem deadlock:")
    if find_deadlock(allocation, max_demand, available):
        print("Deadlock detectado.")
    else:
        print("Nenhum deadlock detectado.")


def test_with_deadlock():
    # Testa um cenário onde existe deadlock.
    total_resources = [1, 1]
    available = [0, 0]  # Todos os recursos estão alocados.
    allocation = [[1, 0], [0, 1]]
    max_demand = [[1, 1], [1, 1]]
    print("Testando ambiente com deadlock:")
    if find_deadlock(allocation, max_demand, available):
        print("Deadlock detectado.")
    else:
        print("Nenhum deadlock detectado.")


def is_safe_state(processes, available, allocation, max_demand):
    work = available[:]
    finish = [False] * len(processes)
    while True:
        made_progress = False
        for i in range(len(processes)):
            if not finish[i] and all(max_demand[i][j] - allocation[i][j] <= work[j] for j in range(len(work))):
                for j in range(len(work)):
                    work[j] += allocation[i][j]
                finish[i] = True
                made_progress = True
                break
        if not made_progress:
            break
    return all(finish)

def request_resources(process_id, request, processes, available, allocation, max_demand):
    # Simula um pedido de recursos, verificando se é seguro conceder os recursos sem causar um deadlock.
    if all(request[j] <= max_demand[process_id][j] - allocation[process_id][j] for j in range(len(request))):
        if all(request[j] <= available[j] for j in range(len(request))):
            # Faz alterações temporárias para verificar o estado seguro.
            temp_available = [available[j] - request[j] for j in range(len(available))]
            temp_allocation = [allocation[process_id][j] + request[j] for j in range(len(request))]
            temp_allocations = [row[:] for row in allocation]
            temp_allocations[process_id] = temp_allocation
            if is_safe_state(processes, temp_available, temp_allocations, max_demand):
                # Atualiza o estado real se for seguro.
                for j in range(len(request)):
                    available[j] -= request[j]
                    allocation[process_id][j] += request[j]
                return True
    return False


def test_prevention_with_bankers_algorithm():
    # Testa o algoritmo do banqueiro para prevenção de deadlocks.
    total_resources = [3, 3]
    available = init_resources(total_resources)
    allocation = [[1, 2], [2, 1]]
    max_demand = [[3, 3], [3, 3]]
    processes = [0, 1]
    request = [1, 1]  # Solicitação de recursos pelo processo 1.
    
    print("Teste de ambiente com alguritmo de prevenção de deadlock (Banqueiro) e deadlock existente:")
    if request_resources(1, request, processes, available, allocation, max_demand):
        print("Acesso garantido.")
    else:
        print("Solicitação negada. Deadlock evitado.")

    if find_deadlock(allocation, max_demand, available):
        print("Deadlock detectado.")
    else:
        print("Nenhum deadlock detectado.")

if __name__ == "__main__":
    test_without_deadlock()
    test_with_deadlock()
    test_prevention_with_bankers_algorithm()