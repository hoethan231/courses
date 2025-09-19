import subprocess
import matplotlib.pyplot as plt

def main():
    timings = []
    size = []
    
    i = 2
    while i <= 2048:
        time = getTimes(i, i, i, i)
        timings.append(time)
        size.append(i)
        print(time)
        i *= 2
        
    plt.plot(size, timings)
    plt.xlabel("Matrix Size n*n")
    plt.ylabel("Execution Time in Seconds")
    plt.show()
    
def getTimes(r1, c1, r2, c2) -> float:
    try:
        subprocess.run(["gcc", "-o", "main", "matrix-mul.c"])
        result = subprocess.run(['./main', str(r1), str(c1), str(r2), str(c2), "1"], capture_output=True, text=True, check=True)
        return result.stdout

    except subprocess.CalledProcessError as e:
        print(f"Error executing C program: {e}")
        print(f"Stderr: {e.stderr}")
    except FileNotFoundError:
        print("Error: C program executable not found. Make sure it's compiled and in the correct path.")
    

if __name__ == "__main__":
    main()