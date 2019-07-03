LATEX_CMD = pdflatex
DEFAULT_PAPER = hcc2019-ndsr-report 
FIGPATH = images

all:	all-$(DEFAULT_PAPER)

latex-only-%: 
	$(LATEX_CMD) $*

process-figs:
	python $(FIGPATH)/process_svg_figs.py

all-%: 
	# $(LATEX_CMD) $* && bibtex $* && $(LATEX_CMD) $*  && $(LATEX_CMD) $*
	latexmk -pdf $*
	
clean:
	rm -f *.aux *.log *.blg *.bbl *.tmp *.out *.dvi *.fls *.fdb_latexmk


%.pdf: %.tex
	latexmk -pdf $*
