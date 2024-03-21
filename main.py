import numpy as np
import heapq
import matplotlib.pyplot as plt
import random

class Node:
    def __init__(self, position, parent=None):
        self.position = position
        self.parent = parent
        self.g = 0
        self.h = 0
        self.f = 0

    def __eq__(self, other):
        return self.position == other.position

    def __lt__(self, other):
        return self.f < other.f

def astar(grid, start, goal):
    open_list = []
    closed_list = []

    start_node = Node(start)
    goal_node = Node(goal)

    heapq.heappush(open_list, (0, start_node))

    while open_list:
        current_node = heapq.heappop(open_list)[1]

        if current_node.position == goal_node.position:
            path = []
            current = current_node
            while current is not None:
                path.append(current.position)
                current = current.parent
            return path[::-1]

        closed_list.append(current_node)

        for next_position in [(0, 1), (0, -1), (1, 0), (-1, 0), (-1, -1), (-1, 1), (1, -1), (1, 1)]:
            node_position = (current_node.position[0] + next_position[0], current_node.position[1] + next_position[1])

            if node_position[0] >= len(grid) or node_position[0] < 0 or node_position[1] >= len(grid[0]) or node_position[1] < 0:
                continue

            if grid[node_position[0]][node_position[1]] != 0:
                continue

            new_node = Node(node_position, current_node)

            if new_node in closed_list:
                continue

            new_node.g = current_node.g + 1
            new_node.h = ((new_node.position[0] - goal_node.position[0]) ** 2) + ((new_node.position[1] - goal_node.position[1]) ** 2)
            new_node.f = new_node.g + new_node.h

            for _, open_node in open_list:
                if new_node == open_node and new_node.g > open_node.g:
                    continue

            heapq.heappush(open_list, (new_node.f, new_node))

    return None

def plan_paths(robot_states, goal_areas, ball_carrier_index):
    max_x = max(robot[0] for robot in robot_states)
    max_y = max(robot[1] for robot in robot_states)

    grid = np.zeros((60, 90))  # Set grid size to 60x90
    for x, y, _, _ in robot_states:
        grid[x][y] = 1  # Marking occupied positions

    paths = []
    for i, state in enumerate(robot_states):
        current_position = (state[0], state[1])
        goal_position = goal_areas[i]

        path = astar(grid, current_position, goal_position)
        if path:
            paths.append(path)
    
    # Mark the ball carrier with orange color
    for i in range(len(paths)):
        if i == ball_carrier_index:
            paths[i].append(paths[i][-1])  # Add the last position again to show the dot
    return paths

# Number of robots
num_robots = 5

# Randomly determine starting positions for robots
robot_states = []
for _ in range(num_robots):
    start_x = random.randint(0, 59)
    start_y = random.randint(0, 89)
    robot_states.append((start_x, start_y, 0, 0))

# Choose the ball carrier randomly
ball_carrier_index = random.randint(0, num_robots - 1)

# Create symmetrical field
field = np.zeros((60, 90))

# Penalty area
field[15:45, 5:25] = 1
field[15:45, 65:85] = 1

# Midfield circle
for i in range(60):
    for j in range(90):
        if np.sqrt((i - 30) ** 2 + (j - 45) ** 2) <= 9:
            field[i, j] = 1

# Goals within penalty area
for i in range(2):
    goal_x = random.randint(15, 44)
    goal_y = random.choice([65, 84])  # Placing goal area in the right penalty area
    field[goal_x, goal_y] = 1

# Goals
field[24:36, 0:3] = 1
field[24:36, 87:90] = 1

# Plot field with grid
plt.imshow(field, cmap='Greens_r', origin='lower', aspect='equal')
plt.title('Play Area')
plt.xlabel('X (10cm divisions)')
plt.ylabel('Y (10cm divisions)')

# Plot grid
plt.grid(color='black', linestyle='-', linewidth=1)

# Assign random colors to robots
colors = [plt.cm.viridis(np.random.rand()) for _ in range(num_robots)]

# Plot robots as circles
for i, (x, y, _, _) in enumerate(robot_states):
    plt.scatter(y, x, s=100, c=colors[i], marker='o', edgecolors='black')

# Place goal areas randomly within the penalty area
goal_areas = []
for _ in range(num_robots):
    goal_x = random.randint(15, 44)
    goal_y = random.choice([65, 84])  # Placing goal area in the right penalty area
    goal_areas.append((goal_x, goal_y))

# Plan paths for robots
planned_paths = plan_paths(robot_states, goal_areas, ball_carrier_index)

# Plot robot movements
for i, path in enumerate(planned_paths):
    x_positions = [pos[0] for pos in path]
    y_positions = [pos[1] for pos in path]
    plt.plot(y_positions, x_positions, marker='o', linestyle='-', color=colors[i])

# Plot ball carrier with orange dot
ball_carrier_x, ball_carrier_y, _, _ = robot_states[ball_carrier_index]
plt.plot(ball_carrier_y, ball_carrier_x, marker='o', markersize=5, color='orange')

# Plot goal areas
for goal in goal_areas:
    plt.scatter(goal[1], goal[0], s=100, c='yellow', marker='*', edgecolors='black')

plt.show()
