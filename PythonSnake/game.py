import pygame
import random
from enum import Enum
from collections import namedtuple

width = 640
height = 480
pygame.init()
font = pygame.font.Font('arial.ttf', 25)


class Direction(Enum):
    RIGHT = 1
    LEFT = 2
    UP = 3
    DOWN = 4

Point = namedtuple('Point', 'x, y')

#rgb colors
WHITE = (255, 255, 255)
RED = (200, 0, 0)
BLUE1 = (0, 0 , 255)
BLUE2 = (0, 100, 255)
BLACK = (0, 0, 0)

BLOCK_SIZE = 20
SPEED = 20

class SnakeGame:

    def __init__(self, width, height):
        self.width = width
        self.height = height
        #init display
        self.display = pygame.display.set_mode((self.width, self.height))
        pygame.display.set_caption('Snake game')
        self.clock = pygame.time.Clock()

        #init game state
        self.direction = Direction.RIGHT

        self.snakehead = Point(self.width/2, self.height/2)
        self.snake = [self.snakehead, Point(self.snakehead.x-BLOCK_SIZE, self.snakehead.y), Point(self.snakehead.x-(2*BLOCK_SIZE), self.snakehead.y)]
        self.score = 0
        self.food = None
        self._place_food()

    
    def _place_food(self):
        x = random.randint(0, (self.width-BLOCK_SIZE)//BLOCK_SIZE)*BLOCK_SIZE
        y = random.randint(0, (self.height-BLOCK_SIZE)//BLOCK_SIZE)*BLOCK_SIZE
        self.food = Point(x,y)
        if self.food in self.snake:
            self._place_food()

    def play_step(self):
        #1 - Collect user input
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                quit()
            if event.type == pygame.KEYDOWN:
                if event.key == pygame.K_LEFT:
                    self.direction = Direction.LEFT
                elif event.key == pygame.K_RIGHT:
                    self.direction = Direction.RIGHT
                elif event.key == pygame.K_UP:
                    self.direction = Direction.UP
                elif event.key == pygame.K_DOWN:
                    self.direction = Direction.DOWN
        #2 - Move snake
        self._move(self.direction) #update the head
        self.snake.insert(0, self.snakehead)
        #3 - Check if game over
        game_over = False

        if self._is_colision():
            game_over = True
            return game_over, self.score
        #4 - Place new food or finalize move
        if self.snakehead == self.food:
            self.score += 1
            self._place_food()
        else:
            self.snake.pop()

        #5 - Update UI and clock
        self._update_ui()
        self.clock.tick(SPEED)

        #6 - Return game over and score
        
        return game_over, self.score

    def _is_colision(self):
        #hits boundary
        if self.snakehead.x > self.width - BLOCK_SIZE or self.snakehead.x < 0 or self.snakehead.y > self.height - BLOCK_SIZE or self.snakehead.y < 0:
            return True
        #hits itself
        if self.snakehead in self.snake[1:]:
            return True
        return False


    def _update_ui(self):
        self.display.fill(BLACK)

        for pt in self.snake:
            pygame.draw.rect(self.display, BLUE1, pygame.Rect(pt.x, pt.y, BLOCK_SIZE, BLOCK_SIZE))
            pygame.draw.rect(self.display, BLUE2, pygame.Rect(pt.x+4, pt.y+4, BLOCK_SIZE-8, BLOCK_SIZE-8))

        pygame.draw.rect(self.display, RED, pygame.Rect(self.food.x, self.food.y, BLOCK_SIZE, BLOCK_SIZE))

        text = font.render("Score: " + str(self.score), True, WHITE)
        self.display.blit(text, [0, 0])
        pygame.display.flip()

    def _move(self, direction):
        x = self.snakehead.x
        y = self.snakehead.y

        if direction == Direction.RIGHT: 
            x += BLOCK_SIZE
        elif direction == Direction.LEFT: 
            x -= BLOCK_SIZE
        elif direction == Direction.UP: 
            y -= BLOCK_SIZE
        elif direction == Direction.DOWN: 
            y += BLOCK_SIZE

        self.snakehead = Point(x, y)


if __name__ == '__main__':
    game = SnakeGame(width, height)

    #game loop
    while True:
        game_over, score = game.play_step()

        #break if game over
        if game_over:
            break

    print("Final score: ", score)

    pygame.quit()