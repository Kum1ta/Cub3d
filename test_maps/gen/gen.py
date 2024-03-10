import random
import sys

def generate_map(width, height):
    map_data = [[0 for _ in range(width)] for _ in range(height)]
    for i in range(width):
        map_data[0][i] = 1
        map_data[height - 1][i] = 1
    for i in range(height):
        map_data[i][0] = 1
        map_data[i][width - 1] = 1
    num_walls = int((width * height) * 0.2)
    for _ in range(num_walls):
        x = random.randint(1, width - 2)
        y = random.randint(1, height - 2)
        map_data[y][x] = 1
    
    return map_data

def print_map(map_data):
    for row in map_data:
        print(''.join(str(cell) for cell in row))

if __name__ == "__main__":
    
	if (len(sys.argv) != 3):
		print("Usage: python gen.py [width] [height]")
		sys.exit(1)
	width = int(sys.argv[1])
	height = int(sys.argv[2])
	map_data = generate_map(width, height)
	print('''NO ./textures/north_wall.jpg
SO ./textures/south_wall.jpg
WE ./textures/west_wall.jpg
EA ./textures/west_wall.jpg

C 30, 136, 243
F 207, 207, 207
''')
	print_map(map_data)