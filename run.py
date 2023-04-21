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

check_points = [int(int(value) * 0.7) for value in max_nodes.values()]
NUM_ITERATIONS = 500

for g in [str(i) for i in range(22,26)]:
    if g == "26":
        break
    try:
        os.mkdir(f"./results/exp_retry_g{g}")
    except:
        pass
    subprocess.call(["./main.exe",g,str((int(max_nodes[g])*1.2/4)*4), \
                    str(NUM_ITERATIONS),str(check_points[int(g) - 5]),f"./results/exp_retry_g{g}/log"])

for g in [str(i) for i in range(26,31)]:
    try:
        os.mkdir(f"./results/exp_g{g}")
    except:
        pass

    subprocess.call(["./main.exe",g,str((int(max_nodes[g])*1.2/4)*4), \
                    str(20),str(check_points[int(g) - 5]),f"./results/exp_g{g}/log"])



check_points = [int(int(value) * 0.6) for value in max_nodes.values()]
for g in [str(i) for i in range(14,26)]:
    try:
        os.mkdir(f"./results/exp_g{g}_check_0_6")
    except:
        pass
    subprocess.call(["./main.exe",g,str((int(max_nodes[g])*1.2/4)*4), \
                str(NUM_ITERATIONS),str(check_points[int(g) - 5]),f"./results/exp_g{g}_check_0_6/log"])


"""
check_points = [int(int(value) * 0.75) for value in max_nodes.values()]
for g in [str(i) for i in range(14,26)]:
    try:
        os.mkdir(f"./results/exp_g{g}_check_0_75")
    except:
        pass
    subprocess.call(["./main.exe",g,str((int(max_nodes[g])*1.2/4)*4), \
                str(NUM_ITERATIONS),str(check_points[int(g) - 5]),f"./results/exp_g{g}_check_0_75/log"])

"""
check_points = [int(int(value) * 75) for value in max_nodes.values()]
for g in [str(i) for i in range(14,31)]:
    try:
        os.mkdir(f"./results/exp_g{g}_GF_regular")
    except:
        pass
    if int(g) > 25:
        NUM_ITERATIONS = 20
    subprocess.call(["./main.exe",g,str((int(max_nodes[g])*1.2/4)*4),str(NUM_ITERATIONS), \
                str(check_points[int(g) - 5]),f"./results/exp_g{g}_GF_regular/log"])

