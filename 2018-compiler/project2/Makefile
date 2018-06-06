main:
	java -cp antlr-3.5.2-complete.jar org.antlr.Tool myparser.g && \
	javac -cp antlr-3.5.2-complete.jar:. testParser.java

%.out:
	java -cp antlr-3.5.2-complete.jar:. testParser input$*.c

clean:
	rm -f myparser*.java myparser.tokens myparser*.class testParser.class
