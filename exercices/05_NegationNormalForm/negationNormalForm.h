#pragma once

#include <iostream>
#include <string>

#include <lib/Node.h>

std::string negation_normal_form(std::string str);

template <class T>
std::unique_ptr<Node<T>> makeNegationNormalForm(Node<T>& root);

template <class T>
std::unique_ptr<Node<T>> loopNegationNormalForm(Node<T>& root);
