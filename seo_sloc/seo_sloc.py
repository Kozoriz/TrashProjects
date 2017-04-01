#!/usr/bin/env python

""" This module analyze text from file or from console.

Metrics of natural text : 
1. Symbols count 
2. Words count
3. Whitespaces count
4. Nausea
5. Wateriness
etc. 

Code metrics : 

"""

# Common modules
import argparse
import os
# import sys
from sys import stdin

# Sloc
from radon import raw
from radon import metrics

# Files generation
## Pdf
from reportlab.pdfgen import canvas
from reportlab.pdfbase import pdfmetrics
from reportlab.lib.units import cm  
from reportlab.rl_config import defaultPageSize  

# Global vars
PAGE_HEIGHT=defaultPageSize[1]  
PAGE_WIDTH=defaultPageSize[0] 

def get_args() : 
		parser = argparse.ArgumentParser(description='This module analyze text from file|console. ')
		parser.add_argument('-f', '--file_for_parse', type=str,
			help='File which will be paresed and analyzed. If not specified will be asked text from input.')

		group = parser.add_mutually_exclusive_group()
		group.add_argument('-c', '--code', help="turn on code analysis", action="store_true")
		group.add_argument('-n', '--natural', help="turn on natural text analysis", action="store_true")
		return parser.parse_args()

def get_text(file_name) : 
	result_text = u""
	if file_name == None : 
		print "File not specified. Please enter text to console <enter 'OK' when done>: "
		while True :
			line = stdin.readline()
		# for line in fileinput.input():
			if line == u"OK\n" : break
			result_text += unicode(line, "utf-8")
	else : 
		full_file_path = os.path.abspath(file_name)
		if not os.path.exists(full_file_path) : 
			print "ERROR : File not exists."
			sys.exit(2)
		print "Reading data from file : "
		with open(full_file_path, 'r') as file : 
			result_text += unicode(file.read(), "utf-8")

	return result_text

def prepare_pdf_for_cirilic (canvas, size=12) : 
	fname = 'a010013l'

	# faceName - view a010013l.AFM file as a plain text and look at
	# row beginning with 'FontName' word (it's usually the fourth row).
	# The word after 'FontName' is the faceName ('URWGothicL-Book' in this case).
	faceName = 'URWGothicL-Book'

	# Define new Type 1 font
	cyrFace = pdfmetrics.EmbeddedType1Face(fname+'.afm', fname+'.pfb')

	# Create a new encoding called 'CP1251'
	cyrenc = pdfmetrics.Encoding('CP1251')

	# Fill in the tuple with Unicode glyphs in accordance with cp1251 (win1251)
	# encoding
	cp1251=(
	'afii10051', 'afii10052', 'quotesinglbase', 'afii10100', 'quotedblbase',
	'ellipsis', 'dagger', 'daggerdbl', 'Euro', 'perthousand', 'afii10058',
	'guilsinglleft', 'afii10059', 'afii10061', 'afii10060', 'afii10145',
	'afii10099', 'quoteleft', 'quoteright', 'quotedblleft', 'quotedblright',
	'bullet', 'endash', 'emdash', 'tilde', 'trademark', 'afii10106',
	'guilsinglright', 'afii10107', 'afii10109', 'afii10108', 'afii10193',
	'space', 'afii10062', 'afii10110', 'afii10057', 'currency', 'afii10050',
	'brokenbar', 'section', 'afii10023', 'copyright', 'afii10053',
	'guillemotleft', 'logicalnot', 'hyphen', 'registered', 'afii10056',
	'degree', 'plusminus', 'afii10055', 'afii10103', 'afii10098', 'mu1',
	'paragraph', 'periodcentered', 'afii10071', 'afii61352', 'afii10101',
	'guillemotright', 'afii10105', 'afii10054', 'afii10102', 'afii10104',
	'afii10017', 'afii10018', 'afii10019', 'afii10020', 'afii10021',
	'afii10022', 'afii10024', 'afii10025', 'afii10026', 'afii10027',
	'afii10028', 'afii10029', 'afii10030', 'afii10031', 'afii10032',
	'afii10033', 'afii10034', 'afii10035', 'afii10036', 'afii10037',
	'afii10038', 'afii10039', 'afii10040', 'afii10041', 'afii10042',
	'afii10043', 'afii10044', 'afii10045', 'afii10046', 'afii10047',
	'afii10048', 'afii10049', 'afii10065', 'afii10066', 'afii10067',
	'afii10068', 'afii10069', 'afii10070', 'afii10072', 'afii10073',
	'afii10074', 'afii10075', 'afii10076', 'afii10077', 'afii10078',
	'afii10079', 'afii10080', 'afii10081', 'afii10082', 'afii10083',
	'afii10084', 'afii10085', 'afii10086', 'afii10087', 'afii10088',
	'afii10089', 'afii10090', 'afii10091', 'afii10092', 'afii10093',
	'afii10094', 'afii10095', 'afii10096', 'afii10097'
	)

	# Replace glyphs from code 128 to code 256 with cp1251 values
	for i in range(128,256):
		cyrenc[i] = cp1251[i-128]

	# Register newly created encoding
	pdfmetrics.registerEncoding(cyrenc)

	# Register type face
	pdfmetrics.registerTypeFace(cyrFace)

	# Register the font with adding '1251' to its name
	pdfmetrics.registerFont(pdfmetrics.Font(faceName+'1251', faceName, 'CP1251'))

	# Use this font and set font size
	canvas.setFont(faceName+'1251', size)

