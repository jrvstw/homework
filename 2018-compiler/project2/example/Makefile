main:
	java -cp antlr-3.5.2-complete.jar org.antlr.Tool Expr.g && \
	javac -cp antlr-3.5.2-complete.jar:. testExpr.java

%.out:
	java -cp antlr-3.5.2-complete.jar:. testExpr input$*.c

clean:
	rm -f Expr*.java Expr.tokens Expr*.class testExpr.class
