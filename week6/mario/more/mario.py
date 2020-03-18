divide_spaces = 2

def main():
    height = get_positive_int()
    for i in range(height):
        spaces = height - i -1
        points = i + 1

        print(' ' * spaces, end='')
        print('#' * points, end='')
        print(' ' * divide_spaces, end='')
        print('#' * points)


def get_positive_int():
    while True:
        try:
            result = int(input("Heigh: "))
            if result < 1 or result > 8:
                raise Exception
            return result
        except Exception as e:
            print("Please enter positive integer between 1 and 8 inclusive!")

main()