// $ANTLR 3.5.2 mylexer.g 2018-04-11 02:41:55

import org.antlr.runtime.*;
import java.util.Stack;
import java.util.List;
import java.util.ArrayList;

@SuppressWarnings("all")
public class mylexer extends Lexer {
	public static final int EOF=-1;
	public static final int ASSIGN=4;
	public static final int BRACKLETS=5;
	public static final int BREAK_=6;
	public static final int CHAR_TYPE=7;
	public static final int COMA=8;
	public static final int COMMENT=9;
	public static final int CONTINUE_=10;
	public static final int DEC_NUM=11;
	public static final int DIGIT=12;
	public static final int ELSE_=13;
	public static final int EQ_OP=14;
	public static final int FLOAT_NUM=15;
	public static final int FLOAT_NUM1=16;
	public static final int FLOAT_NUM2=17;
	public static final int FLOAT_NUM3=18;
	public static final int FLOAT_TYPE=19;
	public static final int GE_OP=20;
	public static final int GT_OP=21;
	public static final int ID=22;
	public static final int IF_=23;
	public static final int INT_TYPE=24;
	public static final int LETTER=25;
	public static final int LE_OP=26;
	public static final int LITERAL=27;
	public static final int LS_OP=28;
	public static final int NE_OP=29;
	public static final int OPERATOR=30;
	public static final int RETURN_=31;
	public static final int SEMICOLON=32;
	public static final int VOID_TYPE=33;
	public static final int WHILE_=34;
	public static final int WS=35;

	// delegates
	// delegators
	public Lexer[] getDelegates() {
		return new Lexer[] {};
	}

	public mylexer() {} 
	public mylexer(CharStream input) {
		this(input, new RecognizerSharedState());
	}
	public mylexer(CharStream input, RecognizerSharedState state) {
		super(input,state);
	}
	@Override public String getGrammarFileName() { return "mylexer.g"; }

