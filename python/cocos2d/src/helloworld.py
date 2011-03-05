#-*- coding: UTF-8 -*-
'''
Created on 2011-2-13

@author: lihex
'''
import sys
import os
sys.path.insert(0, os.path.join(os.path.dirname(__file__),'..'))

import cocos.layer

class HelloWorld(cocos.layer.Layer):
    def __init__(self):
        super(HelloWorld,self).__init__()
        label = cocos.text.Label(u"好Hello,world",
                             font_name="Droid Sans",
                             font_size=32,
                             anchor_x='center',anchor_y='center')
        label.position =320,240
        self.add(label)
    
if __name__ == "__main__":
    cocos.director.director.init()
    hello_layer = HelloWorld()
    main_scene = cocos.scene.Scene (hello_layer)
    cocos.director.director.run(main_scene)
    
