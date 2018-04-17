import os
import pygame
import numpy as np
import random
import time

def print_board(board):
	for i in range(3):
		for j in range(3):
			print("{:2d}".format(board[i][j]), end='')
		print()
	print()

def new_board():
	return np.full((3,3), 0, int)

def init():
	board = new_board()
	board_map = []
	os.environ['SDL_VIDEO_WINDOW_POS'] = "%d, %d" % (100, 100)
	pygame.init()
	pygame.font.init()
	myfont = pygame.font.SysFont("monospace", 25)

	screen = pygame.display.set_mode((650, 650))
	
	for i in range(1,16):
		pygame.draw.line(screen, 0xffffff, (40*i,40), (40*i,600), 4)
		pygame.draw.line(screen, 0xffffff, (40,40*i), (600,40*i), 4)
		

	pygame.display.set_caption('Tic-Tac-Toe')
	pygame.display.update()

	done = False
	no, winner = 9, 0 
	cur_ply = 1

	return done, board, no, winner, cur_ply, myfont, screen, board_map

def update_screen(player, screen, y, x):
	if player == 1:
		pygame.draw.circle(screen, 0x00ffff, ((x+1)*40, (y+1)*40), 14, 0)
	else:
		pygame.draw.circle(screen, 0xffff00, ((x+1)*40, (y+1)*40), 14, 0)
	pygame.display.update()

def user_play(x, y, board_map):
	bx, by = ((x+20)//40)-1, ((y+20)//40)-1
	print("player1 : ",'(',bx,',',by,')')
	board_map.append("( " + str(bx) + ", " + str(by) + ", 1 )")
	update_screen(1, screen, by, bx)
	return 2

def user_play2(x, y, board_map):
	bx, by = ((x+20)//40)-1, ((y+20)//40)-1
	print("player2 : ",'(',bx,',',by,')')
	board_map.append("( " + str(bx) + ", " + str(by) + ", 2 )")
	update_screen(2, screen, by, bx)
	return 1

def out_range(x, y):
    bx, by = ((x+20)//40)-1, ((y+20)//40)-1
    if bx < 0 or bx > 14:
        return 0
    if by < 0 or by > 14: 
        return 0
    return 1

def check_board_map(x, y, board_map):
	bx, by = ((x+20)//40)-1, ((y+20)//40)-1
	for i in board_map:
		if i == "( " + str(bx) + ", " + str(by) + ", 1 )" or i == "( " + str(bx) + ", " + str(by) + ", 2 )":
			return 0
	return 1

def check_board_map_player(bx, by, board_map, player):
	for i in board_map:
		if i == "( " + str(bx) + ", " + str(by) + ", " + str(player) + " )":
			return 1
	return 0
		

def isWin(x, y, board_map, player):
	bx, by = ((x+20)//40)-1, ((y+20)//40)-1
	max_count = 0
	count = 0

	### check up
	for i in range(0,5):
		if check_board_map_player(bx, by-i, board_map, player):
			count = count + 1
		else:
			break

	# print("up: " + str(count))
	if count > max_count:
		max_count = count
	count = 0
	
	### check down
	for i in range(0,5):
		if check_board_map_player(bx, by+i, board_map, player):
			count = count + 1
		else:
			break

	# print("down: " + str(count))
	if count > max_count:
		max_count = count
	count = 0

	### check left
	for i in range(0,5):
		if check_board_map_player(bx-i, by, board_map, player):
			count = count + 1
		else:
			break

	# print("left: " + str(count))
	if count > max_count:
		max_count = count
	count = 0

	### check right
	for i in range(0,5):
		if check_board_map_player(bx+i, by, board_map, player):
			count = count + 1
		else:
			break

	# print("right: " + str(count))
	if count > max_count:
		max_count = count
	count = 0

	### check top right
	for i in range(0,5):
		if check_board_map_player(bx+i, by-i, board_map, player):
			count = count + 1
		else:
			break

	# print("top right: " + str(count))
	if count > max_count:
		max_count = count
	count = 0

	### check down right
	for i in range(0,5):
		if check_board_map_player(bx+i, by+i, board_map, player):
			count = count + 1
		else:
			break

	# print("down right: " + str(count))
	if count > max_count:
		max_count = count
	count = 0

	### check up left
	for i in range(0,5):
		if check_board_map_player(bx-i, by-i, board_map, player):
			count = count + 1
		else:
			break

	# print("up left: " + str(count))
	if count > max_count:
		max_count = count
	count = 0

	### check down left
	for i in range(0,5):
		if check_board_map_player(bx-i, by+i, board_map, player):
			count = count + 1
		else:
			break

	# print("down left: " + str(count))
	if count > max_count:
		max_count = count
	count = 0

	### check win
	if max_count >= 5:
		print("player"+ str(player)+ " is win")
		return player
	else:
		return 0

def show_winner(winner, myfont, screen):
	label = myfont.render("Winner is " + str(winner), 2, (255,0,0))
	pygame.draw.line(screen, 0xffffff, (10,100), (290,100), 30)
	screen.blit(label, (20,85))
	pygame.display.update()

if __name__ == '__main__':
	done, board, no, winner, cur_ply, myfont, screen, board_map = init()
	while not done:

		for event in pygame.event.get():
			if event.type == pygame.QUIT:
				done = True
			elif winner != 0:
				show_winner(winner, myfont, screen)
				if event.type == pygame.KEYDOWN:
					done, board, no, winner, cur_ply, myfont, screen, board_map = init()
			elif event.type == pygame.MOUSEBUTTONDOWN and cur_ply==1:
				if winner == 0:
					posx, posy = pygame.mouse.get_pos()
					if cur_ply==1:
						print(posx, posy)
						if out_range(posx, posy):
							if check_board_map(posx, posy, board_map):
								cur_ply = user_play(posx, posy, board_map)
								winner = isWin(posx, posy, board_map,1)
							else:
								print("hey don't do that")
						else:
							print("out of range")
					
			elif event.type == pygame.MOUSEBUTTONDOWN and cur_ply==2:
				if winner == 0:
					posx, posy = pygame.mouse.get_pos()
					if cur_ply==2:
						print(posx, posy)
						if out_range(posx, posy) :
							if check_board_map(posx, posy, board_map):
								cur_ply = user_play2(posx, posy, board_map)
								winner = isWin(posx, posy, board_map,2)
							else:
								print("hey don't do that ")
						else:
							print("out of range")

 
	pygame.quit()