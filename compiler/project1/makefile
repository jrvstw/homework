main:
	java -cp antlr-3.5.2-complete.jar org.antlr.Tool mylexer.g && \
	javac -cp ./antlr-3.5.2-complete.jar testLexer.java mylexer.java

out:
	java -cp ./antlr-3.5.2-complete.jar:. testLexer input.c

clean:
	rm -f mylexer.java mylexer.tokens mylexer*.class testLexer.class
