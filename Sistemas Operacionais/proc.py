import sys
from multiprocessing import Process, Pipe
import logging

# Configuração do Logger
logging.basicConfig(level=logging.INFO, format='%(asctime)s - %(levelname)s - %(message)s')

def process_sum(numbers, start, end, conn):
    logging.info(f"Processo filho iniciado, processando de {start} a {end-1}")
    result = sum(numbers[start:end])
    logging.info(f"Processo filho calculou a soma: {result}")
    conn.send(result)
    conn.close()

def main():
    if len(sys.argv) < 3:
        logging.error("Uso: python proc.py <filhos> <Intervalo>")
        sys.exit(1)
    
    num_children = int(sys.argv[1])
    numbers = list(map(int, sys.argv[2].split(',')))

    if num_children > len(numbers):
        logging.warning("Número de processos excede o número de elementos. Ajustando o número de processos.")
        num_children = len(numbers)

    chunk_size = len(numbers) // num_children
    remainder = len(numbers) % num_children

    processes = []
    parent_conns = []

    for i in range(num_children):
        start_index = i * chunk_size + min(i, remainder)
        end_index = start_index + chunk_size + (1 if i < remainder else 0)
        
        parent_conn, child_conn = Pipe()
        process = Process(target=process_sum, args=(numbers, start_index, end_index, child_conn))
        process.start()
        child_conn.close()
        
        processes.append(process)
        parent_conns.append(parent_conn)
        logging.info(f"Processo {process.pid} iniciado, responsável pelos índices de {start_index} a {end_index-1}")

    total_sum = 0
    for conn in parent_conns:
        partial_sum = conn.recv()
        total_sum += partial_sum
        logging.info(f"Recebido soma parcial: {partial_sum}, soma total até agora: {total_sum}")
        conn.close()

    for process in processes:
        process.join()
        logging.info(f"Processo {process.pid} concluído")

    logging.info(f"Soma total calculada: {total_sum}")
    print("Total:", total_sum)

if __name__ == "__main__":
    main()
