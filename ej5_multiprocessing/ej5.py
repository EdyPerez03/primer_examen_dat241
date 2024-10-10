import multiprocessing as mp

def calcular_pi_parcial(inicio, fin):
    """Calcula una parte de la serie de Leibniz para Pi."""
    suma = 0.0
    for i in range(inicio, fin):
        term = (-1)**i / (2*i + 1)
        suma += term
    return suma

if __name__ == "__main__":
    n = 1000000  
    num_procesos = 3  
    rango = n // num_procesos  
    pool = mp.Pool(processes=num_procesos)

    resultados = [pool.apply_async(calcular_pi_parcial, (i*rango, (i+1)*rango)) for i in range(num_procesos)]

    pi = sum([res.get() for res in resultados]) * 4
    print("Número de términos hasta el cual calcular Pi  ",n)
    print("Numero de procesadores: ",num_procesos)
    print(f"Pi calculado con multiprocessing: {pi:.15f}")

    pool.close()
    pool.join()
