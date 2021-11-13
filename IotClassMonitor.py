import serial
import time
import mysql.connector as sql

tvar = 1
svar = 1
ser = serial.Serial("COM3",9600)
con = sql.connect(
                    host="localhost",
                    user="root",
                    passwd="",
                    database="classrec"
                )
cur = con.cursor()
while True:
    serin = (ser.readline().decode()).strip()
    cur.execute("select * from teachers")
    row1 = cur.fetchall()
    cur.execute("select * from students")
    row2 = cur.fetchall()
    for i in row1:
        if serin in i:
            ser.write(b"t")
            if tvar %2 !=0:
                print("Entry!","\nUid:",i[0],"\nTeacher Name:",i[1],"\nSubject:",i[2])
                tvar += 1
            else:
                print("Exit!","\nUid:",i[0],"\nTeacher Name:",i[1],"\nSubject:",i[2])
                tvar -= 1
            break
    for j in row2:
        if serin in j:
            ser.write(b"s")
            if svar %2 !=0:
                print("Entry!","\nUid:",j[0],"\nStudent Name:",j[1])
                svar += 1
            else:
                print("Exit!","\nUid:",j[0],"\nStudent Name:",j[1])
                svar -= 1
            break
