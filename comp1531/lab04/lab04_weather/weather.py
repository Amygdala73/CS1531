import datetime
import csv

def weather(date, location):
    [day, month, year] = date.split('-')
    date = f"{year}-{month}-{day}"
    with open('weatherAUS.csv') as f:
        sum_min = 0
        sum_max = 0
        min_len = 0
        max_len = 0
        min_temp = 0
        max_temp = 0
        csv_reader = csv.reader(f, delimiter = ',')
        for row in csv_reader:
            if row[1] is location:
                if row[2] != 'NA':
                    sum_min += float(row[2])
                    min_len += 1
                if row[3] != 'NA':
                    sum_max += float(row[3])
                    max_len += 1
            elif row[0] is date and row[1] is location:
                min_temp = float(row[2])
                max_temp = float(row[3])

        min_avg = sum_min/min_len
        max_avg = sum_max/max_len
        try:
            above_min = min_avg - min_temp
            above_max = max_avg - max_temp

            return (round(abs(above_min), 1), round(abs(above_max), 1))
        except ZeroDivisionError:
            return (None, None)
