main:
	java -cp antlr-3.5.2-complete.jar org.antlr.Tool test1.g && \
	javac -cp ./antlr-3.5.2-complete.jar testLexer.java test1.java

exe:
	java -cp ./antlr-3.5.2-complete.jar:. testLexer input.c

clean:
	rm -f test1.java test1.tokens test1*.class testLexer.class
