ANTLR = antlr-3.5.2-complete.jar

main: input1.s #input2.s input3.s

%.s: %.c myCompiler_test.class
	@java -cp ${ANTLR}:. myCompiler_test $*.c > $*.s

myCompiler_test.class: myCompiler.g myCompiler_test.java
	java -cp ${ANTLR} org.antlr.Tool myCompiler.g && \
	javac -cp ${ANTLR}:. myCompilerLexer.java myCompilerParser.java myCompiler_test.java

clean:
	rm -f myCompiler[^_]*.java *.tokens *.class *.s


sw%:
	ln -f -s $*.g myCompiler.g

input%: input%.s
	gcc input$*.s -o input$*

out: input1.s input2.s input3.s
	gcc input1.s -o input1
	gcc input2.s -o input2
	gcc input3.s -o input3

fno%:
	gcc -S -fno-asynchronous-unwind-tables input$*.c -o input$*.s

