import math

def main():
    low_limit = pow(10, 13)
    upper_limit = pow(10, 16)
    number = get_long("Number: ")
    if not (number > low_limit and number < upper_limit):
        print("INVALID")
        exit(0)
    
    digits_list = [int(i) for i in str(number)]
    if verify_card(digits_list):
        print_card_type(digits_list)
    else:
        print("INVALID")

def get_long(message):
     while True:
        try:
            result = int(input(message))
            if result < 1:
                raise Exception
            return result
        except Exception as e:
            print("Please enter positive integer between 1 and 8 inclusive!")

def verify_card(digits_list):
    digit_len = len(digits_list)
    first_part = 0
    for index in range(digit_len - 2, -1, -2):
        temp_val = digits_list[index]
        temp_val *= 2

        if temp_val > 0:
            if temp_val < 10:
                first_part += temp_val
            else:
                first_part += 1
                first_part += temp_val % 10

    second_part = first_part
    for index in range(digit_len - 1, -1, -2):
        temp = digits_list[index]

        if temp > 0:
            second_part += temp
    
    return second_part % 10 == 0

def print_card_type(digits_list):
    visa_num = 4
    ax_num = 3
    master_num = 5

    for index in range(16):
        temp_val = digits_list[index]

        if temp_val > -1:
            first_digit = temp_val
            second_digit = digits_list[index + 1]
            break
    
    if first_digit == ax_num and (second_digit in [4,7]):
        print("AMEX")
    elif (first_digit == master_num and second_digit > 0 and second_digit < 6):
        print("MASTERCARD")
    elif first_digit == visa_num:
        print("VISA")
    else:
        print("INVALID")



main()