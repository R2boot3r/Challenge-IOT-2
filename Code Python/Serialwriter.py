# -*- coding: utf-8 -*-
"""
Spyder Editor

This is a temporary script file.
"""
import serial
import datetime
import csv



#il va falloir mettre un truc qui prend directement le bon periphérique
ser = serial.Serial('COM4') #/dev/ttyACM2
ser.flushInput()

#contient l'ensemble des ids de nos nodes lora

List_node_lora = ['123','321'] 

#attention ne pas oublier de mettre a la fin du fichier par la suite !

while True:

        ser_bytes = ser.readline()
        decoded_bytes = ser_bytes[0:len(ser_bytes)-2].decode("utf-8")
        print(decoded_bytes)
        
        
        data = decoded_bytes.split(";")
        
        if data[0] in List_node_lora:
            #print("bonjour")
            with open("test_data.csv","a") as f:
                writer = csv.writer(f,delimiter=";")
                now = datetime.datetime.now()
                string = now.strftime("%Y-%m-%d %H:%M:%S")+";"+decoded_bytes
                print(string)
                writer.writerow([string])
