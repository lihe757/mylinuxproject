#!/usr/bin/python
#-*- coding: UTF-8 -*-    
import urllib
from BeautifulSoup import BeautifulSoup
import re
import os

class Translate:
    def Start(self):
        self._get_html_sourse()
        self._get_content("float-lr2 w350")
        self._genrealHtml()
        
#        获取网页源码
    def _get_html_sourse(self):
        url = "http://www.unsv.com/voanews/specialenglish/"
        self.htmlsourse = urllib.urlopen(url).read()
#        print self.htmlsourse

#        解析带有mp3链接的表格元素
    def _get_content(self, div_id):
        soup = BeautifulSoup("".join(self.htmlsourse))
        self.data = str(soup.find("div", {"class":div_id}))
#       print self.data
#       print "------------"
        
        articleSoup = BeautifulSoup(self.data)
        self.title = articleSoup.findAll("div", {"class":"list-item2"})
#        print self.title
		#解析分类
        self.mapArticles=list()
        for title in self.title:
    #        print self.title
            aCategory = title.find("strong").getText()
    #        print "分类："+aCategory
            aDate = title.find("i").getText()
    #        print "日期："+aDate
            aNextCurl = title.find("a", {"class":"black"}).attrMap[u'href']
    #        print "文章地址："+aNextCurl
            aMp3Url = title.find("a", href=re.compile("mp3$"))
            if not aMp3Url == None:
                aMp3Url = aMp3Url.attrMap[u'href']
            #print aMp3Url
            aMap = dict()
            aMap[u'category'] = aCategory
            aMap[u'date'] = aDate
            aMap[u'downMp3Url'] = aMp3Url
            aMap[u'name'] =aMp3Url.split('/').pop()
            aMap[u'articleUrl'] = u"http://www.unsv.com"+aNextCurl
            print aMap[u'articleUrl']
            
            #解析文章
            nexturl = aMap[u'articleUrl']
            htmlsourse = urllib.urlopen(nexturl).read()
            nextSoup = BeautifulSoup(htmlsourse)
            aArticle = nextSoup.find("div", {"id":"articleFulltext"})
            
            #取出img原始
            articleSoup =BeautifulSoup(aArticle.__str__())
            rmImgs=articleSoup.img
            if not rmImgs==None:
                rmImgs.extract()
            aMap[u'article'] = articleSoup.__str__()
            
            self.mapArticles.append(aMap)
        

        
#        生成字典    
    def _genrealHtml(self):

        for aMap in self.mapArticles:
            if not os.path.exists(aMap[u'category']):
                os.mkdir(aMap[u'category'])
            os.chdir(aMap[u'category'])
            f =file(aMap[u'date']+".html",'w')
            f.write("<html>\
                        <body>"
                    )
            str ="<a href=../mp3/"+aMap[u'name']+" target=\"_Blank\">Download MP3</a></br>"
            f.write(str)
            f.write(aMap[u'article'].__str__())
            f.write("    </body>\
                    </html>"
                    )
            os.chdir("..")
            if not os.path.exists("mp3"):
                os.mkdir("mp3")
            os.chdir("mp3")
            if not os.path.exists(aMap[u'name']) and aMap[u'downMp3Url']!=None:
                os.system("wget "+aMap[u'downMp3Url'])            
            os.chdir("..")

if __name__ == "__main__":
    Translate().Start()
