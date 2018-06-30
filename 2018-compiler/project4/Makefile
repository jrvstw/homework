main:
	java -cp antlr-3.5.2-complete.jar org.antlr.Tool myCompiler.g && \
	javac -cp antlr-3.5.2-complete.jar:. myCompilerLexer.java myCompilerParser.java myCompiler_test.java

input%.s:
	java -cp antlr-3.5.2-complete.jar:. myCompiler_test input$*.c

clean:
	rm -f myCompilerLexer.java myCompilerParser.java *.tokens *.class
