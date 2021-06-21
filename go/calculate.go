package main

import "fmt"

func IsLowPriority(temp Node) bool {
	return temp.character == '+' || temp.character == '-'
}

func Combinate(lhs, rhs float64, operation rune) Node {
	switch operation {
	case '+':
		return Node{lhs + rhs, '0'}
	case '-':
		return Node{lhs - rhs, '0'}
	case '*':
		return Node{lhs * rhs, '0'}
	case '/':
		if rhs == 0 {
			return Node{0, 'e'}
		}
		return Node{lhs / rhs, '0'}
	default:
		panic("Unknown operation")
	}
}

func CalculateExpr(i *int, parsedExpr []Node) float64 {
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
			temp = Node{CalculateExpr(i, parsedExpr), '0'}
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
			combinated := Combinate(value.value, temp.value, operation.character)
			if combinated.character == 'e' {
				fmt.Print("error: divide by zero ")
				return 0
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
		combinated := Combinate(value1.value, value2.value, operation.character)
		if combinated.character == 'e' {
			fmt.Print("error: divide by zero ")
			return 0
		}
		stack = append(stack, combinated)
	}
	return stack[size].value
}
