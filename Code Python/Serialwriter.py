# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import serial
import time
import csv



#il va falloir mettre un truc qui prend directement le bon periphérique
ser = serial.Serial('/dev/ttyACM0')
ser.flushInput()

#contient l'ensemble des ids de nos nodes lora

List_node_lora = [123,234] 

#attention ne pas oublier de mettre a la fin du fichier par la suite !

while True:

        ser_bytes = ser.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
        
        
        
        
        
        
        
        
        
        with open("test_data.csv","a") as f:
            writer = csv.writer(f,delimiter=";")
            writer.writerow([decoded_bytes,time.time()])
