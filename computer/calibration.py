import serial
from time import sleep
from threading import Thread

ser = serial.Serial('COM3', 9600)

running = True

actionlist = ["low", "end",
              "high", "end"] + ["high", "end", "low", "end"] * 7
user_instructions = ["keep hand closed", "keep hand closed",
                     "keep hand closed", "keep hand closed",
                     
                     "open thumb", "open thumb",
                     "open thumb", "close thumb",
                     
                     "open index", "open index",
                     "open index", "close index",
                     
                     "open pinky", "open pinky",
                     "open pinky", "close pinky",
                     
                     "open thumb and index", "open thumb and index",
                     "open thumb and index", "close thumb and index",
                     
                     "open thumb and pinky", "open thumb and pinky",
                     "open thumb and pinky", "close thumb and pinky",
                     
                     "open index and pinky", "open index and pinky",
                     "open index and pinky", "close index and pinky",
                     
                     "open all fingers", "open all fingers",
                     "open all fingers", "close all fingers",]

data_points = ["hand closed",
               "hand closed",
               "extend thumb",
               "keep thumb",
               "extend index",
               "keep index",
               "extend pinky",
               "keep pinky",
               "extend thumb index",
               "keep thumb index",
               "extend thumb pinky",
               "keep thumb pinky",
               "extend index pinky",
               "keep index pinky",
               "extend thumb index pinky",
               "keep thumb index pinky"]

mode = "none"

f1, f2, f3, l1, l2, l3 = 0, 0, 0, 0, 0, 0
fluc1, fluc2, fluc3, last1, last2, last3 = 0, 0, 0, 0, 0, 0

def forever_while():
    global f1, f2, f3, l1, l2, l3
    global fluc1, fluc2, fluc3, last1, last2, last3
    global mode
    global running
    
    while running:
        if ser.in_waiting:
            fluc1, fluc2, fluc3, last1, last2, last3 = [float(i) for i in ser.readline().split()[:6]]
            if(mode == "high"):
                f1 = max(f1, fluc1)
                f2 = max(f2, fluc2)
                f3 = max(f3, fluc3)
                l1 = max(l1, last1)
                l2 = max(l2, last2)
                l3 = max(l3, last3)
            if(mode == "low"):
                f1 = min(f1, fluc1)
                f2 = min(f2, fluc2)
                f3 = min(f3, fluc3)
                l1 = min(l1, last1)
                l2 = min(l2, last2)
                l3 = min(l3, last3)
        sleep(0.005)

res = [];

def take_input():
    global f1, f2, f3, l1, l2, l3
    global fluc1, fluc2, fluc3, last1, last2, last3
    global mode

    index = 0
    
    while index < len(actionlist):
        action = actionlist[index]
        print(user_instructions[index])
        if(action == "low"):
            f1, f2, f3 = fluc1, fluc2, fluc3
            l1, l2, l3 = last1, last2, last3
            mode = "low"
        if(action == "high"):
            f1, f2, f3 = fluc1, fluc2, fluc3
            l1, l2, l3 = last1, last2, last3
            mode = "high"
        if(action == "end"):
            res.append([f1, f2, f3, l1, l2, l3])
            mode = "none"
        sleep(2)
        index+=1
        
if __name__ == '__main__':
    t1 = Thread(target=forever_while)
    t2 = Thread(target=take_input)
    t1.start()
    t2.start()
    t2.join()
    running = False
    for i in range(len(res)):
        print("double*", data_points[i].replace(" ", "_"), str(res[i])
              .replace("]", "};")
              .replace("[", "= new double[6] {")
              )
    