class NaturalSEOProcessor : 
	pdf_text_height = 12
	pdf_between_lines_space = 2
	pdf_line_height = pdf_text_height + pdf_between_lines_space
	pdf_first_line = PAGE_HEIGHT-2*cm
	pdf_left_spacing = cm*1.5

	seo_analysis_dict = {
		"symbols_count":0,
		"symbols_without_whitespaces":0,
		"words_count":0,
		"unique_w_count":0,
		"words_dic":{},
	}

	def __init__(self, file_name = None) :
		self.file_name = file_name
		if self.file_name == None : self.file_name = "<console>"

	def calculate_symbols (self, text):	
		self.seo_analysis_dict['symbols_count'] = len(text.replace('\n',''))
		self.seo_analysis_dict["symbols_without_whitespaces"] = self.seo_analysis_dict['symbols_count'] - text.replace('\n','').count(' ')

	def calculate_words (self, text) :
		self.analyzed_text = text
		# Remove \n characters from text
		one_line_text = text.replace('\n', ' ')
		# Remove all except alpha, num, whitespace
		clear_text = u''.join(s for s in one_line_text if s.isalnum() or s==' ') 
		#Split and fill dictionary
		words = clear_text.lower().split(' ')
		for i in range(words.count('')) : 
			words.remove('')
		self.seo_analysis_dict["words_count"] = len(words)
		self.seo_analysis_dict["words_dic"] = dict((word, words.count(word)) for word in words)
		self.seo_analysis_dict["unique_w_count"] = len(self.seo_analysis_dict["words_dic"])
	def save_pdf(self) :
		report_file_name = "seo_report.pdf"
		p = canvas.Canvas(report_file_name)

		p.saveState()  
		p.setFont('Times-Bold',16)  
		p.drawCentredString(PAGE_WIDTH/2.0, self.pdf_first_line, "SEO report")  
		p.setFont('Times-Roman', self.pdf_text_height)  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-1*self.pdf_line_height, "File name : {}".format(self.file_name))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-2*self.pdf_line_height, "Symbols count : {}".format(self.seo_analysis_dict["symbols_count"]))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-3*self.pdf_line_height, "Symbols without whitespaces : {}".format(self.seo_analysis_dict["symbols_without_whitespaces"]))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-4*self.pdf_line_height, "Words count: {}".format(self.seo_analysis_dict["words_count"]))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-5*self.pdf_line_height, "Unique words count : {}".format(self.seo_analysis_dict["unique_w_count"]))  
		
		p.showPage()
		# Wthout it pdf cannot show cirilic
		prepare_pdf_for_cirilic(p, self.pdf_text_height)

		keys = sorted(self.seo_analysis_dict["words_dic"].keys())
		line_num = 0
		for i in xrange(0,len(keys), 3) : 
			p.drawString(self.pdf_left_spacing, self.pdf_first_line-line_num*self.pdf_line_height, u"{} : {}".format(keys[i], self.seo_analysis_dict["words_dic"][keys[i]]))  
			if len(keys)-1 < i+1 : break 
			p.drawString(self.pdf_left_spacing+PAGE_WIDTH/3, self.pdf_first_line-line_num*self.pdf_line_height, u"{} : {}".format(keys[i+1], self.seo_analysis_dict["words_dic"][keys[i+1]]))  
			if len(keys)-1 < i+2 : break 
			p.drawString(self.pdf_left_spacing+PAGE_WIDTH*2/3, self.pdf_first_line-line_num*self.pdf_line_height, u"{} : {}".format(keys[i+2], self.seo_analysis_dict["words_dic"][keys[i+2]]))  

			line_num += 1
			if line_num > 53: 
				p.showPage()
				prepare_pdf_for_cirilic(p, self.pdf_text_height)
				line_num = 0


		p.showPage()
		p.save()
		print "Report saved to {}".format(report_file_name)	
