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
    new = 0
    for i in row1:
        if serin in i:
            new = 1
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
            new = 1
            ser.write(b"s")
            if svar %2 !=0:
                print("Entry!","\nUid:",j[0],"\nStudent Name:",j[1])
                svar += 1
            else:
                print("Exit!","\nUid:",j[0],"\nStudent Name:",j[1])
                svar -= 1
            break
    if new == 0:
        print("Unregistered ID Detected!")
        ch = input("Do you want to register this ID?[y or n]")
        if ch == "y":
            intype = input("Enter card type:\n1)Teacher\n2)Student\nEnter 1 or 2:")
            if intype == "1":
                uid = serin
                name = input("Enter teacher name:")
                sub = input("Enter subject:")
                insert = "insert into teachers(uid,name,sub) values(%s,%s,%s)"
                value = [(uid ,name ,sub )]
                cur.executemany(insert, value)
                print("Sucessfully registered")
            elif intype == "2":
                id = serin
                name = input("Enter Student name:")
                
                insert = "insert into students(uid,name) values(%s,%s)"
                value = [(uid ,name)]
                cur.executemany(insert, value)
                print("Sucessfully registered")
            else:
                print("invalid entry")
        elif ch == "n":
            pass
        else:
            print("invalid choice")
