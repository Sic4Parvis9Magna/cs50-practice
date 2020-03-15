height = input("Height: ")
while((len(height) != 1 or not height.isdigit()) or not (int(height) > 0 and int(height) < 9)):
    print('Heigh supposed to be greater than 0 and less than 9!')
    height = input("Height: ")


height = int(height)

for i in range(height):
    spaces = height - i - 1
    blocks = 1 + i
    print(' ' * spaces + '#' * blocks)