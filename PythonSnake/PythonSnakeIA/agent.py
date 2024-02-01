import torch
import random as rd
import numpy as np
from collections import deque
from game import SnakeGame, Direction, Point, BLOCK_SIZE

MAX_MEMORY = 100_000
BATCH_SIZE = 1000
LR = 0.001

class Agent:

    def __init__(self):
        self.n_games = 0
        self.epsilon = 0 #randomness
        self.gamma = 0 #discount rate
        self.memory = deque(maxlen = MAX_MEMORY) #popleft()
        self.model = None #TODO
        self.trainer = None #TODO

    def get_state(self, game):
        head = game.snake[0]
        point_l = Point(head.x - BLOCK_SIZE, head.y)
        point_r = Point(head.x + BLOCK_SIZE, head.y)
        point_u = Point(head.x, head.y - BLOCK_SIZE)
        point_d = Point(head.x, head.y + BLOCK_SIZE)

        dir_l = game.direction == Direction.LEFT
        dir_r = game.direction == Direction.RIGHT
        dir_u = game.direction == Direction.UP
        dir_d = game.direction == Direction.DOWN

        state = [
            #Danger straight
            (dir_r and game.is_collision(point_r)) or
            (dir_l and game.is_collision(point_l)) or
            (dir_u and game.is_collision(point_u)) or
            (dir_d and game.is_collision(point_d)),

            #Danger right
            (dir_u and game.is_collision(point_u)) or
            (dir_d and game.is_collision(point_d)) or
            (dir_l and game.is_collision(point_l)) or
            (dir_r and game.is_collision(point_r)),

            #Danger left
            (dir_d and game.is_collision(point_d)) or
            (dir_u and game.is_collision(point_u)) or
            (dir_r and game.is_collision(point_r)) or
            (dir_l and game.is_collision(point_l)),

            #Move direction
            dir_l,
            dir_r,
            dir_u,
            dir_d,

            #Food location
            game.food.x < game.head.x, #food left
            game.food.x > game.head.x, #food right
            game.food.y < game.head.y, #food up
            game.food.y > game.head.y, #food down
        ]

        return np.array(state, dtype=int)


    def remember(self, state, action, reward, next_state, over):
        self.memory.append((state, action, reward, next_state, over)) #popleft if MAX_MEMORY is reached

    def train_long_memory(self, state, action, reward, next_state, over):
        if len(self.memory) > BATCH_SIZE:
            mini_sample = rd.sample(self.memory, BATCH_SIZE) #list of tuples
        else:
            mini_sample = self.memory

        states, actions, rewards, next_states, dones = zip(*mini_sample)
        self.trainer.train_step(states, action, reward, next_state, over)
        #for state, action, reward, next_state, done in mini_sample:
        #    self.trainer.train_step(state, action, reward, next_state, over)

    def train_short_memory(self, state, action, reward, next_state, over):
        self.trainer.train_step(state, action, reward, next_state, over)

    def get_action(self, state):
        pass


def train():
    plot_scores = []
    plot_mean_scores = []
    total_score = 0
    record = 0
    agent = Agent()
    game = SnakeGameAI()

    while True:
        #get old state
        state_old = agent.get_state(game)

        #get move
        final_move = agent.get_action(state_old)

        #perform the move and get new state
        reward, done, score = game.play_step(final_move)
        new_state = agent.get_state(game)

        #train short memory
        agent.train_short_memory(state_old, final_move, reward, new_state, done)

        #remember
        agent.remember(state_old, final_move, reward, new_state, done)

        if done:
            #train the long memory
            game.reset()
            agent.n_games += 1
            agent.train_long_memory()

            if score > record:
                record = score
                #agent.model.save()

            print("Game: ", agent.n_games, "Score: ", score, "Record: ", record)

            #TODO plot

if __name__ == 'main':
    train()
