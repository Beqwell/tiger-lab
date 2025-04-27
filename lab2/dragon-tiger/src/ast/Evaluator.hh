#pragma once
#include "nodes.hh"
#include "../utils/errors.hh"

namespace ast {
namespace eval {

// Visitor для вычисления целочисленных выражений.
// Наследуется от ConstASTIntVisitor, у которого все методы
// возвращают int32_t.
class Evaluator : public types::ConstASTIntVisitor {
public:
  // Запустить вычисление от корня AST:
  int32_t evaluate(types::Expr *root);

  // Реализуем только четыре «разумные» операции:
  int32_t visit(const types::IntegerLiteral &lit) override;
  int32_t visit(const types::BinaryOperator  &bin) override;
  int32_t visit(const types::Sequence        &seq) override;
  int32_t visit(const types::IfThenElse      &ite) override;

  // Все остальные узлы — фатальная ошибка:
  int32_t visit(const types::StringLiteral   &n) override {
    utils::error(n.loc, "cannot evaluate string literal");
  }
  int32_t visit(const types::Let             &n) override {
    utils::error(n.loc, "cannot evaluate let-expression");
  }
  int32_t visit(const types::Identifier      &n) override {
    utils::error(n.loc, "cannot evaluate identifier");
  }
  int32_t visit(const types::VarDecl         &n) override {
    utils::error(n.loc, "cannot evaluate var-declaration");
  }
  int32_t visit(const types::FunDecl         &n) override {
    utils::error(n.loc, "cannot evaluate function-declaration");
  }
  int32_t visit(const types::FunCall         &n) override {
    utils::error(n.loc, "cannot evaluate function-call");
  }
  int32_t visit(const types::WhileLoop       &n) override {
    utils::error(n.loc, "cannot evaluate while-loop");
  }
  int32_t visit(const types::ForLoop         &n) override {
    utils::error(n.loc, "cannot evaluate for-loop");
  }
  int32_t visit(const types::Break           &n) override {
    utils::error(n.loc, "cannot evaluate break");
  }
  int32_t visit(const types::Assign          &n) override {
    utils::error(n.loc, "cannot evaluate assignment");
  }
};

} // namespace eval
} // namespace ast
