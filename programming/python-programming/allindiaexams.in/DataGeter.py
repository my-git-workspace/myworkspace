#!/usr/bin/python
from html.parser import HTMLParser
import re
import codecs
import FetchHTML

class Page(object):
	def __init__(self, lno,lurl):
		self.no=lno
		self.url=lurl	

class Question(object):
	def __init__(self):
		self.qno=0
		self.que=''
		self.options=[]
		self.ans=''
		self.boolets=[]
			
class Topic(object):
	def __init__(self, lname, lurl):
		##print("Chapter CTTR called "+lname+" "+lurl);
		#print("Chapter CTTR called ");
		self.name=lname
		self.url=lurl

class QuestionParser(HTMLParser):
	def __init__(self):
		#print("QuestionParser CTTR called")	
		HTMLParser.__init__(self)
		self.questionList=[]
		self.qa_listtag=False	
		self.snotag=False
		self.option_listtag=False
		self.isqueread=False
		self.answerFlag=False
		self.answerAtag=False
		self.listspanTag=False
		self.optionBooletFlag=False
		self.optionDataFlag=False
		self.answerBoolet=''
	def handle_starttag(self, tag, attrs):
		if self.qa_listtag==False and tag=='div':
			for name, value in attrs:
				if name=='class' and value == 'qa_list':
					self.qa_listtag=True			
		if self.qa_listtag==True and tag=='span':
			for name, value in attrs:
				if name=='class' and value == 'sno':
					self.snotag=True
		if self.qa_listtag==True and self.snotag==False and tag=='ul':
			for name, value in attrs:
				if name=='class' and value == 'options_list clearfix':
					self.option_listtag=True
		if tag=='span'	and self.option_listtag==True:
			self.listspanTag=True
			for name, value in attrs:
				if name=='class' and value == 'not-answer option':
					self.answerFlag=False
				if name=='class' and value == 'answer option':
					self.answerFlag=True
	
		if tag=='a' and self.listspanTag==True:
			self.optionBooletFlag=True
					
							
	def handle_endtag(self, tag):
		if self.qa_listtag==True and tag=='div':
			self.qa_listtag=False
			self.questionList.append(self.question);
		if self.qa_listtag==True and tag=='span' and self.snotag==True:
			self.snotag=False
			self.isqueread=True
		if self.qa_listtag==True and tag=='ul':
			self.option_listtag=False
		if self.option_listtag==True and tag=='span':
			self.listspanTag=False
		if self.option_listtag==True and tag=='a':
			self.optionDataFlag=True
			self.optionBooletFlag==False	
		
	def handle_data(self, data):
		if self.qa_listtag==True and self.snotag==True:
			#print("Qno: "+data);
			self.question=Question()
			self.question.qno=data
		if self.isqueread==True:
			#print("Que: "+data);
			self.isqueread=False
			self.question.que=data
		if self.option_listtag==True and self.optionBooletFlag==True and self.optionDataFlag==False:
			#print("boolet: "+data);
			self.question.boolets.append(data)
			self.answerBoolet=data
			self.optionBooletFlag=False

		if self.optionDataFlag==True:
			self.optionDataFlag=False	
			self.question.options.append(data)
			#print("option: "+data);
			if self.answerFlag==True:
				#print("Ans: "+self.answerBoolet);
				self.answerFlag=False
				self.question.ans=self.answerBoolet
			
		
class PageListParser(HTMLParser):
	def __init__(self, lurl):
		##print("page list CTTR called");	
		HTMLParser.__init__(self)
		self.paginationtag=False
		self.pagetag=False
		self.turl=''
		self.pageList=[]
		self.pageList.append(Page(1,lurl));
		self.pages=[]
		self.pages.append(1)
		self.maxpagenumber=0
	def handle_starttag(self, tag, attrs):
		if tag=='div':
			for name, value in attrs:
				if name=='class' and value=='pagination':
					self.paginationtag=True
		
		if self.paginationtag and tag=='a':			
			for name, value in attrs:
				if name=='href':
					self.pagetag=True
					url=re.findall('http[s]?://(?:[a-zA-Z]|[0-9]|[$-_@.&+]|[!*\(\),]|(?:%[0-9a-fA-F][0-9a-fA-F]))+', value)
					if len(url):
						self.turl=value
					
		
	def handle_endtag(self, tag):
		if tag=='div' and self.paginationtag==True :
			self.paginationtag=False
			##print(max(self.pages));
			##print(self.pages);
			##print(self.missing_pages(self.pages))
			self.fill_all_pages_remaining_pages();
	def missing_pages(self, num_list):  
     		 original_list = [x for x in range(num_list[0], num_list[-1] + 1)]  
	     	 num_list = set(num_list)  
	     	 return (list(num_list ^ set(original_list))) 
	def fill_all_pages_remaining_pages(self):
		flag=False	
		for page in self.missing_pages(self.pages):
			##print("page: "+ str(page))
			flag=True
			lpage=Page(page, self.pageList[0].url+"/"+ str(page))
			self.pageList.append(lpage);
		if flag==True:
			flag=False
			self.pageList=sorted(self.pageList, key=lambda pages: int(pages.no))
			
	def handle_data(self, data):
		if self.paginationtag==True and self.pagetag==True:
			self.pagetag=False
			number=re.findall('^-?[0-9]+$',data)
			if len(number):
				if int(data) not in self.pages:
					self.pageList.append(Page(data,self.turl))
					self.pages.append(int(data))
				

class TopicParser(HTMLParser):
	def __init__(self):
		#print("TopicParser CTTR called")
		HTMLParser.__init__(self)
		self.topictag=False
		self.ultag=False
		self.curTag=''
		self.topiclist=[]	
		self.turl=''	
	def handle_starttag(self, tag, attrs):
		self.curTag=tag
		if tag=='ul':
			for name, value in attrs:
				if name=='class' and value=='list_sub':
					self.ultag=True
		if tag=='a' and self.ultag==True:
			for name, value in attrs:
				if name=='href':
					self.topictag=True
					self.turl=value
			
	def handle_endtag(self, tag):
		if self.ultag==True and tag=='ul':
			self.ultag=False
		if self.topictag==True and tag=='a':
			self.topictag=False
	def handle_data(self, data):
		if self.ultag==True and self.topictag==True:
			self.topiclist.append(Topic(data, self.turl));

