#!/usr/bin/python3
from DataGeter import TopicParser
from DataGeter import PageListParser
from DataGeter import QuestionParser
import FetchHTML
import re
import codecs

class FetchAllQue(object):
	def __init__(self, lurl):
		#print("FetchAllQue CTTR called")
		topic=TopicParser();
		topic.feed(FetchHTML.getHTMLPage(lurl))
		for topic in topic.topiclist:
			#print(topic.name);
			pageparser=PageListParser(topic.url)
			pageparser.feed(FetchHTML.getHTMLPage(topic.url))
			for p in pageparser.pageList:
				#print(p.no, p.url);
				queparser=QuestionParser()
				queparser.feed(FetchHTML.getHTMLPage(p.url))

				for que in queparser.questionList:
					tname=topic.name
					tname=tname.replace(' ', '_')
					qno=que.qno.replace('.','');
					csvline=tname+"_"+qno + ","
					csvline+=tname
					csvline+=","+que.que
					csvline=" ".join(csvline.split())
					options=''
					if len(que.boolets)==4 and len(que.options)==4:
						options=que.boolets[0]+que.options[0] + " "
						options+=que.boolets[1]+que.options[1] + " "
						options+=que.boolets[2]+que.options[2] + " "
						options+=que.boolets[3]+que.options[3] 
					print(csvline+ "," +options +","+que.ans)
			
				queparser.close()
			pageparser.close()
			

url='http://www.allindiaexams.in/engineering/cse/c-multiple-choice-questions-answers'
fetch=FetchAllQue(url)



