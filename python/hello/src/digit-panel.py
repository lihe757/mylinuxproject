#-*- coding: UTF-8 -*- 
'''
一个9*9数字拼图游戏
约定0为空白处
'''

import random

digits = [0,1,2,3,4,5,6,7,8]
#将数字打乱
random.shuffle(digits);

#切分成3行
digit1 = digits.__getslice__(0,3)
digit2 = digits.__getslice__(3,6)
digit3 = digits.__getslice__(6,9)
#游戏面板
digit_panel = [digit1, digit2, digit3]

#ensure pos in resonble value
def ensure(origin, min_value, max_value):
    if origin < min_value:
        origin = min_value
    if origin > max_value:
        origin = max_value
    return origin

#show the game panel
def showGamePanel():
    for _row in digit_panel:
        print _row 

#检查是否胜利
def checkWin():
    correct =[1,2,3,4,5,6,7,8,0]
    curDigits = digit1+digit2+digit3
    if correct == curDigits:
        return True
    else:
        return False
    

def gameStart():
    #计算0出现的位置
    row = digits.index(0)/3
    col = digits.index(0)%3
    pos = [row, col]
 #       更新游戏面板
    showGamePanel()
    
    while True:
        key = raw_input("Press 'w a s d' to do move up left down right:")
        print 'key is', key
        if key == 'w':
            row += 1
            row = ensure(row, 0, 2)
        elif key == 's':
            row -= 1
            row = ensure(row, 0, 2)
        elif key == 'a':
            col += 1
            col = ensure(col, 0, 2)
        elif key == 'd':
            col -= 1
            col = ensure(col, 0, 2)
        elif key == 'quit':
            exit()

    
        #保存原有坐标
        oldPos = [pos[0], pos[1]]
        #更新现有坐标
        pos = [row, col]    
        #交换，移动数字
        tmp = digit_panel[pos[0]][pos[1]]
        digit_panel[pos[0]][pos[1]] = 0
        digit_panel[oldPos[0]][oldPos[1]] = tmp

#       更新游戏面板
        showGamePanel()
        if checkWin()==True:
            print 'You  win the game! '
            exit()
        
        
if __name__ =="__main__":
    gameStart()
