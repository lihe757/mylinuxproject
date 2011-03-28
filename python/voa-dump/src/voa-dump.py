#!/usr/bin/python
#-*- coding: UTF-8 -*-    
import urllib
from BeautifulSoup import BeautifulSoup
import re
import os

class Translate:
    def Start(self):
        self._get_html_sourse()
        self._parseHtml("float-lr2 w350")
        self._genrealHtml()
        
#        获取网页源码
    def _get_html_sourse(self):
        url = "http://www.unsv.com/voanews/specialenglish/"
        self.htmlsourse = urllib.urlopen(url).read()
#        print self.htmlsourse

#        解析带有mp3链接的表格元素
    def _parseHtml(self, div_id):
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
            aMap = dict()
            aCategory = title.find("strong").getText()
    #        print "分类："+aCategory
            aDate = title.find("i").getText()
    #        print "日期："+aDate
            aNextCurl = title.find("a", {"class":"black"}).attrMap[u'href']
    #        print "文章地址："+aNextCurl
            aMp3Url = title.find("a", href=re.compile("mp3$"))
            if not aMp3Url == None:
                aMp3Url = aMp3Url.attrMap[u'href']
                aMap[u'name'] =aMp3Url.split('/').pop()
            else:
                aMap[u'name'] =""
            #print aMp3Url
            aMap[u'category'] = aCategory
            aMap[u'date'] = aDate
            aMap[u'downMp3Url'] = aMp3Url
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
        #get a flash plyer
        if not os.path.exists("mp3"):
            os.mkdir("mp3")
        os.chdir("mp3")
        if not os.path.exists("mp3Player_black.swf"):
            os.system("wget http://home.putclub.com/mp3Player_black.swf")
        os.chdir("..")

        #begin to generate html
        for aMap in self.mapArticles:
            if not os.path.exists(aMap[u'category']):
                os.mkdir(aMap[u'category'])
            os.chdir(aMap[u'category'])
            #write html head
            f =file(aMap[u'date']+".html",'w')
            f.write("<html><body>")
            #embed a flash plyer 
            flashText=r'<embed src="../mp3/mp3Player_black.swf" flashvars="mytitle='+aMap[u'category']+aMap[u'date']+r'&amp;myurl=../mp3/'+aMap[u'name']+r'&amp;autoplay=false" quality="high" bgcolor="#ffffff" width="580" height="120" name="mp3Player_black" align="middle" allowscriptaccess="sameDomain" allowfullscreen="false" type="application/x-shockwave-flash" pluginspage="http://www.adobe.com/go/getflashplayer_cn">'
            f.write(flashText)
            #embed a html5 mp3 plyer
            mp3PlayerText=r'</br><audio controls preload="auto" autobuffer ><source src="../mp3/'+aMap[u'name']+r'"/></audio>'
            f.write(mp3PlayerText)
            f.write(r'</br><a href="../mp3/'+aMap[u'name']+r'" target="Blank">Download MP3</a>')
            f.write(aMap[u'article'].__str__())
            f.write("</body></html>")
            #end of html
            os.chdir("..")

            #download mp3
            os.chdir("mp3")
            if not os.path.exists(aMap[u'name']) and aMap[u'downMp3Url']!=None:
                os.system("wget "+aMap[u'downMp3Url'])            
            os.chdir("..")

if __name__ == "__main__":
    Translate().Start()