	// $ANTLR start "VOID_TYPE"
	public final void mVOID_TYPE() throws RecognitionException {
		try {
			int _type = VOID_TYPE;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:11:13: ( 'void' )
			// mylexer.g:11:15: 'void'
			{
			match("void"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "VOID_TYPE"

	// $ANTLR start "INT_TYPE"
	public final void mINT_TYPE() throws RecognitionException {
		try {
			int _type = INT_TYPE;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:12:13: ( 'int' )
			// mylexer.g:12:15: 'int'
			{
			match("int"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "INT_TYPE"

	// $ANTLR start "CHAR_TYPE"
	public final void mCHAR_TYPE() throws RecognitionException {
		try {
			int _type = CHAR_TYPE;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:13:13: ( 'char' )
			// mylexer.g:13:15: 'char'
			{
			match("char"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "CHAR_TYPE"

	// $ANTLR start "FLOAT_TYPE"
	public final void mFLOAT_TYPE() throws RecognitionException {
		try {
			int _type = FLOAT_TYPE;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:14:13: ( 'float' )
			// mylexer.g:14:15: 'float'
			{
			match("float"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "FLOAT_TYPE"

	// $ANTLR start "IF_"
	public final void mIF_() throws RecognitionException {
		try {
			int _type = IF_;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:15:13: ( 'if' )
			// mylexer.g:15:15: 'if'
			{
			match("if"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "IF_"

	// $ANTLR start "ELSE_"
	public final void mELSE_() throws RecognitionException {
		try {
			int _type = ELSE_;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:16:13: ( 'else' )
			// mylexer.g:16:15: 'else'
			{
			match("else"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "ELSE_"

	// $ANTLR start "WHILE_"
	public final void mWHILE_() throws RecognitionException {
		try {
			int _type = WHILE_;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:17:13: ( 'while' )
			// mylexer.g:17:15: 'while'
			{
			match("while"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "WHILE_"

	// $ANTLR start "RETURN_"
	public final void mRETURN_() throws RecognitionException {
		try {
			int _type = RETURN_;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:19:13: ( 'return' )
			// mylexer.g:19:15: 'return'
			{
			match("return"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "RETURN_"

	// $ANTLR start "CONTINUE_"
	public final void mCONTINUE_() throws RecognitionException {
		try {
			int _type = CONTINUE_;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:20:13: ( 'continue' )
			// mylexer.g:20:15: 'continue'
			{
			match("continue"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "CONTINUE_"

	// $ANTLR start "BREAK_"
	public final void mBREAK_() throws RecognitionException {
		try {
			int _type = BREAK_;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:21:13: ( 'break' )
			// mylexer.g:21:15: 'break'
			{
			match("break"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "BREAK_"

	// $ANTLR start "EQ_OP"
	public final void mEQ_OP() throws RecognitionException {
		try {
			int _type = EQ_OP;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:27:7: ( '==' )
			// mylexer.g:27:9: '=='
			{
			match("=="); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "EQ_OP"

	// $ANTLR start "LE_OP"
	public final void mLE_OP() throws RecognitionException {
		try {
			int _type = LE_OP;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:28:7: ( '<=' )
			// mylexer.g:28:9: '<='
			{
			match("<="); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "LE_OP"

	// $ANTLR start "GE_OP"
	public final void mGE_OP() throws RecognitionException {
		try {
			int _type = GE_OP;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:29:7: ( '>=' )
			// mylexer.g:29:9: '>='
			{
			match(">="); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "GE_OP"

	// $ANTLR start "NE_OP"
	public final void mNE_OP() throws RecognitionException {
		try {
			int _type = NE_OP;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:30:7: ( '!=' )
			// mylexer.g:30:9: '!='
			{
			match("!="); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "NE_OP"

	// $ANTLR start "LS_OP"
	public final void mLS_OP() throws RecognitionException {
		try {
			int _type = LS_OP;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:32:7: ( '<' )
			// mylexer.g:32:9: '<'
			{
			match('<'); 
			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "LS_OP"

	// $ANTLR start "GT_OP"
	public final void mGT_OP() throws RecognitionException {
		try {
			int _type = GT_OP;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:33:7: ( '>' )
			// mylexer.g:33:9: '>'
			{
			match('>'); 
			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "GT_OP"

	// $ANTLR start "ASSIGN"
	public final void mASSIGN() throws RecognitionException {
		try {
			int _type = ASSIGN;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:35:13: ( '=' )
			// mylexer.g:35:15: '='
			{
			match('='); 
			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "ASSIGN"

	// $ANTLR start "OPERATOR"
	public final void mOPERATOR() throws RecognitionException {
		try {
			int _type = OPERATOR;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:36:13: ( '+' | '-' | '*' | '/' )
			// mylexer.g:
			{
			if ( (input.LA(1) >= '*' && input.LA(1) <= '+')||input.LA(1)=='-'||input.LA(1)=='/' ) {
				input.consume();
			}
			else {
				MismatchedSetException mse = new MismatchedSetException(null,input);
				recover(mse);
				throw mse;
			}
			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "OPERATOR"

	// $ANTLR start "SEMICOLON"
	public final void mSEMICOLON() throws RecognitionException {
		try {
			int _type = SEMICOLON;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:38:13: ( ';' )
			// mylexer.g:38:15: ';'
			{
			match(';'); 
			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "SEMICOLON"

	// $ANTLR start "COMA"
	public final void mCOMA() throws RecognitionException {
		try {
			int _type = COMA;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:39:13: ( ',' )
			// mylexer.g:39:15: ','
			{
			match(','); 
			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "COMA"

	// $ANTLR start "BRACKLETS"
	public final void mBRACKLETS() throws RecognitionException {
		try {
			int _type = BRACKLETS;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:40:13: ( '{' | '}' | '[' | ']' | '(' | ')' | '<' | '>' )
			// mylexer.g:
			{
			if ( (input.LA(1) >= '(' && input.LA(1) <= ')')||input.LA(1)=='<'||input.LA(1)=='>'||input.LA(1)=='['||input.LA(1)==']'||input.LA(1)=='{'||input.LA(1)=='}' ) {
				input.consume();
			}
			else {
				MismatchedSetException mse = new MismatchedSetException(null,input);
				recover(mse);
				throw mse;
			}
			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "BRACKLETS"

	// $ANTLR start "WS"
	public final void mWS() throws RecognitionException {
		try {
			int _type = WS;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:41:13: ( ( ' ' | '\\r' | '\\t' | '\\n' )+ )
			// mylexer.g:41:15: ( ' ' | '\\r' | '\\t' | '\\n' )+
			{
			// mylexer.g:41:15: ( ' ' | '\\r' | '\\t' | '\\n' )+
			int cnt1=0;
			loop1:
			while (true) {
				int alt1=2;
				int LA1_0 = input.LA(1);
				if ( ((LA1_0 >= '\t' && LA1_0 <= '\n')||LA1_0=='\r'||LA1_0==' ') ) {
					alt1=1;
				}

				switch (alt1) {
				case 1 :
					// mylexer.g:
					{
					if ( (input.LA(1) >= '\t' && input.LA(1) <= '\n')||input.LA(1)=='\r'||input.LA(1)==' ' ) {
						input.consume();
					}
					else {
						MismatchedSetException mse = new MismatchedSetException(null,input);
						recover(mse);
						throw mse;
					}
					}
					break;

				default :
					if ( cnt1 >= 1 ) break loop1;
					EarlyExitException eee = new EarlyExitException(1, input);
					throw eee;
				}
				cnt1++;
			}

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "WS"

	// $ANTLR start "DEC_NUM"
	public final void mDEC_NUM() throws RecognitionException {
		try {
			int _type = DEC_NUM;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:43:13: ( ( '0' | ( '1' .. '9' ) ( DIGIT )* ) )
			// mylexer.g:43:15: ( '0' | ( '1' .. '9' ) ( DIGIT )* )
			{
			// mylexer.g:43:15: ( '0' | ( '1' .. '9' ) ( DIGIT )* )
			int alt3=2;
			int LA3_0 = input.LA(1);
			if ( (LA3_0=='0') ) {
				alt3=1;
			}
			else if ( ((LA3_0 >= '1' && LA3_0 <= '9')) ) {
				alt3=2;
			}

			else {
				NoViableAltException nvae =
					new NoViableAltException("", 3, 0, input);
				throw nvae;
			}

			switch (alt3) {
				case 1 :
					// mylexer.g:43:16: '0'
					{
					match('0'); 
					}
					break;
				case 2 :
					// mylexer.g:43:22: ( '1' .. '9' ) ( DIGIT )*
					{
					if ( (input.LA(1) >= '1' && input.LA(1) <= '9') ) {
						input.consume();
					}
					else {
						MismatchedSetException mse = new MismatchedSetException(null,input);
						recover(mse);
						throw mse;
					}
					// mylexer.g:43:32: ( DIGIT )*
					loop2:
					while (true) {
						int alt2=2;
						int LA2_0 = input.LA(1);
						if ( ((LA2_0 >= '0' && LA2_0 <= '9')) ) {
							alt2=1;
						}

						switch (alt2) {
						case 1 :
							// mylexer.g:
							{
							if ( (input.LA(1) >= '0' && input.LA(1) <= '9') ) {
								input.consume();
							}
							else {
								MismatchedSetException mse = new MismatchedSetException(null,input);
								recover(mse);
								throw mse;
							}
							}
							break;

						default :
							break loop2;
						}
					}

					}
					break;

			}

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "DEC_NUM"

	// $ANTLR start "ID"
	public final void mID() throws RecognitionException {
		try {
			int _type = ID;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:44:13: ( ( LETTER ) ( LETTER | DIGIT )* )
			// mylexer.g:44:15: ( LETTER ) ( LETTER | DIGIT )*
			{
			if ( (input.LA(1) >= 'A' && input.LA(1) <= 'Z')||input.LA(1)=='_'||(input.LA(1) >= 'a' && input.LA(1) <= 'z') ) {
				input.consume();
			}
			else {
				MismatchedSetException mse = new MismatchedSetException(null,input);
				recover(mse);
				throw mse;
			}
			// mylexer.g:44:23: ( LETTER | DIGIT )*
			loop4:
			while (true) {
				int alt4=2;
				int LA4_0 = input.LA(1);
				if ( ((LA4_0 >= '0' && LA4_0 <= '9')||(LA4_0 >= 'A' && LA4_0 <= 'Z')||LA4_0=='_'||(LA4_0 >= 'a' && LA4_0 <= 'z')) ) {
					alt4=1;
				}

				switch (alt4) {
				case 1 :
					// mylexer.g:
					{
					if ( (input.LA(1) >= '0' && input.LA(1) <= '9')||(input.LA(1) >= 'A' && input.LA(1) <= 'Z')||input.LA(1)=='_'||(input.LA(1) >= 'a' && input.LA(1) <= 'z') ) {
						input.consume();
					}
					else {
						MismatchedSetException mse = new MismatchedSetException(null,input);
						recover(mse);
						throw mse;
					}
					}
					break;

				default :
					break loop4;
				}
			}

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "ID"

	// $ANTLR start "FLOAT_NUM"
	public final void mFLOAT_NUM() throws RecognitionException {
		try {
			int _type = FLOAT_NUM;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:45:13: ( FLOAT_NUM1 | FLOAT_NUM2 | FLOAT_NUM3 )
			int alt5=3;
			alt5 = dfa5.predict(input);
			switch (alt5) {
				case 1 :
					// mylexer.g:45:15: FLOAT_NUM1
					{
					mFLOAT_NUM1(); 

					}
					break;
				case 2 :
					// mylexer.g:45:28: FLOAT_NUM2
					{
					mFLOAT_NUM2(); 

					}
					break;
				case 3 :
					// mylexer.g:45:41: FLOAT_NUM3
					{
					mFLOAT_NUM3(); 

					}
					break;

			}
			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "FLOAT_NUM"

	// $ANTLR start "COMMENT"
	public final void mCOMMENT() throws RecognitionException {
		try {
			int _type = COMMENT;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:46:13: ( '/*' ( options {greedy=false; } : . )* '*/' )
			// mylexer.g:46:15: '/*' ( options {greedy=false; } : . )* '*/'
			{
			match("/*"); 

			// mylexer.g:46:20: ( options {greedy=false; } : . )*
			loop6:
			while (true) {
				int alt6=2;
				int LA6_0 = input.LA(1);
				if ( (LA6_0=='*') ) {
					int LA6_1 = input.LA(2);
					if ( (LA6_1=='/') ) {
						alt6=2;
					}
					else if ( ((LA6_1 >= '\u0000' && LA6_1 <= '.')||(LA6_1 >= '0' && LA6_1 <= '\uFFFF')) ) {
						alt6=1;
					}

				}
				else if ( ((LA6_0 >= '\u0000' && LA6_0 <= ')')||(LA6_0 >= '+' && LA6_0 <= '\uFFFF')) ) {
					alt6=1;
				}

				switch (alt6) {
				case 1 :
					// mylexer.g:46:45: .
					{
					matchAny(); 
					}
					break;

				default :
					break loop6;
				}
			}

			match("*/"); 

			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "COMMENT"

	// $ANTLR start "LITERAL"
	public final void mLITERAL() throws RecognitionException {
		try {
			int _type = LITERAL;
			int _channel = DEFAULT_TOKEN_CHANNEL;
			// mylexer.g:47:13: ( '\"' ( . )* '\"' )
			// mylexer.g:47:15: '\"' ( . )* '\"'
			{
			match('\"'); 
			// mylexer.g:47:19: ( . )*
			loop7:
			while (true) {
				int alt7=2;
				int LA7_0 = input.LA(1);
				if ( (LA7_0=='\"') ) {
					alt7=2;
				}
				else if ( ((LA7_0 >= '\u0000' && LA7_0 <= '!')||(LA7_0 >= '#' && LA7_0 <= '\uFFFF')) ) {
					alt7=1;
				}

				switch (alt7) {
				case 1 :
					// mylexer.g:47:20: .
					{
					matchAny(); 
					}
					break;

				default :
					break loop7;
				}
			}

			match('\"'); 
			}

			state.type = _type;
			state.channel = _channel;
		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "LITERAL"

	// $ANTLR start "LETTER"
	public final void mLETTER() throws RecognitionException {
		try {
			// mylexer.g:49:17: ( 'a' .. 'z' | 'A' .. 'Z' | '_' )
			// mylexer.g:
			{
			if ( (input.LA(1) >= 'A' && input.LA(1) <= 'Z')||input.LA(1)=='_'||(input.LA(1) >= 'a' && input.LA(1) <= 'z') ) {
				input.consume();
			}
			else {
				MismatchedSetException mse = new MismatchedSetException(null,input);
				recover(mse);
				throw mse;
			}
			}

		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "LETTER"

	// $ANTLR start "DIGIT"
	public final void mDIGIT() throws RecognitionException {
		try {
			// mylexer.g:50:17: ( '0' .. '9' )
			// mylexer.g:
			{
			if ( (input.LA(1) >= '0' && input.LA(1) <= '9') ) {
				input.consume();
			}
			else {
				MismatchedSetException mse = new MismatchedSetException(null,input);
				recover(mse);
				throw mse;
			}
			}

		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "DIGIT"

	// $ANTLR start "FLOAT_NUM1"
	public final void mFLOAT_NUM1() throws RecognitionException {
		try {
			// mylexer.g:51:20: ( ( DIGIT )+ '.' ( DIGIT )* )
			// mylexer.g:51:22: ( DIGIT )+ '.' ( DIGIT )*
			{
			// mylexer.g:51:22: ( DIGIT )+
			int cnt8=0;
			loop8:
			while (true) {
				int alt8=2;
				int LA8_0 = input.LA(1);
				if ( ((LA8_0 >= '0' && LA8_0 <= '9')) ) {
					alt8=1;
				}

				switch (alt8) {
				case 1 :
					// mylexer.g:
					{
					if ( (input.LA(1) >= '0' && input.LA(1) <= '9') ) {
						input.consume();
					}
					else {
						MismatchedSetException mse = new MismatchedSetException(null,input);
						recover(mse);
						throw mse;
					}
					}
					break;

				default :
					if ( cnt8 >= 1 ) break loop8;
					EarlyExitException eee = new EarlyExitException(8, input);
					throw eee;
				}
				cnt8++;
			}

			match('.'); 
			// mylexer.g:51:33: ( DIGIT )*
			loop9:
			while (true) {
				int alt9=2;
				int LA9_0 = input.LA(1);
				if ( ((LA9_0 >= '0' && LA9_0 <= '9')) ) {
					alt9=1;
				}

				switch (alt9) {
				case 1 :
					// mylexer.g:
					{
					if ( (input.LA(1) >= '0' && input.LA(1) <= '9') ) {
						input.consume();
					}
					else {
						MismatchedSetException mse = new MismatchedSetException(null,input);
						recover(mse);
						throw mse;
					}
					}
					break;

				default :
					break loop9;
				}
			}

			}

		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "FLOAT_NUM1"

	// $ANTLR start "FLOAT_NUM2"
	public final void mFLOAT_NUM2() throws RecognitionException {
		try {
			// mylexer.g:52:20: ( '.' ( DIGIT )+ )
			// mylexer.g:52:22: '.' ( DIGIT )+
			{
			match('.'); 
			// mylexer.g:52:25: ( DIGIT )+
			int cnt10=0;
			loop10:
			while (true) {
				int alt10=2;
				int LA10_0 = input.LA(1);
				if ( ((LA10_0 >= '0' && LA10_0 <= '9')) ) {
					alt10=1;
				}

				switch (alt10) {
				case 1 :
					// mylexer.g:
					{
					if ( (input.LA(1) >= '0' && input.LA(1) <= '9') ) {
						input.consume();
					}
					else {
						MismatchedSetException mse = new MismatchedSetException(null,input);
						recover(mse);
						throw mse;
					}
					}
					break;

				default :
					if ( cnt10 >= 1 ) break loop10;
					EarlyExitException eee = new EarlyExitException(10, input);
					throw eee;
				}
				cnt10++;
			}

			}

		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "FLOAT_NUM2"

	// $ANTLR start "FLOAT_NUM3"
	public final void mFLOAT_NUM3() throws RecognitionException {
		try {
			// mylexer.g:53:20: ( ( DIGIT )+ )
			// mylexer.g:53:22: ( DIGIT )+
			{
			// mylexer.g:53:22: ( DIGIT )+
			int cnt11=0;
			loop11:
			while (true) {
				int alt11=2;
				int LA11_0 = input.LA(1);
				if ( ((LA11_0 >= '0' && LA11_0 <= '9')) ) {
					alt11=1;
				}

				switch (alt11) {
				case 1 :
					// mylexer.g:
					{
					if ( (input.LA(1) >= '0' && input.LA(1) <= '9') ) {
						input.consume();
					}
					else {
						MismatchedSetException mse = new MismatchedSetException(null,input);
						recover(mse);
						throw mse;
					}
					}
					break;

				default :
					if ( cnt11 >= 1 ) break loop11;
					EarlyExitException eee = new EarlyExitException(11, input);
					throw eee;
				}
				cnt11++;
			}

			}

		}
		finally {
			// do for sure before leaving
		}
	}
	// $ANTLR end "FLOAT_NUM3"

	@Override
	public void mTokens() throws RecognitionException {
		// mylexer.g:1:8: ( VOID_TYPE | INT_TYPE | CHAR_TYPE | FLOAT_TYPE | IF_ | ELSE_ | WHILE_ | RETURN_ | CONTINUE_ | BREAK_ | EQ_OP | LE_OP | GE_OP | NE_OP | LS_OP | GT_OP | ASSIGN | OPERATOR | SEMICOLON | COMA | BRACKLETS | WS | DEC_NUM | ID | FLOAT_NUM | COMMENT | LITERAL )
		int alt12=27;
		alt12 = dfa12.predict(input);
		switch (alt12) {
			case 1 :
				// mylexer.g:1:10: VOID_TYPE
				{
				mVOID_TYPE(); 

				}
				break;
			case 2 :
				// mylexer.g:1:20: INT_TYPE
				{
				mINT_TYPE(); 

				}
				break;
			case 3 :
				// mylexer.g:1:29: CHAR_TYPE
				{
				mCHAR_TYPE(); 

				}
				break;
			case 4 :
				// mylexer.g:1:39: FLOAT_TYPE
				{
				mFLOAT_TYPE(); 

				}
				break;
			case 5 :
				// mylexer.g:1:50: IF_
				{
				mIF_(); 

				}
				break;
			case 6 :
				// mylexer.g:1:54: ELSE_
				{
				mELSE_(); 

				}
				break;
			case 7 :
				// mylexer.g:1:60: WHILE_
				{
				mWHILE_(); 

				}
				break;
			case 8 :
				// mylexer.g:1:67: RETURN_
				{
				mRETURN_(); 

				}
				break;
			case 9 :
				// mylexer.g:1:75: CONTINUE_
				{
				mCONTINUE_(); 

				}
				break;
			case 10 :
				// mylexer.g:1:85: BREAK_
				{
				mBREAK_(); 

				}
				break;
			case 11 :
				// mylexer.g:1:92: EQ_OP
				{
				mEQ_OP(); 

				}
				break;
			case 12 :
				// mylexer.g:1:98: LE_OP
				{
				mLE_OP(); 

				}
				break;
			case 13 :
				// mylexer.g:1:104: GE_OP
				{
				mGE_OP(); 

				}
				break;
			case 14 :
				// mylexer.g:1:110: NE_OP
				{
				mNE_OP(); 

				}
				break;
			case 15 :
				// mylexer.g:1:116: LS_OP
				{
				mLS_OP(); 

				}
				break;
			case 16 :
				// mylexer.g:1:122: GT_OP
				{
				mGT_OP(); 

				}
				break;
			case 17 :
				// mylexer.g:1:128: ASSIGN
				{
				mASSIGN(); 

				}
				break;
			case 18 :
				// mylexer.g:1:135: OPERATOR
				{
				mOPERATOR(); 

				}
				break;
			case 19 :
				// mylexer.g:1:144: SEMICOLON
				{
				mSEMICOLON(); 

				}
				break;
			case 20 :
				// mylexer.g:1:154: COMA
				{
				mCOMA(); 

				}
				break;
			case 21 :
				// mylexer.g:1:159: BRACKLETS
				{
				mBRACKLETS(); 

				}
				break;
			case 22 :
				// mylexer.g:1:169: WS
				{
				mWS(); 

				}
				break;
			case 23 :
				// mylexer.g:1:172: DEC_NUM
				{
				mDEC_NUM(); 

				}
				break;
			case 24 :
				// mylexer.g:1:180: ID
				{
				mID(); 

				}
				break;
			case 25 :
				// mylexer.g:1:183: FLOAT_NUM
				{
				mFLOAT_NUM(); 

				}
				break;
			case 26 :
				// mylexer.g:1:193: COMMENT
				{
				mCOMMENT(); 

				}
				break;
			case 27 :
				// mylexer.g:1:201: LITERAL
				{
				mLITERAL(); 

				}
				break;

		}
	}


	protected DFA5 dfa5 = new DFA5(this);
	protected DFA12 dfa12 = new DFA12(this);
	static final String DFA5_eotS =
		"\1\uffff\1\4\3\uffff";
	static final String DFA5_eofS =
		"\5\uffff";
	static final String DFA5_minS =
		"\2\56\3\uffff";
	static final String DFA5_maxS =
		"\2\71\3\uffff";
	static final String DFA5_acceptS =
		"\2\uffff\1\2\1\1\1\3";
	static final String DFA5_specialS =
		"\5\uffff}>";
	static final String[] DFA5_transitionS = {
			"\1\2\1\uffff\12\1",
			"\1\3\1\uffff\12\1",
			"",
			"",
			""
	};

	static final short[] DFA5_eot = DFA.unpackEncodedString(DFA5_eotS);
	static final short[] DFA5_eof = DFA.unpackEncodedString(DFA5_eofS);
	static final char[] DFA5_min = DFA.unpackEncodedStringToUnsignedChars(DFA5_minS);
	static final char[] DFA5_max = DFA.unpackEncodedStringToUnsignedChars(DFA5_maxS);
	static final short[] DFA5_accept = DFA.unpackEncodedString(DFA5_acceptS);
	static final short[] DFA5_special = DFA.unpackEncodedString(DFA5_specialS);
	static final short[][] DFA5_transition;

	static {
		int numStates = DFA5_transitionS.length;
		DFA5_transition = new short[numStates][];
		for (int i=0; i<numStates; i++) {
			DFA5_transition[i] = DFA.unpackEncodedString(DFA5_transitionS[i]);
		}
	}

	protected class DFA5 extends DFA {

		public DFA5(BaseRecognizer recognizer) {
			this.recognizer = recognizer;
			this.decisionNumber = 5;
			this.eot = DFA5_eot;
			this.eof = DFA5_eof;
			this.min = DFA5_min;
			this.max = DFA5_max;
			this.accept = DFA5_accept;
			this.special = DFA5_special;
			this.transition = DFA5_transition;
		}
		@Override
		public String getDescription() {
			return "45:1: FLOAT_NUM : ( FLOAT_NUM1 | FLOAT_NUM2 | FLOAT_NUM3 );";
		}
	}

	static final String DFA12_eotS =
		"\1\uffff\10\24\1\43\1\45\1\47\1\uffff\1\26\4\uffff\2\51\4\uffff\2\24\1"+
		"\55\7\24\10\uffff\1\51\1\24\1\66\1\uffff\7\24\1\76\1\uffff\1\77\2\24\1"+
		"\102\3\24\2\uffff\1\24\1\107\1\uffff\1\110\1\24\1\112\1\24\2\uffff\1\114"+
		"\1\uffff\1\24\1\uffff\1\116\1\uffff";
	static final String DFA12_eofS =
		"\117\uffff";
	static final String DFA12_minS =
		"\1\11\1\157\1\146\1\150\2\154\1\150\1\145\1\162\3\75\1\uffff\1\52\4\uffff"+
		"\2\56\4\uffff\1\151\1\164\1\60\1\141\1\156\1\157\1\163\1\151\1\164\1\145"+
		"\10\uffff\1\56\1\144\1\60\1\uffff\1\162\1\164\1\141\1\145\1\154\1\165"+
		"\1\141\1\60\1\uffff\1\60\1\151\1\164\1\60\1\145\1\162\1\153\2\uffff\1"+
		"\156\1\60\1\uffff\1\60\1\156\1\60\1\165\2\uffff\1\60\1\uffff\1\145\1\uffff"+
		"\1\60\1\uffff";
	static final String DFA12_maxS =
		"\1\175\1\157\1\156\1\157\2\154\1\150\1\145\1\162\3\75\1\uffff\1\52\4\uffff"+
		"\2\71\4\uffff\1\151\1\164\1\172\1\141\1\156\1\157\1\163\1\151\1\164\1"+
		"\145\10\uffff\1\71\1\144\1\172\1\uffff\1\162\1\164\1\141\1\145\1\154\1"+
		"\165\1\141\1\172\1\uffff\1\172\1\151\1\164\1\172\1\145\1\162\1\153\2\uffff"+
		"\1\156\1\172\1\uffff\1\172\1\156\1\172\1\165\2\uffff\1\172\1\uffff\1\145"+
		"\1\uffff\1\172\1\uffff";
	static final String DFA12_acceptS =
		"\14\uffff\1\16\1\uffff\1\23\1\24\1\25\1\26\2\uffff\1\30\1\31\1\22\1\33"+
		"\12\uffff\1\13\1\21\1\14\1\17\1\15\1\20\1\32\1\27\3\uffff\1\5\10\uffff"+
		"\1\2\7\uffff\1\1\1\3\2\uffff\1\6\4\uffff\1\4\1\7\1\uffff\1\12\1\uffff"+
		"\1\10\1\uffff\1\11";
	static final String DFA12_specialS =
		"\117\uffff}>";
	static final String[] DFA12_transitionS = {
			"\2\21\2\uffff\1\21\22\uffff\1\21\1\14\1\27\5\uffff\2\20\2\26\1\17\1\26"+
			"\1\25\1\15\1\22\11\23\1\uffff\1\16\1\12\1\11\1\13\2\uffff\32\24\1\20"+
			"\1\uffff\1\20\1\uffff\1\24\1\uffff\1\24\1\10\1\3\1\24\1\5\1\4\2\24\1"+
			"\2\10\24\1\7\3\24\1\1\1\6\3\24\1\20\1\uffff\1\20",
			"\1\30",
			"\1\32\7\uffff\1\31",
			"\1\33\6\uffff\1\34",
			"\1\35",
			"\1\36",
			"\1\37",
			"\1\40",
			"\1\41",
			"\1\42",
			"\1\44",
			"\1\46",
			"",
			"\1\50",
			"",
			"",
			"",
			"",
			"\1\25\1\uffff\12\25",
			"\1\25\1\uffff\12\52",
			"",
			"",
			"",
			"",
			"\1\53",
			"\1\54",
			"\12\24\7\uffff\32\24\4\uffff\1\24\1\uffff\32\24",
			"\1\56",
			"\1\57",
			"\1\60",
			"\1\61",
			"\1\62",
			"\1\63",
			"\1\64",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"",
			"\1\25\1\uffff\12\52",
			"\1\65",
			"\12\24\7\uffff\32\24\4\uffff\1\24\1\uffff\32\24",
			"",
			"\1\67",
			"\1\70",
			"\1\71",
			"\1\72",
			"\1\73",
			"\1\74",
			"\1\75",
			"\12\24\7\uffff\32\24\4\uffff\1\24\1\uffff\32\24",
			"",
			"\12\24\7\uffff\32\24\4\uffff\1\24\1\uffff\32\24",
			"\1\100",
			"\1\101",
			"\12\24\7\uffff\32\24\4\uffff\1\24\1\uffff\32\24",
			"\1\103",
			"\1\104",
			"\1\105",
			"",
			"",
			"\1\106",
			"\12\24\7\uffff\32\24\4\uffff\1\24\1\uffff\32\24",
			"",
			"\12\24\7\uffff\32\24\4\uffff\1\24\1\uffff\32\24",
			"\1\111",
			"\12\24\7\uffff\32\24\4\uffff\1\24\1\uffff\32\24",
			"\1\113",
			"",
			"",
			"\12\24\7\uffff\32\24\4\uffff\1\24\1\uffff\32\24",
			"",
			"\1\115",
			"",
			"\12\24\7\uffff\32\24\4\uffff\1\24\1\uffff\32\24",
			""
	};

	static final short[] DFA12_eot = DFA.unpackEncodedString(DFA12_eotS);
	static final short[] DFA12_eof = DFA.unpackEncodedString(DFA12_eofS);
	static final char[] DFA12_min = DFA.unpackEncodedStringToUnsignedChars(DFA12_minS);
	static final char[] DFA12_max = DFA.unpackEncodedStringToUnsignedChars(DFA12_maxS);
	static final short[] DFA12_accept = DFA.unpackEncodedString(DFA12_acceptS);
	static final short[] DFA12_special = DFA.unpackEncodedString(DFA12_specialS);
	static final short[][] DFA12_transition;

	static {
		int numStates = DFA12_transitionS.length;
		DFA12_transition = new short[numStates][];
		for (int i=0; i<numStates; i++) {
			DFA12_transition[i] = DFA.unpackEncodedString(DFA12_transitionS[i]);
		}
	}

	protected class DFA12 extends DFA {

		public DFA12(BaseRecognizer recognizer) {
			this.recognizer = recognizer;
			this.decisionNumber = 12;
			this.eot = DFA12_eot;
			this.eof = DFA12_eof;
			this.min = DFA12_min;
			this.max = DFA12_max;
			this.accept = DFA12_accept;
			this.special = DFA12_special;
			this.transition = DFA12_transition;
		}
		@Override
		public String getDescription() {
			return "1:1: Tokens : ( VOID_TYPE | INT_TYPE | CHAR_TYPE | FLOAT_TYPE | IF_ | ELSE_ | WHILE_ | RETURN_ | CONTINUE_ | BREAK_ | EQ_OP | LE_OP | GE_OP | NE_OP | LS_OP | GT_OP | ASSIGN | OPERATOR | SEMICOLON | COMA | BRACKLETS | WS | DEC_NUM | ID | FLOAT_NUM | COMMENT | LITERAL );";
		}
	}

}
