#pragma once

#ifndef CALCULATOR
#define CALCULATOR

#include "execbase.h"

struct calculator : public grammar<calculator>
{
	calculator(stack<double>& eval_, symtab_t& vars_,
		list<Execbase>& oper_, list<Execbase> ::iterator& PCiter_, stack<VarCHRM*>& LastVar_, stack<VarCHRM*>& LastVas_)
		: eval(eval_), vars(vars_), oper(oper_), PCiter(PCiter_), LastVar(LastVar_), LastVas(LastVas_) {}

	template <typename ScannerT>
	struct definition
	{
		definition(calculator const& self)
		{
			self.keywords.add("if") ("else") ("endif") ("var")
				("while") ("endwhile")
				("sin") ("cos") ("exp") ("log10") ("log") ("estar")
				("rhoa") ("patmos") ("max") ("min") ("spec_humid");

			routines =
				((chseq<>("exp(") >> expression >> ')')[make_op1(ExpC<const double>(), self.eval, self.oper)])
				| ((chseq<>("log(") >> expression >> ')')[make_op1(LogC<const double>(), self.eval, self.oper)])
				| ((chseq<>("max(") >> expression >> *(ch_p(',')) >> expression >> ')')[make_op2(MaxC<const double>(), self.eval, self.oper)])
				| ((chseq<>("min(") >> expression >> *(ch_p(',')) >> expression >> ')')[make_op2(MinC<const double>(), self.eval, self.oper)])
				//                |   ((chseq<>("log10(") >> expression >> ')')[make_op1(Log10C<const double>(), self.eval, self.oper)]) //
				;
			hydrology =
				((chseq<>("estar(") >> expression >> ')')[make_op1(estarC<const double>(), self.eval, self.oper)])
				//                |   ((chseq<>("patmos(") >> expression >> ')')  [make_op1(patmosC<const double>(), self.eval, self.oper)]) //
				//                |   ((chseq<>("spec_humid(") >> expression >> *(ch_p(',')) >> expression >> ')')  [make_op2(spec_humidC<const double>(), self.eval, self.oper)]) //
				//                |   ((chseq<>("rhoa(") >> expression >> *(ch_p(',')) >> expression >> *(ch_p(',')) >> expression >> ')')  [execRHOa(self.eval, self.oper)]) //
				;
			trignometry =
				((chseq<>("sin(") >> expression >> ')')[make_op1(SineC<const double>(), self.eval, self.oper)])
				| ((chseq<>("cos(") >> expression >> ')')[make_op1(CosC<const double>(), self.eval, self.oper)])
				//                |   ((chseq<>("tan(") >> expression >> ')')  [make_op1(TanC<const double>(), self.eval, self.oper)])
				;
			factor =
				routines
				| hydrology
				| trignometry
				| real_p[execPush(self.eval, self.oper)]
				| '(' >> logical >> ')'
				| ('-' >> factor)[execNegate(self.eval, self.oper)]
				| ('!' >> factor)[execInvert(self.eval, self.oper)]

				| (identifier[execVget(self.vars, self.eval, self.oper, self.LastVar)]
					>> *('[' >> factor >> ']')[execVindexVget(self.eval, self.oper, self.LastVar)])
				;

			term2 =
				factor
				>> *(('^' >> factor)[make_op2(PowerC<const double>(), self.eval, self.oper)]
					)
				;

			term1 =
				term2
				>> *(('*' >> term2)[make_op2(multiplies<const double>(), self.eval, self.oper)]
					| ('/' >> term2)[make_op2(divides<const double>(), self.eval, self.oper)]
					| ('%' >> term2)[make_op2(::modulus<const double>(), self.eval, self.oper)]
					)
				;

			expression =
				term1
				>> *(('+' >> term1)[make_op2(plus<const double>(), self.eval, self.oper)]
					| ('-' >> term1)[make_op2(minus<const double>(), self.eval, self.oper)]
					)
				;

			logical2 =
				expression
				>> *((">" >> expression)[make_op2B(L_GT<double>(), self.eval, self.oper)]
					| (strlit<>(">=") >> expression)[make_op2B(L_GE<double>(), self.eval, self.oper)]
					| (strlit<>("<=") >> expression)[make_op2B(L_LE<double>(), self.eval, self.oper)]
					| ('<' >> expression)[make_op2B(L_LT<double>(), self.eval, self.oper)]
					| (strlit<>("==") >> expression)[make_op2B(L_EQ<double>(), self.eval, self.oper)]
					| (strlit<>("!=") >> expression)[make_op2B(L_NE<double>(), self.eval, self.oper)]
					)
				;

			logical1 =
				logical2
				>> *((strlit<>("&&") >> logical2)[make_op2BB(L_and<bool>(), self.eval, self.oper)]
					| (strlit<>("AND") >> logical2)[make_op2BB(L_and<bool>(), self.eval, self.oper)]
					)
				;

			logical =
				logical1
				>> *((strlit<>("||") >> logical1)[make_op2BB(L_or<bool>(), self.eval, self.oper)]
					| (strlit<>("OR") >> logical1)[make_op2BB(L_or<bool>(), self.eval, self.oper)]
					)
				;

			IF =
				(((strlit<>("if")
					>> *(blank_p)
					>> "(")
					>> logical >> ')')[execIf(self.eval, self.oper, self.PCiter, self.PCiterIF)])
				>> (*(statement))
				>> (*(strlit<>("else"))[execElse(self.eval, self.oper, self.PCiter, self.PCiterIF)])
				>> (*(statement))
				>> ((strlit<>("endif"))[execEndif(self.eval, self.oper, self.PCiter, self.PCiterIF)])
				;

			WHILE =
				(((strlit<>("while")[execWhile(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
					>> *(blank_p)
					>> "(")
					>> logical >> ')')[execWhile2(self.eval, self.oper, self.PCiter, self.PCiterWHILE)]
				>> (*(statement))
				>> ((strlit<>("endwhile"))[execEndwhile(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
				;

			FOR =
				(((strlit<>("for")
					>> *(blank_p)
					>> "("
					>> (assignment >> *(',' >> assignment) >> ';')))[execFor(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
				>> ((logical >> ';')[execForC(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
				>> ((assignment >> *(',' >> assignment) >> ')')[execForI(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
				>> (*(statement))
				>> ((strlit<>("endfor"))[execEndFor(self.eval, self.oper, self.PCiter, self.PCiterWHILE)])
				;

			identifier =
				lexeme_d[
					(alpha_p >> *(alnum_p | ch_p('_') | '@' | '#'))
						- (self.keywords >> anychar_p - (alnum_p | ch_p('_') | '@' | '#'))

				]
				;

					assignment =
						IF
						| (identifier >> *('[' >> expression >> ']') >> '='
							)[execVset(self.vars, self.eval, self.oper, self.LastVas)][execVindex(self.eval, self.oper, self.LastVas)]
						>> expression[execVassign(self.eval, self.oper, self.LastVas)]
						;

					var_decl =
						identifier[execVadd(self.vars, self.eval, self.oper, self.LastVar)]
						>> *('[' >> factor >> ']')[execVaddN(self.eval, self.oper, self.LastVar)]
						;

					declaration =
						"var" >> var_decl >> *(',' >> var_decl)
						;

					comment =
						lexeme_d[
							("//" >> *(anychar_p - '\n'))
								| ("rem " >> *(anychar_p - '\n'))
								| ("/*" >> *(anychar_p - "*/") >> "*/")
						]
						;

							statement =
								(declaration
									| assignment
									| IF
									| WHILE
									| FOR
									| comment
									| end_p
									| eol_p
									| ch_p(';')
									| blank_p
									)
								;
		}
		rule<ScannerT>      statement, declaration, var_decl, identifier,
			assignment, expression, term, term1, term2,
			factor, routines, hydrology, trignometry, logical, logical1, logical2,
			comment, IF, WHILE, FOR;

		rule<ScannerT> const&
			start() const { return statement; }
	};

public:
	symtab_t& vars;
	symbols<char*> keywords;

	stack<double>& eval;
	stack<VarCHRM*>& LastVar;
	stack<VarCHRM*>& LastVas;

	list<Execbase>& oper;
	list<Execbase> ::iterator& PCiter;

	mutable stack<list<Execbase> ::iterator> PCiterIF;
	mutable stack<list<Execbase> ::iterator> PCiterWHILE;
	mutable stack<list<Execbase> ::iterator> PCiterFOR;
};

#endif // !CALCULATOR
