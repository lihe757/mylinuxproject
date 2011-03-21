#-*- coding: UTF-8 -*-    
import urllib
from BeautifulSoup import BeautifulSoup
from sys import argv
import re,time
import os

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
        title=soup2.findAll("td", {"id":"table_t"})
        self.title=list()
        for t in title:
            self.title.append(t.getText().encode('utf-8'))
            
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
        option = argv[1] if len(argv)>1 else ''
        option2= argv[2] if len(argv)>2 else ''
        if option=='all':
            print "<html>"
            print "<body>"
            index=0
            for title in self.title:
                print title+"</br>"
                for url in self.mp3urls[index]:
                    print url
                    print "</br>"
                index+=1
            print "</body>"
            print "</html>"
        if option=='date':
            print "<html>"
            print "<body>"
            curDate = time.localtime()
            curYear_Month_Day = (curDate.__getattribute__('tm_year')\
                                 ,curDate.__getattribute__('tm_mon')\
                                 ,curDate.__getattribute__('tm_mday')
                                 )
            index=0
            for t in self.title:
                if int(t.__getslice__(10,12))==int(curYear_Month_Day[1]) \
                       and \
                       int(t.__getslice__(12,14))==int(curYear_Month_Day[2]):
                    print t + '</br>' 
                    print "Report</br>"
                    if option2=='down':
                        #替换mp3路径
                        modify =self.mp3urls[index][1]
                        newurl=modify.attrMap['href'].split(u'/').pop()
                        newHref=(u'href','mp3/'+newurl)
						modify.attrs.__delitem__(1)
						modify.attrs.insert(1,newHref)
                        print modify
                        #调用wget下载mp3
                        down_url= self.mp3urls[index][1].attrMap["href"]
                        if not os.path.exists("mp3"):
                            os.mkdir("mp3")
                        os.chdir("mp3")
                        if os.path.exists(newurl):
                            os.remove(newurl)
                        os.system("wget "+down_url)
                    else:
                        print self.mp3urls[index][1]
                index+=1
            print "</body>"
            print "</html>"
            
        else:
            print "option:\n \
                all: downall\n \
                date: down_today\n \
                date down: download mp3"
            

if __name__=="__main__":
	if len(sys.argv) < 2:
		print 'No action specified'
		sys.exit()
	if sys.argv[1].startswith('--'):
		option = sys.argv[1][2:]
		if option == 'version':
			print 'Version 0.1'
		elif option == 'help':
			print '''\
This program gets a mp3 file from the www.putclub.com,which to be use for listening ability exsise.
Options include:
	--version : Prints the version number
	--help    : Display this help'''
		elif option == 'today':
    	Translate().Start()
		elif option == 'week':
    	Translate().Start()
		else:
			print 'Unknown option.'
		sys.exit()

