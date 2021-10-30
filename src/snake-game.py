# Use this python script as a reference for the snake game
#
# Attention:
# - There might be bugs in the code
# - Maybe we did not consider everything

# #%% are code cells in visual studio 2017 or 2019

#%% Imports

import time
import numpy as np
from itertools import *

#%% Globals

# Parameters below result in 1 294 380 000 states (~ 1e9)
# with roughly 4.8 GB of Memory required for V assuming a 32 bit datatype in numpy
#
# Run with caution:
# c = count_combinations()
# V = np.zeros((c,), dtype = np.float32)
#
# print(V.nbytes / 1024**3) # ~ 4.822 GB
#
# Note: A large np.zero array goes first to hard disk (and remains uninitialized), so memory
#       is not a direct problem as long as you do not modify the array
#       If you want to have it in memory try something like
#       np.random.randint(10, size = (c,), dtpye = np.int32)

X = 7
Y = 7
L = 5
L_0 = 3

# Action in terms of successor field of snake's head
up = (-1, 0)
down = (1, 0)
left = (0, -1)
right = (0, 1)

all_actions = [up, down, left, right]

# The randomness in this environment due to the drunken snake, with this probability the wrong
# action is executed
p = 0.2

# Position of the head
snake_pos = (5, 5)

# A fixed exemplary state represented as tuple
snake = [snake_pos, left, left, left]

# Here the goal is extra
goal = (1, 1)

# Used to move the snake's body
opposite_dir = {up: down,
                down: up,
                left: right,
                right: left}

# Used to calculate the changed direction when drunkenness kicks in
# "Rotation by 90 degree clockwise"
shifted_dir = {up: right,
               right: down,
               down: left,
               left: up}

# For printing
conversion = {0: ".",
              1: "x",
              2: "O",
              3: "+"}

#%% Functions

def random_position():
  return np.random.randint(0, X), np.random.randint(0, Y)
def random_action():
  return all_actions[np.random.randint(0, 4)]
def random_body(l):

  # Start with a random direction (after head) for first segment
  body = [random_action()]

  # Then attach the remaining ones
  for _ in range(1, l):
    # Exclude the back direction
    choices = [a for a in all_actions if a is not opposite_dir[body[-1]]]
    body.append(choices[np.random.randint(0, len(choices))])

  return tuple(body)
def initial_snake(l=L_0):

  valid_snake = False

  # Similar to rejection sampling?
  while not valid_snake:

    # Get a snake, maybe it has a self collision (depends on length)
    a_snake = (random_position(),) + random_body(l-1)

    # Verify it, if valid stop and return
    valid_snake = not self_collision(a_snake)
  #end

  return a_snake

def convert_symbols(s):
  """ A function to be mapped on rows of the field """
  return conversion[s]

def print_field(field):
  field2 = [list(map(convert_symbols, line)) for line in field]
  field2 = str.join("\n", [str.join(" ", line) for line in field2])
  print(field2)

def wrap_around(pos):
  px, py = pos

  if px < 0:
    px = X-1
  if py < 0:
    py = Y-1

  if px >= X:
    px = 0
  if py >= Y:
    py = 0

  return px, py

def add(p1, p2):
  return p1[0] + p2[0], p1[1] + p2[1]

def add_wrap(p1, p2):
  return wrap_around(add(p1, p2))

def snake_to_field(a_snake, a_goal):
  field = np.zeros((X, Y), dtype=np.int32)

  field[a_goal] = 3

  pos = a_snake[0]
  field[pos] = 2

  for s in a_snake[1:]:
    pos = add_wrap(pos, s)

    field[pos] = 1
  #end

  return field

def self_collision(a_snake):
  """
  Find collision by counting how many times a tile in the grid is occupied.
  Maybe not the most elegant solution, a quick and dirty solution was needed.
  """
  field = np.zeros((X, Y), dtype=np.int32)

  pos = a_snake[0]
  field[pos] += 1

  for s in a_snake[1:]:
    pos = add_wrap(pos, s)

    field[pos] += 1
  #end

  return np.any(field > 1)

