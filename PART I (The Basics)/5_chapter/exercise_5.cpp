/*
[5]
Write a grammar for bitwise logical expressions. A bitwise logical expression is much like
an arithmetic expression except that the operators are ! (not), ˜ (complement), & (and), | (or),
and ˆ (exclusive or). Each operator does its operation to each bit of its integer operands (see
PPP2.§25.5). ! and ˜ are prefix unary operators. A ˆ binds tighter than a | (just as ∗ binds
tighter than +) so that x|yˆz means x|(yˆz) rather than (x|y)ˆz. The & operator binds tighter than
ˆ so that xˆy&z means xˆ(y&z).
*/

/*
Expression:
	Term
	Expression '!' Term
	Expression '~' Term
	Expression '|' Term
Term:
	Element
	Term '^' Element
Element:
	Primary
	Element '&' Primary
Primary:
	Operand
	'(' Expression ')'
Operand:
	Integer number
*/