# class end

class CodeMetricsProcessor : 
	pdf_text_height = 12
	pdf_between_lines_space = 0.5*cm
	pdf_line_height = pdf_text_height + pdf_between_lines_space
	pdf_first_line = PAGE_HEIGHT-2*cm
	pdf_left_spacing = cm*1.5

	def __init__(self, file_name=None) :
		if file_name == None : 
			self.file_name = "<console>"
		else :
			self.file_name = file_name

	def process(self, text) :
		self.calculated_sloc = raw.analyze(text)	
		self.calculated_metrics = metrics.h_visit(text)
		self.analyzed_text = text

	def get_sloc(self) : 
		return self.calculated_sloc

	def save_pdf(self) :
		assert self.calculated_sloc != None, "Can`t to write pdf before sloc calculation"
		report_file_name = "sloc_report.pdf"
		p = canvas.Canvas(report_file_name)

		p.saveState()  
		p.setFont('Times-Bold',16)  
		p.drawCentredString(PAGE_WIDTH/2.0, self.pdf_first_line, "Code report")  
		p.setFont('Times-Bold',12)  
		p.drawString(self.pdf_left_spacing*2, self.pdf_first_line-2*self.pdf_line_height, "SLOC")  
		p.setFont('Times-Roman', self.pdf_text_height)  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-1*self.pdf_line_height, "File name : {}".format(self.file_name))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-3*self.pdf_line_height, "LOC : {}".format(self.calculated_sloc.loc))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-4*self.pdf_line_height, "LLOC : {}".format(self.calculated_sloc.lloc))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-5*self.pdf_line_height, "SLOC : {}".format(self.calculated_sloc.sloc))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-6*self.pdf_line_height, "Comments : {}".format(self.calculated_sloc.comments))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-7*self.pdf_line_height, "Multi-com. : {}".format(self.calculated_sloc.multi))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-8*self.pdf_line_height, "Blank : {}".format(self.calculated_sloc.blank))  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-9*self.pdf_line_height, "Single-com. : {}".format(self.calculated_sloc.single_comments))  

		p.setFont('Times-Bold',12)  
		p.drawString(self.pdf_left_spacing*2, self.pdf_first_line-10*self.pdf_line_height, "Other")  
		p.setFont('Times-Roman', self.pdf_text_height)  
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-11*self.pdf_line_height, "H1 : {}".format(self.calculated_metrics.h1))
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-12*self.pdf_line_height, "H2 : {}".format(self.calculated_metrics.h2))
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-13*self.pdf_line_height, "N1 : {}".format(self.calculated_metrics.N1))
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-14*self.pdf_line_height, "N2 : {}".format(self.calculated_metrics.N2))
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-15*self.pdf_line_height, "Calculated length : {}".format(self.calculated_metrics.calculated_length))
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-16*self.pdf_line_height, "Volume : {}".format(self.calculated_metrics.volume)) 
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-17*self.pdf_line_height, "Difficulty : {}".format(self.calculated_metrics.difficulty)) 
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-18*self.pdf_line_height, "Effort : {}".format(self.calculated_metrics.effort)) 
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-19*self.pdf_line_height, "Time : {}".format(self.calculated_metrics.time)) 
		p.drawString(self.pdf_left_spacing, self.pdf_first_line-20*self.pdf_line_height, "Bugs : {}".format(self.calculated_metrics.bugs)) 
		
		p.showPage()
		p.save()
		print "Report saved to {}".format(report_file_name)	
#class end

def main() : 	
	args = get_args()
	assert args.code or args.natural, "Please provide --code(-c) or --natural(-n)"
	text = get_text(args.file_for_parse)
		
	if args.natural :
		processor = NaturalSEOProcessor(args.file_for_parse)
		processor.calculate_symbols(text)
		processor.calculate_words(text)
		processor.save_pdf()

	elif args.code : 
		processor = CodeMetricsProcessor(args.file_for_parse)
		processor.process(text)
		sloc_module = processor.get_sloc()
		processor.save_pdf()

if __name__ == '__main__':
    main()
