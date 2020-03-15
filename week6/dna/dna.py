import sys
import csv
import re

def main():
    args = sys.argv
    if len(args) != 3:
        print('Incorrect usage!\n Usage: python dna.py [arg1.csv] [arg2.txt]')
        sys.exit(1)
    csv_db_file_name = args[1]
    sequence_file_name = args[2]
    
    squence = ''
    with open(sequence_file_name) as seq_file:
        squence = seq_file.read()
    csv_rows = []
    with open(csv_db_file_name) as csv_file:
        reader = csv.reader(csv_file)

        for row in reader:
            csv_rows.append(row)
    
    header = csv_rows[0]
    data = csv_rows[0:]
    header_size = len(header)
    data_dict = {}

    for row_index in range(1, len(data)):
        appended_dict = {}
        nex_row = data[row_index]
        for index in range(1, header_size):
            appended_dict[header[index]] = nex_row[index]
        data_dict[nex_row[0]] = appended_dict

    patterns_dict = {}

    for item in header:
        if item != 'name':
            patterns_dict[item] = 0


    fill_max_sequenses(patterns_dict, squence)
    print_name_of_matched(data_dict, patterns_dict)


def fill_max_sequenses(patterns_dict, squence):
    for pattern in patterns_dict:
        max_count = get_max_seq_occurances(pattern, squence)
        patterns_dict[pattern] = max_count


def get_max_seq_occurances(pattern, squence):
    regex = "(({})+)".format(pattern)
    result = re.findall(regex,squence)
    max_occurances = 0
    for result_tuple in result:
        for match in result_tuple:
            size = len(match)/len(pattern)
            if size > max_occurances:
                max_occurances = size
    return max_occurances


def print_name_of_matched(data, patterns_dict):
    found = False
    for name, score_dict in data.items():
        found_mismatch = False
        for pattern, count in patterns_dict.items():
            

            if int(score_dict[pattern]) != count:
                found_mismatch = True
                break
        if not found_mismatch:
            found = True
            print(name)
            break
    
    if not found:
        print('No match')


main()