package main

import (
	"errors"
)

func IsLowPriority(temp Node) bool {
	return temp.character == '+' || temp.character == '-'
}

func Combinate(lhs, rhs float64, operation rune) (Node, error) {
	switch operation {
	case '+':
		return Node{lhs + rhs, '0'}, nil
	case '-':
		return Node{lhs - rhs, '0'}, nil
	case '*':
		return Node{lhs * rhs, '0'}, nil
	case '/':
		if rhs == 0 {
			return Node{}, errors.New("error: divide by zero")
		}
		return Node{lhs / rhs, '0'}, nil
	default:
		panic("Unknown operation")
	}
}

func CalculateExpr(i *int, parsedExpr []Node) (float64, error) {
	var stack []Node
	for ; *i < len(parsedExpr); *i++ {
		if parsedExpr[*i].character == ')' {
			break
		}
		if IsOperation(parsedExpr[*i].character) {
			stack = append(stack, parsedExpr[*i])
			continue
		}
		temp := parsedExpr[*i]
		if parsedExpr[*i].character == '(' {
			*i++
			value, err := CalculateExpr(i, parsedExpr)
			if err != nil {
				return 0, err
			}
			temp = Node{value, '0'}
		}
		last := len(stack) - 1
		if len(stack) == 0 {
			stack = append(stack, temp)
		} else if IsLowPriority(stack[last]) {
			if stack[last].character == '-' {
				stack = stack[:last]
				stack = append(stack, Node{0, '+'})
				temp.value = -temp.value
			}
			stack = append(stack, temp)
		} else {
			operation := stack[last]
			stack = stack[:last]
			last--
			value := stack[last]
			stack = stack[:last]
			combinated, err := Combinate(value.value, temp.value, operation.character)
			if err != nil {
				return 0, err
			}
			stack = append(stack, combinated)
		}
	}
	size := len(stack) - 1
	for size > 1 {
		value2 := stack[size]
		size--
		operation := stack[size]
		size--
		value1 := stack[size]
		stack = stack[:size]
		combinated, err := Combinate(value1.value, value2.value, operation.character)
		if err != nil {
			return 0, err
		}
		stack = append(stack, combinated)
	}
	return stack[size].value, nil
}