def drunken_direction(a_snake, desired_direction):
  """
  First step is to calculate the possible directions.
  This depends on the snake and its viewing direction

  An example:
  . . . . . . . . . . .
  . . . . . . . . . . .
  . . . . x x x x x . .
  . . 1 . x . . . . . .
  . 2 O x x . . . . . .
  . . 3 . . . . . . . .
  . . . . . . . . . . .

  The three numbers 1,2,3 correspond to the actions up, left, down

  From the viewpoint of the snake the actions can be labeled as
  1 = right
  2 = forward
  3 = left

  The drunkenness causes a shift to the right based on the probability
  defined at the beginning, i.e. assuming drunkenness p = 0.2:

  forward -> 80% forward and 20% right
  left -> 80% left and 20% forward
  right -> 100% right

  Once we have the possible actions, one can be picked based on drunkenness
  """

  # Viewing direction of snake is the opposite direction in which the first body part
  # comes
  snake_dir = opposite_dir[a_snake[1]]

  # Special case when desired_direction equals to snake's right direction
  # Only one choice with full probability mass
  if shifted_dir[snake_dir] == desired_direction:
    all_a = [desired_direction]
    all_p = [1.0]

  # Else two direction can occur
  # Probability mass is split according to drunkenness
  else:
    all_a = [desired_direction, shifted_dir[desired_direction]]
    all_p = [1.0 - p, p]

  return all_a[np.random.choice(range(len(all_a)), p=all_p)]

def move(a_snake, a_goal, direction):

  if direction == a_snake[1]:
    raise Exception("Invalid action")

  # Apply noise to movement direction
  direction = drunken_direction(a_snake, direction)

  # With modified direction move the body
  new_snake = [add_wrap(a_snake[0], direction)] + [opposite_dir[direction]]

  # whether last part gets removed depends on head and goal position
  if new_snake[0] == a_goal:
    new_snake += a_snake[1:]
    a_goal = random_position()
  else:
    new_snake += a_snake[1:-1]

  # Reset bahivor, len(snake) > L implies that length 10 can occur, 
  # once the 11th body part is attached the reset happens
  if self_collision(new_snake) or len(new_snake) > L:
    new_snake = initial_snake()
    a_goal = random_position()

  return new_snake, a_goal

def move_print(a_snake, a_goal, direction):
  new_snake, a_goal = move(a_snake, a_goal, direction)
  print_field(snake_to_field(new_snake, a_goal))
  return new_snake, a_goal

def step(direction):
  """ For playing snake in the console """
  global snake, goal
  snake, goal = move_print(snake, goal, direction)

def count_snake_configuration():
  c = 0

  # Only till L because the head is added later
  # Thanks to Jakob: start length is 2 in our case -> less states because
  #                  we have to start at length L_0 minus the head
  for l in range(L_0 - 1, L):
    for a_snake in product(*[[up, down, left, right] for _ in range(l)]):

      a_snake = [(0, 0)] + list(a_snake)

      if not self_collision(a_snake):
        c += 1
      #end
    #end
  #end

  return c

def count_combinations():
  goal_positions = X * Y
  snake_heads = X * Y
  snake_configurations = count_snake_configuration()
  print("Mögliche Zielpositionen: "+str(goal_positions))
  print("Mögliche Kopfpositionen: "+str(snake_heads))
  print("Mögliche BodyConfigurations: "+str(snake_configurations))


  return goal_positions * snake_heads * snake_configurations

#%% Execution code

snake = initial_snake(L_0)

print_field(snake_to_field(snake, goal))

# Does not work for random snakes (e.g. right when pointing to the left)
#for u in [right,right,right, up, up, left, left, left, down, down]*3:
#  step(u)
#  time.sleep(0.25)

c = count_combinations()
print(f"There are {c} states")

print("All done")
