#include "Evaluator.hh"

namespace ast {
namespace eval {

int32_t Evaluator::evaluate(types::Expr *root) {
  // accept возвращает int32_t через ConstASTIntVisitor
  return root->accept(*this);
}

int32_t Evaluator::visit(const types::IntegerLiteral &lit) {
  // в вашем nodes.hh поле называется `value`
  return lit.value;
}

int32_t Evaluator::visit(const types::BinaryOperator &bin) {
  // пускаем сначала левый, потом правый
  int32_t lhs = bin.get_left().accept(*this);
  int32_t rhs = bin.get_right().accept(*this);
  switch (bin.op) {
    case types::o_plus:   return lhs + rhs;
    case types::o_minus:  return lhs - rhs;
    case types::o_times:  return lhs * rhs;
    case types::o_divide:
      if (rhs == 0) utils::error(bin.loc, "division by zero");
      return lhs / rhs;
    case types::o_eq:     return lhs == rhs;
    case types::o_neq:    return lhs != rhs;
    case types::o_lt:     return lhs < rhs;
    case types::o_le:     return lhs <= rhs;
    case types::o_gt:     return lhs > rhs;
    case types::o_ge:     return lhs >= rhs;
  }
  utils::error(bin.loc, "unsupported binary operator");
}

int32_t Evaluator::visit(const types::Sequence &seq) {
  const auto &v = seq.get_exprs();
  if (v.empty()) utils::error(seq.loc, "empty sequence");
  int32_t last = 0;
  for (auto *e : v) last = e->accept(*this);
  return last;
}

int32_t Evaluator::visit(const types::IfThenElse &ite) {
  // ленивая оценка
  if (ite.get_condition().accept(*this))
    return ite.get_then_part().accept(*this);
  else
    return ite.get_else_part().accept(*this);
}

} // namespace eval
} // namespace ast
