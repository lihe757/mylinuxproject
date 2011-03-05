#-*- coding: UTF-8 -*-    
import urllib
from BeautifulSoup import BeautifulSoup
import re

class Translate:
    def Start(self):
        self._get_html_sourse()
        self._get_content("tb1")
        self._remove_tag()
        self.print_result()
#        获取网页源码
    def _get_html_sourse(self):
        url="http://www.putclub.com/article.php?articleid=4672" 
        self.htmlsourse=unicode(urllib.urlopen(url).read(),"gbk","ignore").encode("utf-8","ignore")
#        print self.htmlsourse
#        解析带有mp3链接的表格元素
    def _get_content(self,div_id):
        soup=BeautifulSoup("".join(self.htmlsourse))
        self.data=str(soup.find("table",{"class":div_id}))
#        print self.data
#        print "------------"
        
        soup2=BeautifulSoup(self.data)
        self.title=soup2.findAll("td", {"id":"table_t"})
#        for t in self.title:
#            print t.getText()
            
        urlAday= list()
        mp3url=soup2.findAll("td",id=re.compile("table_[cr]"))
        self.mp3urls=list()
        for u in mp3url:
            urlAday= u.findAll("a",href=re.compile("mp3$"))
            self.mp3urls.append(urlAday)
#        print self.mp3urls
#        print self.mp3urls.__len__()
        
#        生成字典    
    def _remove_tag(self):
        self.urlDict= dict()
        a=0
        for day in self.mp3urls:
            urls=list()
            for one in day:
                urls.append(one.__getattribute__("attrs")[1][1]) 
            self.urlDict[a]=urls
            a=a+1
#        print self.urlDict
#        print self.urlDict[self.title[0].getText()]
                
    def print_result(self):
        index=0
        for title in self.title:
            print title.getText().encode('utf8')
            for url in self.urlDict[index]:
                print url
            index+=1
        pass

if __name__=="__main__":
    Translate().Start()