change = [25, 10, 5, 1]

def main():
    money = int(get_float_input() * 100)
    coins = 0
    while (money > 0):
        for val in change:
            if (money >= val):
                money -= val
                coins += 1
                break
    
    print(coins)

def get_float_input():
    while True:
        money = input("Change owed: ")

        if is_float(money):
            float_val = float(money)
            if float_val > 0.00:
                return float_val

def is_float(value):
  try:
    float(value)
    return True
  except:
    return False

main()