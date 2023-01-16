import subprocess 
import os

max_nodes = {
#    g   max_n
    "5": "8",
    "6": "12",
    "7": "20",
    "8": "24",
    "9": "28",
    "10": "44",
    "11": "48",
    "12": "72",
    "13": "92",
    "14": "128",
    "15": "176",
    "16": "232",
    "17": "332",
    "18": "452",
    "19": "640",
    "20": "904",
    "21": "1272",
    "22": "1786",
    "23": "2536",
    "24": "3560",
    "25": "5044",
    "26": "7124",
    "27": "10132",
    "28": "14488",
    "29": "20812",
    "30": "29784"
}

NUM_ITERATIONS = 10000

for g in max_nodes:
    if g == "26":
        break
    os.mkdir(f"./results/exp_g{g}")
    subprocess.call(["./main.exe",g,max_nodes[g],str(NUM_ITERATIONS),f"results/exp_g{g}/log"]) 