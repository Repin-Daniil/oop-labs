#include <symcpp/symcpp.h>

#include <unordered_map>

#include <array>
#include <string>
#include <symcpp/utils/log.hpp>

using namespace symcpp;

int main() {
  symcpp::utils::log::SetLogTimeEnabled(false);
  symcpp::utils::log::SetLogLocationEnabled(false);

  Symbol x("x");

  std::array<Expression, 8> in;
  in[0] = Cos(x) * Sin(x);
  in[1] = Diff(in[0], x);
  LOG_INFO() << in[0];

  auto root = in[0].Release();

  LOG_INFO() << "Multiplication is operand = " << root->IsA(constants::Expressions::OPERAND);
  LOG_INFO() << "Multiplication is unary =" << root->IsA(constants::Expressions::UNARY_OPERATION);
  LOG_INFO() << "Multiplication is binary = " << root->IsA(constants::Expressions::BINARY_OPERATION);
  LOG_INFO() << "Multiplication is multiplication = " << root->IsA(constants::Expressions::MULTIPLICATION);

  auto root_ptr = dynamic_cast<math::BinaryOperation*>(root.get());

  if (root_ptr) {
    auto unary_ptr = root_ptr->ReleaseLeftArgument();
    LOG_INFO() << "Cos is unary = " << unary_ptr->IsA(constants::Expressions::UNARY_OPERATION);
    LOG_INFO() << "Cos is unary = " << unary_ptr->IsA(constants::Expressions::COS);
    auto raw_unary_ptr = dynamic_cast<math::UnaryOperation*>(unary_ptr.get());
    // auto raw_unary_ptr = static_cast<math::UnaryMinus*>(unary_ptr.get());

    if (raw_unary_ptr) {
      auto var_ptr = raw_unary_ptr->ReleaseArgument();
      LOG_INFO() << "X is variable = " << var_ptr->IsA(constants::Expressions::VARIABLE);
      LOG_INFO() << "X is operand = " << var_ptr->IsA(constants::Expressions::OPERAND);
    }
  } else {
    LOG_ERROR() << "Root is not binary";
  }

  return EXIT_SUCCESS;
}
